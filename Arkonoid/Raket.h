#ifndef RAKET_H
#define RAKET_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Shader.h"
#include "GameObject.h"

class Raket : public GameObject
{
    public:
        Raket(GLFWwindow* window);
        void MoveLeft();
        void MoveRight();
        virtual void Draw();
        virtual void Destroy();
        int Left, Top;
    private:
        float _step;
        glm::vec3 _position;
        GLuint VBO, VAO, EBO;
        GLfloat* _vertices;
        Shader _shader;
};

#endif