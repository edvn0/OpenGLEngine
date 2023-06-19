#include "my_layer.hpp"

#include "common/verify.hpp"
#include "core/execution_scope.hpp"
#include "graphics/mesh.hpp"
#include "graphics/shader.hpp"
#include "graphics/vertex_array.hpp"
#include "processing/background_service.hpp"

#include <thread>

using namespace Engine;

void MyLayer::on_create()
{
	shader = Graphics::Shader::Shader::construct("simple", "Assets/Shaders/simple.vert", "Assets/Shaders/simple.frag");

#if 0
	Background::submit_work([](auto id, const auto& l) mutable {
		using namespace std::chrono_literals;
		for (auto i = 0; i < 1; i++) {
			std::this_thread::sleep_for(1000ms);
			auto something = Graphics::Shader::Shader::construct("simple_in_thread", "Assets/Shaders/simple.vert", "Assets/Shaders/simple.frag");
			l.debug("Current-{}", id);
		}
	});
#endif

	va = Graphics::VertexArray::VertexArray::construct();

	va->bind();
	mesh = Graphics::Mesh::Mesh::construct("Assets/Models/sphere.obj");
	va->unbind();
}

void MyLayer::on_update(std::float_t)
{
	// Render
	// Clear the colorbuffer
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glViewport(0, 0, 1280, 700);

	// Draw our first triangle
	{
		Engine::Core::ExecutionScope::ProfiledExecutionScope s({ va, shader });
		shader->bind();
		mesh->draw();
	}
}

void MyLayer::on_delete() { }
