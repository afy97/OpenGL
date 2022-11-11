#include "pch.h"
#include "cube.h"
#include "camera.h"

#include "shader.c"

static void init_render()
{
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_DEPTH_TEST);

    compile_shaders();
    init_cube();

    glm_mat4_identity(mat_model);
    glm_mat4_identity(mat_view);
    glm_mat4_identity(mat_projection);
    glm_perspective(glm_rad(FOV), ((GLfloat) WIDTH) / ((GLfloat) HEIGHT), 0.1f, 100.0f, mat_projection);
    glm_translate(mat_view, camera_position);
    glm_translate(mat_model, pos_cube);
    
    const m_loc = glGetUniformLocation(shader_program, "model");
    const v_loc = glGetUniformLocation(shader_program, "view");
    const p_loc = glGetUniformLocation(shader_program, "projection");

    glUniformMatrix4fv(m_loc, 1, GL_FALSE, *mat_model);
    glUniformMatrix4fv(v_loc, 1, GL_FALSE, *mat_view);
    glUniformMatrix4fv(p_loc, 1, GL_FALSE, *mat_projection);
}

static void render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    camera_transform();

    glm_mat4_identity(mat_model);
    glm_translate(mat_model, pos_cube);

    const m_loc = glGetUniformLocation(shader_program, "model");
    const v_loc = glGetUniformLocation(shader_program, "view");

    glUniformMatrix4fv(m_loc, 1, GL_FALSE, *mat_model);
    glUniformMatrix4fv(v_loc, 1, GL_FALSE, *mat_view);

    render_cube();
}
