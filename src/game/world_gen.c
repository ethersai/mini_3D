#include "world_gen.h"

#define FNL_IMPL 
#include "FastNoiseLite/FastNoiseLite.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEFAULT_SEED 420

#if 0
Here are all the settings you can play with for FastNoiseLite:

Core Noise Settings:

    seed - Any integer value (changes the entire pattern)
    noise_type - OPENSIMPLEX2, OPENSIMPLEX2S, PERLIN, VALUE, VALUE_CUBIC, CELLULAR
    frequency - Controls scale/zoom (higher = more compressed/detailed, lower = more stretched/smooth)

Fractal Settings (for layering noise):

    fractal_type - NONE, FBM, RIDGED, PINGPONG, DOMAIN_WARP_PROGRESSIVE, DOMAIN_WARP_INDEPENDENT
    octaves - Number of noise layers (more = more detail, typical range 1-8)
    lacunarity - Frequency multiplier between octaves (how much detail increases per layer, typical 2.0)
    gain - Amplitude multiplier between octaves (how much each layer contributes, typical 0.5)
    weighted_strength - How much each octave is weighted by previous octave's output (0.0-1.0)
    ping_pong_strength - Strength of the ping pong effect when using PINGPONG fractal type

Cellular/Voronoi Specific:

    cellular_distance_func - EUCLIDEAN, EUCLIDEANSQ, MANHATTAN, HYBRID
    cellular_return_type - CELLVALUE, DISTANCE, DISTANCE2, DISTANCE2ADD, DISTANCE2SUB, DISTANCE2MUL, DISTANCE2DIV
    cellular_jitter - Randomness of cell points (0.0-1.0, default 1.0)

Domain Warp (for warping coordinates before sampling):

    domain_warp_type - OPENSIMPLEX2, OPENSIMPLEX2_REDUCED, BASICGRID
    domain_warp_amp - Amplitude/strength of the warp effect

All of these dramatically affect terrain shape, smoothness, variation, and features in world generation!
#endif



static fnl_state g_noise;

static WorldGenSettings wgs = {
    .seed =       DEFAULT_SEED,
    .freq =       0.01f,
    .octaves =    6,
    .lacunarity = 2.0f,
    .gain =       0.5f,
}




int main(void)
{
    fnl_state noise = fnlCreateState(); 
    noise.seed = 31353324;
    noise.noise_type = FNL_NOISE_OPENSIMPLEX2;
    noise.fractal_type = FNL_FRACTAL_FBM;
    noise.octaves = 6;
    noise.lacunarity = 2.0f;
    noise.gain = 0.5f;
    noise.frequency = 0.01f;

    float chunk[16][256][16] = {0}; 
    //printf("SIZE OF CHUNK IN BYTES: %zu\n", sizeof(chunk));
    
    for (int y = 0; y < 256; y++) {
        for (int z = 0; z < 16; z++) {
            for (int x = 0; x < 16; x++) {
               chunk[z][y][x] = fnlGetNoise3D(&noise, (FNLfloat)x, (FNLfloat)y, (FNLfloat)z);
            }
        }
    }
    
    int height_map[16][16];

    for (int z = 0; z < 16; z++) {
        for (int x = 0; x < 16; x++) {
/*[-1 to 1]*/float noise_height = fnlGetNoise2D(&noise, (FNLfloat)x, (FNLfloat)z);
/*[0 to 1 */ float normalized_height = (noise_height + 1.0f) * 0.5f; 
             height_map[z][x] = (int)floorf(normalized_height * 256.0f);
             
             








        }
    }

    for (int z = 0; z < 16; z++) {
        for (int x = 0; x < 16; x++) {
            printf("%d ", height_map[z][x]);
        }
        putchar('\n');
    }


#if 0
    for (int y = 0; y < 256; y++) {
        for (int z = 0; z < 16; z++) {
            for (int x = 0; x < 16; x++) {
                if (x == 0 && z == 0) printf("Y: %d\n", y);
                printf("%.2f", chunk[z][y][x]);
            }
            putchar('\n');
        }
        putchar('\n');
    }
#endif
     




    return 0;
}

// // Generate random integer in range [min, max] (inclusive)
// static inline int random_int(int min, int max) {
//     return min + rand() % (max - min + 1);
// }

// // Generate random float in range [0.0, 1.0]
// static inline float random_float(void) {
//     return (float)rand() / (float)RAND_MAX;
// }

// // Generate random float in range [min, max]
// static inline float random_float_range(float min, float max) {
//     return min + random_float() * (max - min);
// }

// void chunk_create(Chunk* chunk)
// {
//     memset(chunk->blocks, BLOCK_AIR, sizeof(chunk->blocks));

//     for (int y = 0; y < 64; y++) {
//         for (int z = 0; z < 16; z++) {
//             for (int x = 0; x < 16; x++) {
//                 chunk->blocks[y][z][x] = BLOCK_STONE;
//             }
//         }
//     }
// }
