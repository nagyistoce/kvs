/****************************************************************************/
/**
 *  @file VersionChecker.h
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
#ifndef KVS_KVSCHECK_VERSION_CHECKER_H_INCLUDE
#define KVS_KVSCHECK_VERSION_CHECKER_H_INCLUDE

#include <string>
#include <iostream>


namespace kvscheck
{

/*==========================================================================*/
/**
 *  KVS version checker class.
 */
/*==========================================================================*/
class VersionChecker
{
protected:

    std::string m_name; ///< KVS version name

public:

    VersionChecker( void );

public:

    const std::string& name( void ) const;

    friend std::ostream& operator << ( std::ostream& os, const VersionChecker& checker );
};

} // end of namespace kvscheck

#endif // KVS_KVSCHECK_VERSION_CHECKER_H_INCLUDE
