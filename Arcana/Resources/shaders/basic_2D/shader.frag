#version 460 core

layout (location=0) in vec4 f_color;
layout (location=1) in vec2 f_uv;
layout (location=2) in flat float f_texID;
layout (location=3) in float f_tileFactor;
layout (location=4) in flat  int f_entityID;

layout (location=0) out vec4 FRAG_COLOR;
layout (location=1) out int entID;

uniform sampler2D un_textures[32];

void main(){
    vec4 color = f_color;
    switch(int(f_texID)){
        case  0: color *= texture(un_textures[0], f_uv * f_tileFactor); break;
        case  1: color *= texture(un_textures[1], f_uv * f_tileFactor); break;
        case  2: color *= texture(un_textures[2], f_uv * f_tileFactor); break;
        case  3: color *= texture(un_textures[3], f_uv * f_tileFactor); break;
        case  4: color *= texture(un_textures[4], f_uv * f_tileFactor); break;
        case  5: color *= texture(un_textures[5], f_uv * f_tileFactor); break;
        case  6: color *= texture(un_textures[6], f_uv * f_tileFactor); break;
        case  7: color *= texture(un_textures[7], f_uv * f_tileFactor); break;
        case  8: color *= texture(un_textures[8], f_uv * f_tileFactor); break;
        case  9: color *= texture(un_textures[9], f_uv * f_tileFactor); break;
        case 10: color *= texture(un_textures[10], f_uv * f_tileFactor); break;
        case 11: color *= texture(un_textures[11], f_uv * f_tileFactor); break;
        case 12: color *= texture(un_textures[12], f_uv * f_tileFactor); break;
        case 13: color *= texture(un_textures[13], f_uv * f_tileFactor); break;
        case 14: color *= texture(un_textures[14], f_uv * f_tileFactor); break;
        case 15: color *= texture(un_textures[15], f_uv * f_tileFactor); break;
        case 16: color *= texture(un_textures[16], f_uv * f_tileFactor); break;
        case 17: color *= texture(un_textures[17], f_uv * f_tileFactor); break;
        case 18: color *= texture(un_textures[18], f_uv * f_tileFactor); break;
        case 19: color *= texture(un_textures[19], f_uv * f_tileFactor); break;
        case 20: color *= texture(un_textures[20], f_uv * f_tileFactor); break;
        case 21: color *= texture(un_textures[21], f_uv * f_tileFactor); break;
        case 22: color *= texture(un_textures[22], f_uv * f_tileFactor); break;
        case 23: color *= texture(un_textures[23], f_uv * f_tileFactor); break;
        case 24: color *= texture(un_textures[24], f_uv * f_tileFactor); break;
        case 25: color *= texture(un_textures[25], f_uv * f_tileFactor); break;
        case 26: color *= texture(un_textures[26], f_uv * f_tileFactor); break;
        case 27: color *= texture(un_textures[27], f_uv * f_tileFactor); break;
        case 28: color *= texture(un_textures[28], f_uv * f_tileFactor); break;
        case 29: color *= texture(un_textures[29], f_uv * f_tileFactor); break;
        case 30: color *= texture(un_textures[30], f_uv * f_tileFactor); break;
        case 31: color *= texture(un_textures[31], f_uv * f_tileFactor); break;
    }
    FRAG_COLOR = color;
    entID = f_entityID;

//* f_color
//    FRAG_COLOR = texture(un_textures[int(f_texID)], f_uv * f_tileFactor)* f_color;
}