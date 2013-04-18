/*****************************************************************************/
/**
 *  @file   OpenGL.cpp
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
/*****************************************************************************/
#include "OpenGL.h"
#include <kvs/Assert>


namespace
{

std::string GLGetString( GLenum name )
{
    std::string ret;
    const GLubyte* c = NULL;
    KVS_GL_CALL( c = glGetString( name ) );
    while ( *c ) ret += *c++;
    return ret;
}

std::string GLUGetString( GLenum name )
{
    std::string ret;
    const GLubyte* c = NULL;
    KVS_GL_CALL( c = gluGetString( name ) );
    while ( *c ) ret += *c++;
    return ret;
}

std::string GLEWGetString( GLenum name )
{
    std::string ret;
    const GLubyte* c = glewGetString( name );
    while ( *c ) ret += *c++;
    return ret;
}

}

namespace kvs
{

namespace OpenGL
{

/*===========================================================================*/
/**
 *  @brief  Returns OpenGL description.
 *  @return OpenGL description
 */
/*===========================================================================*/
std::string Description()
{
    const std::string description( "OpenGL - The Industry's Foundation for High Performance Graphics" );
    return description;
}

/*===========================================================================*/
/**
 *  @brief  Returns OpenGL version.
 *  @return OpenGL version
 */
/*===========================================================================*/
std::string Version()
{
    return ::GLGetString( GL_VERSION );
}

/*===========================================================================*/
/**
 *  @brief  Returns GLSL (OpenGL Shading Language) version.
 *  @return GLSL version
 */
/*===========================================================================*/
std::string GLSLVersion()
{
#if defined( GL_SHADING_LANGUAGE_VERSION )
    return ::GLGetString( GL_SHADING_LANGUAGE_VERSION );
#elif defined( GL_SHADING_LANGUAGE_VERSION_ARB )
    return ::GLGetString( GL_SHADING_LANGUAGE_VERSION_ARB );
#else
    return "Unknown";
#endif
}

/*===========================================================================*/
/**
 *  @brief  Returns GLU version.
 *  @return GLU version
 */
/*===========================================================================*/
std::string GLUVersion()
{
    return ::GLUGetString( GLU_VERSION );
}

/*===========================================================================*/
/**
 *  @brief  Returns GLEW version.
 *  @return GLEW version
 */
/*===========================================================================*/
std::string GLEWVersion()
{
    return ::GLEWGetString( GLEW_VERSION );
}

/*===========================================================================*/
/**
 *  @brief  Returns vendor information.
 *  @return vender information
 */
/*===========================================================================*/
std::string Vendor()
{
    return ::GLGetString( GL_VENDOR );
}

/*===========================================================================*/
/**
 *  @brief  Returns renderer (GPU) information.
 *  @return rendere information
 */
/*===========================================================================*/
std::string Renderer()
{
    return ::GLGetString( GL_RENDERER );
}

/*===========================================================================*/
/**
 *  @brief  Returns OpenGL extension name list.
 *  @return extension name list
 */
/*===========================================================================*/
kvs::StringList ExtensionList()
{
    kvs::StringList extensions;
    std::stringstream list( ::GLGetString( GL_EXTENSIONS ) );
    std::string name;
    while ( list >> name )
    {
        extensions.push_back( name );
    }

    return extensions;
}

/*===========================================================================*/
/**
 *  @brief  Returns OpenGL error code.
 *  @return error code
 */
/*===========================================================================*/
GLenum ErrorCode()
{
    return glGetError();
}

/*===========================================================================*/
/**
 *  @brief  Checks OpenGL error.
 *  @return true, if no error
 */
/*===========================================================================*/
bool HasError()
{
    const GLenum error_code = kvs::OpenGL::ErrorCode();
    if ( error_code == GL_NO_ERROR ) return false;
    return true;
}

/*===========================================================================*/
/**
 *  @brief  Returns OpenGL error string.
 *  @param  error_code [in] OpenGL error code
 *  @return error string
 */
/*===========================================================================*/
std::string ErrorString( const GLenum error_code )
{
    std::string error_string;
    const GLubyte* c = gluErrorString( error_code );
    while ( *c ) error_string += *c++;
    return error_string;
}

void GetBooleanv( GLenum pname, GLboolean* params )
{
    KVS_GL_CALL( glGetBooleanv( pname, params ) );
}

void GetDoublev( GLenum pname, GLdouble* params )
{
    KVS_GL_CALL( glGetDoublev( pname, params ) );
}

void GetFloatv( GLenum pname, GLfloat* params )
{
    KVS_GL_CALL( glGetFloatv( pname, params ) );
}

void GetIntegerv( GLenum pname, GLint* params )
{
    KVS_GL_CALL( glGetIntegerv( pname, params ) );
}

GLboolean Boolean( GLenum pname )
{
    GLboolean param;
    kvs::OpenGL::GetBooleanv( pname, &param );
    return param;
}

GLdouble Double( GLenum pname )
{
    GLdouble param;
    kvs::OpenGL::GetDoublev( pname, &param );
    return param;
}

GLfloat Float( GLenum pname )
{
    GLfloat param;
    kvs::OpenGL::GetFloatv( pname, &param );
    return param;
}

GLint Integer( GLenum pname )
{
    GLint param;
    kvs::OpenGL::GetIntegerv( pname, &param );
    return param;
}

GLint MaxTextureSize()
{
    return kvs::OpenGL::Integer( GL_MAX_TEXTURE_SIZE );
}

GLint Max3DTextureSize()
{
    return kvs::OpenGL::Integer( GL_MAX_3D_TEXTURE_SIZE );
}

GLint MaxTextureImageUnits()
{
    return kvs::OpenGL::Integer( GL_MAX_TEXTURE_IMAGE_UNITS );
}

GLint MaxCombinedTextureImageUnits()
{
    return kvs::OpenGL::Integer( GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS );
}

GLint MaxColorAttachments()
{
    return kvs::OpenGL::Integer( GL_MAX_COLOR_ATTACHMENTS );
}

GLint MaxRenderBufferSize()
{
    return kvs::OpenGL::Integer( GL_MAX_RENDERBUFFER_SIZE );
}

void Flush()
{
    KVS_GL_CALL( glFlush() );
}

void Finish()
{
    KVS_GL_CALL( glFinish() );
}

void Enable( GLenum cap )
{
    KVS_GL_CALL( glEnable( cap ) );
}

void Disable( GLenum cap )
{
    KVS_GL_CALL( glDisable( cap ) );
}

bool IsEnabled( GLenum cap )
{
    GLboolean result = GL_FALSE;
    KVS_GL_CALL( result = glIsEnabled( cap ) );
    return result == GL_TRUE;
}

void SetBlendFunc( GLenum sfactor, GLenum dfactor )
{
    KVS_GL_CALL( glBlendFunc( sfactor, dfactor ) );
}

void SetShadeModel( GLenum mode )
{
    KVS_GL_CALL( glShadeModel( mode ) );
}

void SetMatrixMode( GLenum mode )
{
    KVS_GL_CALL( glMatrixMode( mode ) );
}

void SetDrawBuffer( GLenum mode )
{
    KVS_GL_CALL( glDrawBuffer( mode ) );
}

void SetDrawBuffers( GLsizei n, const GLenum* bufs )
{
    KVS_GL_CALL( glDrawBuffers( n, bufs ) );
}

void SetViewport( GLint x, GLint y, GLsizei width, GLsizei height )
{
    KVS_GL_CALL( glViewport( x, y, width, height ) );
}

void SetOrtho( GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble near, GLdouble far )
{
    KVS_GL_CALL( glOrtho( left, right, bottom, top, near, far ) );
}

void SetOrtho( GLdouble left, GLdouble right, GLdouble bottom, GLdouble top )
{
    KVS_GL_CALL( gluOrtho2D( left, right, bottom, top ) );
}

void SetPerspective( GLdouble fovy, GLdouble aspect, GLdouble near, GLdouble far )
{
    KVS_GL_CALL( gluPerspective( fovy, aspect, near, far ) );
}

void SetFrustum( GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble near, GLdouble far )
{
    KVS_GL_CALL( glFrustum( left, right, bottom, top, near, far ) );
}

void GetModelViewMatrix( GLfloat* params )
{
    kvs::OpenGL::GetFloatv( GL_MODELVIEW_MATRIX, params );
}

void GetProjectionMatrix( GLfloat* params )
{
    kvs::OpenGL::GetFloatv( GL_PROJECTION_MATRIX, params );
}

void GetViewport( GLint* params )
{
    kvs::OpenGL::GetIntegerv( GL_VIEWPORT, params );
}

void LoadIdentity()
{
    KVS_GL_CALL( glLoadIdentity() );
}

void LoadMatrix( const GLfloat* m )
{
    KVS_GL_CALL( glLoadMatrixf( m ) );
}

void LoadMatrix( const GLdouble* m )
{
    KVS_GL_CALL( glLoadMatrixd( m ) );
}

void MultMatrix( const GLfloat* m )
{
    KVS_GL_CALL( glMultMatrixf( m ) );
}

void MultMatrix( const GLdouble* m )
{
    KVS_GL_CALL( glMultMatrixd( m ) );
}

void Rotate( GLfloat angle, GLfloat x, GLfloat y, GLfloat z )
{
    KVS_GL_CALL( glRotatef( angle, x, y, z ) );
}

void Scale( GLfloat x, GLfloat y, GLfloat z )
{
    KVS_GL_CALL( glScalef( x, y, z ) );
}

void Translate( GLfloat x, GLfloat y, GLfloat z )
{
    KVS_GL_CALL( glTranslatef( x, y, z ) );
}

void PushMatrix()
{
    KVS_GL_CALL( glPushMatrix() );
}

void PopMatrix()
{
    KVS_GL_CALL( glPopMatrix() );
}

void PushAttrib( GLbitfield mask )
{
    KVS_GL_CALL( glPushAttrib( mask ) );
}

void PopAttrib()
{
    KVS_GL_CALL( glPopAttrib() );
}

WithPushedMatrix::WithPushedMatrix( GLenum mode )
{
    m_current_mode = kvs::OpenGL::Integer( GL_MATRIX_MODE );
    kvs::OpenGL::SetMatrixMode( mode );
    kvs::OpenGL::PushMatrix();
}

WithPushedMatrix::~WithPushedMatrix()
{
    kvs::OpenGL::PopMatrix();
    kvs::OpenGL::SetMatrixMode( m_current_mode );
}

void WithPushedMatrix::loadIdentity()
{
    kvs::OpenGL::LoadIdentity();
}

void WithPushedMatrix::loadMatrix( const GLfloat* m )
{
    kvs::OpenGL::LoadMatrix( m );
}

void WithPushedMatrix::loadMatrix( const GLdouble* m )
{
    kvs::OpenGL::LoadMatrix( m );
}

void WithPushedMatrix::multMatrix( const GLfloat* m )
{
    kvs::OpenGL::MultMatrix( m );
}

void WithPushedMatrix::multMatrix( const GLdouble* m )
{
    kvs::OpenGL::MultMatrix( m );
}

void WithPushedMatrix::rotate( GLfloat angle, GLfloat x, GLfloat y, GLfloat z )
{
    kvs::OpenGL::Rotate( angle, x, y, z );
}

void WithPushedMatrix::scale( GLfloat x, GLfloat y, GLfloat z )
{
    kvs::OpenGL::Scale( x, y, z );
}

void WithPushedMatrix::translate( GLfloat x, GLfloat y, GLfloat z )
{
    kvs::OpenGL::Translate( x, y, z );
}

WithPushedAttrib::WithPushedAttrib( GLbitfield mask )
{
    kvs::OpenGL::PushAttrib( mask );
}

WithPushedAttrib::~WithPushedAttrib()
{
    kvs::OpenGL::PopAttrib();
}

WithEnabled::WithEnabled( GLenum cap ):
    m_cap( cap )
{
    kvs::OpenGL::Enable( cap );
}

WithEnabled::~WithEnabled()
{
    kvs::OpenGL::Disable( m_cap );
}

void ActivateTextureUnit( GLint unit )
{
    KVS_ASSERT( unit >= 0 );
    KVS_ASSERT( unit < kvs::OpenGL::MaxCombinedTextureImageUnits() );
    KVS_GL_CALL( glActiveTexture( GL_TEXTURE0 + unit ) );
}

} // end of namespace OpenGL

} // end of namespace kvs