#pragma once

#include "common.h"
#include "texture.h"

struct vertex_t {
    vertex_t(const glm::vec3 &vertex, const glm::vec3 &normal, const glm::vec2 &tex, const glm::vec3 &color) 
        :vertex(vertex),
         normal(normal),
         tex(tex),
         color(color) { }

    vertex_t(){}

    glm::vec3 vertex, normal;
    glm::vec2 tex;
    glm::vec3 color;
};

struct mesh_t {
    std::vector<vertex_t> verticies;
    GLuint vao, vbo, vertexCount;
    glm::vec3 minBound, maxBound;
    glm::vec3 position;
    bool modified;
    
    mesh_t();

    bool loadStl(const char *filename);

    bool loadObj(const char *filepath);

    virtual bool isLoaded();

    // Generate gl buffers
    virtual bool load();

    // Delete gl buffers
    virtual bool unload();

    virtual void clear();

    virtual void mesh();

    virtual void render();
};
