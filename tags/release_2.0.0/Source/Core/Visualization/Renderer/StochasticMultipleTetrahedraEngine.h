/*****************************************************************************/
/**
 *  @file   StochasticMultipleTetrahedraEngine.h
 *  @author Jun Nishimura
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
#ifndef KVS__STOCHASTIC_MULTIPLE_TETRAHEDRA_ENGINE_H_INCLUDE
#define KVS__STOCHASTIC_MULTIPLE_TETRAHEDRA_ENGINE_H_INCLUDE

#include "StochasticRenderingEngine.h"
#include "StochasticTetrahedraEngine.h"
#include <kvs/UnstructuredVolumeObject>
#include <kvs/TransferFunction>
#include <kvs/ProgramObject>
#include <kvs/GeometryShader>
#include <kvs/VertexBufferObject>
#include <kvs/IndexBufferObject>
#include <kvs/PreIntegrationTable>


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Stochastic rendering engine class for unstructured volume object.
 */
/*===========================================================================*/
class StochasticMultipleTetrahedraEngine : public kvs::StochasticTetrahedraEngine
{
    friend class StochasticRendererBase;
    friend class StochasticMultipleTetrahedraRenderer;

public:

    typedef kvs::StochasticTetrahedraEngine BaseClass;

protected:

    const kvs::UnstructuredVolumeObject* m_ref_volume2; ///< pointer to the 2nd volume data (reference only)
    kvs::TransferFunction m_tfunc2; ///< transfer function for the 2nd volume data
    kvs::VertexBufferObject m_vbo2; ///< buffer object for storing the indices, coords, values, and normals of the 2nd volume data
    kvs::IndexBufferObject m_ibo2; ///< buffer object for stroing the connections of the 2nd volume data
    size_t m_loc_identifier2; ///< location identifier for the 2nd volume data
    size_t m_loc_values2; ///< location identifier of values for the volume data
    kvs::PreIntegrationTable m_table2; ///< pre-integration table for the 2nd volume data
    kvs::ProgramObject m_shader_program2; ///< GLSL shader program for the 2nd volume data
    kvs::Texture2D m_extra_texture;

public:

    StochasticMultipleTetrahedraEngine();
    StochasticMultipleTetrahedraEngine(
        const kvs::UnstructuredVolumeObject* volume1,
        const kvs::UnstructuredVolumeObject* volume2 );

    void initialize();
    void setTransferFunction( const kvs::TransferFunction& tfunc, const size_t index );
    const kvs::TransferFunction& transferFunction( const size_t index ) const;
    kvs::TransferFunction& transferFunction( const size_t index );
    void attachObjects( const kvs::ObjectBase* object1, const kvs::ObjectBase* object2 );
    void attachObject( const kvs::ObjectBase* object, const size_t index );

protected:

    void create_preintegration_table();
    template <typename T>
    void create_vertexbuffer_from_volume_of( const size_t index );
    void setup_shader_of( const size_t index );
    void initialize_shader();
    void initialize_shader_of( const size_t index );
    void create_vertex_buffer();
    void download_vertex_buffer();
    void draw_vertex_buffer( const float modelview_matrix[16] );
    void set_extra_texture( const kvs::Texture2D& extra_texture );
};

} // end of namespace kvs

#endif // KVS__STOCHASTIC_MULTIPLE_TETRAHEDRA_ENGINE_H_INCLUDE