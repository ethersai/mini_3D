#ifndef DG3D_MESH_H
#define DG3D_MESH_H

#include <glad/glad.h>

/////////////
// THE MESH
typedef struct {
    GLuint   vao;
    GLuint   vbo;
    uint32_t vertex_count;
} DG3D_Mesh;

#endif