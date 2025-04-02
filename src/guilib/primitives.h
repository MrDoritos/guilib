#pragma once

#include "common.h"

namespace gui {
    template<typename T>
    int add_rectangle_2d(T *verts, const glm::vec4 &XYWH, const glm::vec4 &UVWH) {
        const auto &x = XYWH.x, &y = XYWH.y, &w = XYWH.z, &h = XYWH.w;
        const auto &u = UVWH.x, &v = UVWH.y, &uw = UVWH.z, &vh = UVWH.w;

        const T verticies[6] = {
            {x,y,u,v},
            {x+w,y,u+uw,v},
            {x,y+h,u,v+vh},
            {x+w,y,u+uw,v},
            {x+w,y+h,u+uw,v+vh},
            {x,y+h,u,v+vh}
        };

        memcpy(verts, &verticies[0], sizeof verticies);

        return 6;
    }

    template<typename T>
    int add_rectangle_3d(T *verts, const glm::mat4 &matrix, const glm::vec3 &scale, const glm::vec4 &UVWH, const glm::vec3 &color = glm::vec4(0)) {
        const glm::vec4 size[2] = {
                glm::vec4(scale, 1.0f),
                glm::vec4(-scale, 1.0f)};

        const glm::vec3 origin(matrix[3]),
                        normal(glm::vec4(1.0) * matrix);

        /*
        const glm::vec3 a(matrix[2] * size[0]),
                        b(matrix[0] * size[0]),
                        c(matrix[0] * size[1]),
                        d(matrix[2] * size[1]);
        */

        const glm::vec3 a(matrix * glm::vec4(0,0,0,0)),
                        b(matrix * glm::vec4(0,1,0,0)),
                        c(matrix * glm::vec4(1,0,0,0)),
                        d(matrix * glm::vec4(1,1,0,0));

        const float &u = UVWH.x, &v = UVWH.y, &uw = UVWH.z, &vh = UVWH.w;

        struct {
            const glm::vec3 coords;
            const glm::vec2 tex;
            const glm::vec3 color;
        } verticies[6] = {
            {a, {u,v}, color},
            {b, {u+uw,v}, color},
            {c, {u,v+vh}, color},
            {b, {u+uw,v}, color},
            {d, {u+uw,v+vh}, color},
            {c, {u,v+vh}, color}
        };

        for (int i = 0; i < 6; i++)
            verts[i] = T(verticies[i].coords + origin, normal, verticies[i].tex, verticies[i].color);

        return 6;
    }

}