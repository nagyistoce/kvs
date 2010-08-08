/****************************************************************************/
/**
 *  @file FileFormatBase.cpp
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
#include "FileFormatBase.h"


namespace kvs
{

/*==========================================================================*/
/**
 *  Constructs a new empty FileFormatBase.
 */
/*==========================================================================*/
FileFormatBase::FileFormatBase( void )
    : m_filename("")
    , m_is_success( false )
{
}

/*==========================================================================*/
/**
 *  Destroys the FileFormatBase.
 */
/*==========================================================================*/
FileFormatBase::~FileFormatBase( void )
{
}

const std::string& FileFormatBase::filename( void ) const
{
    return( m_filename );
}

/*==========================================================================*/
/**
 *  Returns true if the reading is success; otherwise returns false.
 *
 *  @return Whether the reading is success or not.
 */
/*==========================================================================*/
const bool FileFormatBase::isSuccess( void ) const
{
    return( m_is_success );
}

/*==========================================================================*/
/**
 *  Returns true if the reading is failure; otherwise returns false.
 *
 *  @return Whether the reading is failure or not.
 */
/*==========================================================================*/
const bool FileFormatBase::isFailure( void ) const
{
    return( !m_is_success );
}

} // end of namespace kvs