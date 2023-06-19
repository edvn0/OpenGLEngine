//
// Created by edwin on 6/18/23.
//

#pragma once

#include "common/types.hpp"

#include <cstdint>
#include <filesystem>
#include <glm/glm.hpp>
#include <glm/gtc/epsilon.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/hash.hpp>

namespace Engine::Graphics::Mesh {

	static constexpr auto vertex_is_same = [](auto&& a, auto&& b) -> bool { return glm::all(glm::epsilonEqual(a, b, 0.00001f)); };

	struct Vertex {
		glm::vec4 pos {};
		glm::vec2 tex_coord {};
		glm::vec3 normal {};

		bool operator==(const Vertex& other) const { return vertex_is_same(pos, other.pos) && normal == other.normal; }
	};

	class Mesh {
	public:
		virtual ~Mesh() = default;

		virtual void draw() const {};

		static RefPtr<Mesh> construct(std::string_view name, const void* data, std::size_t size);
		static RefPtr<Mesh> construct(const std::filesystem::path&);
	};

} // namespace Engine::Graphics::Mesh

template <> struct std::hash<Engine::Graphics::Mesh::Vertex> {
	std::size_t operator()(const Engine::Graphics::Mesh::Vertex& vertex) const
	{
		return hash<glm::vec4>()(vertex.pos) ^ (hash<glm::vec2>()(vertex.tex_coord) << 1) ^ (hash<glm::vec3>()(vertex.normal) << 1);
	}
};
