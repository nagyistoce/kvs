/****************************************************************************/
/**
 *  @file Xorshift128.h
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright (c) Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/****************************************************************************/
#ifndef KVS__XORSHIFT_128_H_INCLUDE
#define KVS__XORSHIFT_128_H_INCLUDE

#include <kvs/ClassName>
#include <kvs/Type>


namespace kvs
{

/*==========================================================================*/
/**
 *  Xorshift128 class.
 */
/*==========================================================================*/
class Xorshift128
{
    kvsClassName_without_virtual( kvs::Xorshift128 );

private:

    kvs::UInt32 m_x;
    kvs::UInt32 m_y;
    kvs::UInt32 m_z;
    kvs::UInt32 m_w;

public:

    Xorshift128();

public:

    void setSeed( kvs::UInt32 );

public:

    float rand();

    kvs::UInt32 randInteger();

public:

    float operator ()();
};

/*==========================================================================*/
/**
 *  .
 *
 *  @return TODO
 */
/*==========================================================================*/
inline float Xorshift128::rand()
{
    const float t24 = 1.0 / 16777216.0; /* 0.5**24 */
    return t24 * ( this->randInteger() >> 8 );
}

inline kvs::UInt32 Xorshift128::randInteger()
{
    kvs::UInt32 t = ( m_x ^ ( m_x << 11 ) );

    m_x = m_y;
    m_y = m_z;
    m_z = m_w;
    m_w = ( m_w ^ ( m_w >> 19 ) ) ^ ( t ^ ( t >> 8 ) );

    return m_w;
}

/*==========================================================================*/
/**
 *  .
 *
 *  @return TODO
 */
/*==========================================================================*/
inline float Xorshift128::operator ()()
{
    return this->rand();
}

} // end of namespace kvs

#endif // KVS__XORSHIFT_128_H_INCLUDE