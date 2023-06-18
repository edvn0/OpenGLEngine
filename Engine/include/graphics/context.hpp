#pragma once
#include "common/types.hpp"

namespace Engine::Context {

	class Context {
	public:
		virtual ~Context() = default;

		static RefPtr<Context> construct();

	protected:
		Context() = default;
	};

} // namespace Engine::Context
