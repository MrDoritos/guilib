#pragma once

#include "ui_text.h"

struct ui_slider_t : public ui_element_t {
    using ui_slider_v = float;
    using callback_t = std::function<void(ui_slider_t*, ui_slider_v)>;

    ui_slider_v min, max, value, drag_value, initial_value;
    bool cursor_drag, limit, skip_text;
    glm::vec2 cursor_start, drag_start;
    callback_t value_change_callback;

    ui_text_t *title_text, *min_text, *max_text, *value_text;
    float title_pos_y;
    float text_pos_y;
    std::string title_cached;
    texture_t *textTexture;
    shader_program_t *textProgram;

    ui_slider_t(GLFWwindow *window, shader_program_t *textProgram, texture_t *textTexture, glm::vec4 XYWH, ui_slider_v min, ui_slider_v max, ui_slider_v value, std::string title = std::string(), bool limit = true, callback_t value_change_callback = callback_t(), bool skip_text = false, bool hidden = false);

    ui_slider_t() {}

    virtual void set_min(ui_slider_v min);

    virtual void set_max(ui_slider_v max);

    virtual std::string vtos(ui_slider_v v);

    virtual void set_value(ui_slider_v v, bool callback = true);

    virtual void set_title(std::string title = std::string());

    virtual bool arrange_text();

    bool reset() override;

    std::string get_element_name() override;

    bool onCursor(double x, double y) override;

    glm::vec4 get_slider_position();

    bool onMouse(int button, int action, int mods) override;

    bool mesh() override;

    bool render() override;
};

namespace gui {
    template<typename T = ui_slider_t::ui_slider_v>
    struct UISliderSocket {
        struct ui_slider_t *slider;
    
        virtual void onChange(T value) {}
        virtual void onReset() {}
    };

    template<typename T = ui_slider_t::ui_slider_v>
    struct UISliderSocketPtr : public UISliderSocket<T> {
        UISliderSocketPtr(T *T_ptr):T_ptr(T_ptr) { 
            assert(T_ptr && "T_ptr is null\n");
        }

        T *T_ptr;

        void onChange(T value) override {
            *T_ptr = value;
        }
    };

    template<typename T = ui_slider_t::ui_slider_v, typename Socket = UISliderSocket<T>>
    struct UISliderSocketable : public ui_slider_t {
        using value_type = T;
        using socket_type = Socket;
        using base_type = ui_slider_t;

        socket_type socket;

        UISliderSocketable(const base_type &base, const socket_type &&socket)
                :base_type(base),socket(socket) { 
            this->socket.slider = this;
        }

        void set_value(value_type v, bool callback = true) override {
            socket.onChange(v);

            base_type::set_value(v, callback);
        }

        bool reset() override {
            socket.onReset();

            return glsuccess;
        }
    };
    
};
    