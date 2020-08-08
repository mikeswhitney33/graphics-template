#include "billboard.hpp"

Billboard::Billboard()
{

}

Billboard::Billboard(const char * fsource)
:shader(nullptr)
{
    float vertices[] = {
        -1.0f, -1.0f,
        -1.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, -1.0f
    };
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);
    glEnableVertexAttribArray(0);

    const char * vsource = "#version 330 core\n"
    "layout(location = 0) in vec2 aPos;"
    "uniform vec2 size;"
    "uniform vec3 center;"
    "uniform mat4 view;"
    "void main() {"
    "vec3 camr = vec3(view[0][0], view[1][0], view[2][0]);"
    "vec3 camu = vec3(view[0][1], view[1][1], view[2][1]);"
    "vec3 pos = center * camr * aPos.x * size.x + camu * aPos.y * size.y;"
    "gl_Position = vec4(pos, 1);"
    "}\0";
    shader = new Shader();
    shader->addVertexShader(vsource);
    shader->addFragmentShader(fsource);
    shader->link();
}

Billboard::~Billboard()
{
    if(shader != nullptr)
    {
        delete shader;
    }
}

void Billboard::draw(const glm::mat4 & view, const glm::vec3 & pos) const
{
    glBindVertexArray(VAO);
    shader->use();
    shader->setMat4("view", view);
    shader->setVec3("center", pos);
    shader->setVec2("size", glm::vec2(1, 1));
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}