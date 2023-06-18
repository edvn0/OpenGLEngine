#include "opengl/shader.hpp"

#include "common/logger.hpp"
#include "errors/graphics_exception.hpp"

#include <algorithm>

namespace OpenGL::Shader {

	Shader::~Shader() { glDeleteProgram(program); }

	void Shader::bind() { glUseProgram(program); }

	Shader::Shader(const std::filesystem::path& vertex, const std::filesystem::path& fragment)
	{
		Engine::Logging::Logger logger { "OpenGL::Shader" };
		const auto vertex_file = read_file(vertex);
		const auto vertex_data = vertex_file.c_str();
		const auto fragment_file = read_file(fragment);
		const auto fragment_data = fragment_file.c_str();

		logger.debug("{}", vertex_file);
		logger.debug("{}", fragment_file);

		static const auto compile = [&logger = logger](GLenum type, auto data) {
			GLuint shader = glCreateShader(type);
			glShaderSource(shader, 1, data, nullptr);
			glCompileShader(shader);
			GLint success;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

			if (!success) {
				GLchar info_log[512];
				glGetShaderInfoLog(shader, 512, nullptr, info_log);
				logger.error("{} shader compilation failure. Info: {}", type == GL_VERTEX_SHADER ? "Vertex" : "Fragment", info_log);
				throw Engine::Errors::Graphics::InitialisationException();
			}
			return shader;
		};

		auto vertex_shader = compile(GL_VERTEX_SHADER, &vertex_data);
		auto fragment_shader = compile(GL_FRAGMENT_SHADER, &fragment_data);

		// Link shaders
		program = glCreateProgram();
		glAttachShader(program, vertex_shader);
		glAttachShader(program, fragment_shader);
		glLinkProgram(program);
		GLint success;
		glGetProgramiv(program, GL_LINK_STATUS, &success);
		if (!success) {
			GLchar info_log[512];
			glGetProgramInfoLog(program, 512, nullptr, info_log);
			logger.error("Shader linking failure. Info: {}", info_log);
		}
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);
	}

} // namespace OpenGL::Shader
