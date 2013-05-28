/****************************************************************************/
/**
 *  @file FileFormatBase.h
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
#ifndef KVS__FILE_FORMAT_BASE_H_INCLUDE
#define KVS__FILE_FORMAT_BASE_H_INCLUDE

#include <string>


namespace kvs
{

/*==========================================================================*/
/**
 *  FileFormatBase.
 */
/*==========================================================================*/
class FileFormatBase
{
private:

    std::string m_filename; ///< Filename.
    bool m_is_success; ///< Whether the reading is success or not.

public:

    FileFormatBase();
    virtual ~FileFormatBase();

    const std::string& filename() const;
    bool isSuccess() const;
    bool isFailure() const;

    virtual bool read( const std::string& filename ) = 0;
    virtual bool write( const std::string& filename ) = 0;

protected:

    void setFilename( const std::string& filename );
    void setSuccess( const bool success );
};

} // end of namespace kvs

#endif // KVS__FILE_FORMAT_BASE_H_INCLUDE