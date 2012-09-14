/*****************************************************************************/
/**
 *  @file   Undef.h
 *  @author Naohisa Sakamoto
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright (c) Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/*****************************************************************************/
#ifndef KVS__GRADS__UNDEF_H_INCLUDE
#define KVS__GRADS__UNDEF_H_INCLUDE

#include <string>
#include <fstream>
#include <kvs/Type>


namespace kvs
{

namespace grads
{

/*===========================================================================*/
/**
 *  @brief  UNDEF entry.
 */
/*===========================================================================*/
struct Undef
{
    kvs::Real32 value; ///< undefined value

    bool read( std::string line, std::ifstream& ifs );
};

} // end of namespace grads

} // end of namespace kvs

#endif // KVS__GRADS__UNDEF_H_INCLUDE
