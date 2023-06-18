#pragma once

#include <memory>

namespace Engine {
	template <class T> using RefPtr = std::shared_ptr<T>;

	template <class T> using ScopePtr = std::unique_ptr<T>;

	template <class T, typename... Args> RefPtr<T> construct_ref(Args&&... args) { return std::make_shared<T>(std::forward<Args>(args)...); }

	template <class T, typename... Args> ScopePtr<T> construct_scoped(Args&&... args) { return std::make_unique<T>(std::forward<Args>(args)...); }
} // namespace Engine
