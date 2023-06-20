#include "common/logger_provider.hpp"

#include <fmt/format.h>
#include <spdlog/fmt/ostr.h> // must be included
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

// clang-format off
#include "common/logger_provider_fs_path.inl"
#include "common/logger_provider_vertex.inl"
// clang-format on

namespace Engine::Logging {

	void LoggerProvider::initialise(const std::filesystem::path& cwd)
	{
		std::vector<spdlog::sink_ptr> sinks;
		sinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
		const std::filesystem::path file_path = cwd / std::filesystem::path { "Engine.log" };
		sinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>(file_path.string(), true));

		sinks[0]->set_pattern("%^[%T] %n: %v%$");
		sinks[1]->set_pattern("[%T] [%l] %n: %v");

		core_logger = construct_ref<spdlog::logger>("OpenGLEngine", std::begin(sinks), std::end(sinks));
		spdlog::register_logger(core_logger);
		core_logger->set_level(spdlog::level::debug);
		core_logger->flush_on(spdlog::level::debug);

		application_logger = construct_ref<spdlog::logger>("Application", std::begin(sinks), std::end(sinks));
		spdlog::register_logger(application_logger);
		application_logger->set_level(spdlog::level::debug);
		application_logger->flush_on(spdlog::level::debug);

		core_logger->info("Engine::Logging::CoreLogger intialised! Working directory: {}.", cwd);
		application_logger->info("Engine::Logging::ApplicationLogger intialised! Working directory: {}", cwd);
	}

} // namespace Engine::Logging
