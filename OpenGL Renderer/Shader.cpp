
#include "Include.h"
#include "Util.hpp"
#include "Shader.h"

#include <iostream>
#include <glm/gtc/type_ptr.hpp> // Included for glm::value_pt, needed for SetVec

const std::string shaderPath = "shaders/";

const char* vertexShaderSource = "#version 460 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 460 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

void Shader::Load(std::string vertexPath, std::string fragmentPath) {
    const char* vertexSource = Util::ReadFileChar(shaderPath + vertexPath + ".vert");
    const char* fragmentSource = Util::ReadFileChar(shaderPath + fragmentPath + ".frag");

    //vertexSource = vertexShaderSource;
    //fragmentSource = fragmentShaderSource;

    unsigned int vertexShader, fragmentShader, shaderProgram;
    int success;
    char infoLog[512];

    // Compile the vertex shader
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    // Check if it actually compiled
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "Error compiling Vertex Shader (" + vertexPath + ")" << std::endl;
    }

    // Compile the fragment shader
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    // Check if it actually compiled
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "Error compiling Fragment Shader (" + fragmentPath + ")" << std::endl;
    }

    // Link both Shaders together
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "Error linking shaders (" + vertexPath + ", " + fragmentPath + ")" << std::endl;
    }
    else {
        ID = shaderProgram;
    }

    // Delete the shaders we compiled
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::Use() {
    glUseProgram(ID);
}

void Shader::SetBool(std::string name, bool value) {
    int location = glGetUniformLocation(ID, name.c_str());
    glUniform1i(location, (int)value);
}

void Shader::SetInt(std::string name, int value) {
    int location = glGetUniformLocation(ID, name.c_str());
    glUniform1i(location, (int)value);
}

void Shader::SetFloat(std::string name, float value) {
    int location = glGetUniformLocation(ID, name.c_str());
    glUniform1f(location, value);
}

void Shader::SetVec3(std::string name, glm::vec3 value) {
    int location = glGetUniformLocation(ID, name.c_str());
    glUniform3fv(location, 1, glm::value_ptr(value));
}

void Shader::SetVec4(std::string name, glm::vec4 value) {
    int location = glGetUniformLocation(ID, name.c_str());
    glUniform4fv(location, 1, glm::value_ptr(value));
}

void Shader::SetMat4(std::string name, glm::mat4 value) {
    int location = glGetUniformLocation(ID, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}
