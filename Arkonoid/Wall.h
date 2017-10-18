#ifndef WALL_H
#define WALL_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "GameObject.h"

class Wall : public GameObject
{
public:
    Wall(GLFWwindow* window);
    virtual void Draw();
    virtual void Destroy();
private:
    GLuint _vbo, _vao, _ebo;
    Shader _shader;
};

#endif