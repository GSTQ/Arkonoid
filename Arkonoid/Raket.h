#ifndef RAKET_H
#define RAKET_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Shader.h"

class Raket
{
    public:
        Raket();
        Raket(GLFWwindow* window);
        void MoveLeft();
        void MoveRight();
        void Draw();
        void Destroy();
    private:
        float GetX(int cell);
        float GetY(int cell);
        GLuint VBO, VAO, EBO;
        GLfloat* _vertices;
        Shader _shader;
        glm::vec3 _position;
};

#endif