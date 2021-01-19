#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Mesh.h"
#include "Shader.h"
#include "Polygon.h"
#include "Camera.h"

float deltaTime = 0.0f;    // Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

Camera cam;
int clickCount = 0;
int width, height;


void processInput(GLFWwindow *window, Camera *cam) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cam->moveForward(cam->getSpeed() * deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cam->moveBackward(deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cam->moveLeftward(deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cam->moveRightward(deltaTime);
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
	cam.mouse_callback(window, xpos, ypos);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        std::cout << "size of vertices : " << size(Vertices) << std::endl;

        double xpos, ypos;
        //getting cursor position
        glfwGetCursorPos(window, &xpos, &ypos);
        float xClip = (xpos + 0.5f) / 320.0f - 1.0f;
        float yClip = 1.0f - (ypos + 0.5f) / 240.0f;
        Vertices.push_back(xClip);
        Vertices.push_back(yClip);
        clickCount++;
        Indices.push_back();
        std::cout << "new size of vertices : " << size(Vertices) << std::endl;
        for (int i = 0; i < size(Vertices); i++) {
            std::cout << "point " << i << " : " << Vertices[i] << std::endl;;
        }
    }
}

//Rezise
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
	glViewport(0, 0, width, height);
}

void messageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message,
                     const void *userParam) {
	switch (severity) {
		case GL_DEBUG_SEVERITY_HIGH:
			std::cout << "ERROR " << id << ": " << message << std::endl;

		case GL_DEBUG_SEVERITY_MEDIUM:
			std::cout << "WARNING " << id << ": " << message << std::endl;
			break;
		case GL_DEBUG_SEVERITY_LOW:
			std::cout << "INFO " << id << ": " << message << std::endl;
			break;
	}
}

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

	GLFWwindow *window = glfwCreateWindow(800, 600, "cpp-base", nullptr, nullptr);

	if (window == nullptr) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	glViewport(0, 0, 800, 600); // Zone de rendu

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); //Rezise

	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glEnable(GL_DEPTH_TEST);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glDebugMessageCallback(messageCallback, nullptr);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

	std::cout << "Driver: " << glGetString(GL_VERSION) << "\n";
	std::cout << "GPU: " << glGetString(GL_RENDERER) << "\n";

	Shader myShader("basic");
	Mesh mesh;

	cam.init();

	while (!glfwWindowShouldClose(window)) {
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
        mesh.setVertices(&Vertices, sizeof(Vertices) / sizeof(float));
        mesh.setIndices(&Indices, sizeof(Indices) / sizeof(uint16_t));

        // Envents
		glfwPollEvents();

		// Inputs
		processInput(window, &cam);
		glfwSetCursorPosCallback(window, mouse_callback);

		//Rendering
		glClearColor(0.1f, 0.2f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		myShader.bind();

		//Use mesh
        mesh.bind();
		glDrawElements(GL_LINE_LOOP, sizeof(Indices) / sizeof(uint16_t), GL_UNSIGNED_SHORT, nullptr);
        mesh.unbind();

		//Draw mesh

		glfwSwapBuffers(window);
	}
	glfwTerminate();
	return 0;
}
