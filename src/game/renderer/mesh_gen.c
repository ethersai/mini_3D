#include "mesh_gen.h"
#include "mesh.h"

#include <glad/glad.h>
#include "mesh.h"
#include "game/game_info.h".
// i love software. acies7 [Fri Nov 21 21:01:50].

// precalculated XD
float buffer_chunk_vertices[8000];

void generate_debug_chunk_vertices(float* data)
{
    int idx = 0;

    for (int y = 0; y < 64; y++) {
        for (int z = 0; z < 9; z++) {

            data[idx+0] = 0.0f;
            data[idx+1] = (float)y;
            data[idx+2] = (float)z; 

            data[idx+3] = 8.0f; 
            data[idx+4] = (float)y;
            data[idx+5] = (float)z;

            idx += 6;
        }
    }

    for (int y = 0; y < 64; y++) {
        for (int x = 0; x < 9; x++) {

            data[idx+0] = (float)x;
            data[idx+1] = (float)y;
            data[idx+2] = 0.0f;

            data[idx+3] = (float)x;
            data[idx+4] = (float)y;
            data[idx+5] = 8.0f;

            idx += 6;
        }
    }

    for (int x = 0; x < 9; x++) {
        for (int z = 0; z < 9; z++) {

            data[idx+0] = (float)x;
            data[idx+1] = 0.0f;
            data[idx+2] = (float)z;

            data[idx+3] = (float)x;
            data[idx+4] = 63.0f;
            data[idx+5] = (float)z;

            idx += 6;
        }
    }
}


int mesh_gen_create_debug_grid(DG3D_Mesh* mesh)
{
    if (!mesh) 
        return 1;

    generate_debug_chunk_vertices(buffer_chunk_vertices);
    if (dg3d_mesh_create_chunk_debug(mesh, 2000, 
        sizeof(buffer_chunk_vertices), buffer_chunk_vertices, GL_STATIC_DRAW))
    {
        return 1;
    }
    



    
    
}