#version 460 core

layout (location = 0) in vec3 v_position;

uniform mat4 un_ViewProjection;
uniform mat4 un_model;


void main() {
	gl_Position = un_ViewProjection * un_model * vec4(v_position, 1.0);
}
