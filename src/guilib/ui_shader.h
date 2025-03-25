#pragma once

#include "shader_program.h"

namespace gui {

struct UIShader : public shader_program_t {
    UIShader(const shader_program_t &base)
            :shader_program_t(base),
             mixFactor(0) { }

    template<typename ...T>
    UIShader(T ...shaders):shader_program_t(shaders...) { }

    float mixFactor;

    void use() override {
        shader_program_t::use();

        set_f("mixFactor", mixFactor);
    }
};

}