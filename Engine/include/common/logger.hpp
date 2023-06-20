#pragma once

#include "common/config.hpp"
#include "common/types.hpp"

#include <fmt/format.h>
#include <fmt/std.h>
#include <iostream>
#include <iterator>
#include <string_view>

namespace spdlog {
	class logger;
}

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
		virtual void info(std::string_view format, fmt::format_args&& args = {}) const = 0;
		virtual void debug(std::string_view format, fmt::format_args&& args = {}) const = 0;
		virtual void trace(std::string_view format, fmt::format_args&& args = {}) const = 0;
		virtual void warning(std::string_view format, fmt::format_args&& args = {}) const = 0;
		virtual void error(std::string_view format, fmt::format_args&& args = {}) const = 0;
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
		void info(std::string_view format, fmt::format_args&& args = {}) const override;
		void debug(std::string_view format, fmt::format_args&& args = {}) const override;
		void trace(std::string_view format, fmt::format_args&& args = {}) const override;
		void warning(std::string_view format, fmt::format_args&& args = {}) const override;
		void error(std::string_view format, fmt::format_args&& args = {}) const override;

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
				const auto f = fmt::format(logger_base_format, logging_scope, format);
				logger->info(f, fmt::make_format_args(args...));
			}
		}

		void info(std::string_view format)
		{
			if constexpr (!is_release) {
				const auto f = fmt::format(logger_base_format, logging_scope, format);
				if (f.empty())
					return;
				logger->info(f);
			}
		}

		template <typename... Args> void debug(std::string_view format, Args&&... args)
		{
			if constexpr (!is_release) {
				const auto f = fmt::format(logger_base_format, logging_scope, format);
				logger->debug(f, fmt::make_format_args(args...));
			}
		}

		void debug(std::string_view format)
		{
			if constexpr (!is_release) {
				const auto f = fmt::format(logger_base_format, logging_scope, format);
				logger->debug(f);
			}
		}

		template <typename... Args> void trace(std::string_view format, Args&&... args)
		{
			if constexpr (!is_release) {
				const auto f = fmt::format(logger_base_format, logging_scope, format);
				logger->trace(f, fmt::make_format_args(args...));
			}
		}

		void trace(std::string_view format)
		{
			if constexpr (!is_release) {
				const auto f = fmt::format(logger_base_format, logging_scope, format);
				logger->trace(f);
			}
		}

		template <typename... Args> void warning(std::string_view format, Args&&... args)
		{
			if constexpr (!is_release) {
				const auto f = fmt::format(logger_base_format, logging_scope, format);
				logger->warning(f, fmt::make_format_args(args...));
			}
		}

		void warning(std::string_view format)
		{
			if constexpr (!is_release) {
				const auto f = fmt::format(logger_base_format, logging_scope, format);
				logger->warning(f);
			}
		}

		template <typename... Args> void error(std::string_view format, Args&&... args)
		{
			if constexpr (!is_release) {
				const auto f = fmt::format(logger_base_format, logging_scope, format);
				logger->error(f, fmt::make_format_args(args...));
			}
		}

		void error(std::string_view format)
		{
			if constexpr (!is_release) {
				const auto f = fmt::format(logger_base_format, logging_scope, format);
				logger->error(f);
			}
		}

		template <typename... Args> void info(std::string_view format, Args&&... args) const
		{
			if constexpr (!is_release) {
				const auto f = fmt::format(logger_base_format, logging_scope, format);
				logger->info(f, fmt::make_format_args(args...));
			}
		}

		void info(std::string_view format) const
		{
			if constexpr (!is_release) {
				const auto f = fmt::format(logger_base_format, logging_scope, format);
				if (f.empty())
					return;
				logger->info(f);
			}
		}

		template <typename... Args> void debug(std::string_view format, Args&&... args) const
		{
			if constexpr (!is_release) {
				const auto f = fmt::format(logger_base_format, logging_scope, format);
				logger->debug(f, fmt::make_format_args(args...));
			}
		}

		void debug(std::string_view format) const
		{
			if constexpr (!is_release) {
				const auto f = fmt::format(logger_base_format, logging_scope, format);
				logger->debug(f);
			}
		}

		template <typename... Args> void trace(std::string_view format, Args&&... args) const
		{
			if constexpr (!is_release) {
				const auto f = fmt::format(logger_base_format, logging_scope, format);
				logger->trace(f, fmt::make_format_args(args...));
			}
		}

		void trace(std::string_view format) const
		{
			if constexpr (!is_release) {
				const auto f = fmt::format(logger_base_format, logging_scope, format);
				logger->trace(f);
			}
		}

		template <typename... Args> void warning(std::string_view format, Args&&... args) const
		{
			if constexpr (!is_release) {
				const auto f = fmt::format(logger_base_format, logging_scope, format);
				logger->warning(f, fmt::make_format_args(args...));
			}
		}

		void warning(std::string_view format) const
		{
			if constexpr (!is_release) {
				const auto f = fmt::format(logger_base_format, logging_scope, format);
				logger->warning(f);
			}
		}

		template <typename... Args> void error(std::string_view format, Args&&... args) const
		{
			if constexpr (!is_release) {
				const auto f = fmt::format(logger_base_format, logging_scope, format);
				logger->error(f, fmt::make_format_args(args...));
			}
		}

		void error(std::string_view format) const
		{
			if constexpr (!is_release) {
				const auto f = fmt::format(logger_base_format, logging_scope, format);
				logger->error(f);
			}
		}

	private:
		ScopePtr<ILogger> logger;
		std::string_view logging_scope { "" };
		static constexpr std::string_view logger_base_format { "{}::{}" };
	};

} // namespace Engine::Logging

static auto get_logger(std::string_view scope) { return Engine::Logging::Logger { scope }; }
