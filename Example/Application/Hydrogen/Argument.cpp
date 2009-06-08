/*****************************************************************************/
/**
 *  @file   Argument.cpp
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
#include "Argument.h"


/*===========================================================================*/
/**
 *  @brief  Constructs a new Argument class.
 *  @param  argc [in] argument count
 *  @param  argv [in] argument values
 */
/*===========================================================================*/
Argument::Argument( int argc, char** argv ):
    kvs::CommandLine( argc, argv )
{
    add_help_option();
    add_option( "r", "Volume resolution. (default: 64 64 64)", 3, false );
    add_option( "a", "External ascii type for KVSML format. (optional)", 0, false );
    add_option( "b", "External binary type for KVSML format. (optional)", 0, false );
    add_option( "verbose", "Verbose mode. (optional)", 0, false );
    add_value( "Output filename [ *.fld | *.kvsml ]. (default: hydrogen.kvsml)", false );
}
