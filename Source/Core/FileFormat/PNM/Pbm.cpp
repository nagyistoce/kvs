/****************************************************************************/
/**
 *  @file Pbm.cpp
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
#include "Pbm.h"
#include <string>
#include <iostream>
#include <fstream>
#include <kvs/Message>
#include <kvs/File>


namespace kvs
{

bool Pbm::CheckFileExtension( const std::string& filename )
{
    const kvs::File file( filename );
    if ( file.extension() == "pbm" || file.extension() == "PBM" )
    {
        return true;
    }

    return false;
}

bool Pbm::CheckFileFormat( const std::string& filename )
{
    // Open the file.
    std::ifstream ifs( filename.c_str(), std::ios::binary | std::ios::in );
    if( !ifs.is_open() )
    {
        kvsMessageError( "Cannot open %s.", filename.c_str() );
        return false;
    }

    // Read header information.
    kvs::pnm::Header header( ifs );
    return header.isP1() || header.isP4();
}

/*==========================================================================*/
/**
 *  Constructor.
 */
/*==========================================================================*/
Pbm::Pbm()
{
}

/*==========================================================================*/
/**
 *  Constructor.
 *  @param width  [in] width
 *  @param height [in] height
 *  @param data   [in] pixel data
 */
/*==========================================================================*/
Pbm::Pbm( const size_t width, const size_t height, const kvs::BitArray& data ):
    m_width( width ),
    m_height( height ),
    m_data( data )
{
    this->set_header();
}

/*==========================================================================*/
/**
 *  Constructor.
 *  @param filename [in] PBM image filename
 */
/*==========================================================================*/
Pbm::Pbm( const std::string& filename )
{
    this->read( filename );
}

/*==========================================================================*/
/**
 *  Returns the header information.
 *  @return header information
 */
/*==========================================================================*/
const Pbm::Header& Pbm::header() const
{
    return m_header;
}

/*==========================================================================*/
/**
 *  Returns the image width.
 *  @return image width
 */
/*==========================================================================*/
size_t Pbm::width() const
{
    return m_width;
}

/*==========================================================================*/
/**
 *  Returns the image height.
 *  @return image height
 */
/*==========================================================================*/
size_t Pbm::height() const
{
    return m_height;
}

/*==========================================================================*/
/**
 *  Returns the pixel data.
 *  @param  pixel data (bit array)
 */
/*==========================================================================*/
const kvs::BitArray& Pbm::data() const
{
    return m_data;
}

void Pbm::print( std::ostream& os, const kvs::Indent& indent ) const
{
    os << indent << "Filename : " << BaseClass::filename() << std::endl;
    m_header.print( os, indent );
}

/*==========================================================================*/
/**
 *  Read PBM image.
 *  @param filename [in] filename
 *  @return true, if the reading process is done successfully
 */
/*==========================================================================*/
bool Pbm::read( const std::string& filename )
{
    BaseClass::setFilename( filename );
    BaseClass::setSuccess( true );

    // Open the file.
    std::ifstream ifs( filename.c_str(), std::ios::binary | std::ios::in );
    if( !ifs.is_open() )
    {
        kvsMessageError( "Cannot open %s.", filename.c_str() );
        BaseClass::setSuccess( false );
        return false;
    }

    // Read header information.
    m_header.read( ifs );

    // Get the image information.
    m_width   = m_header.width();
    m_height  = m_header.height();

    // Allocate the pixel data.
    const size_t npixels = m_width * m_height;
    m_data.allocate( npixels );

    // Ascii data.
    if ( m_header.isP1() )
    {
        for ( size_t i = 0; i < npixels; i++ )
        {
            size_t v;
            ifs >> v;

            if ( v == 1 ) m_data.set(i);
            else          m_data.reset(i);
        }
    }
    // Binary data.
    else if ( m_header.isP4() )
    {
        ifs.read( reinterpret_cast<char*>( m_data.data() ), m_header.size() );
    }
    else
    {
        kvsMessageError( "%s is not PGM format.", filename.c_str() );
        ifs.close();

        BaseClass::setSuccess( false );
        return false;
    }

    ifs.close();

    return true;
}

/*==========================================================================*/
/**
 *  Write PBM image.
 *  @param filename [in] filename
 *  @return true, if the writing process is done successfully
 */
/*==========================================================================*/
bool Pbm::write( const std::string& filename )
{
    BaseClass::setFilename( filename );
    BaseClass::setSuccess( true );

    // Open the file.
    std::ofstream ofs( filename.c_str(), std::ios::binary | std::ios::out | std::ios::trunc );
    if( !ofs.is_open() )
    {
        kvsMessageError( "Cannot open %s.", filename.c_str() );
        BaseClass::setSuccess( false );
        return false;
    }

    // Write header information.
    this->set_header();
    m_header.write( ofs );

    ofs.write( reinterpret_cast<char*>( m_data.data() ), m_header.size() );
    ofs.close();

    return true;
}

/*===========================================================================*/
/**
 *  @brief  Set header information.
 */
/*===========================================================================*/
void Pbm::set_header()
{
    const std::string format = "P4";
    m_header.set( format, m_width, m_height );
}

} // end of namespace kvs
