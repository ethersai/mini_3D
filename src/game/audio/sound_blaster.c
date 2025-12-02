#include "sound_blaster.h"
#include "wave_file_loader.h"
#include <stdlib.h>
#include <AL/al.h>
#include <AL/alc.h>

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


int audio_sound_blaster_init(void)
{
    if (internal_audio_openal_init(NULL)) {
        return 1;
    }



    return 0;
}



