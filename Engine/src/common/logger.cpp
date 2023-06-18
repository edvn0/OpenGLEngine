#include "common/logger.hpp"

#include "common/config.hpp"
#include "common/logger_provider.hpp"
#include "common/types.hpp"

#include <cassert>
#include <fmt/core.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

namespace Engine::Logging {

	DefaultLogger::DefaultLogger()
		: core_logger(LoggerProvider::get_core_logger())
	{
		assert(core_logger);
	}

	DefaultLogger::~DefaultLogger() { }

	void DefaultLogger::info(std::string_view format, fmt::format_args&& args)
	{
		const auto formatted = fmt::vformat(format, args);
		core_logger->info(formatted);
	};

	void DefaultLogger::debug(std::string_view format, fmt::format_args&& args)
	{
		const auto formatted = fmt::vformat(format, args);
		core_logger->debug(formatted);
	};

	void DefaultLogger::trace(std::string_view format, fmt::format_args&& args)
	{
		const auto formatted = fmt::vformat(format, args);
		core_logger->trace(formatted);
	};

	void DefaultLogger::warning(std::string_view format, fmt::format_args&& args)
	{
		const auto formatted = fmt::vformat(format, args);
		core_logger->warn(formatted);
	};

	void DefaultLogger::error(std::string_view format, fmt::format_args&& args)
	{
		const auto formatted = fmt::vformat(format, args);
		core_logger->error(formatted);
	};

} // namespace Engine::Logging
