#pragma once

#include "shader_program.h"

namespace gui {

struct UIShader : public shader_program_t {
    UIShader(const shader_program_t &base)
            :shader_program_t(base),
             mixFactor(0) { }

    template<typename ...T>
    UIShader(T ...shaders):shader_program_t(shaders...),mixFactor(0),projection(1.0f) { }

    float mixFactor;
    glm::mat4 projection;

    void use() override {
        shader_program_t::use();

        glDisable(GL_DEPTH_TEST);
        glDisable(GL_CULL_FACE);

        set_f("mixFactor", mixFactor);
        set_m4("projection", projection);
    }
};

}