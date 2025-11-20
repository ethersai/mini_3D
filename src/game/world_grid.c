#include "world_grid.h"

#include <linmath/linmath.h>
#include "misc/math_misc.h"

#include <stdint.h>

#define DG_CHUNK_X 8
#define DG_CHUNK_Y 64
#define DG_CHUNK_Z 8


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

int grid_3d_generate_debug_chunk_data(float* data)
{

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