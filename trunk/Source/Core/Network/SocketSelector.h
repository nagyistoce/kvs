/****************************************************************************/
/**
 *  @file SocketSelector.h
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
#ifndef KVS_CORE_SOCKET_SELECTOR_H_INCLUDE
#define KVS_CORE_SOCKET_SELECTOR_H_INCLUDE

#include "Socket.h"
#include "SocketTimer.h"


namespace kvs
{

/*==========================================================================*/
/**
 *  Socket select class.
 */
/*==========================================================================*/
class SocketSelector
{
protected:

    fd_set m_readable; ///< readable descriptor
    fd_set m_writable; ///< writable descriptor

public:

    SocketSelector( void );

    SocketSelector( const SocketSelector& other );

    virtual ~SocketSelector( void );

public:

    void setReadable( const kvs::Socket::id_type& socket_id );

    void setWritable( const kvs::Socket::id_type& socket_id );

    bool isReadable( const kvs::Socket::id_type& socket_id );

    bool isWritable( const kvs::Socket::id_type& socket_id );

    void clearReadable( const kvs::Socket::id_type& socket_id );

    void clearWritable( const kvs::Socket::id_type& socket_id );

    void clear( void );

    int select( const kvs::SocketTimer& timeout );
};

} // end of namespace kvs

#endif // KVS_CORE_SOCKET_SELECTOR_H_INCLUDE