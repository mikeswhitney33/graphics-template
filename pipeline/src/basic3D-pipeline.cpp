#include "basic3D-pipeline.hpp"
#include "exceptions.hpp"
#include "input.hpp"


Basic3DPipeline::Basic3DPipeline()
:GraphicsPipeline("Basic", 800, 600)
{}


void Basic3DPipeline::on_mouse_move(double xpos, double ypos)
{
    if(Input::getInstance()->isLeftMouseDown())
    {
        double xdiff = lastx - xpos;
        double ydiff = ypos - lasty;
        lastx = xpos;
        lasty = ypos;
        camera.rotate(xdiff, ydiff);
    }
}
void Basic3DPipeline::on_left_mouse_down()
{
    lastx = Input::getInstance()->getMouseX();
    lasty = Input::getInstance()->getMouseY();
}
void Basic3DPipeline::on_right_mouse_down()
{

}
void Basic3DPipeline::on_left_mouse_up()
{

}
void Basic3DPipeline::on_right_mouse_up()
{

}
void Basic3DPipeline::on_key_down(int key)
{

}
void Basic3DPipeline::on_key_up(int key)
{

}
void Basic3DPipeline::setup()
{
        float vertices[] = {
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
    glEnableVertexAttribArray(0);

    const char * vsource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;"
    "uniform mat4 model;"
    "uniform mat4 view;"
    "uniform mat4 projection;"
    "void main(){"
    "gl_Position = projection * view * model * vec4(aPos, 1.0);"
    "}\0";

    const char * fsource = "#version 330 core\n"
    "out vec4 FragColor;"
    "void main(){"
    "FragColor = vec4(1, 0, 0, 1);"
    "}\0";

    shader = new Shader();
    shader->addVertexShader(vsource);
    shader->addFragmentShader(fsource);
    shader->link();

    glEnable(GL_DEPTH_TEST);
    camera.Position = glm::vec3(0, 0, 3);
}
void Basic3DPipeline::takedown()
{

}
void Basic3DPipeline::update(double delta_time)
{
    if(Input::getInstance()->isKeyDown(GLFW_KEY_W)) camera.move(FORWARD, delta_time);
    if(Input::getInstance()->isKeyDown(GLFW_KEY_S)) camera.move(BACKWARD, delta_time);
    if(Input::getInstance()->isKeyDown(GLFW_KEY_A)) camera.move(LEFT, delta_time);
    if(Input::getInstance()->isKeyDown(GLFW_KEY_D)) camera.move(RIGHT, delta_time);
}
void Basic3DPipeline::draw()
{
    glClearColor(0.2, 0.3, 0.3, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindVertexArray(VAO);
    shader->use();
    shader->setMat4("model", glm::mat4(1));
    shader->setMat4("view", camera.getViewMatrix());
    shader->setMat4("projection", glm::perspective(glm::radians(45.0f), get_aspect(), 0.1f, 100.0f));
    glDrawArrays(GL_TRIANGLES, 0, 36);
}


int main() {
    Basic3DPipeline pipeline;
    try {
        pipeline.mainloop();
    } catch(PipelineException e) {
        std::cout << e.what() << std::endl;
        return -1;
    } catch(ShaderException e) {
        std::cout << e.what() << std::endl;
        return -1;
    }
    return 0;
}
