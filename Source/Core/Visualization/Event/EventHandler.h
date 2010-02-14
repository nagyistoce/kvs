/*****************************************************************************/
/**
 *  @file   EventHandler.h
 *  @author Naohisa Sakamoto
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright 2007 Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/*****************************************************************************/
#ifndef KVS__EVENT_HANDLER_H_INCLUDE
#define KVS__EVENT_HANDLER_H_INCLUDE

#include <vector>
#include "EventListener.h"


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Event handler class.
 */
/*===========================================================================*/
class EventHandler
{
protected:

    std::vector<kvs::EventListener*> m_listeners; ///< list of the event listener

public:

    EventHandler( void );

    virtual ~EventHandler( void );

public:

    void attach( kvs::EventListener* listener );

    void detach( kvs::EventListener* listener );

    void clear( void );

    void notify( kvs::EventBase* event = NULL );
};

} // end of namespace kvs

#endif // KVS__EVENT_HANDLER_H_INCLUDE