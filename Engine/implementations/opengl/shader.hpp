#pragma once

#include "graphics/shader.hpp"

#include <glad/glad.h>

namespace OpenGL::Shader {

	class Shader : public Engine::Graphics::Shader::Shader {
	public:
		explicit Shader(std::string_view name, const std::filesystem::path& vertex, const std::filesystem::path& fragment);
		~Shader() override;

		virtual void bind() override;
		virtual void unbind() override {}

		std::string_view get_identifier() override { return shader_name; }

	private:
		GLuint program;
		std::string shader_name;
	};

} // namespace OpenGL::Shader