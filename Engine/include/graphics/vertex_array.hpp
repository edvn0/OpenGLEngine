//
// Created by edwin on 6/18/23.
//

#pragma once

#include "common/identifiable.hpp"
#include "common/types.hpp"
#include "core/bindable.hpp"
#include "graphics/buffer_object.hpp"
#include "graphics/mesh.hpp"

#include <cstdint>
#include <filesystem>
#include <vector>

namespace Engine::Graphics::VertexArray {

	class VertexArray : public Engine::Core::Bindable::Bindable, Engine::Common::Identifiable::Identifiable {
	public:
		virtual ~VertexArray() = default;

		virtual std::size_t index_count() const = 0;
		virtual std::size_t vertex_count() const = 0;

		static RefPtr<VertexArray> construct(std::vector<Engine::Graphics::Vertex::Vertex>&& vertices, std::vector<std::uint32_t>&& indices);
	};

} // namespace Engine::Graphics::VertexArray
