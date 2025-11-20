#ifndef DG_RENDERER_H
#define DG_RENDERER_H

#include <stddef.h>
#include <stdint.h>
#include <linmath/linmath.h>

#include "camera.h"
#include "shader.h"

typedef GLint uniform;

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

int dg3d_ssbo_create(DG3D_ShaderStorageBuffer* ssbo, GLsizeiptr size, GLuint binding_point, GLenum usage);
void dg3d_ssbo_update(DG3D_ShaderStorageBuffer* ssbo, GLintptr offset, GLsizeiptr size, const void* data);
void dg3d_ssbo_destroy(DG3D_ShaderStorageBuffer* ssbo);

///////////////
// MESH KINDA
typedef struct {
    GLuint   vao;
    GLuint   vbo;
    uint32_t vertex_count;
} DG3D_Mesh;

int dg3d_mesh_create(DG3D_Mesh* mesh, uint32_t vertex_count, GLsizeiptr buf_size, const void* data, GLenum usage);
void dg3d_mesh_destroy(DG3D_Mesh* mesh);

////////////
// Shaders
typedef struct {
    GLuint      id;
    uniform     u_model;
} DefaultShader;

typedef struct {
    GLuint id;
} ScreenQuadShader;

typedef struct {
    GLuint  id;
    uniform u_color;  
} LinesShader;

/////////////
// Renderer
typedef struct {

    DefaultShader    shader_default;
    ScreenQuadShader shader_screen_quad;
    LinesShader      shader_lines;

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

extern DG3D_Mesh chunk_debug_lines;


int  dg3d_renderer_init(DG3D_Renderer* renderer, int width, int height);
void dg3d_begin_frame(DG3D_Renderer* renderer, DG3D_Camera* camera);
void dg3d_render_cube(DG3D_Renderer* renderer, mat4x4 model, GLuint texture);
//void dg3d_render_line(DG3D_Renderer* renderer, vec4 color, float* line_segments); // GLETER2D candidate?
void dg3d_renderer_shutdown(DG3D_Renderer* renderer);

void dg3d_render_mesh(DG3D_Renderer* renderer, DG3D_Mesh* mesh, vec4 color);

#endif