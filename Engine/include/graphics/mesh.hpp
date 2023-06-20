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
		virtual ~Mesh() = default;

		virtual void draw() const {};

		static RefPtr<Mesh> construct(const std::filesystem::path&);
		static RefPtr<Mesh> construct(std::string_view, const void*, std::size_t);
	};

} // namespace Engine::Graphics::Mesh
