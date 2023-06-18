#pragma once

#include <exception>
#include <optional>
#include <variant>

namespace Application {

	template <typename T> class Result {
	private:
		using ResultImpl = std::variant<T, std::exception>;

	public:
		ResultImpl error_or;

		explicit Result(const T& value)
			: error_or(value)
		{
		}

		explicit Result(const std::exception& exc)
			: error_or(exc)
		{
		}

		operator bool() const { return has_value(); }
		bool has_value() const { return error_or.index() == 0; }

		T value() const { return std::get<T>(error_or); }
	};

	Result<int> engine_main();

} // namespace Application
