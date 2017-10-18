#ifndef GAMEOBJ_H
#define GAMEOBJ_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"

class GameObject
{
public:
    GameObject();
    GameObject(GLFWwindow* window);
    virtual void Draw();
    virtual void Destroy();
protected:
    float GetX(int cell);
    float GetY(int cell);
    int _width, _height;
};
#endif