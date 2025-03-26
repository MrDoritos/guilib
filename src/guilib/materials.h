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

    inline void set_light(const v3 &ambient, const v3 &diffuse, const v3 &specular) {
        this->ambient = ambient;
        this->diffuse = diffuse;
        this->specular = specular;
    }

    inline void set_position(const v3 &position) {
        this->position = position;
    }
};

namespace gui {

struct MaterialShader : public shader_program_t {
    inline MaterialShader(const shader_program_t &base, material_t *material, light_t *light):shader_program_t(base),material(material),light(light){}
    inline MaterialShader(){}
    template<typename ...T>
    inline MaterialShader(material_t *material, light_t *light, T ...shaders)
        :MaterialShader(shader_program_t(shaders...), material, light) { }

    material_t *material;
    light_t *light;
    glm::vec3 eye_position;

    inline void set_material(material_t *material) {
        this->material = material;
    }

    inline void set_light(light_t *light) {
        this->light = light;
    }

    inline void set_light(const light_t &light) {
        assert(this->light && "Light is null\n");
        *this->light = light;
    }

    inline void set_eye_position(const glm::vec3 &eye_position) {
        this->eye_position = eye_position;
    }

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

        set_v3("eyePos", eye_position);
    }
};

}