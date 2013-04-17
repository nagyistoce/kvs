/****************************************************************************/
/**
 *  @file Texture1D.h
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
#ifndef KVS__TEXTURE_1D_H_INCLUDE
#define KVS__TEXTURE_1D_H_INCLUDE

#include <kvs/Texture>


namespace kvs
{

/*==========================================================================*/
/**
 *  1D texture class.
 */
/*==========================================================================*/
class Texture1D : public kvs::Texture
{
public:

    typedef kvs::Texture BaseClass;

private:

    bool m_is_downloaded; ///< if true, the texture is downloaded

public:

    Texture1D();
    virtual ~Texture1D();

    bool isDownloaded() const;

    void create( const size_t width, const void* data = NULL );
    void release();
    void download( const size_t width, const void* data, const size_t offset = 0 );
};

} // end of namespace kvs

#endif // KVS__TEXTURE_1D_H_INCLUDE