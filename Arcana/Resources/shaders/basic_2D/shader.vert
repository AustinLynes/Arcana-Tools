#version 460 core

// coding conventions....
/*
    v_  prefix for inputs to vertex shader
    f_  prefix for outputs/inputs to fragment shader
    un_ prfix for uniforms


*/

layout (location=0) in vec3 v_position;
layout (location=1) in vec4 v_color;
layout (location=2) in vec2 v_uv;
layout (location=3) in float v_texID;
layout (location=4) in float v_tileFactor;
layout (location=5) in int v_entityID;

uniform mat4 un_ViewProjection;

layout (location=0) out vec4 f_color;
layout (location=1) out vec2 f_uv;
layout (location=2) out flat float f_texID;
layout (location=3) out float f_tileFactor;
layout (location=4) out flat int f_entityID;

void main() {
    
    gl_Position = un_ViewProjection * vec4(v_position, 1.0);

    f_color = v_color;
    f_uv = v_uv;
    f_texID = v_texID;
    f_tileFactor = v_tileFactor;
    f_entityID = v_entityID;

}
