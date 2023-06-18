#pragma once

#include "graphics/shader.hpp"

#include <glad/glad.h>

namespace OpenGL::Shader {

	class Shader : public Engine::Graphics::Shader::Shader {
	public:
		explicit Shader(const std::filesystem::path& vertex, const std::filesystem::path& fragment);
		~Shader() override;

		virtual void bind() override;

	private:
		GLuint program;
	};

} // namespace OpenGL::Shader