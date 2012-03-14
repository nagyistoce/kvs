/* DONT'T EDIT THIS FILE.
 * THIS IS GENERATED BY "Configure/configure_shader.py".
 */
#ifndef KVS__GLEW__GLSL__RayCastingRenderer_H_INCLUDE
#define KVS__GLEW__GLSL__RayCastingRenderer_H_INCLUDE

#include <string>

namespace kvs { namespace glew { namespace glsl {

namespace RayCastingRenderer
{

namespace Vertex
{

const std::string bounding_cube =
    "varying float depth;\n"
    "\n"
    "void main( void )\n"
    "{\n"
    "    gl_FrontColor = gl_Vertex;\n"
    "    gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;\n"
    "\n"
    "    depth = ( 1.0 + gl_Position.z / gl_Position.w ) * 0.5;\n"
    "}\n"
;

const std::string ray_caster =
    "void main( void )\n"
    "{\n"
    "    gl_FrontColor = gl_Color;\n"
    "    gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;\n"
    "}\n"
;

} // end of namespace Vertex

namespace Geometry
{

} // end of namespace Geometry

namespace Fragment
{

const std::string bounding_cube =
    "varying float depth;\n"
    "\n"
    "void main( void )\n"
    "{\n"
    "    gl_FragColor.rgb = gl_Color.rgb;\n"
    "    gl_FragColor.a = depth;\n"
    "}\n"
;

const std::string ray_caster =
    "struct Shading\n"
    "{\n"
    "    float Ka; // ambient\n"
    "    float Kd; // diffuse\n"
    "    float Ks; // specular\n"
    "    float S;  // shininess\n"
    "};\n"
    "\n"
    "vec3 ShadingNone( in Shading shading, in vec3 color )\n"
    "{\n"
    "    return( color );\n"
    "}\n"
    "\n"
    "vec3 ShadingLambert( in Shading shading, in vec3 color, in vec3 L, in vec3 N )\n"
    "{\n"
    "#if defined( ENABLE_TWO_SIDE_LIGHTING )\n"
    "    float dd = abs( dot( N, L ) );\n"
    "#else\n"
    "    float dd = max( dot( N, L ), 0.0 );\n"
    "#endif\n"
    "\n"
    "    float Ia = shading.Ka;\n"
    "    float Id = shading.Kd * dd;\n"
    "\n"
    "    return( color * ( Ia + Id ) );\n"
    "}\n"
    "\n"
    "vec3 ShadingPhong( in Shading shading, in vec3 color, in vec3 L, in vec3 N, in vec3 V )\n"
    "{\n"
    "    vec3 R = reflect( -L, N );\n"
    "#if defined( ENABLE_TWO_SIDE_LIGHTING )\n"
    "    float dd = abs( dot( N, L ) );\n"
    "    float ds = pow( abs( dot( R, V ) ), shading.S );\n"
    "#else\n"
    "    float dd = max( dot( N, L ), 0.0 );\n"
    "    float ds = pow( max( dot( R, V ), 0.0 ), shading.S );\n"
    "#endif\n"
    "    if ( dd <= 0.0 ) ds = 0.0;\n"
    "\n"
    "    float Ia = shading.Ka;\n"
    "    float Id = shading.Kd * dd;\n"
    "    float Is = shading.Ks * ds;\n"
    "\n"
    "    return( color * ( Ia + Id ) + Is );\n"
    "}\n"
    "\n"
    "vec3 ShadingBlinnPhong( in Shading shading, in vec3 color, in vec3 L, in vec3 N, in vec3 V )\n"
    "{\n"
    "    vec3 H = normalize( L + V );\n"
    "#if defined( ENABLE_TWO_SIDE_LIGHTING )\n"
    "    float dd = abs( dot( N, L ) );\n"
    "    float ds = pow( abs( dot( H, N ) ), shading.S );\n"
    "#else\n"
    "    float dd = max( dot( N, L ), 0.0 );\n"
    "    float ds = pow( max( dot( H, N ), 0.0 ), shading.S );\n"
    "#endif\n"
    "    if ( dd <= 0.0 ) ds = 0.0;\n"
    "\n"
    "    float Ia = shading.Ka;\n"
    "    float Id = shading.Kd * dd;\n"
    "    float Is = shading.Ks * ds;\n"
    "\n"
    "    return( color * ( Ia + Id ) + Is );\n"
    "}\n"
    "struct Volume\n"
    "{\n"
    "    vec3 resolution; // volume resolution\n"
    "    vec3 resolution_ratio; // ratio of the resolution (256x256x128 => 1:1:0.5)\n"
    "    vec3 resolution_reciprocal; // reciprocal number of the resolution\n"
    "    float min_range; // min. range of the value\n"
    "    float max_range; // max. range of the value\n"
    "    sampler3D data; // volume data (scalar field)\n"
    "};\n"
    "struct TransferFunction\n"
    "{\n"
    "    sampler1D data; // transfer function data\n"
    "    float min_value; // min. scalar value\n"
    "    float max_value; // max. scalar value\n"
    "};\n"
    "\n"
    "uniform sampler2D        entry_points;      // entry points (front face)\n"
    "uniform sampler2D        exit_points;       // exit points (back face)\n"
    "uniform vec3             offset;            // offset width for the gradient\n"
    "uniform float            dt;                // sampling step\n"
    "uniform float            opaque;            // opaque value\n"
    "uniform vec3             light_position;    // light position in the object coordinate\n"
    "uniform vec3             camera_position;   // camera position in the object coordinate\n"
    "uniform Volume           volume;            // volume data\n"
    "uniform Shading          shading;           // shading parameter\n"
    "uniform TransferFunction transfer_function; // 1D transfer function\n"
    "uniform sampler2D        jittering_texture; // texture for jittering\n"
    "uniform float            width;             // screen width\n"
    "uniform float            height;            // screen height\n"
    "uniform sampler2D        depth_texture;     // depth texture for depth buffer\n"
    "uniform sampler2D        color_texture;     // color texture for color buffer\n"
    "uniform float            to_zw1;            // scaling parameter: (f*n)/(f-n)\n"
    "uniform float            to_zw2;            // scaling parameter: 0.5*((f+n)/(f-n))+0.5\n"
    "uniform float            to_ze1;            // scaling parameter: 0.5 + 0.5*((f+n)/(f-n))\n"
    "uniform float            to_ze2;            // scaling parameter: (f-n)/(f*n)\n"
    "\n"
    "\n"
    "vec3 estimateGradient( in sampler3D v, in vec3 p, in vec3 o )\n"
    "{\n"
    "    float s0 = texture3D( v, p + vec3( o.x, 0.0, 0.0 ) ).w;\n"
    "    float s1 = texture3D( v, p + vec3( 0.0, o.y, 0.0 ) ).w;\n"
    "    float s2 = texture3D( v, p + vec3( 0.0, 0.0, o.z ) ).w;\n"
    "    float s3 = texture3D( v, p - vec3( o.x, 0.0, 0.0 ) ).w;\n"
    "    float s4 = texture3D( v, p - vec3( 0.0, o.y, 0.0 ) ).w;\n"
    "    float s5 = texture3D( v, p - vec3( 0.0, 0.0, o.z ) ).w;\n"
    "\n"
    "    return( vec3( s3 - s0, s4 - s1, s5 - s2 ) );\n"
    "}\n"
    "\n"
    "vec3 estimateGradient8( in sampler3D v, in vec3 p, in vec3 o )\n"
    "{\n"
    "    vec3 g0 = estimateGradient( v, p, o );\n"
    "    vec3 g1 = estimateGradient( v, p + vec3( -o.x, -o.y, -o.z ), o );\n"
    "    vec3 g2 = estimateGradient( v, p + vec3(  o.x,  o.y,  o.z ), o );\n"
    "    vec3 g3 = estimateGradient( v, p + vec3( -o.x,  o.y, -o.z ), o );\n"
    "    vec3 g4 = estimateGradient( v, p + vec3(  o.x, -o.y,  o.z ), o );\n"
    "    vec3 g5 = estimateGradient( v, p + vec3( -o.x, -o.y,  o.z ), o );\n"
    "    vec3 g6 = estimateGradient( v, p + vec3(  o.x,  o.y, -o.z ), o );\n"
    "    vec3 g7 = estimateGradient( v, p + vec3( -o.x,  o.y,  o.z ), o );\n"
    "    vec3 g8 = estimateGradient( v, p + vec3(  o.x, -o.y, -o.z ), o );\n"
    "    vec3 mix0 = mix( mix( g1, g2, 0.5 ), mix( g3, g4, 0.5 ), 0.5 );\n"
    "    vec3 mix1 = mix( mix( g5, g6, 0.5 ), mix( g7, g8, 0.5 ), 0.5 );\n"
    "\n"
    "    return( mix( g0, mix( mix0, mix1, 0.5 ), 0.75 ) );\n"
    "}\n"
    "\n"
    "float ray_depth( in float t, in float entry_depth, in float exit_depth )\n"
    "{\n"
    "    float zw_front = entry_depth;\n"
    "    float ze_front = 1.0 / ((zw_front - to_ze1)*to_ze2);\n"
    "\n"
    "    float zw_back = exit_depth;\n"
    "    float ze_back = 1.0 / ((zw_back - to_ze1)*to_ze2);\n"
    "\n"
    "    float ze_current = ze_front + t * (ze_back - ze_front);\n"
    "    float zw_current = (1.0/ze_current)*to_zw1 + to_zw2;\n"
    "\n"
    "    return zw_current;\n"
    "}\n"
    "\n"
    "void main( void )\n"
    "{\n"
    "    // Entry and exit point.\n"
    "    vec2 index = vec2( gl_FragCoord.x / width, gl_FragCoord.y / height );\n"
    "    vec3 entry_point = ( volume.resolution - vec3(1.0) ) * texture2D( entry_points, index ).xyz;\n"
    "    vec3 exit_point = ( volume.resolution - vec3(1.0) ) * texture2D( exit_points, index ).xyz;\n"
    "    if ( entry_point == exit_point ) { discard; } // out of cube\n"
    "\n"
    "    // Ray direction.\n"
    "    vec3 direction = dt * normalize( exit_point - entry_point );\n"
    "\n"
    "    // Stochastic jittering.\n"
    "#if defined( ENABLE_JITTERING )\n"
    "    entry_point = entry_point + 0.1 * direction * texture2D( jittering_texture, gl_FragCoord.xy / 32.0 ).x;\n"
    "#endif\n"
    "\n"
    "    // Ray traversal.\n"
    "    float segment = distance( exit_point, entry_point );\n"
    "    int nsteps = int( floor( segment / dt ) );\n"
    "    vec3 position = entry_point;\n"
    "    vec4 dst = vec4( 0.0, 0.0, 0.0, 0.0 );\n"
    "\n"
    "    // Transfer function scale.\n"
    "    float tfunc_scale = 1.0 / ( transfer_function.max_value - transfer_function.min_value );\n"
    "\n"
    "    float entry_depth = texture2D( entry_points, index ).w;\n"
    "    float exit_depth = texture2D( exit_points, index ).w;\n"
    "    float depth0 = texture2D( depth_texture, index ).x;\n"
    "    vec3 color0 = texture2D( color_texture, index ).rgb;\n"
    "    for ( int i = 0; i < nsteps; i++ )\n"
    "    {\n"
    "        // Get the scalar value from the 3D texture.\n"
    "        vec3 volume_index = vec3( position / ( volume.resolution - vec3(1.0) ) );\n"
    "        vec4 value = texture3D( volume.data, volume_index );\n"
    "        float scalar = mix( volume.min_range, volume.max_range, value.w );\n"
    "\n"
    "        // Get the source color from the transfer function.\n"
    "        float tfunc_index = ( scalar - transfer_function.min_value ) * tfunc_scale;\n"
    "        vec4 src = texture1D( transfer_function.data, tfunc_index );\n"
    "        if ( src.a != 0.0 )\n"
    "        {\n"
    "            // Get the normal vector.\n"
    "            vec3 offset_index = vec3( volume.resolution_reciprocal );\n"
    "            vec3 normal = estimateGradient( volume.data, volume_index, offset_index );\n"
    "\n"
    "            vec3 L = normalize( light_position - position );\n"
    "            vec3 N = normalize( gl_NormalMatrix * normal );\n"
    "\n"
    "#if   defined( ENABLE_LAMBERT_SHADING )\n"
    "            src.rgb = ShadingLambert( shading, src.rgb, L, N );\n"
    "\n"
    "#elif defined( ENABLE_PHONG_SHADING )\n"
    "            vec3 V = normalize( camera_position - position );\n"
    "            src.rgb = ShadingPhong( shading, src.rgb, L, N, V );\n"
    "\n"
    "#elif defined( ENABLE_BLINN_PHONG_SHADING )\n"
    "            vec3 V = normalize( camera_position - position );\n"
    "            src.rgb = ShadingBlinnPhong( shading, src.rgb, L, N, V );\n"
    "\n"
    "#else // DISABLE SHADING\n"
    "            src.rgb = ShadingNone( shading, src.rgb );\n"
    "#endif\n"
    "\n"
    "            // Front-to-back composition.\n"
    "            dst.rgb += ( 1.0 - dst.a ) * src.a * src.rgb;\n"
    "            dst.a += ( 1.0 - dst.a ) * src.a;\n"
    "\n"
    "            // Early ray termination.\n"
    "            if ( dst.a > opaque )\n"
    "            {\n"
    "                dst.a = 1.0;\n"
    "                break; // break\n"
    "            }\n"
    "        }\n"
    "\n"
    "        float t = float(i) / float( nsteps - 1 );\n"
    "        float depth = ray_depth( t, entry_depth, exit_depth );\n"
    "        if ( depth > depth0 )\n"
    "        {\n"
    "            dst.rgb += ( 1.0 - dst.a ) * color0.rgb;\n"
    "            dst.a = 1.0;\n"
    "            break;\n"
    "        }\n"
    "\n"
    "        position += direction;\n"
    "    }\n"
    "\n"
    "    gl_FragColor = dst;\n"
    "}\n"
;

} // end of namespace Fragment

} // end of namespace RayCastingRenderer

} } } // end of namespace kvs, glew, glsl

#endif // KVS__GLEW__GLSL__RayCastingRenderer_H_INCLUDE
