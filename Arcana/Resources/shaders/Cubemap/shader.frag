#version 460 core

layout(location =0) in vec3 f_pos;

uniform sampler2D cubemap_ref;
uniform sampler2D cubemap_env;

layout(location=0) out vec4 FRAG_COLOR;


const vec2 invAtan = vec2(0.1591, 0.3183);
vec2 SampleSphericalMap(vec3 v) {
	vec2 uv = vec2(atan(v.z, v.x), asin(v.y));
	uv *= invAtan;
	uv += 0.5;
	return uv;
}

void main(){
	vec2 uv = SampleSphericalMap(normalize(f_pos));
	vec4 color = texture(cubemap_env, uv);
	FRAG_COLOR = color;
}