#version 460 core

layout (location = 0) in vec3 pos;

layout(location = 1) uniform  mat4 proj;
layout(location = 0) uniform  mat4 view;

out vec3 texcoords;

void main() 
{
   texcoords = pos;
   vec4 p = proj*vec4(mat3(view)*pos, 1.0);
   gl_Position = p.xyww;
}

