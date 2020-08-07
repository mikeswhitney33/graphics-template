#ifndef GRAPHICS_PIPELINE_HPP
#define GRAPHICS_PIPELINE_HPP

#include <iostream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>




class GraphicsPipeline
{
public:
    GraphicsPipeline(const std::string & title, int screen_width, int screen_height);
    ~GraphicsPipeline();
    void mainloop();

    virtual void on_mouse_move(double xpos, double ypos);
    virtual void on_left_mouse_down();
    virtual void on_right_mouse_down();
    virtual void on_left_mouse_up();
    virtual void on_right_mouse_up();
    virtual void on_key_down(int key);
    virtual void on_key_up(int key);
protected:
    virtual void setup();
    virtual void takedown();
    virtual void update(double delta_time);
    virtual void draw();
private:
    std::string title;
    int screen_width, screen_height;
    float aspect;
    GLFWwindow * window;
};


#endif // GRAPHICS_PIPELINE_HPP