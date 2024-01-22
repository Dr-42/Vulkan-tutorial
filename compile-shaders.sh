#!/bin/sh

glslc -o shaders/vert.spv -fshader-stage=vert shaders/vertex_shader.glsl
glslc -o shaders/frag.spv -fshader-stage=frag shaders/fragment_shader.glsl
