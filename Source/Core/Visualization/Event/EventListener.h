/*****************************************************************************/
/**
 *  @file   EventListener.h
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
#ifndef KVS__EVENT_LISTENER_H_INCLUDE
#define KVS__EVENT_LISTENER_H_INCLUDE

#include <kvs/ScreenBase>
#include <kvs/WindowBase>
#include <kvs/EventBase>
#include <kvs/MouseEvent>
#include <kvs/KeyEvent>
#include <kvs/WheelEvent>
#include <kvs/TimeEvent>


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Event listener class.
 */
/*===========================================================================*/
class EventListener
{
private:

    int              m_event_type; ///< event type
    kvs::ScreenBase* m_screen; ///< pointer to the screen
    kvs::WindowBase* m_window; ///< pointer to the window

public:

    EventListener( void );

    virtual ~EventListener( void );

public:

    virtual void onEvent( kvs::EventBase* event = 0 );

public:

    const int eventType( void ) const;

    kvs::ScreenBase* screen( void );

    kvs::WindowBase* window( void );

    void setEventType( int event_type );

    void setScreen( kvs::ScreenBase* screen );

    void setWindow( kvs::WindowBase* window );

public:

    virtual void paintEvent( void );

    virtual void resizeEvent( int width, int height );

    virtual void mousePressEvent( kvs::MouseEvent* event );

    virtual void mouseMoveEvent( kvs::MouseEvent* event );

    virtual void mouseReleaseEvent( kvs::MouseEvent* event );

    virtual void mouseDoubleClickEvent( kvs::MouseEvent* event );

    virtual void wheelEvent( kvs::WheelEvent* event );

    virtual void keyPressEvent( kvs::KeyEvent* event );

    virtual void timerEvent( kvs::TimeEvent* event );
};

} // end of namespace kvs

#endif // KVS__EVENT_LISTENER_H_INCLUDE
