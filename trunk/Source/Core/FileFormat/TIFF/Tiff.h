/****************************************************************************/
/**
 *  @file Tiff.h
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
#ifndef KVS_CORE_TIFF_TIFF_H_INCLUDE
#define KVS_CORE_TIFF_TIFF_H_INCLUDE

#include "../FileFormatBase.h"
#include <kvs/ClassName>
#include <kvs/Type>
#include <kvs/Message>
#include <kvs/AnyValueArray>
#include "Header.h"
#include "ImageFileDirectory.h"


namespace kvs
{

class Tiff : public kvs::FileFormatBase
{
    kvsClassName( Tiff );

public:

    typedef kvs::FileFormatBase BaseClass;

    typedef kvs::tiff::Header             Header;
    typedef kvs::tiff::ImageFileDirectory IFD;

public:

    enum ColorMode
    {
        UnknownColorMode = 0,
        Gray8            = 1,
        Gray16           = 2,
        Color24          = 3
    };

private:

    Tiff::Header       m_header;          ///< header information
    Tiff::IFD          m_ifd;             ///< 0-th IFD

    size_t             m_width;           ///< width
    size_t             m_height;          ///< height
    size_t             m_bits_per_sample; ///< bits per channel (sample)
    ColorMode          m_color_mode;      ///< color mode
    kvs::AnyValueArray m_raw_data;        ///< raw data

public:

    Tiff( void );

    Tiff( const std::string& filename );

    virtual ~Tiff( void );

public:

    const Tiff::Header& header( void ) const;

    const Tiff::IFD& ifd( void ) const;

public:

    size_t width( void ) const;

    size_t height( void ) const;

    size_t bitsPerSample( void ) const;

    ColorMode colorMode( void ) const;

    kvs::AnyValueArray rawData( void ) const;

    bool isSupported( void ) const;

public:

    const bool read( const std::string& filename );

private:

    const bool write( const std::string& filename );

private:

    size_t get_width( void ) const;

    size_t get_height( void ) const;

    size_t get_bits_per_sample( void ) const;

    size_t get_samples_per_pixel( void ) const;

    size_t get_photometirc_interpretation( void ) const;

    size_t get_rows_per_strip( void ) const;

    size_t get_compression_mode( void ) const;

    kvs::AnyValueArray get_strip_offsets( void ) const;

    kvs::AnyValueArray get_strip_bytes( void ) const;

    ColorMode get_color_mode( void ) const;

    kvs::AnyValueArray get_raw_data( std::ifstream& ifs ) const;

public:

    static const bool CheckFileExtension( const std::string& filename );

    static const bool CheckFileFormat( const std::string& filename );
};

} // end of namespace kvs

#endif // KVS_CORE_TIFF_TIFF_H_INCLUDE
