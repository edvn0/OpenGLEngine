#pragma once

#include "common/config.hpp"
#include "errors/verification_exception.hpp"

#include <string_view>

namespace Engine::Verify {

	// API
	// Verify::that(my_param->has_value()).with_error("My param is missing value.")

	void log_error(std::string_view base_name, std::string_view error_message);

	namespace {
		struct Verification {
			explicit Verification(bool) noexcept;

			void with_error(std::string_view log_scope, std::string_view);

		private:
			bool passed_verification { false };
			std::string_view message;
		};

		Verification::Verification(bool value) noexcept
			: passed_verification(value)
		{
		}

		void Verification::with_error(std::string_view log_scope, std::string_view error)
		{
			message = error;

			if (!passed_verification) {
				log_error(log_scope, error);
				throw Errors::Verify::VerificationException(error);
			}
		}
	} // namespace

	template <typename T>
	requires std::is_convertible_v<T, bool>
	static void that(T&& potentially_invalid, std::string_view error = "Verification failure.", std::string_view log_scope = "Verify")
	{
		if (!is_release) {
			Verification verification(static_cast<bool>(std::forward<T>(potentially_invalid)));
			verification.with_error(log_scope, error);
		}
	}

} // namespace Engine::Verify
