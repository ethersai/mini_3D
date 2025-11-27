#include "world_grid.h"

#include <linmath/linmath.h>
#include "misc/math_misc.h"

#include <stdint.h>

enum
{
    CHUNK_X = 16,
    CHUNK_Y = 256,
    CHUNK_Z = 16,
};

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
