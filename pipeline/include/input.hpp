#ifndef INPUT_HPP
#define INPUT_HPP

#include "graphics-pipeline.hpp"
#include <map>

class Input {
public:
    static Input * getInstance();
    void setGraphicsPipeline(GraphicsPipeline * pipeline);
    void on_mouse_move(double xpos, double ypos);
    void on_left_mouse_down();
    void on_right_mouse_down();
    void on_left_mouse_up();
    void on_right_mouse_up();
    void on_key_down(int key);
    void on_key_up(int key);

    bool isLeftMouseDown() const;
    bool isRightMouseDown() const;
    bool isKeyDown(int key) const;
private:
    static Input * instance;
    GraphicsPipeline * pipeline;
    Input();
    ~Input();

    bool leftMouseDown;
    bool rightMouseDown;
    std::map<int, bool>keymap;
};

#endif // INPUT_HPP