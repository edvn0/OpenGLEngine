//
// Created by edwinc on 6/19/23.
//

#include <concepts>
#include <type_traits>
#include <vector>

namespace Engine::Core::ExecutionScope {

	namespace {
		template <typename From, typename To>
		concept same = std::is_same_v<From, To>;
	}

	template<class T>
	concept Bindable = requires(RefPtr<T> t) {
		{
			t->bind()
		} -> same<void>;
	};

	template<class T>
	concept Unbindable = requires(RefPtr<T> t) {
		{
			t->unbind()
		} -> same<void>;
	};

	template<typename T> requires Bindable<T> && Unbindable<T>
	class ExecutionScope {
	public:
		[[maybe_unused]] explicit ExecutionScope(RefPtr<T> t):scoped_t(t) {
			scoped_t->bind();
		};

		~ExecutionScope() {
			scoped_t->unbind();
		}

		auto operator ->() {
			return *scoped_t;
		}

		auto operator ->()const {
			return *scoped_t;
		}

	private:
		RefPtr<T> scoped_t;
	};

}