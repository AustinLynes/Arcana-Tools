#version 460 core

// input from vertex data
layout (location =0) in vec3 v_position;
layout (location =1) in vec3 v_normal;
layout (location =2) in vec3 v_color;
layout (location =3) in vec2 v_uv;
//layout (location = 4)in int  v_entityID;

uniform mat4 un_ViewProjection; 

uniform mat4 un_model;
uniform mat4 un_rotation;
uniform mat4 un_scale;



layout (location =0) out vec3 pos;
layout (location =1) out vec3 color;
layout (location =2) out vec3 norm;
layout (location =3) out vec2 uv;
//layout (location =4) out vec4 lightSpacePos;

void main(){

	pos = vec3(un_model * un_rotation * un_scale * vec4(v_position, 1.0));
	
	norm = v_normal;	
	color = v_color;

	uv =  v_uv;
	
//	lightSpacePos = un_lightSpaceMatrix * vec4(pos, 1.0f);

//	entityID = v_entityID;

	gl_Position = un_ViewProjection * vec4(pos, 1.0);
}