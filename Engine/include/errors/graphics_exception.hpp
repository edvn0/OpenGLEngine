#pragma once

#include <exception>

namespace Engine::Errors::Graphics {

	class InitialisationException : public std::exception {
	public:
		const char* what() const noexcept override { return "Graphics: Could not initialise"; }
	};

} // namespace Engine::Errors::Graphics
