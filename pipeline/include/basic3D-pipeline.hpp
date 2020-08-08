#ifndef BASIC3D_PIPELINE_HPP
#define BASIC3D_PIPELINE_HPP

#include "graphics-pipeline.hpp"

#include "camera.hpp"
#include "shader.hpp"

class Basic3DPipeline :public GraphicsPipeline
{
public:
    Basic3DPipeline();
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
    Camera camera;
    Shader * shader;
    unsigned int VAO;
    double lastx, lasty;
};

#endif // BASIC3D_PIPELINE