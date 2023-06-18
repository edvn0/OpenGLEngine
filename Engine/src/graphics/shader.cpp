#include "graphics/shader.hpp"
#include "errors/graphics_exception.hpp"
#include "common/logger.hpp"

#include "opengl/shader.hpp"

#include <fstream>

namespace Engine::Graphics::Shader {

	RefPtr<Shader> Shader::construct(const std::filesystem::path& vertex, const std::filesystem::path& fragment)
	{
		return construct_ref<OpenGL::Shader::Shader>(vertex, fragment);
	}

	std::string Shader::read_file(const std::filesystem::path& path)
	{
		Logging::Logger logger { "Shader" };
		std::ifstream input_stream(path.string(), std::ios::ate | std::ios::in);
		if (!input_stream) {
			logger.error("Could not open path {}.", path.string());
			throw Errors::Graphics::InitialisationException();
		}

		const std::size_t size = input_stream.tellg();
		input_stream.seekg(0);

		std::string buffer;
		buffer.resize(size);
		input_stream.read(buffer.data(), size);

		return buffer;
	}
} // namespace Engine::Graphics::Shader
