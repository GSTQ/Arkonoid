#include "Shader.h"

using namespace std;

Shader::Shader()
{

}

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
    string vertexCode, fragmentCode;
    ifstream vShaderFile, fShaderFile;
    // �������������, ��� ifstream ������� ����� ���������� ����������
    vShaderFile.exceptions(ifstream::failbit);
    fShaderFile.exceptions(ifstream::failbit);
    try
    {
        // ��������� �����
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // ��������� ������ � ������
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // ��������� �����
        vShaderFile.close();
        fShaderFile.close();
        // ��������������� ������ � ������ GLchar
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (ifstream::failure e)
    {
        cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << endl;
    }
    const GLchar* vShaderCode = vertexCode.c_str();
    const GLchar* fShaderCode = fragmentCode.c_str();

    GLuint vertex, fragment;
    GLint success;
    GLchar infoLog[512];

    // ��������� ������
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    // ���� ���� ������ - ������� ��
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
    };

    //����������� ������
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    // ���� ���� ������ - ������� ��
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
    };


    // ��������� ���������
    this->Program = glCreateProgram();
    glAttachShader(this->Program, vertex);
    glAttachShader(this->Program, fragment);
    glLinkProgram(this->Program);
    //���� ���� ������ - ������� ��
    glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
        cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
    }

    // ������� �������, ��������� ��� ��� � ��������� � ��� ������ �� �����.
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::Use() 
{
    glUseProgram(this->Program);
}
