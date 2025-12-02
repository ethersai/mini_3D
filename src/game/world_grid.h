#ifndef DG_WORLD_GRID_H
#define DG_WORLD_GRID_H

#include <linmath/linmath.h>

typedef int ivec2[2];
typedef int ivec4[4];

enum
{
    CHUNK_X = 16,
    CHUNK_Y = 256,
    CHUNK_Z = 16,
};

void world_grid_pos_to_chunk_coordinate(vec3 pos, ivec2 chunk_coords);
void world_grid_chunk_coords_to_world_coords(ivec2 chunk_coords, ivec4 out_coords);

#endif
