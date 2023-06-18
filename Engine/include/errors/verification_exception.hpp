#pragma once

#include <exception>
#include <string_view>

namespace Engine::Errors::Verify {

	class VerificationException : public std::exception {
	public:
		explicit VerificationException(std::string_view message)
			: exc_message(message)
		{
		}
		const char* what() const noexcept override { return exc_message.data(); }

	private:
		std::string_view exc_message;
	};

} // namespace Engine::Errors::Verify
