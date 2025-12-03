#include "sound_blaster.h"
#include <stdlib.h>
#include <AL/al.h>
#include <AL/alc.h>

// NOTE: Only works on arrays, not pointers!
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

static int internal_audio_openal_init(const char* device)
{
    ALCdevice* Device;
    ALCcontext* Context;
    Device = alcOpenDevice(device);
    if (Device == NULL) {
        return 1;
    }

    Context = alcCreateContext(Device, NULL);
    alcMakeContextCurrent(Context);

    return 0;
}

static void internal_audio_openal_shutdown(void)
{
    ALCdevice* Device;
    ALCcontext* Context;
    Context=alcGetCurrentContext();
    Device=alcGetContextsDevice(Context);
    alcMakeContextCurrent(NULL);
    alcDestroyContext(Context);
    alcCloseDevice(Device);
}


int sound_blaster_init(void)
{
    if (internal_audio_openal_init(NULL)) {
        return 1;
    }

    return 0;
}

void sound_blaster_shutdown(void)
{
    internal_audio_openal_shutdown();
}





