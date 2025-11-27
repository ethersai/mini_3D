#include "world_gen.h"

#define FNL_IMPL 
#include "FastNoiseLite/FastNoiseLite.h"

#include <stdint.h>

#define DEFAULT_SEED 420

static fnl_state noise_state;
uint8_t chunk_rd[CHUNK_X][CHUNK_Y][CHUNK_Z]; /*[0,0]*/
uint8_t chunk_ld[CHUNK_X][CHUNK_Y][CHUNK_Z]; /*[-1,0]*/
uint8_t chunk_lu[CHUNK_X][CHUNK_Y][CHUNK_Z]; /*[-1, -1]*/
uint8_t chunk_ru[CHUNK_X][CHUNK_Y][CHUNK_Z]; /*[0, -1]*/ 

const WorldGenSettings PRESETS[WGEN_COUNT] = 
{
    [WGEN_DEFAULT] = 
    {
        .frequency = 0.01f,
        .noise_type = FNL_NOISE_OPENSIMPLEX2,
        .fractal_type = FNL_FRACTAL_FBM,
        .octaves = 5,
        .lacunarity = 2.0f,
        .gain = 0.5f,
    },
    [WGEN_CRAZY] = 
    {
        .frequency = 0.03f,      
        .noise_type = FNL_NOISE_PERLIN,
        .fractal_type = FNL_FRACTAL_RIDGED,  
        .octaves = 8,            
        .lacunarity = 2.5f, 
        .gain = 0.6f,             
    },
};

WorldGenConfig wgenconf = {
    .seed = DEFAULT_SEED,
    .settings = PRESETS[WGEN_DEFAULT],
};

void world_gen_initialize_noise_gen(WorldGenConfig config)
{
    noise_state = fnlCreateState();
    // User should be able to play with those.
    noise_state.seed         = config.seed;
    noise_state.noise_type   = config.settings.noise_type;
    noise_state.fractal_type = config.settings.fractal_type;
    noise_state.octaves      = config.settings.octaves;
    noise_state.lacunarity   = config.settings.lacunarity;
    noise_state.gain         = config.settings.gain;
    noise_state.frequency    = config.settings.frequency;
   
    // Those will be hardcoded (at least for now.)
    noise_state.rotation_type_3d = FNL_ROTATION_IMPROVE_XZ_PLANES;
}
void world_gen_chunk_at(ivec2 chunk_coord)
{

}


#if 0
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
#endif

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
