#ifndef WALL_H
#define WALL_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"

class Wall
{
public:
    Wall();
    Wall(GLFWwindow* window);
    void Draw();
    void Destroy();
private:
    GLuint _vbo, _vao, _ebo;
    Shader _shader;
};

#endif