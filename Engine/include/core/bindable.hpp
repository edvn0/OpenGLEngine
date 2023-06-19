//
// Created by edwinc on 6/19/23.
//

namespace Engine::Core::Bindable {
	class Bindable {
	public:
		virtual ~Bindable() = default;

		virtual void bind() = 0;
		virtual void unbind() = 0;
	};
}