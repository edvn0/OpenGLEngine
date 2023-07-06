#include "my_layer.hpp"

#include "common/verify.hpp"
#include "core/execution_scope.hpp"
#include "graphics/buffer_object.hpp"
#include "graphics/mesh.hpp"
#include "graphics/shader.hpp"
#include "graphics/uniform_buffer.hpp"
#include "graphics/vertex_array.hpp"
#include "processing/background_service.hpp"
#include "scene/camera.hpp"

#include <thread>

using namespace Engine;

struct UBO {
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;
	glm::mat4 mvp;
};

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

	camera = Engine::Scene::SceneCamera::SceneCamera(45.0f, 1280.0f, 720.f, 0.1f, 1000.f);

	std::vector<V> vertices;
	vertices.push_back(V { .pos = glm::vec4 { 1.0 }, .tex_coord = glm::vec2 { 1.0 }, .normal = glm::vec3 { 1.0 } });
	vertices.push_back(V { .pos = glm::vec4 { 0.0 }, .tex_coord = glm::vec2 { 1.0 }, .normal = glm::vec3 { 1.0 } });
	vertices.push_back(V { .pos = glm::vec4 { -1.0 }, .tex_coord = glm::vec2 { 1.0 }, .normal = glm::vec3 { 1.0 } });

	made_up = Graphics::Mesh::Mesh::construct("Triangle", vertices.data(), vertices.size() * sizeof(V));

	ubo = Graphics::UniformBuffer::UniformBuffer::construct(256);
	UBO ubo_data {};
	ubo->set_data(&ubo_data, sizeof(UBO));
}

void MyLayer::on_update(std::float_t ts)
{
	camera.on_update(ts);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glViewport(0, 0, 1280, 700);

	// Draw our first triangle
	{
		update_uniforms();

		shader->bind();
		mesh->draw();
		made_up->draw();
		shader->unbind();
		ubo->unbind();
	}
}

void MyLayer::on_delete() { }

void MyLayer::update_uniforms()
{
	const glm::mat4 model = glm::translate(glm::mat4 { 1.0 }, { 0, -1, 0 });
	const glm::mat4 view = camera.get_view_matrix();
	const glm::mat4 projection = camera.get_projection();
	const auto mvp = projection * view * model;
	UBO ubo_data { .model = model, .view = view, .projection = projection, .mvp = mvp };
	ubo->set_data(&ubo_data, sizeof(UBO));
	ubo->bind();
}
