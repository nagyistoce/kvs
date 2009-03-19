/*****************************************************************************/
/**
 *  @file   ObjectInformation.h
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
#ifndef KVSVIEW__OBJECT_INFORMATION_H_INCLUDE
#define KVSVIEW__OBJECT_INFORMATION_H_INCLUDE

#include <iostream>
#include <kvs/ObjectBase>


namespace kvsview
{

/*===========================================================================*/
/**
 *  Displaying the object information.
 */
/*===========================================================================*/
class ObjectInformation
{
    const kvs::ObjectBase* m_object; // pointer to the object

    ObjectInformation( void );

public:

    explicit ObjectInformation( const kvs::ObjectBase* object );

    friend std::ostream& operator << ( std::ostream& os, const ObjectInformation& info );
};

} // end of namespace kvsview

#endif // KVSVIEW__OBJECT_INFORMATION_H_INCLUDE
