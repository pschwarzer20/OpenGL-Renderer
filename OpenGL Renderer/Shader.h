#pragma once

#include <iostream>

class Shader {
public:
    unsigned int ID;

    void Load(std::string vertexShader, std::string fragmentShader);
    void Use();
    void SetBool(std::string name, bool value);
    void SetInt(std::string name, int value);
    void SetFloat(std::string name, float value);
    void SetVec3(std::string name, glm::vec3 value);
    void SetVec4(std::string name, glm::vec4 value);
    void SetMat4(std::string name, glm::mat4 value);
};
