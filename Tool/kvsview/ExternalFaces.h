/*****************************************************************************/
/**
 *  @file   ExternalFaces.h
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
#ifndef KVSVIEW__EXTERNAL_FACES_H_INCLUDE
#define KVSVIEW__EXTERNAL_FACES_H_INCLUDE

#include <string>
#include <kvs/Type>
#include <kvs/CommandLine>
#include <kvs/TransferFunction>
#include "Argument.h"


namespace kvsview
{

namespace ExternalFaces
{

const std::string CommandName("ExternalFaces");
const std::string Description("Extract external faces of the volume data. (optional)");

/*===========================================================================*/
/**
 *  Argument class.
 */
/*===========================================================================*/
class Argument : public kvsview::Argument::Common
{
public:

    Argument( int argc, char** argv );

public:

    const kvs::UInt8 opacity( void );

    const kvs::TransferFunction transferFunction( void );
};

/*===========================================================================*/
/**
 *  Main class for a fld2kvsml.
 */
/*===========================================================================*/
class Main
{
protected:

    int         m_argc;         ///< argument count
    char**      m_argv;         ///< argument values
    std::string m_input_name;   ///< input filename
    std::string m_output_name;  ///< output filename

public:

    Main( int argc, char** argv );

public:

    const bool exec( void );
};

} // end of namespace ExternalFaces

} // end of namespace kvsview

#endif // KVSVIEW__EXTERNAL_FACES_H_INCLUDE
