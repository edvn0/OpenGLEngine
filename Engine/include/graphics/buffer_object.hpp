//
// Created by edwin on 6/18/23.
//

#pragma once

#include "buffer_object.hpp"
#include "common/identifiable.hpp"
#include "common/types.hpp"
#include "core/bindable.hpp"
#include "graphics/mesh.hpp"

#include <cstdint>
#include <filesystem>
#include <fmt/format.h>
#include <glm/glm.hpp>
#include <glm/gtc/epsilon.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/hash.hpp>
#include <glm/gtx/string_cast.hpp>
#include <vector>

namespace Engine::Graphics::Vertex {

	static constexpr auto vertex_is_same = [](auto&& a, auto&& b) -> bool { return glm::all(glm::epsilonEqual(a, b, 0.00001f)); };

	struct Vertex {
		glm::vec4 pos { 0.0f };
		glm::vec2 tex_coord { 0.0f };
		glm::vec3 normal { 0.0f };

		bool operator==(const Vertex& other) const { return vertex_is_same(pos, other.pos) && normal == other.normal; }

		friend struct fmt::formatter<Engine::Graphics::Vertex::Vertex>;
	};

} // namespace Engine::Graphics::Vertex

template <> struct std::hash<Engine::Graphics::Vertex::Vertex> {
	std::size_t operator()(const Engine::Graphics::Vertex::Vertex& vertex) const
	{
		return hash<glm::vec4>()(vertex.pos) ^ (hash<glm::vec2>()(vertex.tex_coord)) ^ (hash<glm::vec3>()(vertex.normal));
	}
};

namespace Engine::Graphics::BufferObject {

	class VertexBuffer : public Engine::Core::Bindable::Bindable, Engine::Common::Identifiable::Identifiable {
	public:
		virtual ~VertexBuffer() = default;

		virtual std::size_t count() const = 0;

		static RefPtr<VertexBuffer> construct(std::vector<Engine::Graphics::Vertex::Vertex>&& vertices);
		static RefPtr<VertexBuffer> construct(const void*, std::size_t);
	};

	class IndexBuffer : public Engine::Core::Bindable::Bindable, Engine::Common::Identifiable::Identifiable {
	public:
		virtual ~IndexBuffer() = default;

		virtual std::size_t count() const = 0;

		static RefPtr<IndexBuffer> construct(std::vector<std::uint32_t>&& indices);
	};

} // namespace Engine::Graphics::BufferObject
