#include "graphics/shader.hpp"

#include "common/fs.hpp"
#include "opengl/shader.hpp"

#include <fstream>

namespace Engine::Graphics::Shader {

	RefPtr<Shader> Shader::construct(const std::filesystem::path& vertex, const std::filesystem::path& fragment)
	{
		return construct_ref<OpenGL::Shader::Shader>(vertex, fragment);
	}

	std::string Shader::read_file(const std::filesystem::path& path)
	{
		return FS::read_file(path);
	}
} // namespace Engine::Graphics::Shader
