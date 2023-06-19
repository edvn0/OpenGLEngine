#include "graphics/shader.hpp"

#include "common/fs.hpp"
#include "opengl/shader.hpp"

#include <mutex>

namespace Engine::Graphics::Shader {

	RefPtr<Shader> Shader::construct(std::string_view name, const std::filesystem::path& vertex, const std::filesystem::path& fragment)
	{
		return construct_ref<OpenGL::Shader::Shader>(name, vertex, fragment);
	}

	std::string Shader::read_file(const std::filesystem::path& path)
	{
		static std::mutex mutex;
		std::scoped_lock lock(mutex);
		return FS::read_file(path);
	}
} // namespace Engine::Graphics::Shader
