/****************************************************************************/
/**
 *  @file   Texture3D.cpp
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
#include "Texture3D.h"
#include <kvs/Math>
#include <kvs/OpenGL>
#include <iostream>


namespace kvs
{

/*==========================================================================*/
/**
 *  Constructor.
 */
/*==========================================================================*/
Texture3D::Texture3D():
    Texture( GL_TEXTURE_3D ),
    m_is_downloaded( false ),
    m_wrap_s( GL_CLAMP ),
    m_wrap_t( GL_CLAMP ),
    m_wrap_r( GL_CLAMP ),
    m_width( 0 ),
    m_height( 0 ),
    m_depth( 0 ),
    m_pixels( 0 )
{
}

/*==========================================================================*/
/**
 *  Destructor.
 */
/*==========================================================================*/
Texture3D::~Texture3D()
{
    this->release();
}

/*==========================================================================*/
/**
 *  Returns the wrap method for s-axis.
 */
/*==========================================================================*/
GLenum Texture3D::wrapS() const
{
    return( m_wrap_s );
}

/*==========================================================================*/
/**
 *  Returns the wrap method for t-axis.
 */
/*==========================================================================*/
GLenum Texture3D::wrapT() const
{
    return( m_wrap_t );
}

/*==========================================================================*/
/**
 *  Returns the wrap method for r-axis.
 */
/*==========================================================================*/
GLenum Texture3D::wrapR() const
{
    return( m_wrap_r );
}

/*==========================================================================*/
/**
 *  Returns the texture width.
 */
/*==========================================================================*/
size_t Texture3D::width() const
{
    return( m_width );
}

/*==========================================================================*/
/**
 *  Returns the texture height.
 */
/*==========================================================================*/
size_t Texture3D::height() const
{
    return( m_height );
}

/*==========================================================================*/
/**
 *  Returns the texture depth.
 */
/*==========================================================================*/
size_t Texture3D::depth() const
{
    return( m_depth );
}

bool Texture3D::isDownloaded() const
{
    return( m_is_downloaded );
}

/*==========================================================================*/
/**
 *  Set the wrap method for s-axis.
 *  @param wrap_s [in] wrap method for s-axis
 */
/*==========================================================================*/
void Texture3D::setWrapS( const GLenum wrap_s )
{
    m_wrap_s = wrap_s;
}

/*==========================================================================*/
/**
 *  Set the wrap method for t-axis.
 *  @param wrap_t [in] wrap method for t-axis
 */
/*==========================================================================*/
void Texture3D::setWrapT( const GLenum wrap_t )
{
    m_wrap_t = wrap_t;

}

/*==========================================================================*/
/**
 *  Set the wrap method for r-axis.
 *  @param wrap_r [in] wrap method for r-axis
 */
/*==========================================================================*/
void Texture3D::setWrapR( const GLenum wrap_r )
{
    m_wrap_r = wrap_r;
}

/*==========================================================================*/
/**
 *  Create the texture.
 */
/*==========================================================================*/
void Texture3D::create( const size_t width, const size_t height, const size_t depth )
{
    m_width  = width;
    m_height = height;
    m_depth  = depth;

    BaseClass::generateTexture();
    BaseClass::bind();
    BaseClass::setParameter( GL_TEXTURE_MAG_FILTER, m_mag_filter );
    BaseClass::setParameter( GL_TEXTURE_MIN_FILTER, m_min_filter );
    BaseClass::setParameter( GL_TEXTURE_WRAP_S, m_wrap_s );
    BaseClass::setParameter( GL_TEXTURE_WRAP_T, m_wrap_t );
    BaseClass::setParameter( GL_TEXTURE_WRAP_R, m_wrap_r );
    this->download( width, height, depth, NULL );
}

/*==========================================================================*/
/**
 *  Release the texture.
 */
/*==========================================================================*/
void Texture3D::release()
{
    BaseClass::deleteTexture();
    m_is_downloaded = false;
}

/*==========================================================================*/
/**
 *  Download the texture data to the GPU.
 *  @param width  [in] texture width
 *  @param height [in] texture height
 *  @param depth  [in] texture depth
 *  @param pixels [in] pointer to the pixel data
 *  @param xoffset [in] texel offset in the x direction within the pixel data
 *  @param yoffset [in] texel offset in the y direction within the pixel data
 *  @param zoffset [in] texel offset in the z direction within the pixel data
 */
/*==========================================================================*/
void Texture3D::download(
    const size_t width,
    const size_t height,
    const size_t depth,
    const void*  pixels,
    const size_t xoffset,
    const size_t yoffset,
    const size_t zoffset )
{
    const GLint swap = kvs::OpenGL::Integer( GL_UNPACK_SWAP_BYTES );
    const GLint alignment = kvs::OpenGL::Integer( GL_UNPACK_ALIGNMENT );
    BaseClass::setPixelStorageMode( GL_UNPACK_SWAP_BYTES, swap ? GL_TRUE : GL_FALSE );
    BaseClass::setPixelStorageMode( GL_UNPACK_ALIGNMENT, 1 );

    if ( !m_is_downloaded )
    {
        BaseClass::setImage3D( width, height, depth, pixels );
        m_is_downloaded = true;
    }
    else
    {
        BaseClass::setSubImage3D( width, height, depth, pixels, xoffset, yoffset, zoffset );
    }

    BaseClass::setPixelStorageMode( GL_UNPACK_SWAP_BYTES, swap );
    BaseClass::setPixelStorageMode( GL_UNPACK_ALIGNMENT, alignment );
}

/*==========================================================================*/
/**
 *  Returns the used texture memory size.
 *  @return Used texture memory size [byte]
 */
/*==========================================================================*/
unsigned int Texture3D::UsedTextureMemorySize()
{
    return( Texture3D::get_texture_memory_size_on_gpu( GL_PROXY_TEXTURE_3D ) );
}

/*==========================================================================*/
/**
 *  Returns the used texture memory size for given proxy.
 *  @param proxy [in] proxy
 *  @return Used texture memory size [byte]
 */
/*==========================================================================*/
unsigned int Texture3D::get_texture_memory_size_on_gpu( const GLenum proxy )
{
    // Get the texture size.
    GLint texture_size[3] = { 0, 0, 0 };
    glGetTexLevelParameteriv( proxy, 0, GL_TEXTURE_WIDTH,  &(texture_size[0]) );
    glGetTexLevelParameteriv( proxy, 0, GL_TEXTURE_HEIGHT, &(texture_size[1]) );
    glGetTexLevelParameteriv( proxy, 0, GL_TEXTURE_DEPTH,  &(texture_size[2]) );

    // Get the each channel size.
    GLint channel_size[7] = { 0, 0, 0, 0, 0, 0, 0 };
    glGetTexLevelParameteriv( proxy, 0, GL_TEXTURE_RED_SIZE,       &(channel_size[0]) );
    glGetTexLevelParameteriv( proxy, 0, GL_TEXTURE_GREEN_SIZE,     &(channel_size[1]) );
    glGetTexLevelParameteriv( proxy, 0, GL_TEXTURE_BLUE_SIZE,      &(channel_size[2]) );
    glGetTexLevelParameteriv( proxy, 0, GL_TEXTURE_ALPHA_SIZE,     &(channel_size[3]) );
    glGetTexLevelParameteriv( proxy, 0, GL_TEXTURE_LUMINANCE_SIZE, &(channel_size[4]) );
    glGetTexLevelParameteriv( proxy, 0, GL_TEXTURE_INTENSITY_SIZE, &(channel_size[5]) );

    if ( GLEW_EXT_paletted_texture )
    {
        glGetTexLevelParameteriv( proxy, 0, GL_TEXTURE_INDEX_SIZE_EXT, &(channel_size[6]) );
    }

    if ( GLEW_ARB_texture_compression )
    {
        // Get compressed texture size.
        GLint compressed[1] = { 0 };
        glGetTexLevelParameteriv( proxy, 0, GL_TEXTURE_COMPRESSED_ARB, &(compressed[0]) );
        if( compressed[0] )
        {
            GLint  size[1] = { 0 };
#if   GL_TEXTURE_COMPRESSED_IMAGE_SIZE_ARB
            GLenum pname = GL_TEXTURE_COMPRESSED_IMAGE_SIZE_ARB;
            glGetTexLevelParameteriv( proxy, 0, pname, &(size[0]) );
#elif GL_TEXTURE_IMAGE_SIZE_ARB
            GLenum pname = GL_TEXTURE_IMAGE_SIZE_ARB;
            glGetTexLevelParameteriv( proxy, 0, pname, &(size[0]) );
#endif
            return( size[0] );
        }
    }

    // Compute the number of bytes per voxel.
    GLint total_bits =
        channel_size[0] +
        channel_size[1] +
        channel_size[2] +
        channel_size[3] +
        channel_size[4] +
        channel_size[5] +
        channel_size[6];

    // Convert unit from 'bit' to 'byte'.
    GLfloat bytes = (GLfloat)total_bits / 8.0f;

    // Round up to the next whole byte.
    if( !kvs::Math::Equal( bytes, (GLfloat)( (GLint)bytes) ) )
    {
        bytes = (GLfloat)((GLint)bytes) + 1.0f;
    }

    // compute the amount of texture memory used.
    return( texture_size[0] * texture_size[1] * texture_size[2] * (GLint)bytes );
}

} // end of namespace kvs
