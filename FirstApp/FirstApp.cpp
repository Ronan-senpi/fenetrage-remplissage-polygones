#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../common/GLShader.h"

struct Vertex {
    float x, y;
    float r, g, b;
};

struct Application {
    GLShader shader;

    bool Initialize() {
        shader.LoadVertexShader("basic.vs.glsl");
        shader.LoadFragmentShader("basic.fs.glsl");
        shader.Create();

        return true;
    }

    void Terminate() {
        shader.Destroy();
    }

    /// <summary>
/// Render here
/// </summary>
/// <param name="window"></param>
    void Display(GLFWwindow* window) {
        int width, height;
        /* Render here */
        glfwGetWindowSize(window, &width, &height);

        glViewport(0, 0, width, height);
        glClearColor(.5f, .5f, .5f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        //static const float triangle[] = {
        //    //(x,y)
        //    -0.8f, +0.8f, //1er sommet
        //    0.0f, -0.8f, // 2eme sommet
        //    +0.8f, +0.8f // 3eme sommet
        //};

        static const float triangle[] = {
            -0.8f,+0.8f,// Premier Sommet
            1.f, 0.f, 0.f,
            0.0f,-0.8f, // Deuxième Sommet
            0.f,1.f,0.f,
            +0.8f,+0.8f, // Troisième Sommet
            0.f,0.f,1.f
        };

        static const unsigned short indices[] = { 0, 1, 2 };

        GLuint program = shader.GetProgram();
        glUseProgram(program);
        //On indique a OpenGL la structuration des sommets
        //Stride : Interval en octets entre deux sommets
        GLint posLocation = glGetAttribLocation(program, "a_Position");
        //TODO : Faire en sorte que "Triangle" reste sur le GPU tant qu'il ne change pas
        // Buffer object, VBO(slide 28), 
        //TD 1 a partir de II rendu de triangle -Partie B
        glVertexAttribPointer(posLocation, 2 /*(x,y)*/, GL_FLOAT, false, sizeof(Vertex)/*Stride*/, triangle);
        glEnableVertexAttribArray(posLocation);

        GLint colorLocation = glGetAttribLocation(program, "a_Color");

        glVertexAttribPointer(colorLocation, 3 /*(r,g,b)*/, GL_FLOAT, false, sizeof(Vertex)/*Stride*/, &triangle[2]);
        glEnableVertexAttribArray(colorLocation);

        //dessine moi un triangle
        glDrawArrays(GL_TRIANGLES, 0, 3 /*nb sommets*/);

        glDrawElements(GL_TRIANGLES, 3 /*nb indice */, GL_UNSIGNED_SHORT, indices);
    }
};



int main(void)
{
    GLFWwindow* window;
    Application app;
    /* Initialize the glfw3 library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Initialize the glew library */
    glewInit();

    /*Important pour le tp*/
    app.Initialize();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        app.Display(window);
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    app.Terminate();
    glfwTerminate();
    return 0;
}
