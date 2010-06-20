/*****************************************************************************/
/**
 *  @file   RayCastingRenderer.cpp
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright 2007 Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/*****************************************************************************/
#include "RayCastingRenderer.h"
#include "CommandName.h"
#include "ObjectInformation.h"
#include "FileChecker.h"
#include <kvs/IgnoreUnusedVariable>
#include <kvs/File>
#include <kvs/KVSMLObjectStructuredVolume>
#include <kvs/AVSField>
#include <kvs/PipelineModule>
#include <kvs/VisualizationPipeline>
#include <kvs/RayCastingRenderer>
#include <kvs/Bounds>
#include <kvs/PaintEventListener>
#include <kvs/MouseDoubleClickEventListener>
#include <kvs/KeyPressEventListener>
#include <kvs/Key>
#include <kvs/glut/Application>
#include <kvs/glut/Screen>
#include <kvs/glut/LegendBar>
#include <kvs/glut/OrientationAxis>
#include <kvs/glut/Label>
#include <kvs/glut/TransferFunctionEditor>
#if defined( KVS_SUPPORT_GLEW )
#include <kvs/glew/RayCastingRenderer>
#endif

namespace { bool HasBounds = false; }
namespace { bool Shown = false; }


namespace kvsview
{

namespace RayCastingRenderer
{

/*===========================================================================*/
/**
 *  @brief  Set shader and transfer function to ray casting renderer.
 *  @param  arg [in] command line argument
 *  @param  renderer [in] renderer module
 */
/*===========================================================================*/
template <typename Renderer>
const void Initialize(
    const kvsview::RayCastingRenderer::Argument& arg,
    kvs::PipelineModule& renderer )
{
    // Transfer function.
    const kvs::TransferFunction& function = arg.transferFunction();
    renderer.get<Renderer>()->setTransferFunction( function );

    // Shading on/off.
    const bool noshading = arg.noShading();
    if ( noshading ) renderer.get<Renderer>()->disableShading();
    else renderer.get<Renderer>()->enableShading();

    // Shader type.
    const float ka = arg.ambient();
    const float kd = arg.diffuse();
    const float ks = arg.specular();
    const float n = arg.shininess();
    const int shader = arg.shader();
    switch ( shader )
    {
    case 0: // Lamber shading
    {
        renderer.get<Renderer>()->setShader( kvs::Shader::Lambert( ka, kd ) );
        break;
    }
    case 1: // Phong shading
    {
        renderer.get<Renderer>()->setShader( kvs::Shader::Phong( ka, kd, ks, n ) );
        break;
    }
    case 2: // Blinn-phong shading
    {
        renderer.get<Renderer>()->setShader( kvs::Shader::BlinnPhong( ka, kd, ks, n ) );
        break;
    }
    default: break;
    }
}

/*===========================================================================*/
/**
 *  @brief  Transfer function editor class.
 */
/*===========================================================================*/
class TransferFunctionEditor : public kvs::glut::TransferFunctionEditor
{
    bool m_no_gpu; ///!< flag to check if the GPU shader is enabled
    kvs::glut::LegendBar* m_legend_bar; ///!< pointer to the legend bar

public:

    TransferFunctionEditor( kvs::glut::Screen* screen, const bool no_gpu ):
        kvs::glut::TransferFunctionEditor( screen ),
        m_no_gpu( no_gpu ) {}

    void apply( void )
    {
        const kvs::RendererBase* base = screen()->rendererManager()->renderer();
        if ( m_no_gpu )
        {
            kvs::RayCastingRenderer* renderer = (kvs::RayCastingRenderer*)base;
            renderer->setTransferFunction( transferFunction() );
        }
        else
        {
            kvs::glew::RayCastingRenderer* renderer = (kvs::glew::RayCastingRenderer*)base;
            renderer->setTransferFunction( transferFunction() );
        }

        m_legend_bar->setColorMap( transferFunction().colorMap() );

        screen()->redraw();
    }

    void attachLegendBar( kvs::glut::LegendBar* legend_bar )
    {
        m_legend_bar = legend_bar;
    }
};

/*===========================================================================*/
/**
 *  @brief  Key press event.
 */
/*===========================================================================*/
class KeyPressEvent : public kvs::KeyPressEventListener
{
    void update( kvs::KeyEvent* event )
    {
        switch ( event->key() )
        {
        case kvs::Key::o: screen()->controlTarget() = kvs::ScreenBase::TargetObject; break;
        case kvs::Key::l: screen()->controlTarget() = kvs::ScreenBase::TargetLight; break;
        case kvs::Key::c: screen()->controlTarget() = kvs::ScreenBase::TargetCamera; break;
        default: break;
        }
    }
};

/*===========================================================================*/
/**
 *  @brief  Mouse double-click event.
 */
/*===========================================================================*/
class MouseDoubleClickEvent : public kvs::MouseDoubleClickEventListener
{
    TransferFunctionEditor* m_editor; ///!< pointer to the transfer function

public:

    void update( kvs::MouseEvent* event )
    {
        if ( ::Shown ) m_editor->hide();
        else m_editor->showWindow();

        ::Shown = !::Shown;
    }

    void attachTransferFunctionEditor( TransferFunctionEditor* editor )
    {
        m_editor = editor;
    }
};

/*===========================================================================*/
/**
 *  @brief  Label class to show the frame rate.
 */
/*===========================================================================*/
class Label : public kvs::glut::Label
{
public:

    Label( kvs::ScreenBase* screen ):
        kvs::glut::Label( screen )
    {
        setMargin( 10 );
    }

    void screenUpdated( void )
    {
        const int id = ::HasBounds ? 2 : 1;
        const kvs::RendererBase* renderer = screen()->rendererManager()->renderer( id );

        std::stringstream fps;
        fps << std::setprecision(4) << renderer->timer().fps();
        setText( std::string( "fps: " + fps.str() ).c_str() );
    }
};

/*===========================================================================*/
/**
 *  @brief  Legend bar class.
 */
/*===========================================================================*/
class LegendBar : public kvs::glut::LegendBar
{
public:

    LegendBar( kvs::ScreenBase* screen ):
        kvs::glut::LegendBar( screen )
    {
        setWidth( 200 );
        setHeight( 50 );
    }

    void screenResized( void )
    {
        setX( screen()->width() - width() );
        setY( screen()->height() - height() );
    }
};

/*===========================================================================*/
/**
 *  @brief  Orientation axis class.
 */
/*===========================================================================*/
class OrientationAxis : public kvs::glut::OrientationAxis
{
public:

    OrientationAxis( kvs::ScreenBase* screen ):
        kvs::glut::OrientationAxis( screen )
    {
        setMargin( 10 );
        setSize( 90 );
        setBoxType( kvs::glut::OrientationAxis::SolidBox );
        enableAntiAliasing();
    }

    void screenResized( void )
    {
        setY( screen()->height() - height() );
    }
};

/*===========================================================================*/
/**
 *  @brief  Constructs a new Argument class for a point renderer.
 *  @param  argc [in] argument count
 *  @param  argv [in] argument values
 */
/*===========================================================================*/
Argument::Argument( int argc, char** argv ):
    kvsview::Argument::Common( argc, argv, "RayCastingRenderer")
{
    // Parameters for the RayCastingRenderer class.
    add_option( kvsview::RayCastingRenderer::CommandName, kvsview::RayCastingRenderer::Description, 0 );
    add_option( "t", "Transfer function file. (optional: <filename>)", 1, false );
    add_option( "noshading", "Disable shading. (optional)", 0, false );
    add_option( "nolod", "Disable Level-of-Detail control. (optional)", 0, false );
    add_option( "nogpu", "Disable GPU rendering. (optional)", 0, false );
    add_option( "ka", "Coefficient of the ambient color. (default: lambert=0.4, phong=0.3)", 1, false );
    add_option( "kd", "Coefficient of the diffuse color. (default: lambert=0.6, phong=0.5)", 1, false );
    add_option( "ks", "Coefficient of the specular color. (default: 0.8)", 1, false );
    add_option( "n", "Shininess. (default: 100.0)", 1, false );
    add_option( "shader", "Shader type. (default: 0)\n"
                "\t      0 = Lambert shading\n"
                "\t      1 = Phong shading\n"
                "\t      2 = Blinn-Phong shading", 1, false );
}

/*===========================================================================*/
/**
 *  @brief  Returns the shader number.
 *  @return shader number
 */
/*===========================================================================*/
const int Argument::shader( void ) const
{
    const int default_value = 0;

    if ( this->hasOption("shader") ) return( this->optionValue<int>("shader") );
    else return( default_value );
}

/*===========================================================================*/
/**
 *  @brief  Check whether the "noshading" option is specified or not.
 *  @return true, if the "noshading" option is specified
 */
/*===========================================================================*/
const bool Argument::noShading( void ) const
{
    return( this->hasOption("noshading") );
}

/*===========================================================================*/
/**
 *  @brief  Check whether the "nolod" option is specified or not.
 *  @return true, if the "nolod" option is specified
 */
/*===========================================================================*/
const bool Argument::noLOD( void ) const
{
    return( this->hasOption("nolod") );
}

/*===========================================================================*/
/**
 *  @brief  Check whether the "nogpu" option is specified or not.
 *  @return true, if the "nogpu" option is specified
 */
/*===========================================================================*/
const bool Argument::noGPU( void ) const
{
#if defined( KVS_SUPPORT_GLEW )
    return( this->hasOption("nogpu") );
#else
    return( true );
#endif
}

/*===========================================================================*/
/**
 *  @brief  Returns the coefficient for ambient color.
 *  @return coefficient for ambient color
 */
/*===========================================================================*/
const float Argument::ambient( void ) const
{
    const float default_value = this->shader() == 0 ? 0.4f : 0.3f;

    if ( this->hasOption("ka") ) return( this->optionValue<float>("ka") );
    else return( default_value );
}

/*===========================================================================*/
/**
 *  @brief  Returns the coefficient for diffuse color.
 *  @return coefficient for diffuse color
 */
/*===========================================================================*/
const float Argument::diffuse( void ) const
{
    const float default_value = this->shader() == 0 ? 0.6f : 0.5f;

    if ( this->hasOption("kd") ) return( this->optionValue<float>("kd") );
    else return( default_value );
}

/*===========================================================================*/
/**
 *  @brief  Returns the coefficient for specular color.
 *  @return coefficient for specular color
 */
/*===========================================================================*/
const float Argument::specular( void ) const
{
    const float default_value = 0.8f;

    if ( this->hasOption("ks") ) return( this->optionValue<float>("ks") );
    else return( default_value );
}

/*===========================================================================*/
/**
 *  @brief  Returns the coefficient for shininess.
 *  @return coefficient for shininess
 */
/*===========================================================================*/
const float Argument::shininess( void ) const
{
    const float default_value = 100.0f;

    if ( this->hasOption("n") ) return( this->optionValue<float>("n") );
    else return( default_value );
}

/*===========================================================================*/
/**
 *  @brief  Returns a transfer function.
 *  @return transfer function
 */
/*===========================================================================*/
const kvs::TransferFunction Argument::transferFunction( void ) const
{
    if ( this->hasOption("t") )
    {
        const std::string filename = this->optionValue<std::string>("t");
        return( kvs::TransferFunction( filename ) );
    }
    else
    {
        const size_t resolution = 256;
        return( kvs::TransferFunction( resolution ) );
    }
}

/*===========================================================================*/
/**
 *  @brief  Constructs a new Main class for a point renderer.
 *  @param  argc [in] argument count
 *  @param  argv [in] argument values
 */
/*===========================================================================*/
Main::Main( int argc, char** argv )
{
    m_argc = argc;
    m_argv = argv;
}

/*===========================================================================*/
/**
 *  @brief  Executes main process.
 */
/*===========================================================================*/
const bool Main::exec( void )
{
    kvs::glut::Application app( m_argc, m_argv );

    // Parse specified arguments.
    RayCastingRenderer::Argument arg( m_argc, m_argv );
    if( !arg.parse() ) return( false );

    // Create screen.
    kvs::glut::Screen screen( &app );

    RayCastingRenderer::KeyPressEvent key_press_event;
    RayCastingRenderer::MouseDoubleClickEvent mouse_double_click_event;

    screen.setSize( 512, 512 );
    screen.addKeyPressEvent( &key_press_event );
    screen.addMouseDoubleClickEvent( &mouse_double_click_event );
    screen.setTitle( kvsview::CommandName + " - " + kvsview::RayCastingRenderer::CommandName );

    // Check the input point data.
    m_input_name = arg.value<std::string>();
    if ( !( kvsview::FileChecker::ImportableStructuredVolume( m_input_name ) ||
            kvsview::FileChecker::ImportableUnstructuredVolume( m_input_name ) ) )
    {
        kvsMessageError("%s is not volume data.", m_input_name.c_str());
        return( false );
    }

    // Visualization pipeline.
    kvs::VisualizationPipeline pipe( m_input_name );
    pipe.import();

    // Verbose information.
    if ( arg.verboseMode() )
    {
        std::cout << "IMPORTED OBJECT" << std::endl;
        std::cout << kvsview::ObjectInformation( pipe.object() ) << std::endl;
        std::cout << std::endl;
    }

    // Label (fps).
    RayCastingRenderer::Label label( &screen );
    label.show();

    // Legend bar.
    RayCastingRenderer::LegendBar legend_bar( &screen );
    const double min_value = kvs::VolumeObjectBase::DownCast( pipe.object() )->minValue();
    const double max_value = kvs::VolumeObjectBase::DownCast( pipe.object() )->maxValue();
    legend_bar.setColorMap( arg.transferFunction().colorMap() );
    legend_bar.setRange( min_value, max_value );
    legend_bar.show();

    // Orientation axis.
    RayCastingRenderer::OrientationAxis orientation_axis( &screen );
    orientation_axis.show();

    // For bounding box.
    if ( arg.hasOption("bounds") )
    {
        ::HasBounds = true;

        kvs::LineObject* bounds = new kvs::Bounds( pipe.object() );

        bounds->setColor( kvs::RGBColor( 0, 0, 0 ) );
        if ( arg.hasOption("bounds_color") )
        {
            const kvs::UInt8 r( static_cast<kvs::UInt8>(arg.optionValue<int>("bounds_color",0)) );
            const kvs::UInt8 g( static_cast<kvs::UInt8>(arg.optionValue<int>("bounds_color",1)) );
            const kvs::UInt8 b( static_cast<kvs::UInt8>(arg.optionValue<int>("bounds_color",2)) );
            bounds->setColor( kvs::RGBColor( r, g, b ) );
        }

        kvs::VisualizationPipeline p( bounds );
        p.exec();
        p.renderer()->disableShading();

        screen.registerObject( &p );
    }

    // Set up a RayCastingRenderer class.
    if ( arg.noGPU() )
    {
        kvs::PipelineModule renderer( new kvs::RayCastingRenderer );
        RayCastingRenderer::Initialize<kvs::RayCastingRenderer>( arg, renderer );

        if ( !arg.noLOD() )
        {
            renderer.get<kvs::RayCastingRenderer>()->enableLODControl();
        }

        pipe.connect( renderer );
    }
#if defined( KVS_SUPPORT_GLEW )
    else
    {
        kvs::PipelineModule renderer( new kvs::glew::RayCastingRenderer );
        RayCastingRenderer::Initialize<kvs::glew::RayCastingRenderer>( arg, renderer );

        pipe.connect( renderer );
    }
#endif

    // Construct the visualization pipeline.
    if ( !pipe.exec() )
    {
        kvsMessageError("Cannot execute the visulization pipeline.");
        return( false );
    }
    screen.registerObject( &pipe );

    // Verbose information.
    if ( arg.verboseMode() )
    {
        std::cout << "RENDERERED OBJECT" << std::endl;
        std::cout << kvsview::ObjectInformation( pipe.object() ) << std::endl;
        std::cout << std::endl;
        std::cout << "VISUALIZATION PIPELINE" << std::endl;
        std::cout << pipe << std::endl;
    }

    // Apply the specified parameters to the global and the visualization pipeline.
    arg.applyTo( screen, pipe );
    arg.applyTo( screen );

    // Show the screen.
    screen.show();

    // Create transfer function editor.
    RayCastingRenderer::TransferFunctionEditor editor( &screen, arg.noGPU() );
    editor.setVolumeObject( kvs::VolumeObjectBase::DownCast( pipe.object() ) );
    editor.setTransferFunction( arg.transferFunction() );
    editor.attachLegendBar( &legend_bar );
    editor.show();
    editor.hide();
    ::Shown = false;

    // Attach the transfer function editor to the mouse double-click event.
    mouse_double_click_event.attachTransferFunctionEditor( &editor );

    return( app.run() );
}

} // end of namespace Default

} // end of namespace kvsview