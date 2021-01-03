#include <string>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../common/GLShader.h"

#include "./src/imgui/imgui.h"
#include "./src/imgui/imgui_impl_glfw_gl3.h"

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

        std::cout << "OpenGL version supported by this platform : " << glGetString(GL_VERSION);
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
            -0.8,-0.8f,// Premier Sommet
            1.f, 0.f, 0.f,
            -0.5f, +0.6f, // Deuxième Sommet
            0.f,1.f,0.f,
            +0.4f,+0.5f, // Troisième Sommet
            0.f,0.f,1.f,
            +0.9f,-0.9f, // Quatrième Sommet
            1.f,1.f,1.f
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
        glDrawArrays(GL_POLYGON, 0, 4 /*nb sommets*/);

        glDrawElements(GL_POLYGON, 4 /*nb indice */, GL_UNSIGNED_SHORT, indices);
    }
};

struct ImguiSetup
{

    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    /// <summary>
    /// Execute before loop
    /// </summary>
    /// <param name="window"></param>
    void Initialize(GLFWwindow* window){
        ImGui::CreateContext();
        ImGui_ImplGlfwGL3_Init(window, true);
        ImGui::StyleColorsDark();
    }

    /// <summary>
    /// Exectute at begin of loop update but after clear and before swap buffer
    /// </summary>
    void FirstUpdate() {
        ImGui_ImplGlfwGL3_NewFrame();
    }
    /// <summary>
    /// Exectute in loop update
    /// </summary>
    void Update() {

        static float f = 0.0f;
        static int counter = 0;
        ImGui::Text("Hello, world!");                           // Display some text (you can use a format string too)
        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f    
        ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

        ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our windows open/close state
        ImGui::Checkbox("Another Window", &show_another_window);

        if (ImGui::Button("Button"))                            // Buttons return true when clicked (NB: most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

        ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
    }
    /// <summary>
    /// Execute at end of loop 
    /// </summary>
    void LastUpdate() {

    }

    /// <summary>
    /// Execute after loop
    /// </summary>
    void Terminate() {
        ImGui_ImplGlfwGL3_Shutdown();
        ImGui::DestroyContext();
    }
};


int main(void)
{

    GLFWwindow* window;
    Application app;
    ImguiSetup imguiSetup;
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

    imguiSetup.Initialize(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        imguiSetup.FirstUpdate();
        app.Display(window);

        imguiSetup.Update();
        /* Swap front and back buffers */
        glfwSwapBuffers(window);


        /* Poll for and process events */
        glfwPollEvents();

    }
    imguiSetup.Terminate();
    app.Terminate();
    glfwTerminate();
    return 0;
}
