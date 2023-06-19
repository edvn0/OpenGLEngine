//
// Created by edwin on 6/18/23.
//

#pragma once

#include "common/types.hpp"
#include "graphics/mesh.hpp"

#include <cstdint>
#include <filesystem>
#include <glad/glad.h>

namespace OpenGL::Mesh {
	class Mesh : public Engine::Graphics::Mesh::Mesh {
	public:
		~Mesh() override;

		void draw() const override;

		explicit Mesh(const std::string_view name, const void* data, std::size_t size);
		explicit Mesh(const std::filesystem::path&);

	private:
		std::string mesh_name;
		GLuint vertex_object;
		GLuint index_object;
		std::size_t vertex_count;
		std::size_t index_count;
	};
} // namespace OpenGL::Mesh
