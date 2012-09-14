/*****************************************************************************/
/**
 *  @file   GriddedBinaryDataFile.h
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
#ifndef KVS__GRADS__GRIDDED_BINARY_DATA_FILE_H_INCLUDE
#define KVS__GRADS__GRIDDED_BINARY_DATA_FILE_H_INCLUDE

#include <string>
#include <kvs/ValueArray>
#include <kvs/Type>


namespace kvs
{

namespace grads
{

/*===========================================================================*/
/**
 *  @brief  GriddedBinaryDataFile class.
 */
/*===========================================================================*/
class GriddedBinaryDataFile
{
private:

    bool m_sequential; ///< sequential data or not
    bool m_big_endian; ///< big endian data or not
    std::string m_filename; ///< data filename
    mutable kvs::ValueArray<kvs::Real32> m_values; ///< data values

public:

    GriddedBinaryDataFile();

public:

    void setSequential( const bool sequential );
    void setBigEndian( const bool big_endian );
    void setFilename( const std::string& filename );
    const std::string& filename() const;
    const kvs::ValueArray<kvs::Real32>& values() const;
    bool load() const;
    void free() const;
};

} // end of namespace grads

} // end of namespace kvs

#endif // KVS__GRADS__GRIDDED_BINARY_DATA_FILE_H_INCLUDE
