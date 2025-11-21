#include "world_grid.h"

#include <linmath/linmath.h>
#include "misc/math_misc.h"

#include <stdint.h>

#define DG_CHUNK_X 8
#define DG_CHUNK_Y 64
#define DG_CHUNK_Z 8

float chunk_grid_data[1024*512]; // 2MiB

game_world_quadrant grid_3d_position_to_quadrant(vec3 pos)
{
    float x_axis = pos[0];
    float z_axis = pos[2];
    if (x_axis >= 0.0f) 
    {
        return (z_axis >= 0.0f) ? QUADRANT_I : QUADRANT_IV;
    }
    else 
    {
        return (z_axis >= 0.0f) ? QUADRANT_II : QUADRANT_III;
    }
}

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



#if 0 
// TODO STUDY, DONT STEAL FROM CLAUDE WITHOUT UNDERSTANDING
game_world_quadrant grid_3d_position_to_quadrant(vec3 pos) {
    // fastest possible assembly?
    int xi = pos[0] < 0;
    int zi = pos[2] < 0;
    int idx = (xi << 1) | zi;
    
    static const game_world_quadrant table[4] = {
        QUADRANT_I,   // x >= 0, z >= 0
        QUADRANT_IV,  // x >= 0, z < 0
        QUADRANT_II,  // x < 0,  z >= 0
        QUADRANT_III  // x < 0,  z < 0
    };
    
    return table[idx];
}
#endif

void grid_3d_position_to_sector(const vec3 pos, unsigned int sector_size, vec2 out_sector)
{
    // TODO
    vec3 wordl_origin;
    mathm_vec3_zero(wordl_origin);

}