#version 460 core

layout(location=0) in vec3 v_position;

uniform mat4 un_View;
uniform mat4 un_Projection;
layout (location = 0) out vec3 f_pos;

void main(){
	f_pos = v_position; 
	vec4 pos = un_Projection * un_View * vec4(v_position, 1.0);
	gl_Position = pos.xyww;
}