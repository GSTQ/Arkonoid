#define GLEW_STATIC

#include "Wall.h"
#include "Shader.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "iostream"
#include <GLFW/glfw3.h>


using namespace std;

Wall::Wall()
{

}

float GetX(int cell)
{
    int maxCell = 60;
    return -1 + cell * 2.0f / maxCell;
}

float GetY(int cell)
{
    int maxCell = 80;
    return -1 + cell * 2.0f / maxCell;
}

Wall::Wall(GLFWwindow* window)
{
    float vertices[] = {
        // Positions
        GetX(2), GetY(80), 0.0f, //0
        GetX(2), GetY(0), 0.0f, //1
        GetX(0), GetY(0), 0.0f, //2
        GetX(0), GetY(80), 0.0f, //3
        GetX(0), GetY(78), 0.0f, //4
        GetX(60), GetY(78), 0.0f, //5
        GetX(60), GetY(80), 0.0f, //6
        GetX(60), GetY(0), 0.0f, //7
        GetX(58), GetY(0), 0.0f, //8
        GetX(58), GetY(80), 0.0f, //9

    };

    GLuint indices[] = {
        0, 1, 3, // First Triangle
        1, 2, 3,  // Second Triangle
        3, 4, 5,
        3, 5, 6,
        6, 7, 9,
        7, 8, 9
    };

    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vbo);
    glGenBuffers(1, &_ebo);

    glBindVertexArray(_vao);

    glBindBuffer(GL_ARRAY_BUFFER, _vbo);

    cout << "Wall vrtices size=" << sizeof(vertices) << endl;
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0); // Unbind VAO

    _shader = Shader("vertex.glsl", "fragment.glsl");
}

void Wall::Draw()
{
    _shader.Use();

    glm::mat4 transform;
    transform = glm::translate(transform, glm::vec3(0, 0, 0));

    GLint transformLoc = glGetUniformLocation(_shader.Program, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

    GLint colorLocation = glGetUniformLocation(_shader.Program, "ourColor");
    glUniform4f(colorLocation, 0.5f, 0.5f, 0.5f, 1.0f);

    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Wall::Destroy()
{
    glDeleteVertexArrays(1, &_vao);
    glDeleteBuffers(1, &_vbo);
    glDeleteBuffers(1, &_ebo);
}