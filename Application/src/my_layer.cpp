#include "my_layer.hpp"

#include "common/verify.hpp"
#include "core/execution_scope.hpp"
#include "graphics/mesh.hpp"
#include "graphics/shader.hpp"
#include "graphics/vertex_array.hpp"
#include "graphics/buffer_object.hpp"
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

	mesh = Graphics::Mesh::Mesh::construct("Assets/Models/sphere.obj");

  using V = Engine::Graphics::Vertex::Vertex;

  std::vector<V> vertices;
  vertices.push_back(V{.pos=glm::vec4{1.0}, .tex_coord=glm::vec2{1.0}, .normal=glm::vec3{1.0}});

  made_up = Graphics::Mesh::Mesh::construct("Triangle", vertices.data(), vertices.size() * sizeof(V));
}

void MyLayer::on_update(std::float_t)
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glViewport(0, 0, 1280, 700);

	// Draw our first triangle
	{
		shader->bind();
		mesh->draw();
	  made_up->draw();
  }
}

void MyLayer::on_delete() { }
