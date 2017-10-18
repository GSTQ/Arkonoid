#define GLEW_STATIC

#include "Raket.h"
#include "Shader.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "iostream"
#include <GLFW/glfw3.h>

using namespace std;


Raket::Raket(GLFWwindow* window) : GameObject(window)
{
    int verticesCount = 12;

    _vertices = new GLfloat[verticesCount]{
        // Positions
        GetX(35),  GetY(4), 0.0f, //1
        GetX(35),  GetY(2),  0.0f, //2
        GetX(25),  GetY(2),  0.0f, //3
        GetX(25),  GetY(4), 0.0f, //0
    };

    GLuint indices[] = {
        0, 1, 3, // First Triangle
        1, 2, 3  // Second Triangle
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    cout << "Raket vertices size=" << sizeof(_vertices) * verticesCount << endl;
    glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices) * verticesCount, _vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0); // Unbind VAO

    _shader = Shader("vertex.glsl", "fragment.glsl");
    _position = glm::vec3(0.0f, 0.0f, 0.0f);
}

void Raket::Draw()
{
    _shader.Use();

    glm::mat4 transform;
    transform = glm::translate(transform, _position);

    GLint transformLoc = glGetUniformLocation(_shader.Program, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

    GLint colorLocation = glGetUniformLocation(_shader.Program, "ourColor");
    glUniform4f(colorLocation, 1.0f, 0.5f, 0.5f, 1.0f);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Raket::Destroy()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Raket::MoveLeft()
{
    float step = 2.0f / (_width / 10.0f);
    if (_position.x - 5 * step > GetX(2))
    {
        _position.x -= step;
    }
}

void Raket::MoveRight()
{
    float step = 2.0f / (_width / 10.0f);
    if (_position.x  + 5 * step < GetX(58))
    {
        _position.x += step;
    }
}
