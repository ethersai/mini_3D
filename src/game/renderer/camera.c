#include "camera.h"

#include <assert.h>
#include <float.h>
#include <stdio.h>
#include <linmath/linmath.h>

#include "platform/platform_input.h"
#include "misc/math_misc.h"

#define MOUSE_SENS 0.1f

int camera_init(DG3D_Camera* cam, const vec3 pos, const vec3 target, const vec3 up, float fov, float width, float height, float znear, float zfar) 
{
    mat4x4_identity(cam->view);
    mat4x4_identity(cam->projection);

    cam->pos[0] = pos[0];
    cam->pos[1] = pos[1];
    cam->pos[2] = pos[2];

    cam->target[0] = target[0];
    cam->target[1] = target[1];
    cam->target[2] = target[2];

    cam->up[0] = up[0];
    cam->up[1] = up[1];
    cam->up[2] = up[2];

    cam->aspect_ratio = width / height;
    
    // Calculate yaw and pitch from direction
    vec3 dir; 
    vec3_sub(dir, cam->pos, cam->target);
    vec3_norm(dir, dir);

    cam->yaw = mathm_r_to_deg(atan2f(dir[2], dir[0]));
    cam->pitch = mathm_r_to_deg(asinf(dir[1]));

    mat4x4_look_at(cam->view, pos, target, up);
    mat4x4_perspective(cam->projection, fov, cam->aspect_ratio, znear, zfar);

    // Movement aspects.
    cam->mov_speed = 5.0f;
    cam->mov_friction = 5.0f;
    cam->mov_velocity[0] = 0.0f;
    cam->mov_velocity[1] = 0.0f;
    cam->mov_velocity[2] = 0.0f;

    return 0;
}

void camera_update(DG3D_Camera* cam, float dt)
{
    // x = cos(yaw) * cos(pitch)
    // y = sin(yaw) * cos(pitch)
    // z = sin(pitch) but since y here is the up.
    vec3 camera_front;
    camera_front[0] = cos(mathm_deg_to_r(cam->yaw)) * cos(mathm_deg_to_r(cam->pitch));
    camera_front[1] = sin(mathm_deg_to_r(cam->pitch));
    camera_front[2] = sin(mathm_deg_to_r(cam->yaw)) * cos(mathm_deg_to_r(cam->pitch));
    vec3_norm(camera_front, camera_front);

    vec3 world_up = {0.0f, 1.0f, 0.0f};
    vec3 camera_right;
    vec3_mul_cross(camera_right, camera_front, world_up);
    vec3_norm(camera_right, camera_right);

    vec3 direction = {0};
    if (platform_is_key_down(KEY_W)) {
        vec3_sub(direction, direction, camera_front);
    }   
    if (platform_is_key_down(KEY_S)) {
        vec3_add(direction, direction, camera_front);
    }
    if (platform_is_key_down(KEY_A)) {
        vec3_add(direction, direction, camera_right);
    }
    if (platform_is_key_down(KEY_D)) {
        vec3_sub(direction, direction, camera_right);
    }
    if (platform_is_key_down(KEY_Q)) {
        vec3_add(direction, direction, world_up);
    }
    if (platform_is_key_down(KEY_Z)) {
        vec3_sub(direction, direction, world_up);
    }

    
    if (vec3_len(direction) > FLT_EPSILON) {
        vec3_norm(direction, direction);
        vec3_scale(cam->mov_velocity, direction, cam->mov_speed);
    }

    vec3 displacement;
    vec3_scale(displacement, cam->mov_velocity, dt);
    vec3_add(cam->pos, cam->pos, displacement);

    // apply friction
    vec3_scale(cam->mov_velocity, cam->mov_velocity, (1 - cam->mov_friction * dt));

    if (vec3_len(cam->mov_velocity) <= FLT_EPSILON) {
        cam->mov_velocity[0] = 0.0f;
        cam->mov_velocity[1] = 0.0f;
        cam->mov_velocity[2] = 0.0f;
    }

    vec3 target;                
    vec3_sub(target, cam->pos, camera_front);
    mat4x4_look_at(cam->view, cam->pos, target, cam->up);
}

void camera_update_on_screen_resize(DG3D_Camera* cam, float width, float height)
{
    float aspect_ratio = width / height;
    cam->aspect_ratio = aspect_ratio;
    mat4x4_perspective(cam->projection, cam->fov, aspect_ratio, cam->znear, cam->zfar);
}

void camera_process_mouse_movement(DG3D_Camera* cam, float xoffset, float yoffset)
{
    xoffset *= MOUSE_SENS;
    yoffset *= MOUSE_SENS;

    cam->yaw   += xoffset;
    cam->pitch += yoffset;

    if (cam->pitch > 89.0f)
        cam->pitch = 89.0f;
    if (cam->pitch < -89.0f)
        cam->pitch = -89.0f;
}

// in radians!!
void camera_set_fov(DG3D_Camera* cam, float fov)
{
    cam->fov = fov;
    mat4x4_perspective(cam->projection, cam->fov, cam->aspect_ratio, cam->znear, cam->zfar);
}

void camera_set_clip_planes(DG3D_Camera* cam, float znear, float zfar)
{
    cam->znear = znear;
    cam->zfar = zfar;
    mat4x4_perspective(cam->projection, cam->fov, cam->aspect_ratio, cam->znear, cam->zfar);
}  
