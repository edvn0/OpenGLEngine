#version 420 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 tex;
layout (location = 2) in vec3 normals;

layout (location = 0) out vec2 out_tex;
layout (location = 1) out vec3 out_normals;

void main() {
    gl_Position = position;
    out_tex = tex;
    out_normals = normals;
}
