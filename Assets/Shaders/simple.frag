#version 420 core

layout (location = 0) in vec2 out_tex;
layout (location = 1) in vec3 out_normals;

layout (location = 0) out vec4 colour;

layout (std140) uniform UBO {
	mat4 model;
	mat4 view;
	mat4 projection;
	mat4 mvp;
};

void main() {
    colour = vec4(out_normals.xyz, 1.0f);
}
