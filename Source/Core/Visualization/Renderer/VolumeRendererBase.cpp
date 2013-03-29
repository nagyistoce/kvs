/****************************************************************************/
/**
 *  @file   VolumeRendererBase.cpp
 *  @author Naohisa Sakamoto
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright (c) Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/****************************************************************************/
#include "VolumeRendererBase.h"
#include <kvs/Camera>
#include <kvs/Math>


namespace kvs
{

/*==========================================================================*/
/**
 *  Constructor.
 */
/*==========================================================================*/
VolumeRendererBase::VolumeRendererBase()
{
    this->initialize();
}

/*==========================================================================*/
/**
 *  Destructor.
 */
/*==========================================================================*/
VolumeRendererBase::~VolumeRendererBase()
{
    this->clear();
}

size_t VolumeRendererBase::windowWidth() const
{
    return m_width;
}

size_t VolumeRendererBase::windowHeight() const
{
    return m_height;
}

/*==========================================================================*/
/**
 *  Set the transder function.
 *  @param tfunc [in] transfer function
 */
/*==========================================================================*/
void VolumeRendererBase::setTransferFunction( const kvs::TransferFunction& tfunc )
{
    m_tfunc = tfunc;
}

void VolumeRendererBase::setWindowSize( const size_t width, const size_t height )
{
    m_width = width;
    m_height = height;
}

/*==========================================================================*/
/**
 *  Enable shading function.
 */
/*==========================================================================*/
void VolumeRendererBase::enableShading()
{
    m_enable_shading = true;
}

/*==========================================================================*/
/**
 *  Disable shading function.
 */
/*==========================================================================*/
void VolumeRendererBase::disableShading()
{
    m_enable_shading = false;
}

/*==========================================================================*/
/**
 *  Test whether the shading is enable or disable.
 *  @return true, if the shading is enable.
 */
/*==========================================================================*/
const bool VolumeRendererBase::isEnabledShading() const
{
    return( m_enable_shading );
}

/*==========================================================================*/
/**
 *  Get the trunsfer function.
 *  @return transfer function
 */
/*==========================================================================*/
const kvs::TransferFunction& VolumeRendererBase::transferFunction() const
{
    return( m_tfunc );
}

/*==========================================================================*/
/**
 *  Get the trunsfer function.
 *  @return transfer function
 */
/*==========================================================================*/
kvs::TransferFunction& VolumeRendererBase::transferFunction()
{
    return( m_tfunc );
}

/*==========================================================================*/
/**
 *  Initialize.
 */
/*==========================================================================*/
void VolumeRendererBase::initialize()
{
    m_width = 0;
    m_height = 0;

    m_enable_shading = true;
    m_shader = NULL;

    m_depth_buffer.setFormat( GL_DEPTH_COMPONENT );
    m_depth_buffer.setType( GL_FLOAT );

    m_color_buffer.setFormat( GL_RGBA );
    m_color_buffer.setType( GL_UNSIGNED_BYTE );
}

/*==========================================================================*/
/**
 *  Clear.
 */
/*==========================================================================*/
void VolumeRendererBase::clear()
{
    if ( m_shader )
    {
        delete m_shader;
        m_shader = NULL;
    }
}

/*==========================================================================*/
/**
 *  Draw the rendering image.
 */
/*==========================================================================*/
void VolumeRendererBase::draw_image()
{
    // Get viewport information.
    int viewport[4];
    glGetIntegerv( GL_VIEWPORT, (GLint*)viewport );

    glDepthFunc( GL_LEQUAL );
    glDepthMask( GL_TRUE );
    glColorMask( GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE );
    this->draw_depth_buffer( viewport );

    glBlendFunc( GL_ONE, GL_ONE_MINUS_SRC_ALPHA );
    glColorMask( GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE );
    this->draw_color_buffer( viewport );
}

/*==========================================================================*/
/**
 *  Draw the depth buffer.
 */
/*==========================================================================*/
void VolumeRendererBase::draw_depth_buffer( const int* viewport )
{
    // Enable/Disable OpenGL parameters.
    glEnable( GL_DEPTH_TEST );

    // Send depth data to the frame buffer (depth buffer).
    m_depth_buffer.draw( m_width, m_height, viewport, m_depth_data.data() );

    // Recover OpenGL parameters.
    glDisable( GL_DEPTH_TEST );
}

/*==========================================================================*/
/**
 *  Draw color buffer.
 */
/*==========================================================================*/
void VolumeRendererBase::draw_color_buffer( const int* viewport )
{
    // Enable/Disable OpenGL parameters.
    glEnable( GL_BLEND );
    glDisable( GL_DEPTH_TEST );

    // Send color data to the frame buffer (color buffer).
    m_color_buffer.draw( m_width, m_height, viewport, m_color_data.data() );

    // Recover OpenGL parameters.
    glDisable( GL_BLEND );
    glEnable( GL_DEPTH_TEST );
}

} // end of namespace kvs
