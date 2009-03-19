/****************************************************************************/
/**
 *  @file File.h
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
#ifndef KVS_CORE_FILE_H_INCLUDE
#define KVS_CORE_FILE_H_INCLUDE

#include <cstdio>
#include <cstdlib>
#include <climits>
#include <string>

#include "ClassName.h"


namespace kvs
{

/*==========================================================================*/
/**
 *  File class
 */
/*==========================================================================*/
class File
{
    kvsClassName( File );

protected:

    std::string m_file_path; ///< file path (ex. "/tmp/abc/xyz.tar.gz")
    std::string m_path_name; ///< path name (ex. "/tmp/abc")
    std::string m_file_name; ///< file name (ex. "xyz.tar.gz")
    std::string m_base_name; ///< base name (ex. "xyz")
    std::string m_extension; ///< complete extension (ex. "tar.gz")

public:

    File( void );

    File( const std::string& file_path );

    File( const File& file );

    virtual ~File( void );

public:

    const bool operator <( const File& file ) const;

    const bool operator ==( const File& file ) const;

public:

    const std::string filePath( bool absolute = false ) const;

    const std::string pathName( bool absolute = false ) const;

    const std::string fileName( void ) const;

    const std::string baseName( void ) const;

    const std::string extension( bool complete = false ) const;

    const size_t byteSize( void ) const;

    const bool isFile( void ) const;

    const bool isExisted( void ) const;

    const bool parse( const std::string& file_path );

public:

    static const std::string Separator( void );
};

} // end of namespace kvs

#endif // KVS_CORE_FILE_H_INCLUDE
