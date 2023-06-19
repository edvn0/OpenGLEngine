//
// Created by edwin on 6/18/23.
//

#include "graphics/mesh.hpp"

#include "opengl/mesh.hpp"

namespace Engine::Graphics::Mesh {

	RefPtr<Mesh> Mesh::construct(std::string_view name, const void* data, std::size_t size) { return construct_ref<OpenGL::Mesh::Mesh>(name, data, size); }

	RefPtr<Mesh> Mesh::construct(const std::filesystem::path& path) { return construct_ref<OpenGL::Mesh::Mesh>(path); }

}