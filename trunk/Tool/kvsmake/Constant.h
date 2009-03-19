/****************************************************************************/
/**
 *  @file Constant.h
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
#ifndef KVS_KVSMAKE_CONSTANT_H_INCLUDE
#define KVS_KVSMAKE_CONSTANT_H_INCLUDE

#include <cstdlib> // For std::getenv.
#include <string>  // For std::string.

#include <kvs/Compiler>


namespace kvsmake
{

const std::string KVS_DIR( std::getenv( "KVS_DIR" ) );

#if defined ( KVS_COMPILER_VC )
const std::string MakeCommand( "nmake" );
const std::string Makefile   ( "Makefile.vc.kvs" );

const std::string MakefileTemplate ( KVS_DIR + "\\bin\\Makefile.vc.kvs.template" );
const std::string VCProjectTemplate( KVS_DIR + "\\bin\\VCProject.template" );
const std::string QtProjectTemplate( KVS_DIR + "\\bin\\QtProject.template" );

const std::string VCProjectCUDATemplate( KVS_DIR + "\\bin\\VCProjectCUDA.template" );
#else
const std::string MakeCommand( "make" );
const std::string Makefile   ( "Makefile.kvs" );

const std::string MakefileTemplate ( KVS_DIR + "/bin/Makefile.kvs.template" );
const std::string QtProjectTemplate( KVS_DIR + "/bin/QtProject.template" );
#endif

} // end of namespace kvsmake

#endif // KVS_KVSMAKE_CONSTANT_H_INCLUDE
