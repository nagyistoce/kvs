/****************************************************************************/
/**
 *  @file FilterBase.h
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
#ifndef KVS_CORE_FILTER_BASE_H_INCLUDE
#define KVS_CORE_FILTER_BASE_H_INCLUDE

#include <kvs/ObjectBase>
#include <kvs/ClassName>
#include <kvs/Module>


namespace kvs
{

/*==========================================================================*/
/**
 *  Filter base class.
 */
/*==========================================================================*/
class FilterBase
{
    kvsClassName( FilterBase );

    kvsModuleBase;

protected:

    bool m_good; ///< good

public:

    FilterBase( void );

    virtual ~FilterBase( void );

public:

    virtual kvs::ObjectBase* exec( const kvs::ObjectBase* object ) = 0;

public:

    const bool good( void ) const;

    const bool fail( void ) const;
};

} // end of namespace kvs

#endif // KVS_CORE_FILTER_BASE_H_INCLUDE
