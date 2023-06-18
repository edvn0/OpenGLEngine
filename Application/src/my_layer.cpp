#include "my_layer.hpp"
#include "processing/background_service.hpp"
#include "graphics/shader.hpp"

#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <thread>

using namespace Engine;

void MyLayer::on_create()
{
	shader = Graphics::Shader::Shader::construct("Assets/Shaders/simple.vert", "Assets/Shaders/simple.frag");

	Background::submit_work([&something = this->something](auto id) mutable {
		using namespace std::chrono_literals;
		something = Graphics::Shader::Shader::construct("Assets/Shaders/simple.vert", "Assets/Shaders/simple.frag");
		Logging::Logger logger { "InThread" };
		logger.debug("Current-{}", id);
	});

	// Set up vertex data (and buffer(s)) and attribute pointers
	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f, // Left
		0.5f, -0.5f, 0.0f, // Right
		0.0f, 0.5f, 0.0f // Top
	};
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex
									  // buffer object so afterwards we can safely unbind

	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)
}

void MyLayer::on_update(std::float_t)
{
	// Render
	// Clear the colorbuffer
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glViewport(0, 0, 1280, 700);

	// Draw our first triangle
	shader->bind();
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
}

void MyLayer::on_delete()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}
