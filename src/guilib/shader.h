#pragma once

#include <fstream>
#include <sstream>

#include "common.h"

struct shader_t {
    GLuint shaderId;
    GLenum type;
    std::string path;

    inline shader_t(const GLenum &type)
    :type(type),shaderId(gluninitialized) { }

    inline shader_t(const GLenum &type, const std::string &path)
    :type(type),shaderId(gluninitialized),path(path) { }

    inline constexpr bool isLoaded() const {
        return shaderId != gluninitialized;
    }

    bool load(const std::string &path);

    bool load();
};

namespace gui {

struct VertexShader : public shader_t {
    VertexShader():shader_t(GL_VERTEX_SHADER){}
    VertexShader(const std::string &path):shader_t(GL_VERTEX_SHADER, path) {}
};

struct FragmentShader : public shader_t {
    FragmentShader():shader_t(GL_FRAGMENT_SHADER){}
    FragmentShader(const std::string &path):shader_t(GL_FRAGMENT_SHADER, path) {}
};

}