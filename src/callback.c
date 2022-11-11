#include "camera.h"
#include "pch.h"

static vec2 prev_pos_mouse;

static void error_callback(int error_code, const char* description)
{
    fprintf(stderr, "%x - %s\n", error_code, description);
    exit(error_code);
}

static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED) {
        vec2 current_pos_mouse = {xpos, ypos};
        vec2 delta_pos_mouse;

        glm_vec2_sub(current_pos_mouse, prev_pos_mouse, delta_pos_mouse);

        if (glm_vec2_norm(delta_pos_mouse) < (WIDTH >> 2)) {
            const GLfloat delta_x = (-delta_pos_mouse[0]) * ROTATION_GAIN;
            const GLfloat delta_y = (+delta_pos_mouse[1]) * ROTATION_GAIN;
            const GLfloat tetha_x = delta_x + camera_orientation[0];
            const GLfloat tetha_y = delta_y + camera_orientation[1];
            const GLfloat clump_x = tetha_x - (2 * M_PI);

            camera_orientation[0] = 0 < clump_x ? clump_x : tetha_x;
            camera_orientation[1] = max(min(tetha_y, M_PI_2), -M_PI_2);
            camera_orientation[2] = 0.0f;
        }

        glm_vec2_copy(current_pos_mouse, prev_pos_mouse);
    }
}

static void enable_window_focus_lock(GLFWwindow* window)
{
    if (glfwRawMouseMotionSupported()) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
        glfwSetCursorPosCallback(window, cursor_pos_callback);
    }
}

static void disable_window_focus_lock(GLFWwindow* window)
{
    glfwSetCursorPosCallback(window, NULL);
    glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_FALSE);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

static void window_focus_callback(GLFWwindow* window, int focused)
{
    if (focused) {
        enable_window_focus_lock(window);
    } else {
        disable_window_focus_lock(window);
    }
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (glfwGetInputMode(window, GLFW_CURSOR) != GLFW_CURSOR_DISABLED) {
        enable_window_focus_lock(window);
    }
}

static int key_state[6] = {0};
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    int is_active = action != GLFW_RELEASE;

    switch (key) {
    case GLFW_KEY_W:
        key_state[0] = is_active;
        break;
    case GLFW_KEY_S:
        key_state[1] = is_active;
        break;
    case GLFW_KEY_A:
        key_state[2] = is_active;
        break;
    case GLFW_KEY_D:
        key_state[3] = is_active;
        break;
    case GLFW_KEY_Q:
        key_state[4] = is_active;
        break;
    case GLFW_KEY_E:
        key_state[5] = is_active;
        break;
    case GLFW_KEY_ESCAPE:
        disable_window_focus_lock(window);
        break;
    }

    camera_motion_direction[0] = key_state[3] - key_state[2]; // D-A
    camera_motion_direction[1] = key_state[5] - key_state[4]; // E-Q
    camera_motion_direction[2] = key_state[0] - key_state[1]; // W-S
}
