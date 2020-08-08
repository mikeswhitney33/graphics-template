#ifndef BILLBOARD_HPP
#define BILLBOARD_HPP

#include "glm/glm.hpp"
#include "shader.hpp"


class Billboard
{
public:
    Billboard();
    ~Billboard();
    Billboard(const char * fsource);
    void draw(const glm::mat4 & view, const glm::vec3 & pos) const;
private:
    unsigned int VAO;
    Shader * shader;
};


#endif // BILLBOARD_HPP