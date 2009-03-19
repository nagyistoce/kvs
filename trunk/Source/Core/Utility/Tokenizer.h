/****************************************************************************/
/**
 *  @file Tokenizer.h
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
#ifndef KVS_CORE_TOKENIZER_H_INCLUDE
#define KVS_CORE_TOKENIZER_H_INCLUDE

#include <string>


namespace kvs
{

/*==========================================================================*/
/**
 *  Delimit tokens.
 */
/*==========================================================================*/
class Tokenizer
{
protected:

    std::string            m_source;    ///< source std::string
    std::string            m_delimiter; ///< delimiter set
    std::string            m_token;     ///< token
    std::string::size_type m_first;     ///< first position
    std::string::size_type m_last;      ///< last position

public:

    Tokenizer( void );

    Tokenizer( const std::string& source, const std::string& delimiter );

    Tokenizer( const Tokenizer& t );

public:

    Tokenizer& operator = ( const Tokenizer& t );

    Tokenizer& operator = ( const std::string& source );

public:

    const bool isLast( void ) const;

    const std::string token( void );

protected:

    void get_token( void );
};

} // end of namespace kvs

#endif // KVS_CORE_TOKENIZER_H_INCLUDE
