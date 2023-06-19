//
// Created by edwinc on 6/19/23.
//

#pragma once

#include "graphics/vertex_array.hpp"

#include <glad/glad.h>

namespace OpenGL::VertexArray {

		class VertexArray : public Engine::Graphics::VertexArray::VertexArray {
		public:
			VertexArray();
			~VertexArray() override;

			void bind() override;
			void unbind() override;

			std::string_view get_identifier() override { return "VertexArray"; }

		private:
			GLuint object {0};
		};

	} // namespace OpenGL

