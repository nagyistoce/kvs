/****************************************************************************/
/**
 *  @file PointObject.cpp
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright 2007-2008 Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/****************************************************************************/
#include "PointObject.h"
#include "LineObject.h"
#include "PolygonObject.h"
#include <kvs/Assert>


namespace kvs
{

PointObject::PointObject( void )
{
}

PointObject::PointObject(
    const kvs::ValueArray<kvs::Real32>& coords,
    const kvs::ValueArray<kvs::UInt8>&  colors,
    const kvs::ValueArray<kvs::Real32>& normals,
    const kvs::ValueArray<kvs::Real32>& sizes ):
    kvs::GeometryObjectBase( coords, colors, normals )
{
    this->setSizes( sizes );
}

PointObject::PointObject(
    const kvs::ValueArray<kvs::Real32>& coords,
    const kvs::ValueArray<kvs::UInt8>&  colors,
    const kvs::ValueArray<kvs::Real32>& normals,
    const kvs::Real32                   size ):
    kvs::GeometryObjectBase( coords, colors, normals )
{
    this->setSize( size );
}

PointObject::PointObject(
    const kvs::ValueArray<kvs::Real32>& coords,
    const kvs::RGBColor&                color,
    const kvs::ValueArray<kvs::Real32>& normals,
    const kvs::ValueArray<kvs::Real32>& sizes ):
    kvs::GeometryObjectBase( coords, color, normals )
{
    this->setSizes( sizes );
}

PointObject::PointObject(
    const kvs::ValueArray<kvs::Real32>& coords,
    const kvs::ValueArray<kvs::Real32>& normals,
    const kvs::ValueArray<kvs::Real32>& sizes ):
    kvs::GeometryObjectBase( coords, normals )
{
    this->setSizes( sizes );
}

PointObject::PointObject(
    const kvs::ValueArray<kvs::Real32>& coords,
    const kvs::RGBColor&                color,
    const kvs::ValueArray<kvs::Real32>& normals,
    const kvs::Real32                   size ):
    kvs::GeometryObjectBase( coords, color, normals )
{
    this->setSize( size );
}

PointObject::PointObject(
    const kvs::ValueArray<kvs::Real32>& coords,
    const kvs::ValueArray<kvs::UInt8>&  colors,
    const kvs::ValueArray<kvs::Real32>& sizes ):
    kvs::GeometryObjectBase( coords, colors )
{
    this->setSizes( sizes );
}

PointObject::PointObject(
    const kvs::ValueArray<kvs::Real32>& coords,
    const kvs::RGBColor&                color,
    const kvs::ValueArray<kvs::Real32>& sizes ):
    kvs::GeometryObjectBase( coords, color )
{
    KVS_ASSERT( coords.size() == sizes.size() * 3 );

    this->setSizes( sizes );
}

PointObject::PointObject(
    const kvs::ValueArray<kvs::Real32>& coords,
    const kvs::ValueArray<kvs::UInt8>&  colors,
    const kvs::Real32                   size ):
    kvs::GeometryObjectBase( coords, colors )
{
    this->setSize( size );
}

PointObject::PointObject(
    const kvs::ValueArray<kvs::Real32>& coords,
    const kvs::RGBColor&                color,
    const kvs::Real32                   size ):
    kvs::GeometryObjectBase( coords, color )
{
    this->setSize( size );
}

PointObject::PointObject(
    const kvs::ValueArray<kvs::Real32>& coords ):
    kvs::GeometryObjectBase( coords )
{
    this->setSize( 1 );
}

PointObject::PointObject( const kvs::LineObject* line )
{
    BaseClass::setCoords( line->coords() );

    if( line->colorType() == kvs::LineObject::VertexColor )
    {
        BaseClass::setColors( line->colors() );
    }
    else
    {
        BaseClass::setColor( line->color() );
    }

    this->setSize( line->size() );

    BaseClass::setMinMaxObjectCoords(
        line->minObjectCoord(),
        line->maxObjectCoord() );

    BaseClass::setMinMaxExternalCoords(
        line->minExternalCoord(),
        line->maxExternalCoord() );
}

PointObject::PointObject( const kvs::PolygonObject* polygon )
{
    BaseClass::setCoords( polygon->coords() );

    if( polygon->colorType() == kvs::PolygonObject::VertexColor )
    {
        BaseClass::setColors( polygon->colors() );
    }
    else
    {
        BaseClass::setColor( polygon->color() );
    }

    if( polygon->normalType() == kvs::PolygonObject::VertexNormal )
    {
        BaseClass::setNormals( polygon->normals() );
    }

    this->setSize( 1.0f );

    BaseClass::setMinMaxObjectCoords(
        polygon->minObjectCoord(),
        polygon->maxObjectCoord() );

    BaseClass::setMinMaxExternalCoords(
        polygon->minExternalCoord(),
        polygon->maxExternalCoord() );
}

PointObject::~PointObject( void )
{
    this->clear();
}

kvs::PointObject* PointObject::DownCast( kvs::ObjectBase* object )
{
    kvs::GeometryObjectBase* geometry = kvs::GeometryObjectBase::DownCast( object );
    if ( !geometry ) return( NULL );

    const kvs::GeometryObjectBase::GeometryType type = geometry->geometryType();
    if ( type != kvs::GeometryObjectBase::Point )
    {
        kvsMessageError("Input object is not a point object.");
        return( NULL );
    }

    kvs::PointObject* point = static_cast<kvs::PointObject*>( geometry );

    return( point );
}

const kvs::PointObject* PointObject::DownCast( const kvs::ObjectBase* object )
{
    return( PointObject::DownCast( const_cast<kvs::ObjectBase*>( object ) ) );
}

PointObject& PointObject::operator += ( const PointObject& object )
{
    if ( this->coords().size() == 0 )
    {
        // Copy the object.
        BaseClass::setCoords( object.coords() );
        BaseClass::setNormals( object.normals() );
        BaseClass::setColors( object.colors() );
        this->setSizes( object.sizes() );

        BaseClass::setMinMaxObjectCoords(
            object.minObjectCoord(),
            object.maxObjectCoord() );
        BaseClass::setMinMaxExternalCoords(
            object.minExternalCoord(),
            object.maxExternalCoord() );
    }
    else
    {
        if ( !BaseClass::hasMinMaxObjectCoords() )
        {
            BaseClass::updateMinMaxCoords();
        }

        kvs::Vector3f min_object_coord( BaseClass::minObjectCoord() );
        kvs::Vector3f max_object_coord( BaseClass::maxObjectCoord() );

        min_object_coord.x() = kvs::Math::Min( min_object_coord.x(), object.minObjectCoord().x() );
        min_object_coord.y() = kvs::Math::Min( min_object_coord.y(), object.minObjectCoord().y() );
        min_object_coord.z() = kvs::Math::Min( min_object_coord.z(), object.minObjectCoord().z() );

        max_object_coord.x() = kvs::Math::Max( max_object_coord.x(), object.maxObjectCoord().x() );
        max_object_coord.y() = kvs::Math::Max( max_object_coord.y(), object.maxObjectCoord().y() );
        max_object_coord.z() = kvs::Math::Max( max_object_coord.z(), object.maxObjectCoord().z() );

        BaseClass::setMinMaxObjectCoords( min_object_coord, max_object_coord );
        BaseClass::setMinMaxExternalCoords( min_object_coord, max_object_coord );

        // Integrate the coordinate values.
        kvs::ValueArray<kvs::Real32> coords;
        const size_t ncoords = this->coords().size() + object.coords().size();
        kvs::Real32* pcoords = coords.allocate( ncoords );
        if ( pcoords != NULL )
        {
            // x,y,z, ... + x,y,z, ... = x,y,z, ... ,x,y,z, ...
            memcpy( pcoords, this->coords().pointer(), this->coords().byteSize() );
            memcpy( pcoords + this->coords().size(), object.coords().pointer(), object.coords().byteSize() );
        }
        BaseClass::setCoords( coords );

        // Integrate the normal vectors.
        kvs::ValueArray<kvs::Real32> normals;
        if ( this->normals().size() > 0 )
        {
            if ( object.normals().size() > 0 )
            {
                // nx,ny,nz, ... + nx,ny,nz, ... = nx,ny,nz, ... ,nx,ny,nz, ...
                const size_t nnormals = this->normals().size() + object.normals().size();
                kvs::Real32* pnormals = normals.allocate( nnormals );
                if ( pnormals != NULL )
                {
                    memcpy( pnormals, this->normals().pointer(), this->normals().byteSize() );
                    memcpy( pnormals + this->normals().size(), object.normals().pointer(), object.normals().byteSize() );
                }
            }
            else
            {
                // nx,ny,nz, ... + (none) = nx,ny,nz, ... ,0,0,0, ...
                const size_t nnormals = this->normals().size() + object.coords().size();
                kvs::Real32* pnormals = normals.allocate( nnormals );
                if ( pnormals != NULL )
                {
                    memcpy( pnormals, this->normals().pointer(), this->normals().byteSize() );
                    memset( pnormals + this->normals().size(), 0, object.coords().byteSize() );
                }
            }
        }
        else
        {
            if ( object.normals().size() > 0 )
            {
                const size_t nnormals = this->coords().size() + object.normals().size();
                kvs::Real32* pnormals = normals.allocate( nnormals );
                if ( pnormals != NULL )
                {
                    // (none) + nx,ny,nz, ... = 0,0,0, ... ,nz,ny,nz, ...
                    memset( pnormals, 0, this->coords().byteSize() );
                    memcpy( pnormals + this->coords().size(), object.normals().pointer(), object.normals().byteSize() );
                }
            }
        }
        this->setNormals( normals );

        // Integrate the color values.
        kvs::ValueArray<kvs::UInt8> colors;
        if ( this->colors().size() > 1 )
        {
            if ( object.colors().size() > 1 )
            {
                // r,g,b, ... + r,g,b, ... = r,g,b, ... ,r,g,b, ...
                const size_t ncolors = this->colors().size() + object.colors().size();
                kvs::UInt8* pcolors = colors.allocate( ncolors );
                if ( pcolors != NULL )
                {
                    memcpy( pcolors, this->colors().pointer(), this->colors().byteSize() );
                    memcpy( pcolors + this->colors().size(), object.colors().pointer(), object.colors().byteSize() );
                }
            }
            else
            {
                // r,g,b, ... + R,G,B = r,g,b, ... ,R,G,B, ... ,R,G,B
                const size_t ncolors = this->colors().size() + object.coords().size();
                kvs::UInt8* pcolors = colors.allocate( ncolors );
                if ( pcolors != NULL )
                {
                    memcpy( pcolors, this->colors().pointer(), this->colors().byteSize() );
                    pcolors += this->colors().size();
                    const kvs::RGBColor color = object.color();
                    for ( size_t i = 0; i < object.coords().size(); i += 3 )
                    {
                        *(pcolors++) = color.r();
                        *(pcolors++) = color.g();
                        *(pcolors++) = color.b();
                    }
                }
            }
        }
        else
        {
            if ( object.colors().size() > 1 )
            {
                // R,G,B + r,g,b, ... = R,G,B, ... ,R,G,B, r,g,b, ...
                const size_t ncolors = this->coords().size() + object.colors().size();
                kvs::UInt8* pcolors = colors.allocate( ncolors );
                if ( pcolors != NULL )
                {
                    const kvs::RGBColor color = this->color();
                    for ( size_t i = 0; i < this->coords().size(); i += 3 )
                    {
                        *(pcolors++) = color.r();
                        *(pcolors++) = color.g();
                        *(pcolors++) = color.b();
                    }
                    memcpy( pcolors, object.colors().pointer(), object.colors().byteSize() );
                }
            }
            else
            {
                const kvs::RGBColor color1 = this->color();
                const kvs::RGBColor color2 = object.color();
                if ( color1 == color2 )
                {
                    // R,G,B + R,G,B = R,G,B
                    const size_t ncolors = 3;
                    kvs::UInt8* pcolors = colors.allocate( ncolors );
                    if ( pcolors != NULL )
                    {
                        *(pcolors++) = color1.r();
                        *(pcolors++) = color1.g();
                        *(pcolors++) = color1.b();
                    }
                }
                else
                {
                    // R,G,B + R,G,B = R,G,B, ... ,R,G,B, ...
                    const size_t ncolors = this->coords().size() + object.coords().size();
                    kvs::UInt8* pcolors = colors.allocate( ncolors );
                    if ( pcolors != NULL )
                    {
                        for ( size_t i = 0; i < this->coords().size(); i += 3 )
                        {
                            *(pcolors++) = color1.r();
                            *(pcolors++) = color1.g();
                            *(pcolors++) = color1.b();
                        }
                        for ( size_t i = 0; i < object.coords().size(); i += 3 )
                        {
                            *(pcolors++) = color2.r();
                            *(pcolors++) = color2.g();
                            *(pcolors++) = color2.b();
                        }
                    }
                }
            }
        }
        this->setColors( colors );

        // Integrate the size values.
        kvs::ValueArray<kvs::Real32> sizes;
        if ( this->sizes().size() > 1 )
        {
            if ( object.sizes().size() > 1 )
            {
                // s, ... + s, ... = s, ... ,s, ...
                const size_t nsizes = this->sizes().size() + object.sizes().size();
                kvs::Real32* psizes = sizes.allocate( nsizes );
                if ( psizes != NULL )
                {
                    memcpy( psizes, this->sizes().pointer(), this->sizes().byteSize() );
                    memcpy( psizes + this->sizes().size(), object.sizes().pointer(), object.sizes().byteSize() );
                }
            }
            else
            {
                // s, ... + S = s, ... ,S, ... ,S
                const size_t nsizes = this->sizes().size() + object.coords().size();
                kvs::Real32* psizes = sizes.allocate( nsizes );
                if ( psizes != NULL )
                {
                    memcpy( psizes, this->sizes().pointer(), this->sizes().byteSize() );
                    psizes += this->colors().size();
                    const kvs::Real32 size = object.size();
                    for ( size_t i = 0; i < object.coords().size(); i++ )
                    {
                        *(psizes++) = size;
                    }
                }
            }
        }
        else
        {
            if ( object.sizes().size() > 1 )
            {
                // S + s, ... = S, ... ,S, s, ...
                const size_t nsizes = this->coords().size() + object.sizes().size();
                kvs::Real32* psizes = sizes.allocate( nsizes );
                if ( psizes != NULL )
                {
                    const kvs::Real32 size = this->size();
                    for ( size_t i = 0; i < this->coords().size(); i++ )
                    {
                        *(psizes++) = size;
                    }
                    memcpy( psizes, object.sizes().pointer(), object.sizes().byteSize() );
                }
            }
            else
            {
                const kvs::Real32 size1 = this->size();
                const kvs::Real32 size2 = object.size();
                if ( size1 == size2 )
                {
                    // S + S = S
                    const size_t nsizes = 1;
                    kvs::Real32* psizes = sizes.allocate( nsizes );
                    if ( psizes != NULL )
                    {
                        *(psizes++) = size1;
                    }
                }
                else
                {
                    // S + S = S, ... , S, ...
                    const size_t nsizes = this->coords().size() + object.coords().size();
                    kvs::Real32* psizes = sizes.allocate( nsizes );
                    if ( psizes != NULL )
                    {
                        for ( size_t i = 0; i < this->coords().size(); i++ )
                        {
                            *(psizes++) = size1;
                        }
                        for ( size_t i = 0; i < object.coords().size(); i++ )
                        {
                            *(psizes++) = size2;
                        }
                    }
                }
            }
        }
        this->setSizes( sizes );
    }

    return( *this );
}

std::ostream& operator << ( std::ostream& os, const PointObject& object )
{
    os << "Object type:  " << "point object" << std::endl;
#ifdef KVS_COMPILER_VC
#if KVS_COMPILER_VERSION_LESS_OR_EQUAL( 8, 0 )
    // @TODO Cannot instance the object that is a abstract class here (error:C2259).
#endif
#else
    os << static_cast<const kvs::GeometryObjectBase&>( object ) << std::endl;
#endif
    os << "Number of sizes:  " << object.nsizes();

    return( os );
}

void PointObject::clear( void )
{
    BaseClass::clear();
    m_sizes.deallocate();
}

void PointObject::setSizes( const kvs::ValueArray<kvs::Real32>& sizes )
{
    m_sizes = sizes;
}

void PointObject::setSize( const kvs::Real32 size )
{
    m_sizes.allocate( 1 );
    m_sizes[0] = size;
}

const PointObject::BaseClass::GeometryType PointObject::geometryType( void ) const
{
    return( BaseClass::Point );
}

const size_t PointObject::nsizes( void ) const
{
    return( m_sizes.size() );
}

const kvs::Real32 PointObject::size( const size_t index ) const
{
    return( m_sizes[index] );
}

const kvs::ValueArray<kvs::Real32>& PointObject::sizes( void ) const
{
    return( m_sizes );
}

} // end of namespace kvs
