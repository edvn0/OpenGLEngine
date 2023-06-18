#include "common/verify.hpp"

#include "common/logger.hpp"

namespace Engine::Verify {
	void log_error(std::string_view base_name, std::string_view error_message)
	{
		Logging::Logger logger { base_name };
		logger.error("Verification failed. Message: '{}'", error_message);
	}
} // namespace Engine::Verify
