#ifndef DG_RENDERER_H
#define DG_RENDERER_H

#include <stddef.h>
#include <linmath/linmath.h>

#include "camera.h"
#include "shader.h"

///////////////////
// Unifrom Buffer
typedef struct {
    GLuint handle;
    size_t max_size;
    GLuint binding_point;
} DG3D_UniformBuffer;

int dg3d_uniform_buffer_create(DG3D_UniformBuffer* ubo, size_t size, GLuint binding_point, GLenum usage);
void dg3d_uniform_buffer_update(DG3D_UniformBuffer* ubo, GLintptr offset, GLsizeiptr size, const void* data);
void dg3d_uniform_buffer_destroy(DG3D_UniformBuffer* ubo);

//! SSBO and UBO binding points do not collide

///////////////
// SSBO
typedef struct {
    GLuint handle;
    size_t max_size;
    GLuint binding_point;
} DG3D_ShaderStorageBuffer;

int dg3d_ssbo_create(DG3D_ShaderStorageBuffer* ssbo, GLuint binding_point, GLenum usage);
void dg3d_ssbo_update(DG3D_ShaderStorageBuffer* ssbo, GLintptr offset, GLsizeiptr size, const void* data);
void dg3d_ssbo_destroy(DG3D_ShaderStorageBuffer* ssbo);

////////////
// Shaders
typedef struct {
    GLuint      id;
    GLint       u_model;
} DefaultShader;

typedef struct {
    GLuint id;
} ScreenQuadShader;

typedef struct {
    GLuint id;
} LinesShader;

/////////////
// Renderer
typedef struct {

    DefaultShader    shader_default;
    ScreenQuadShader shader_screen_quad;

    DG3D_UniformBuffer ubo_matrices;

    GLuint cube_vao;
    GLuint cube_vbo;
    GLuint cube_ebo;

    GLuint screen_quad_vao;
    GLuint screen_quad_vbo;

    GLuint fbo_main;
    GLuint fbo_main_texture;      // RGBA8           
    GLuint fbo_main_renderbuffer; // DEPTH 24 STENCIL 8

    int viewport_width;
    int viewport_height;
    
} DG3D_Renderer;


int  dg3d_renderer_init(DG3D_Renderer* renderer, int width, int height);
void dg3d_begin_frame(DG3D_Renderer* renderer, DG3D_Camera* camera);
void dg3d_render_cube(DG3D_Renderer* renderer, mat4x4 model, GLuint texture);
void dg3d_render_line(DG3D_Renderer* renderer, vec4 color, float* line_segments); // GLETER2D candidate?
void dg3d_renderer_shutdown(DG3D_Renderer* renderer);

#endif