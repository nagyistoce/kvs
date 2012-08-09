#!/usr/bin/python

import sys
import os

#=============================================================================
#  Utility functions.
#=============================================================================

def Include( filename ):
    file = open( filename, "r" )
    path = os.path.split( filename )[0]
    for line in file:
        if line.startswith("//") or line.startswith("/**") or line.startswith("/*-") or line.startswith("/*=") or line.startswith(" *") or line.startswith(" */"):
            continue
        if line.find("#include") != -1:
            return Include( path + "/" + line.split("\"")[1] )
        print "    \"" + line.replace('\n', '') + "\\n\"\n",
    return 1

def Write( filename ):
    file = open( filename, "r" )
    path = os.path.split( filename )[0]
    param = os.path.splitext( os.path.split( filename )[1] )[0]
    print "const std::string " + param + " ="
    for line in file:
        if line.startswith("//") or line.startswith("/**") or line.startswith("/*-") or line.startswith("/*=") or line.startswith(" *") or line.startswith(" */"):
            continue
        if line.startswith("#include"):
            Include( path + "/" + line.split("\"")[1] )
            continue
        print "    \"" + line.replace('\n', '') + "\\n\"\n",
    print ";\n"

def ShaderList( path, extension ):
    shader_list = []
    for root, dirs, files in os.walk( path ):
        for filename in files:
            if os.path.splitext( filename )[1] == extension:
                shader_list.append( path + "/" + filename )
    return shader_list


#=============================================================================
#  Initialize.
#=============================================================================

source_path = "../Source/SupportGLEW/"

shader_dir_list = []

file = open( source_path + "/KVS_SHADER_DIR_LIST", "r" )
for line in file:
    shader_dir_list.append( source_path + line.replace('\n', '') )


#=============================================================================
#  Write header files.
#=============================================================================

for shader_dir in shader_dir_list:

    vertex_shader_list = ShaderList( shader_dir, ".vert" )
    geometry_shader_list = ShaderList( shader_dir, ".geom" )
    fragment_shader_list = ShaderList( shader_dir, ".frag" )
    dirname = os.path.split( shader_dir )[1]

    sys.stdout = open( shader_dir + "/Shader.h", "w" )
    print "/* DONT'T EDIT THIS FILE."
    print " * THIS IS GENERATED BY \"Configure/configure_shader.py\"."
    print " */"
    print "#ifndef KVS__GLEW__GLSL__" + dirname + "_H_INCLUDE"
    print "#define KVS__GLEW__GLSL__" + dirname + "_H_INCLUDE"
    print ""
    print "#include <string>"
    print ""
    print "namespace kvs { namespace glew { namespace glsl {"
    print ""

    print "namespace " + dirname
    print "{"
    print ""

    print "namespace Vertex"
    print "{"
    print ""
    for filename in vertex_shader_list:
        Write( filename )
    print "} // end of namespace Vertex"
    print ""
    print "namespace Geometry"
    print "{"
    print ""
    for filename in geometry_shader_list:
        Write( filename )
    print "} // end of namespace Geometry"
    print ""
    print "namespace Fragment"
    print "{"
    print ""
    for filename in fragment_shader_list:
        Write( filename )
    print "} // end of namespace Fragment"

    print ""
    print "} // end of namespace " + dirname

    print ""
    print "} } } // end of namespace kvs, glew, glsl"
    print ""
    print "#endif // KVS__GLEW__GLSL__" + dirname + "_H_INCLUDE"