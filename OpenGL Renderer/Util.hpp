#pragma once

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <string>

namespace Util {
    std::string ReadFile(std::string path);
    char* ReadFileChar(std::string path);
}

std::string Util::ReadFile(std::string path) {
    std::string contents;
    std::ifstream file(path);
    
    std::string line;
    while (std::getline(file, line)) {
        contents += line + "\n";
    }

    return contents;
}

char* Util::ReadFileChar(std::string path) {
    std::string source;
    std::ifstream file(path);

    // Loop over each line, add it to a string with a line skip at the end
    std::string line;
    while (std::getline(file, line)) {
        source += line + "\n";
    }

    // Create a char array with the size of the source string and copy it over
    char* content = new char[source.size() + 1];
    std::copy(source.begin(), source.end(), content);
    content[source.size()] = '\0';

    return content;
}
