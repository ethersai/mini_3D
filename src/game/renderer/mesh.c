#include "mesh.h"

int dg3d_mesh_create_chunk_debug(DG3D_Mesh* mesh, 
    uint32_t vertex_count, GLsizeiptr buf_size, const void* data, GLenum usage)
{
    glGenVertexArrays(1, &mesh->vao);
    glGenBuffers(1, &mesh->vbo);
    glBindVertexArray(mesh->vao);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
    glBufferData(GL_ARRAY_BUFFER, buf_size, data, usage);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (sizeof(float) * 3), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    mesh->vertex_count = vertex_count;
    return 0;
}

void dg3d_mesh_destroy(DG3D_Mesh* mesh)
{
    if (!mesh) return;
    glDeleteVertexArrays(1, &mesh->vao);
    glDeleteBuffers(1, &mesh->vbo);
    mesh->vertex_count = 0;   
}