#ifndef CUBE_H
#define CUBE_H

#include "pch.h"

static vec3 pos_cube = {0.0f, 0.0f, 0.0f};

static GLuint cube_vbo;
static GLuint cube_vao;
static GLuint cube_ebo;

static GLfloat cube_vertices[] = {
    -1.0f,  1.0f,  1.0f, // 0
     1.0f,  1.0f,  1.0f, // 1
     1.0f, -1.0f,  1.0f, // 2
    -1.0f, -1.0f,  1.0f, // 3
    -1.0f, -1.0f, -1.0f, // 4
     1.0f, -1.0f, -1.0f, // 5
     1.0f,  1.0f, -1.0f, // 6
    -1.0f,  1.0f, -1.0f  // 7
};

static GLuint cube_indices[] = {
    0, 3, 1,
    2, 1, 3,
    3, 4, 2,
    5, 2, 4,
    4, 7, 5,
    6, 5, 7,
    3, 0, 4,
    7, 4, 0,
    0, 1, 7,
    6, 7, 1,
    1, 2, 6,
    5, 6, 2
};

void init_cube();
void render_cube();

#endif
