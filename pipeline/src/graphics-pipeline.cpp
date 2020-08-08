#include "graphics-pipeline.hpp"
#include "input.hpp"
#include "exceptions.hpp"

void cursorpos_callback(GLFWwindow * window, double xpos, double ypos)
{
    Input::getInstance()->on_mouse_move(xpos, ypos);
}

void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
    if(action == GLFW_PRESS && key == GLFW_KEY_ESCAPE) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    if(action == GLFW_PRESS) {
        Input::getInstance()->on_key_down(key);
    }
    if(action == GLFW_RELEASE) {
        Input::getInstance()->on_key_up(key);
    }
}

void mousebutton_callback(GLFWwindow * window, int button, int action, int mods) {
    if(action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT) {
        Input::getInstance()->on_left_mouse_down();
    }
    else if(action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_RIGHT) {
        Input::getInstance()->on_right_mouse_down();
    }
    else if(action == GLFW_RELEASE && button == GLFW_MOUSE_BUTTON_LEFT) {
        Input::getInstance()->on_left_mouse_up();
    }
    else if(action == GLFW_RELEASE && button == GLFW_MOUSE_BUTTON_RIGHT) {
        Input::getInstance()->on_right_mouse_up();
    }
}

GraphicsPipeline::GraphicsPipeline(const std::string & title, int screen_width, int screen_height)
:title(title), screen_width(screen_width), screen_height(screen_height), aspect((float)screen_width/(float)screen_height), window(nullptr)
{

}

float GraphicsPipeline::get_aspect() const
{
    return aspect;
}

GraphicsPipeline::~GraphicsPipeline()
{
    if(window != NULL) {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
}

void GraphicsPipeline::mainloop()
{
    if(glfwInit() == GLFW_FALSE) {
        throw PipelineException("Failed to initialize GLFW");
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GL_FALSE);
#endif
    GLFWwindow * window = glfwCreateWindow(screen_width, screen_height, title.c_str(), NULL, NULL);
    if(window == NULL) {
        throw PipelineException("Failed to make window");
    }
    glfwMakeContextCurrent(window);
    glfwSetCursorPosCallback(window, cursorpos_callback);
    glfwSetMouseButtonCallback(window, mousebutton_callback);
    glfwSetKeyCallback(window, key_callback);
    Input::getInstance()->setGraphicsPipeline(this);
    if(gladLoadGL() == GL_FALSE) {
        throw PipelineException("Failed to init glad");
    }
    glViewport(0, 0, screen_width, screen_height);
    setup();
    double last_time = glfwGetTime();
    while(!glfwWindowShouldClose(window)) {
        double cur_time = glfwGetTime();
        double delta_time = cur_time - last_time;
        last_time = cur_time;

        update(delta_time);
        draw();

        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    takedown();
}

void GraphicsPipeline::setup()
{

}

void GraphicsPipeline::takedown()
{

}

void GraphicsPipeline::update(double delta_time)
{

}

void GraphicsPipeline::draw()
{
    glClearColor(0.2, 0.3, 0.3, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}


void GraphicsPipeline::on_mouse_move(double xpos, double ypos)
{

}
void GraphicsPipeline::on_left_mouse_down()
{

}
void GraphicsPipeline::on_right_mouse_down()
{

}
void GraphicsPipeline::on_left_mouse_up()
{

}
void GraphicsPipeline::on_right_mouse_up()
{

}
void GraphicsPipeline::on_key_down(int key)
{

}
void GraphicsPipeline::on_key_up(int key)
{

}
