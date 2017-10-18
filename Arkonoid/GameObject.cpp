#define GLEW_STATIC

#include "GameObject.h"
#include <GLFW/glfw3.h>

using namespace std;

GameObject::GameObject(GLFWwindow* window)
{
    glfwGetWindowSize(window, &_width, &_height);
}

float GameObject::GetX(int cell)
{
    int maxCell = _width / 10;
    return -1 + cell * 2.0f / maxCell;
}

float GameObject::GetY(int cell)
{
    int maxCell = _height / 10;
    return -1 + cell * 2.0f / maxCell;
}

void GameObject::Draw()
{
    // default implementation
}

void GameObject::Destroy()
{
    // default implementation
}