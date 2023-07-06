#include "graphics/types.hpp"
#include "graphics/uniform_buffer.hpp"

namespace OpenGL::UniformBuffer {

	class UniformBuffer : public Engine::Graphics::UniformBuffer::UniformBuffer {
	public:
		explicit UniformBuffer(std::size_t size);
		~UniformBuffer() override;

		void bind() override;
		void unbind() override;
		void set_data(const void* data, std::size_t size) override;

	private:
		std::size_t max_size { 0 };
		GLuint object { 0 };
	};

} // namespace OpenGL::UniformBuffer
