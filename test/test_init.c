#include <stdlib.h>
#include <stdio.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main(int argc, char ** argv)
{
    if(glfwInit() == GLFW_FALSE)
    {
        fprintf(stderr, "Failed initialize GLWF\n");
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GL_FALSE);
#endif

    GLFWwindow * window = glfwCreateWindow(800, 600, "Test", NULL, NULL);
    if(window == NULL)
    {
        fprintf(stderr, "Failed to make window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if(gladLoadGL() == GL_FALSE)
    {
        fprintf(stderr, "Failed to init glad\n");
        glfwTerminate();
        glfwDestroyWindow(window);
        return -1;
    }
    glViewport(0, 0, 800, 600);

    glClearColor(0.2, 0.3, 0.3, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwPollEvents();
    glfwSwapBuffers(window);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
