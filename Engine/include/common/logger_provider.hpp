#pragma once

#include "common/types.hpp"

#include <filesystem>

namespace spdlog {
	class logger;
}

namespace Engine::Logging {
	class LoggerProvider {
	public:
		LoggerProvider() = delete;

		static void initialise(const std::filesystem::path& cwd);

		static RefPtr<spdlog::logger>& get_core_logger() { return core_logger; };
		static RefPtr<spdlog::logger>& get_application_logger() { return application_logger; };

	private:
		inline static RefPtr<spdlog::logger> core_logger;
		inline static RefPtr<spdlog::logger> application_logger;
	};
} // namespace Engine::Logging

