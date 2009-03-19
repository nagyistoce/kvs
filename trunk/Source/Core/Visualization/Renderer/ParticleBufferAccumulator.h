/****************************************************************************/
/**
 *  @file ParticleBufferAccumulator.h
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
#ifndef KVS_CORE_PARTICLE_BUFFER_ACCUMULATOR_H_INCLUDE
#define KVS_CORE_PARTICLE_BUFFER_ACCUMULATOR_H_INCLUDE

#include <kvs/PointObject>
#include <kvs/ParticleBuffer>
#include <kvs/ParticleVolumeRenderer>
#include <kvs/ValueArray>
#include <kvs/ClassName>
#include <vector>


namespace kvs
{

/*==========================================================================*/
/**
 *  Particle buffer accumulator.
 */
/*==========================================================================*/
class ParticleBufferAccumulator : public kvs::ParticleBuffer
{
    kvsClassName( ParticleBufferAccumulator );

public:

    typedef kvs::ParticleBuffer SuperClass;

    typedef std::vector<kvs::PointObject*>            ObjectList;
    typedef std::vector<kvs::ParticleVolumeRenderer*> RendererList;

protected:

    kvs::ValueArray<kvs::UInt8> m_id_buffer; ///< object ID buffer [0,255]

public:

    ParticleBufferAccumulator(
        const size_t width,
        const size_t height,
        const size_t subpixel_level );

    virtual ~ParticleBufferAccumulator( void );

public:

    bool create(
        const size_t width,
        const size_t height,
        const size_t subpixel_level );

    void clean( void );

    void clear( void );

public:

    void accumulate( const size_t id, const kvs::ParticleBuffer* buffer );

    void add( const size_t bindex, const size_t id, const kvs::Real32 depth, const kvs::UInt32 vindex );

    void createImage(
        ObjectList&                   object_list,
        RendererList&                 renderer_list,
        kvs::ValueArray<kvs::UInt8>*  color,
        kvs::ValueArray<kvs::Real32>* depth );
};

} // end of namespace kvs

#endif // KVS_CORE_PARTICLE_BUFFER_ACCUMULATOR_H_INCLUDE
