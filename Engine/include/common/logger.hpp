#pragma once

#include "common/config.hpp"
#include "common/types.hpp"

#include <fmt/format.h>
#include <fmt/std.h>
#include <iostream>
#include <iterator>
#include <string_view>

// clang-format off
namespace spdlog {
	class logger;
}
// clang-format on
namespace Engine {
	using namespace std::string_view_literals;
}

namespace Engine::Logging {

	class ILogger {
	public:
		virtual ~ILogger() = default;

		virtual void info(std::string_view format, fmt::format_args&& args = {}) = 0;
		virtual void debug(std::string_view format, fmt::format_args&& args = {}) = 0;
		virtual void trace(std::string_view format, fmt::format_args&& args = {}) = 0;
		virtual void warning(std::string_view format, fmt::format_args&& args = {}) = 0;
		virtual void error(std::string_view format, fmt::format_args&& args = {}) = 0;
	};

	class DefaultLogger : public ILogger {
	public:
		DefaultLogger();
		~DefaultLogger() override;

		void info(std::string_view format, fmt::format_args&& args = {}) override;
		void debug(std::string_view format, fmt::format_args&& args = {}) override;
		void trace(std::string_view format, fmt::format_args&& args = {}) override;
		void warning(std::string_view format, fmt::format_args&& args = {}) override;
		void error(std::string_view format, fmt::format_args&& args = {}) override;

	private:
		RefPtr<spdlog::logger> core_logger;
	};

	class Logger {
	public:
		explicit Logger(ScopePtr<ILogger> ilogger)
			: logger(std::move(ilogger))
		{
		}

		explicit Logger(std::string_view scope, ScopePtr<ILogger> ilogger)
			: logger(std::move(ilogger))
			, logging_scope(scope)
		{
		}

		explicit Logger(std::string_view scope)
			: logger(std::make_unique<DefaultLogger>())
			, logging_scope(scope)
		{
		}

		Logger()
			: logger(std::make_unique<DefaultLogger>())
		{
		}

		template <typename... Args> void info(std::string_view format, Args&&... args)
		{
			if constexpr (!is_release) {
				const auto f = fmt::format("{}::{}", logging_scope, format);
				logger->info(f, fmt::make_format_args(args...));
			}
		}

		void info(std::string_view format)
		{
			if constexpr (!is_release) {
				const auto f = fmt::format("{}::{}", logging_scope, format);
				if (f.empty())
					return;
				logger->info(f);
			}
		}

		template <typename... Args> void debug(std::string_view format, Args&&... args)
		{
			if constexpr (!is_release) {
				const auto f = fmt::format("{}::{}", logging_scope, format);
				logger->debug(f, fmt::make_format_args(args...));
			}
		}

		void debug(std::string_view format)
		{
			if constexpr (!is_release) {
				const auto f = fmt::format("{}::{}", logging_scope, format);
				logger->debug(f);
			}
		}

		template <typename... Args> void trace(std::string_view format, Args&&... args)
		{
			if constexpr (!is_release) {
				const auto f = fmt::format("{}::{}", logging_scope, format);
				logger->trace(f, fmt::make_format_args(args...));
			}
		}

		void trace(std::string_view format)
		{
			if constexpr (!is_release) {
				const auto f = fmt::format("{}::{}", logging_scope, format);
				logger->trace(f);
			}
		}

		template <typename... Args> void warning(std::string_view format, Args&&... args)
		{
			if constexpr (!is_release) {
				const auto f = fmt::format("{}::{}", logging_scope, format);
				logger->warning(f, fmt::make_format_args(args...));
			}
		}

		void warning(std::string_view format)
		{
			if constexpr (!is_release) {
				const auto f = fmt::format("{}::{}", logging_scope, format);
				logger->warning(f);
			}
		}

		template <typename... Args> void error(std::string_view format, Args&&... args)
		{
			if constexpr (!is_release) {
				const auto f = fmt::format("{}::{}", logging_scope, format);
				logger->error(f, fmt::make_format_args(args...));
			}
		}

		void error(std::string_view format)
		{
			if constexpr (!is_release) {
				const auto f = fmt::format("{}::{}", logging_scope, format);
				logger->error(f);
			}
		}

	private:
		ScopePtr<ILogger> logger;
		std::string_view logging_scope { "" };
	};

} // namespace Engine::Logging