//
// Created by edwin on 6/18/23.
//

#pragma once

#include "common/types.hpp"

#include <cstdint>
#include <filesystem>

namespace Engine::Graphics::Mesh {
	class Mesh {
	public:
		static RefPtr<Mesh> construct(const void* data, std::size_t size);
		static RefPtr<Mesh> construct(const std::filesystem::path&);
	};
}
