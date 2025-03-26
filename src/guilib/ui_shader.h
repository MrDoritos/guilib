#pragma once

#include "shader_program.h"

namespace gui {

struct UIShader : public shader_program_t {
    inline UIShader(const shader_program_t &base, const float &mixFactor, const glm::mat4 &projection)
        :shader_program_t(base),
         mixFactor(mixFactor),
         projection(projection) { }

    inline UIShader(const shader_program_t &base)
        :UIShader(base, 0.0f, glm::mat4(1.0f)) { }

    template<typename ...T>
    inline UIShader(T ...shaders)
        :UIShader(shader_program_t(shaders...)) { }

    float mixFactor;
    glm::mat4 projection;

    // Maintain constant aspect ratio
    void set_buffer_size(int width, int height) {
        auto aspect = float(width) / height;
        projection = glm::translate(glm::mat4(1), glm::vec3(0,1-aspect,0));
        projection = glm::scale(projection, glm::vec3(1, aspect, 1));
    }

    glm::mat4 get_projection() override {
        return projection;
    }

    void use() override {
        shader_program_t::use();

        glDisable(GL_DEPTH_TEST);
        glDisable(GL_CULL_FACE);

        set_f("mixFactor", mixFactor);
        set_m4("projection", projection);
    }
};

}