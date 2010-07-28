/****************************************************************************/
/**
 *  @file Attribute.h
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
#ifndef KVS__DCM_ATTRIBUTE_H_INCLUDE
#define KVS__DCM_ATTRIBUTE_H_INCLUDE

#include <fstream>
#include <string>


namespace kvs
{

namespace dcm
{

/*===========================================================================*/
/**
 *  @brief  DICOM attribute class.
 */
/*===========================================================================*/
class Attribute
{
protected:

    bool m_part10; ///< part10 flag
    bool m_swap;   ///< swap flag

public:

    Attribute( void );

    virtual ~Attribute( void );

public:

    const bool part10( void ) const;

    const bool swap( void ) const;

public:

    Attribute& operator = ( const Attribute& a );

public:

    bool check( std::ifstream& ifs );
};

} // end of namespace dcm

} // end of namespace kvs

#endif // KVS__DCM_ATTRIBUTE_H_INCLUDE