#include <iostream>

#include "graphics-pipeline.hpp"
#include "exceptions.hpp"
#include "shader.hpp"


class RectanglePipeline : public GraphicsPipeline {
public:
    RectanglePipeline():GraphicsPipeline("triangle", 800, 600),shader(nullptr){
    }

    ~RectanglePipeline() {
        if(shader != nullptr) {
            delete shader;
        }
    }

protected:
    virtual void setup() {
        float vertices[] = {
            -0.5, -0.5,
            -0.5, 0.5,
            0.5, 0.5,
            0.5, -0.5
        };

        unsigned int VBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void *) 0);
        glEnableVertexAttribArray(0);

        const char * vsource = "#version 330 core\n"
        "layout (location = 0) in vec2 aPos;"
        "void main(){"
        "gl_Position = vec4(aPos, 0, 1);"
        "}\0";
        const char * fsource = "#version 330 core\n"
        "out vec4 FragColor;"
        "void main(){"
        "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);"
        "}\0";
        shader = new Shader();
        shader->addVertexShader(vsource);
        shader->addFragmentShader(fsource);
        shader->link();
    }

    virtual void draw()
    {
        glClearColor(0.2, 0.3, 0.3, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glBindVertexArray(VAO);
        shader->use();
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    }
private:
    unsigned int VAO;
    Shader * shader;
};

int main(int argc, char ** argv) {
    RectanglePipeline pipeline;
    try {
        pipeline.mainloop();
    } catch(PipelineException e) {
        std::cerr << e.what() << std::endl;
        return -1;
    } catch(ShaderException e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }
    return 0;
}
