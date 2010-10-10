/*****************************************************************************/
/**
 *  @file   Isosurface.cpp
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright (c) Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/*****************************************************************************/
#include "Isosurface.h"
#include <kvs/DebugNew>
#include <kvs/PipelineModule>
#include <kvs/VisualizationPipeline>
#include <kvs/Isosurface>
#include <kvs/Value>
#include <kvs/KeyPressEventListener>
#include <kvs/Key>
#include <kvs/glut/Screen>
#include <kvs/glut/Application>
#include <kvs/glut/LegendBar>
#include <kvs/glut/OrientationAxis>
#include "CommandName.h"
#include "ObjectInformation.h"
#include "FileChecker.h"
#include "Widget.h"


namespace kvsview
{

namespace Isosurface
{

/*===========================================================================*/
/**
 *  @brief  Isolevel slider class.
 */
/*===========================================================================*/
class IsolevelSlider : public kvs::glut::Slider
{
    const kvs::VolumeObjectBase*   m_volume; ///< pointer to the volume object
    kvs::TransferFunction          m_tfunc;  ///< transfer function
    kvs::PolygonObject::NormalType m_normal; ///< normal vector type

public:

    IsolevelSlider( kvs::glut::Screen* screen ):
        kvs::glut::Slider( screen ),
        m_volume( NULL ),
        m_tfunc( NULL ),
        m_normal( kvs::PolygonObject::PolygonNormal ) {}

    void setVolumeObject( const kvs::VolumeObjectBase* volume )
    {
        m_volume = volume;
    }

    void setTransferFunction( const kvs::TransferFunction& tfunc )
    {
        m_tfunc = tfunc;
    }

    void setNormal( const kvs::PolygonObject::NormalType normal )
    {
        m_normal = normal;
    }

    void valueChanged( void )
    {
        const double level = this->value();
        const bool d = true;
        kvs::PolygonObject* object = new kvs::Isosurface( m_volume, level, m_normal, d, m_tfunc );
        if ( object ) screen()->objectManager()->change( 1, object );
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
 *  @brief  Constructs a new Argument class.
 *  @param  argc [in] argument count
 *  @param  argv [in] argument values
 */
/*===========================================================================*/
Argument::Argument( int argc, char** argv ):
    kvsview::Argument::Common( argc, argv, "Isosurface")
{
    // Parameters for the isosurface class.
    add_option( kvsview::Isosurface::CommandName, kvsview::Isosurface::Description, 0 );
    add_option( "l", "Isosurface level. (default: mean value)", 1, false );
    add_option( "n", "Normal vector type; 'poly[gon]' 'vert[ex]'. (default: poly)", 1, false );
    add_option( "t", "Transfer function file. (optional: <filename>)", 1, false );
    add_option( "T", "Transfer function file with range adjustment. (optional: <filename>)", 1, false );
}

/*===========================================================================*/
/**
 *  @brief  Returns a isolevel.
 *  @param  volume [in] pointer to the volume object
 *  @param  transfer_function [in] transfer function
 *  @return isolevel level
 */
/*===========================================================================*/
const kvs::Real64 Argument::isolevel(
    const kvs::VolumeObjectBase* volume,
    const kvs::TransferFunction& transfer_function )
{
    if ( !volume->hasMinMaxValues() ) volume->updateMinMaxValues();
    float min_value = volume->minValue();
    float max_value = volume->maxValue();
    if ( transfer_function.hasRange() )
    {
        min_value = transfer_function.minValue();
        max_value = transfer_function.maxValue();
    }
    const kvs::Real64 default_value = ( max_value + min_value ) * 0.5;

    if ( this->hasOption("l") ) return( this->optionValue<kvs::Real64>("l") );
    else return( default_value );
}

/*===========================================================================*/
/**
 *  @brief  Returns a polygon normal vector type.
 *  @return normal vector type
 */
/*===========================================================================*/
const kvs::PolygonObject::NormalType Argument::normalType( void )
{
    const kvs::PolygonObject::NormalType default_value = kvs::PolygonObject::PolygonNormal;

    kvs::PolygonObject::NormalType normal_type = default_value;
    if ( this->hasOption("n") )
    {
        const std::string option_value = this->optionValue<std::string>("n");
        if ( option_value == "poly" ||
             option_value == "polygon" )
        {
            normal_type = kvs::PolygonObject::PolygonNormal;
        }
        else if ( option_value == "vert" ||
                  option_value == "vertex" )
        {
            normal_type = kvs::PolygonObject::VertexNormal;
        }
        else
        {
            kvsMessageError("Unknown normal type '%s'.",option_value.c_str());
        }
    }

    return( normal_type );
}

/*===========================================================================*/
/**
 *  @brief  Returns a transfer function.
 *  @param  volume [in] pointer to the volume object
 *  @return transfer function
 */
/*===========================================================================*/
const kvs::TransferFunction Argument::transferFunction( const kvs::VolumeObjectBase* volume )
{
    if ( this->hasOption("t") )
    {
        const std::string filename = this->optionValue<std::string>("t");
        return( kvs::TransferFunction( filename ) );
    }
    else if ( this->hasOption("T") )
    {
        const std::string filename = this->optionValue<std::string>("T");
        kvs::TransferFunction tfunc( filename );
        tfunc.adjustRange( volume );
        return( tfunc );
    }
    else
    {
        const size_t resolution = 256;
        return( kvs::TransferFunction( resolution ) );
    }
}

/*===========================================================================*/
/**
 *  @brief  Constructs a new Main class.
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
    // GLUT viewer application.
    kvs::glut::Application app( m_argc, m_argv );

    // Parse specified arguments.
    Isosurface::Argument arg( m_argc, m_argv );
    if( !arg.parse() ) return( false );

    // Event.
    kvsview::Isosurface::KeyPressEvent key_press_event;

    // Create screen.
    kvs::glut::Screen screen( &app );
    screen.addKeyPressEvent( &key_press_event );
    screen.setSize( 512, 512 );
    screen.setTitle( kvsview::CommandName + " - " + kvsview::Isosurface::CommandName );

    // Check the input point data.
    m_input_name = arg.value<std::string>();
    if ( !(kvsview::FileChecker::ImportableStructuredVolume( m_input_name ) ||
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

    // Pointer to the volume object data.
    const kvs::VolumeObjectBase* volume = kvs::VolumeObjectBase::DownCast( pipe.object() );

    // Transfer function.
    const kvs::TransferFunction tfunc = arg.transferFunction( volume );

    // Legend bar.
    kvsview::Widget::LegendBar legend_bar( &screen );
    legend_bar.setColorMap( tfunc.colorMap() );
    if ( !tfunc.hasRange() )
    {
        const kvs::VolumeObjectBase* object = kvs::VolumeObjectBase::DownCast( pipe.object() );
        const kvs::Real32 min_value = object->minValue();
        const kvs::Real32 max_value = object->maxValue();
        legend_bar.setRange( min_value, max_value );
    }
    legend_bar.show();

    // Orientation axis.
    kvsview::Widget::OrientationAxis orientation_axis( &screen );
    orientation_axis.show();

    // Set up isosurface class.
    kvs::PipelineModule mapper( new kvs::Isosurface );
    const kvs::Real64 level = arg.isolevel( volume, tfunc );
    const kvs::PolygonObject::NormalType normal = arg.normalType();
    mapper.get<kvs::Isosurface>()->setIsolevel( level );
    mapper.get<kvs::Isosurface>()->setNormalType( normal );
    mapper.get<kvs::Isosurface>()->setTransferFunction( tfunc );
    pipe.connect( mapper );

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

    // Show the screen and the slider widget.
    screen.show();

    // Slider.
    kvsview::Isosurface::IsolevelSlider slider( &screen );
    slider.setMargin( 10 );
    slider.setCaption("Isolevel");
    slider.setVolumeObject( volume );
    slider.setTransferFunction( tfunc );
    slider.setNormal( normal );
    slider.setValue( static_cast<float>( level ) );
    slider.setRange( legend_bar.minValue(), legend_bar.maxValue() );
    slider.show();

    return( arg.clear(), app.run() );
}

} // end of namespace Isosurface

} // end of namespace kvsview
