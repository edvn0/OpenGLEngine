#pragma once

#include "common/identifiable.hpp"
#include "common/types.hpp"

#include <filesystem>
#include <string>

namespace Engine::Graphics::Shader {

	class Shader: public Common::Identifiable::Identifiable {
	public:
		virtual ~Shader() = default;

		virtual void bind() = 0;

		static RefPtr<Shader> construct(std::string_view name, const std::filesystem::path& vertex, const std::filesystem::path& fragment);

	protected:
		std::string read_file(const std::filesystem::path&);
	};

} // namespace Engine::Graphics::Shader