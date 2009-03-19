/****************************************************************************/
/**
 *  @file HttpConnector.h
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
#ifndef KVS_CORE_HTTP_CONNECTOR_H_INCLUDE
#define KVS_CORE_HTTP_CONNECTOR_H_INCLUDE

#include "TCPSocket.h"
#include "Url.h"
#include "SocketTimer.h"
#include <iostream>
#include <fstream>


namespace kvs
{

/*==========================================================================*/
/**
 *  HTTP connector class.
 */
/*==========================================================================*/
class HttpConnector
{
protected:

    kvs::TCPSocket m_connector; ///< TCP socket connector
    std::string    m_hostname;  ///< hostname
    int            m_port;      ///< port number

public:

    HttpConnector( void );

    HttpConnector( const kvs::Url& url, const kvs::SocketTimer* timeout = 0 );

    virtual ~HttpConnector( void );

public:

    bool connect( const kvs::Url& url, const kvs::SocketTimer* timeout = 0 );

    void close( void );

    bool get( const std::string& path, const std::string& filename );

    bool get( const std::string& path, std::ostream& output_stream );
};

} // end of namespace kvs

#endif // KVS_CORE_HTTP_CONNECTOR_H_INCLUDE
