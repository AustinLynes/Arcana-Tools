#version 460 core

uniform vec3 un_lightColor;
uniform int un_entityID;



layout (location=0) out vec4 FragColor;
layout (location=1) out int EntityID;

void main(){
		FragColor = vec4(un_lightColor, 1.0);
		EntityID = un_entityID;
}