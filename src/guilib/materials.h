#pragma once

#include "shader_program.h"

struct material_t {
    inline material_t(texture_t *diffuse, texture_t *specular, float gloss)
    :diffuse(diffuse),specular(specular),shininess(gloss) { }
    texture_t *diffuse, *specular;
    float shininess;

    inline void use(const int &unit = 0) const {
        diffuse->use(unit);
        specular->use(unit + 1);
    }
};

struct light_t {
    using v3 = glm::vec3;
    inline light_t(v3 position, v3 ambient, v3 diffuse, v3 specular)
    :position(position),ambient(ambient),diffuse(diffuse),specular(specular) { } 
    v3 position, ambient, diffuse, specular;
};

struct MaterialShader : public shader_program_t {
    MaterialShader(const shader_program_t &base, material_t *material, light_t *light):shader_program_t(base),material(material),light(light){}
    MaterialShader(){}

    material_t *material;
    light_t *light;

    void use() override {
        shader_program_t::use();

        material->use();

        set_v3("light.position", light->position);
        set_v3("light.ambient", light->ambient);
        set_v3("light.specular", light->specular);
        set_v3("light.diffuse", light->diffuse);

        set_f("material.shininess", material->shininess);
        set_sampler("material.diffuse", material->diffuse, 0);
        set_sampler("material.specular", material->specular, 1);
    }
};