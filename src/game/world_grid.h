#ifndef DG_WORLD_GRID_H
#define DG_WORLD_GRID_H

#include <linmath/linmath.h>

typedef enum {
    QUADRANT_I,
    QUADRANT_II,
    QUADRANT_III,
    QUADRANT_IV
} game_world_quadrant;

void grid_3d_position_to_sector(const vec3 pos, unsigned int sector_size, vec2 out_sector);
void generate_debug_chunk_vertices(float* data);
game_world_quadrant grid_3d_position_to_quadrant(vec3 pos);

#endif