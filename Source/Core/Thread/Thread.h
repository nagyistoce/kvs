/****************************************************************************/
/**
 *  @file Thread.h
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
#ifndef KVS__THREAD_H_INCLUDE
#define KVS__THREAD_H_INCLUDE

#include <kvs/Platform>

#if defined ( KVS_PLATFORM_WINDOWS )
#include <windows.h>
#include <process.h>
#else
#include <pthread.h>
#endif


namespace kvs
{

/*==========================================================================*/
/**
 *  Thread class.
 */
/*==========================================================================*/
class Thread
{
public:

#if defined ( KVS_PLATFORM_WINDOWS )
    typedef HANDLE Handler;
    typedef unsigned ( __stdcall * WinRoutine )( void* );
#else
    typedef pthread_t Handler;
#endif
    typedef void* ( *Routine )( void* );

protected:

    bool m_is_running; ///< thread running flag
    Handler m_handler; ///< handler
    Routine m_routine; ///< routine (thread function)

public:

    Thread();
    Thread( Routine routine );
    virtual ~Thread();

    virtual void run() = 0;

    Handler& handler();
    const Handler& handler() const;
    bool isRunning() const;
    bool start();
    bool wait();
    void quit();

    static void sleep( int sec );
    static void msleep( int msec );
    static void usleep( int usec );

protected:

    bool create_thread( Routine routine, void* arg );
    void delete_thread();
};

} // end of namespace kvs

#endif // KVS__THREAD_H_INCLUDE
