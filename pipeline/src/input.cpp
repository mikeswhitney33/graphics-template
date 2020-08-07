#include "input.hpp"


Input * Input::getInstance()
{
    if(instance == nullptr) {
        instance = new Input();
    }
    return instance;
}

void Input::setGraphicsPipeline(GraphicsPipeline * pipeline)
{
    this->pipeline = pipeline;
}

void Input::on_mouse_move(double xpos, double ypos)
{
    if(pipeline != nullptr) {
        pipeline->on_mouse_move(xpos, ypos);
    }
}

void Input::on_left_mouse_down()
{
    if(pipeline != nullptr) {
        pipeline->on_left_mouse_down();
    }
    leftMouseDown = true;
}

void Input::on_right_mouse_down()
{
    if(pipeline != nullptr) {
        pipeline->on_right_mouse_down();
    }
    rightMouseDown = true;
}

void Input::on_left_mouse_up()
{
    if(pipeline != nullptr) {
        pipeline->on_left_mouse_up();
    }
    leftMouseDown = false;
}

void Input::on_right_mouse_up()
{
    if(pipeline != nullptr) {
        pipeline->on_right_mouse_up();
    }
    rightMouseDown = false;
}

void Input::on_key_up(int key)
{
    if(pipeline != nullptr) {
        pipeline->on_key_up(key);
    }
    keymap[key] = false;
}

void Input::on_key_down(int key)
{
    if(pipeline != nullptr) {
        pipeline->on_key_down(key);
    }
    keymap[key] = true;
}

bool Input::isLeftMouseDown() const
{
    return leftMouseDown;
}

bool Input::isRightMouseDown() const
{
    return rightMouseDown;
}

bool Input::isKeyDown(int key) const
{
    std::map<int, bool>::const_iterator val = keymap.find(key);
    if(val == keymap.end()) {
        return false;
    }
    return val->second;
}

Input * Input::instance = nullptr;

Input::Input()
:pipeline(nullptr)
{}

Input::~Input()
{}

