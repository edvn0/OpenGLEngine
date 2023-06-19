#version 420 core

layout (location = 0) in vec2 out_tex;
layout (location = 1) in vec3 out_normals;

layout (location = 0) out vec4 colour;

void main() {
    colour = vec4(out_tex.xy, 0.5f, 1.0f) * vec4(out_normals.xyz, 1.0f);
}
