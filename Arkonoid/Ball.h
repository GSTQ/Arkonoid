#ifndef BALL_H
#define BALL_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Shader.h"
#include "GameObject.h"

class Ball : public GameObject
{
public:
    Ball(GLFWwindow* window);
    virtual void Draw();
    virtual void Destroy();
private:
    GLuint VBO, VAO, EBO;
    GLfloat* _vertices;
    Shader _shader;
    glm::vec3 _position;
};


#endif
