#include "opengl/shader.hpp"

#include "common/logger.hpp"
#include "errors/graphics_exception.hpp"

#include <algorithm>

namespace OpenGL::Shader {

	Shader::~Shader() {
		auto logger = get_logger("OpenGL::Shader");
		logger.debug("Destructor for shader with name {}", shader_name);

		glDeleteProgram(program); }

	void Shader::bind() { glUseProgram(program); }

	namespace {
		enum class ObjectType { Shader, Program };
	}

	static auto read_error(auto object, ObjectType type)
	{
		static constexpr auto buffer_size = 512ul;
		std::string buffer;
		buffer.resize(buffer_size);

		switch (type) {
		case ObjectType::Shader: {
			glGetShaderInfoLog(object, buffer_size, nullptr, buffer.data());
			break;
		}
		case ObjectType::Program: {
			glGetProgramInfoLog(object, buffer_size, nullptr, buffer.data());
			break;
		}
		}

		buffer.shrink_to_fit();
		return buffer;
	}

	Shader::Shader(std::string_view name, const std::filesystem::path& vertex, const std::filesystem::path& fragment): shader_name(name)
	{
		Engine::Logging::Logger logger { "OpenGL::Shader" };
		const auto vertex_file = Shader::read_file(vertex);
		const auto vertex_data = vertex_file.c_str();
		const auto fragment_file = Shader::read_file(fragment);
		const auto fragment_data = fragment_file.c_str();

		static const auto compile = [&logger = logger](GLenum type, auto data) {
			GLuint shader = glCreateShader(type);
			glShaderSource(shader, 1, data, nullptr);
			glCompileShader(shader);
			GLint success;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

			if (!success) {
				auto info_log = read_error(shader, ObjectType::Shader);
				const auto size = info_log.size() == 0 ? "Empty": std::to_string(info_log.size());
				const auto info_data = info_log.empty() ? "No data" : info_log;
				logger.error("{} shader compilation failure. Info: Size: {}, Data: {}", type == GL_VERTEX_SHADER ? "Vertex" : "Fragment",
					size, info_data);
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
			auto info_log = read_error(program, ObjectType::Program);
			const auto size = info_log.size() == 0 ? "Empty": std::to_string(info_log.size());
			const auto info_data = info_log.empty() ? "No data" : info_log;
			logger.error("Shader linking failure. Info: Size: {}, Data: {}",
				size, info_data);

		}
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);

		logger.debug("Successfully compiled and linked a vertex and a fragment shader into a shader program.");
	}

} // namespace OpenGL::Shader
