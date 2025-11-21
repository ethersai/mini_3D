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

int dg3d_mesh_create_chunk_debug(DG3D_Mesh* mesh, 
    uint32_t vertex_count, GLsizeiptr buf_size, const void* data, GLenum usage);
    
void dg3d_mesh_destroy(DG3D_Mesh* mesh);





#endif