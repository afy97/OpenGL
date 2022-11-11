#ifndef CAMERA_H
#define CAMERA_H

#define WIDTH 1024
#define HEIGHT 720
#define FOV 45.0f

#define MOTION_GAIN 4.0f
#define ROTATION_GAIN 0.0002f

#include "pch.h"

static mat4 mat_model;
static mat4 mat_view;
static mat4 mat_projection;

static vec3 camera_orientation = {-0.3f, 0.5f, 0.0f};
static vec3 camera_position = {-2.0f, 3.0f, 6.0f};
static ivec3 camera_motion_direction = {0, 0, 0};

static void camera_transform()
{
    const GLdouble move = delta_time * MOTION_GAIN;

    vec3 camera_target;
    vec3 camera_right;
    vec3 camera_up;

    glm_vec3_copy(GLM_ZUP, camera_target);
    glm_vec3_negate(camera_target);
    glm_vec3_rotate(camera_target, camera_orientation[0], GLM_YUP);
    glm_cross(GLM_YUP, camera_target, camera_right);
    glm_vec3_normalize(camera_right);
    glm_vec3_rotate(camera_target, camera_orientation[1], camera_right);
    glm_cross(camera_target, camera_right, camera_up);
    glm_look(camera_position, camera_target, camera_up, mat_view);

    if (camera_motion_direction[0]) {
        const GLfloat magnitude = (-camera_motion_direction[0]) * move;
        camera_position[0] += magnitude * camera_right[0];
        camera_position[2] += magnitude * camera_right[2];
    }

    if (camera_motion_direction[1]) {
        const GLfloat magnitude = (-camera_motion_direction[1]) * move;
        camera_position[1] += magnitude;
    }

    if (camera_motion_direction[2]) {
        const GLfloat magnitude = (-camera_motion_direction[2]) * move;
        camera_position[0] += magnitude * camera_target[0];
        camera_position[1] += magnitude * camera_target[1];
        camera_position[2] += magnitude * camera_target[2];
    }
}

#endif
