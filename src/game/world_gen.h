#ifndef DG_WORLD_GEN_H
#define DG_WORLD_GEN_H

#include "game/world_grid.h"

#include "FastNoiseLite/FastNoiseLite.h"
#include <stdint.h>

typedef enum
{
    WGEN_DEFAULT = 0,
    WGEN_CRAZY,
    WGEN_COUNT,
} WorldGenSettingsPredefined;

typedef struct {
    float                frequency;         // Scale of terrain features
    fnl_noise_type       noise_type;        // OpenSimplex2, Perlin, etc.
    fnl_fractal_type     fractal_type;      // FBM for terrain
    int                  octaves;           // Detail level (3-8 typical)
    float                lacunarity;        // Frequency multiplier (2.0 default)
    float                gain;              // Amplitude multiplier (0.5 default)
} WorldGenSettings;

typedef struct {
    int              seed;
    WorldGenSettings settings;
} WorldGenConfig;


#endif

#if 0
Quick tweaking guide:
Frequency:

0.005 = Huge mountains, slow rolling
0.01 = Good default terrain
0.02 = Hills and valleys
0.05 = Small bumpy features

Octaves:

3 = Smooth, basic shapes
5 = Nice detail (recommended)
8 = Maximum detail (slower)

Lacunarity:

2.0 = Standard (each octave 2x frequency)
2.5 = More contrast, rougher
1.5 = Smoother transitions

Gain:

0.3 = Subtle details
0.5 = Balanced (default)
0.7 = Strong, pronounced details

#endif
