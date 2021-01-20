#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Polygon.h"
#include "ImguiSetup.h"
#include "Math/Point.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

bool drawingPolygon = true;
glm::vec3 polygonColor(1.0f, 1.0f, 1.0f);
glm::vec3 cutColor(1.0f, 0.0f, 0.0f);
ImguiSetup im;

std::vector<Point> polygonVertices = {};
std::vector<unsigned int> polygonIndices = {};

std::vector<Point> cutVertices = {};
std::vector<unsigned int> cutIndices = {};

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void processInput(GLFWwindow *window);

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {

        double xpos, ypos;
        //getting cursor position
        glfwGetCursorPos(window, &xpos, &ypos);
        int width, height;
        glfwGetWindowSize(window, &width, &height);
        float xClip = (xpos / width) * 2.0 - 1.0;
        float yClip = 1.0 - (ypos / height) * 2.0; // the Y is usually upside down

        Point p(xClip, yClip);
        if (im.getIsWindowTracing()) {
            polygonVertices.push_back(p);
            polygonIndices.push_back(polygonVertices.size() - 1);
        } else {
            cutVertices.push_back(p);
            cutIndices.push_back(cutVertices.size() - 1);
        }
    }
}

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char *vertexShaderSource = "#version 430 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, 0, 1.0);\n"
                                 "}\0";
const char *fragmentShaderSource = "#version 430 core\n"
                                   "layout (location = 2) uniform vec3 color;\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(color, 1.0f);\n"
                                   "}\n\0";

int main() {
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

    unsigned int polygonVBO, polygonVAO, polygonEBO;
    unsigned int cutVBO, cutVAO, cutEBO;

    im.init(window);
    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window)) {
        if (polygonVertices.size() > 3) {
            glGenVertexArrays(1, &polygonVAO);
            glGenBuffers(1, &polygonVBO);
            glGenBuffers(1, &polygonEBO);
            // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
            glBindVertexArray(polygonVAO);

            glBindBuffer(GL_ARRAY_BUFFER, polygonVBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, polygonEBO);
            glBufferData(GL_ARRAY_BUFFER, polygonVertices.size() * sizeof(Point), &polygonVertices[0], GL_STATIC_DRAW);

            glBufferData(GL_ELEMENT_ARRAY_BUFFER, polygonIndices.size() * sizeof(Point), &polygonIndices[0],
                         GL_STATIC_DRAW);

            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *) 0);
            glEnableVertexAttribArray(0);

            // note that this is allowed, the call to glVertexAttribPointer registered polygonVBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            // remember: do NOT unbind the polygonEBO while a polygonVAO is active as the bound element buffer object IS stored in the polygonVAO; keep the polygonEBO bound.
            //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

            // You can unbind the polygonVAO afterwards so other polygonVAO calls won't accidentally modify this polygonVAO, but this rarely happens. Modifying other
            // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
            glBindVertexArray(0);
        }
        if (cutVertices.size() > 3) {
            glGenVertexArrays(1, &cutVAO);
            glGenBuffers(1, &cutVBO);
            glGenBuffers(1, &cutEBO);
            // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
            glBindVertexArray(cutVAO);

            glBindBuffer(GL_ARRAY_BUFFER, cutVBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cutEBO);
            glBufferData(GL_ARRAY_BUFFER, cutVertices.size() * sizeof(Point), &cutVertices[0], GL_STATIC_DRAW);

            glBufferData(GL_ELEMENT_ARRAY_BUFFER, cutIndices.size() * sizeof(Point), &cutIndices[0],
                         GL_STATIC_DRAW);

            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *) 0);
            glEnableVertexAttribArray(0);

            // note that this is allowed, the call to glVertexAttribPointer registered polygonVBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            // remember: do NOT unbind the polygonEBO while a polygonVAO is active as the bound element buffer object IS stored in the polygonVAO; keep the polygonEBO bound.
            //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

            // You can unbind the polygonVAO afterwards so other polygonVAO calls won't accidentally modify this polygonVAO, but this rarely happens. Modifying other
            // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
            glBindVertexArray(0);
        }
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        im.firstUpdate();
        if (polygonVertices.size() > 3) {
            // draw our first triangle
            glUseProgram(shaderProgram);
            glUniform3fv(2, 1, glm::value_ptr(polygonColor));

            glBindVertexArray(
                    polygonVAO); // seeing as we only have a single polygonVAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
            //glDrawArrays(GL_TRIANGLES, 0, 6);
            glDrawElements(GL_LINE_LOOP, polygonIndices.size(), GL_UNSIGNED_INT, 0);
        }
        if (cutVertices.size() > 3) {
            // draw our first triangle
            glUseProgram(shaderProgram);
            glUniform3fv(2, 1, glm::value_ptr(cutColor));

            glBindVertexArray(
                    cutVAO); // seeing as we only have a single polygonVAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
            //glDrawArrays(GL_TRIANGLES, 0, 6);
            glDrawElements(GL_LINE_LOOP, cutIndices.size(), GL_UNSIGNED_INT, 0);
        }
        // glBindVertexArray(0); // no need to unbind it every time
        im.update();
        im.lastUpdate();
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &polygonVAO);
    glDeleteBuffers(1, &polygonVBO);
    glDeleteBuffers(1, &polygonEBO);
    glDeleteProgram(shaderProgram);
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_TRUE)
        drawingPolygon = !drawingPolygon;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}