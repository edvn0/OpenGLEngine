#pragma once

#include "common/logger.hpp"
#include "common/logger_provider.hpp"
#include "graphics/graphics.hpp"
#include "graphics/mesh.hpp"
#include "graphics/shader.hpp"
#include "graphics/uniform_buffer.hpp"
#include "graphics/vertex_array.hpp"
#include "main.hpp"
#include "scene/camera.hpp"
#include "scene/scene_camera.hpp"
#include "startup/startup.hpp"

#include <glad/glad.h>
#include <thread>

using namespace Engine;

class MyLayer : public Layer::Layer {
public:
	explicit MyLayer(Startup::Main<1>&)
		: logger("MyLayer") {};
	~MyLayer() override { logger.info("Deleted layer MyLayer."); };

	void on_create() override;
	void on_update(std::float_t) override;
	void on_delete() override;

private:
	void update_uniforms();

	Logging::Logger logger;
	Scene::SceneCamera::SceneCamera camera;
	RefPtr<Graphics::Shader::Shader> shader;
	RefPtr<Graphics::Mesh::Mesh> mesh;
	RefPtr<Graphics::UniformBuffer::UniformBuffer> ubo;
	RefPtr<Graphics::Mesh::Mesh> made_up;
};
