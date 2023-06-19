//
// Created by edwinc on 6/19/23.
//

#include "common/clock.hpp"
#include "common/logger.hpp"
#include "common/types.hpp"
#include "core/bindable.hpp"

#include <concepts>
#include <type_traits>
#include <vector>

namespace Engine::Core::ExecutionScope {

	namespace {
		template <typename From, typename To>
		concept same = std::is_same_v<From, To>;
	}

	template <class T>
	concept Bindable = requires(RefPtr<T> t) {
		{
			t->bind()
		} -> same<void>;
	};

	template <class T>
	concept Unbindable = requires(RefPtr<T> t) {
		{
			t->unbind()
		} -> same<void>;
	};

	template <class T>
	concept Scopeable = Unbindable<T> && Bindable<T>;

	template <Scopeable T> class SingleExecutionScope {
	public:
		[[maybe_unused]] explicit SingleExecutionScope(RefPtr<T> t)
			: scoped_t(t)
		{
			scoped_t->bind();
		};

		~SingleExecutionScope() { scoped_t->unbind(); }

		auto operator->() { return *scoped_t; }
		auto operator->() const { return *scoped_t; }

	private:
		RefPtr<T> scoped_t;
	};

	namespace {
		struct Stopwatch {
			double start { Clock::Clock::time_ns() };

			double elapsed_ms() { return (Clock::Clock::time_ns() - start) / 1000.0; }
		};
	} // namespace

	template <Scopeable T, bool Profiled = false> class Scope {
	public:
		[[maybe_unused]] explicit Scope(std::initializer_list<RefPtr<T>> ptrs)
			: data(ptrs)
		{
			inside_scope([&data = data]() {
				for (auto& scoped : data) {
					scoped->bind();
				}
			});
		}

		~Scope()
		{
			inside_scope([&data = data]() {
				for (auto i = data.rbegin(); i != data.rend(); ++i) {
					auto scoped = *i;
					scoped->unbind();
				}
			});
		}

	private:
		template <typename F> auto inside_scope(F&& func)
		{
			if constexpr (Profiled) {
				Stopwatch watch;
				func();
				logger.debug("Time taken: {:3f}", watch.elapsed_ms());
			} else {
				func();
			}
		}
		std::vector<RefPtr<T>> data;
		Logging::Logger logger { get_logger("ExecutionScope::Scope") };
	};

	using ExecutionScope = Engine::Core::ExecutionScope::Scope<Engine::Core::Bindable::Bindable, false>;
	using ProfiledExecutionScope = Engine::Core::ExecutionScope::Scope<Engine::Core::Bindable::Bindable, true>;

} // namespace Engine::Core::ExecutionScope