#pragma once

#include <glm/gtc/matrix_transform.hpp>

#include "common.h"

namespace util {
    template<typename T = float, typename vec = glm::vec<3, T>, typename mat = glm::mat<4, 4, T>>
    constexpr inline vec matrix_to_vector(const mat &m) {
        return glm::normalize(vec(m[2]));
    }
    
    template<typename T = float, typename vec = glm::vec<3, T>, typename mat = glm::mat<4, 4, T>>
    constexpr inline mat vector_to_matrix(const vec &v) {
        using vec4 = glm::vec<4, T>;

        const vec4 h_coords = vec4(v[0], v[1], v[2], T(1));
        const mat h_matrix = mat(h_coords, h_coords, h_coords, h_coords);

        return mat(T(1)) * h_matrix;        
    }
    
    template<typename T = float, typename vec = glm::vec<3, T>>
    constexpr inline vec rotate_vector_3d(const vec &v, const vec &axis, const T &degrees) {
        const T radians = glm::radians(degrees);
        using mat = glm::mat<4, 4, T>;

        const mat matrix = util::vector_to_matrix(v);
        const mat rotated = glm::rotate(matrix, radians, axis);

        return util::matrix_to_vector(rotated);
    }

    template<typename T = float, typename vec = glm::vec<3, T>>
    constexpr inline vec map_to_xy(const vec &pos, const T &degrees = T(0), const vec &axis = vec(T(0)), const vec &origin = vec(T(0)), const vec &translate = vec(T(0))) {
        const T radians = glm::radians(degrees);

        auto matrix = glm::mat<4, 4, T>(T(1));
        matrix = glm::rotate<T>(matrix, radians, axis);
        auto _pos = pos - origin;

        return vec(matrix * glm::vec<4, T>(_pos[0], _pos[1], _pos[2], T(1))) + translate;
    }

    template<typename T = float, typename T2 = T, typename T3 = T>
    constexpr inline T wrap(const T &v, const T2 &min, const T3 &max) {
        T ret = v;
        const T r = max - min;
        while (ret < min) ret += r;
        while (ret > max) ret -= r;
        return ret;
    }

    // Also known as clamp
    template<typename T = float, typename T2 = T, typename T3 = T>
    constexpr inline T clip(const T &v, const T2 &min, const T3 &max) {
        T ret = v;
        if (ret < min) ret = min;
        if (ret > max) ret = max;
        return ret;
    }

    // Don't really know what this would be called
    template<typename V_T = float,
             typename M_T = float,
             int V_L = 2,
             int M_L = 4,
             typename vec = glm::vec<V_L, V_T>,
             typename mat = glm::mat<M_L, M_L, M_T>>
    constexpr inline vec project_screen(const vec &screen, const mat &projection) {
        using m_vec = glm::vec<M_L, typename mat::value_type>;
        using s_vec = glm::vec<V_L, typename m_vec::value_type>;
        m_vec v;

        constexpr auto count = std::min(V_L, M_L);
        for (auto i = 0; i < count; i++)
            v[i] = screen[i];

        return vec(v / projection);
    }

    template<typename V_T = float,
             typename M_T = float,
             int M_L = 4,
             typename vec = glm::vec<2, V_T>,
             typename mat = glm::mat<M_L, M_L, M_T>>
    constexpr inline vec project_screen(const V_T &x, const V_T &y, const mat &projection) {
        return project_screen(vec(x, y), projection);
    }
}