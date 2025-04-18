#pragma once

#include <glm/gtc/matrix_transform.hpp>

#include "common.h"

struct camera_t;

struct camera_t {
    inline camera_t(const glm::vec3 position = {0,0,0.}, const float pitch = 0., const float yaw = 0., const float fov = 90.)
    :position(position),pitch(pitch),yaw(yaw),fov(fov),
     up(0.0f,1.0f,0.0f),near(0.1f),far(1000.0f),last_mouse({0}),
     screenWidth(0),screenHeight(0)
    { calculate_normals(); }

    glm::vec3 position, up, front, right;
    float fov, near, far, pitch, yaw;
    double last_mouse[2];
    int screenWidth, screenHeight;
    bool no_mouse = true;
    bool interactive = false;

    inline glm::mat4 get_view_matrix() const {
        return glm::lookAt(position, position + front, up);
    }

    inline glm::mat4 get_projection_matrix() const {
        return glm::perspective(glm::radians(this->fov),
                                float(screenWidth) / screenHeight, 
                                this->near, this->far) * viewport_inversion;
    }

    inline glm::mat4 get_billboard_matrix() const {
        glm::mat4 mat(1.0);
        mat = glm::rotate(mat, -glm::radians(this->yaw + 90), up);
        mat = glm::rotate(mat, glm::radians(this->pitch + 90), glm::vec3(1, 0, 0));
        return mat;
    }

    inline constexpr bool isInteractive() const {
        return interactive;
    }

    void calculate_normals();

    void mousePress(GLFWwindow *window, int button, int action, int mods);

    void mouseMove(GLFWwindow *window, double x, double y);

    void joystick_move(GLFWwindow *window, float pitch, float yaw);

    void keyboard(GLFWwindow *window, float deltaTime);

    void onFramebuffer(GLFWwindow *window, int width, int height);
};
