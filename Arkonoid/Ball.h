#ifndef BALL_H
#define BALL_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Shader.h"
#include "GameObject.h"
#include "Raket.h"

class Ball : public GameObject
{
public:
    Ball(GLFWwindow* window, Raket* raket);
    virtual void Draw();
    virtual void Destroy();
private:
    Raket* _raket;
    GLuint VBO, VAO, EBO;
    GLfloat* _vertices;
    Shader _shader;
    glm::vec3 _position;
};


#endif
