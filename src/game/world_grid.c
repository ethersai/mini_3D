#include "world_grid.h"

#include <linmath/linmath.h>

#include <math.h>
#include <stdint.h>

void world_grid_pos_to_chunk_coordinate(vec3 pos, ivec2 chunk_coords)
{
    chunk_coords[0] = floorf(pos[0] / CHUNK_X);
    chunk_coords[1] = floorf(pos[2] / CHUNK_Z);
}

void world_grid_chunk_coords_to_world_coords(ivec2 chunk_coords, ivec4 out_coords)
{
     // [local_x_start, local_z_start, upper_x, upper_z] 
    out_coords[0] = CHUNK_X * chunk_coords[0]; // local_x    
    out_coords[1] = CHUNK_Z * chunk_coords[1]; // local_z
    out_coords[2] = (CHUNK_X * chunk_coords[0]) + CHUNK_X; //upper_x 
    out_coords[3] = (CHUNK_Z * chunk_coords[1]) + CHUNK_Z; //upper_z
}

#if 0
void world_grid_loop_over_chunk_relative_to_origin(ivec2 chunk_coords)
{
    int upper_x = (CHUNK_X * chunk_coords[0]) + CHUNK_X;
    int upper_z = (CHUNK_Z * chunk_coords[1]) + CHUNK_Z;

    for (int local_z = CHUNK_Z * chunk_coords[1]; local_z < upper_z; local_z++) {
        for (int local_x = CHUNK_X * chunk_coords[0]; local_x < upper_x; local_x++) {
            printf("[%d, %d] ", local_z, local_x);
        }
        putchar('\n');
    }
}

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
#endif
