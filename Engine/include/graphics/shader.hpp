#pragma once

#include "common/types.hpp"

#include <filesystem>
#include <string>

namespace Engine::Graphics::Shader {

	class Shader {
	public:
		virtual ~Shader() = default;

		virtual void bind() = 0;

		static RefPtr<Shader> construct(const std::filesystem::path& vertex, const std::filesystem::path& fragment);

	protected:
		std::string read_file(const std::filesystem::path&);
	};

} // namespace Engine::Graphics::Shader