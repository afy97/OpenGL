#include "pch.h"

static GLchar *vert_shader_code =
"#version 460\n"
"layout (location = 0) in vec3 position;\n"
"out vec4 vertex_color;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"void main() {\n"
"    gl_Position = projection * view * model * vec4(position, 1.0);\n"
"    vertex_color = vec4(max(position, (0, 0, 0)), 1.0);\n"
"}\n";

static GLchar *frag_shader_code =
"#version 460\n"
"out vec4 frag_color;\n"
"in vec4 vertex_color;\n"
"void main() {\n"
"    frag_color = vertex_color;\n"
"}\n";

static GLuint vert_shader;
static GLuint frag_shader;
static GLuint shader_program;

static void compile_shader_code(const GLchar *value, GLuint target)
{
    GLint result = 0;

    glShaderSource(target, 1, &value, NULL);
    glCompileShader(target);
    glGetShaderiv(target, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE) {
        GLint max_len = 512;
        glGetShaderiv(target, GL_INFO_LOG_LENGTH, &max_len);

        GLchar *err_log = malloc(max_len);
        memset(err_log, 0, max_len);
        glGetShaderInfoLog(target, max_len, &max_len, err_log);

        perror(err_log);
        free(err_log);

        glDeleteShader(target);
    }
}

static void compile_shaders()
{
    GLint result = 0;

    shader_program = glCreateProgram();
    vert_shader = glCreateShader(GL_VERTEX_SHADER);
    frag_shader = glCreateShader(GL_FRAGMENT_SHADER);

    compile_shader_code(vert_shader_code, vert_shader);
    compile_shader_code(frag_shader_code, frag_shader);

    glAttachShader(shader_program, vert_shader);
    glAttachShader(shader_program, frag_shader);
    glLinkProgram(shader_program);
    glGetProgramiv(shader_program, GL_LINK_STATUS, &result);

    if (result == GL_FALSE) {
        GLint max_len = 512;
        glGetProgramiv(shader_program, GL_INFO_LOG_LENGTH, &max_len);

        GLchar *err_log = malloc(max_len);
        memset(err_log, 0, max_len);
        glGetProgramInfoLog(shader_program, max_len, &max_len, err_log);

        perror(err_log);
        free(err_log);

        glDeleteProgram(shader_program);
    } else {
        glUseProgram(shader_program);
        glDeleteShader(vert_shader);
        glDeleteShader(frag_shader);
    }
}
