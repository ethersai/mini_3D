#ifndef DG_WORLD_GEN_H
#define DG_WORLD_GEN_H

#include "game/world_grid.h"

#include "FastNoiseLite/FastNoiseLite.h"
#include <stdint.h>

typedef struct {

    int                  seed;
    float                freq;
    int                  octaves;
    float                lacunarity;
    float                gain;
    fnl_noise_type       noise_type;

    //*CLAUDE was right!
    // Keep internal/hardcoded:

    // rotation_type_3d -    Users won't understand this, just set IMPROVE_XZ_PLANES
    // fractal_type -        Pick FBM for terrain, users don't need to change
    // weighted_strength -   Too technical, default is fine
    // cellular_* settings - Only if you're using cellular noise for specific features
    // domain_warp_* -       Advanced technique, hardcode if you use it
    
} WorldGenSettings;

typedef enum {
    BLOCK_AIR = 0,
    BLOCK_STONE,
    BLOCK_TYPE_COUNT,
} block_type;


uint8_t chunk[

typedef struct {
    uint8_t blocks[128][16][16];
} Chunk;

void chunk_create(Chunk* chunk);

#endif
