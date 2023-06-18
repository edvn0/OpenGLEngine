//
// Created by edwin on 6/18/23.
//

#pragma once

#include "common/types.hpp"

#include <cstdint>
#include <filesystem>

namespace OpenGL::Mesh {
	class Mesh : public Engine::Graphics::Mesh::Mesh {
	public:
		explicit Mesh(const void* data, std::size_t size);
		explicit Mesh(const std::filesystem::path&);
	};
}
