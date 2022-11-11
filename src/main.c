#include "pch.h"

#include "callback.c"
#include "render.c"

#define VSYNC GLFW_TRUE
#define MSAA_SAMPLE_RATE 8

int main()
{
    glfwInit();
    glfwSetErrorCallback(error_callback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, MSAA_SAMPLE_RATE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL", NULL, NULL);
    enable_window_focus_lock(window);

    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetWindowFocusCallback(window, window_focus_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(VSYNC);

    glewInit();

    init_render();

    while (!glfwWindowShouldClose(window)) {
        const GLdouble time = glfwGetTime();
        delta_time = time - prev_time;

        glfwPollEvents();
        render();
        glfwSwapBuffers(window);

        prev_time = time;
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
