#include "iostream"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "Raket.h"
#include "Wall.h"


// Window dimensions
const GLuint WIDTH = 600, HEIGHT = 800;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

Raket* _raket;

GLFWwindow* initWindow();

int main()
{
    std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;
    GLFWwindow* window = initWindow();
    _raket = &Raket(window);
    Wall wall = Wall(window);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        wall.Draw();
        (*_raket).Draw();

        glfwSwapBuffers(window);
    }

    (*_raket).Destroy();
    wall.Destroy();
    glfwTerminate();


    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    //  огда пользователь нажимает ESC, мы устанавливаем свойство WindowShouldClose в true, 
    // и приложение после этого закроетс€
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if (key == GLFW_KEY_RIGHT)
    {
        (*_raket).MoveRight();
    }
    if (key == GLFW_KEY_LEFT)
    {
        (*_raket).MoveLeft();
    }
}

GLFWwindow* initWindow()
{
    //Init GLFW
    glfwInit();
    //Using OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //”становка профайла дл€ которого создаетс€ контекст
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return NULL;
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return NULL;
    }

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    return window;
}
