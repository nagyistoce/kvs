/*****************************************************************************/
/**
 *  @file   ResizeEventListener.h
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
#ifndef KVS__RESIZE_EVENT_LISTENER_H_INCLUDE
#define KVS__RESIZE_EVENT_LISTENER_H_INCLUDE

#include <kvs/EventListener>


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  ResizeEventListener class.
 */
/*===========================================================================*/
class ResizeEventListener : public kvs::EventListener
{
public:

    ResizeEventListener( void );

    virtual ~ResizeEventListener( void );

public:

    virtual void update( int width, int height ) = 0;

private:

    void onEvent( kvs::EventBase* event );
};

} // end of namespace kvs

#endif // KVS__RESIZE_EVENT_LISTENER_H_INCLUDE
