#include "world_gen.h"

#define FNL_IMPL 
#include "FastNoiseLite/FastNoiseLite.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEFAULT_SEED 420

static fnl_state g_noise;

typedef struct {

    


} WorldGenSettings;

typedef struct {




} WorldGenContext;

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