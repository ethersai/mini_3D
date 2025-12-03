#include "sound_blaster.h"
#include "game/loaders/wave_file.h"
#include "platform/platform_log.h"
#include <assert.h>
#include <stdlib.h>
#include <AL/al.h>
#include <AL/alc.h>

// At the top with other statics
static ALuint g_test_source = 0;

static ALuint g_sound_buffers[SOUND_COUNT];
static const char* g_sound_paths[SOUND_COUNT] = 
{
    [SOUND_EXAMPLE] = "sounds/example.wav",
    [SOUND_PUNCH] = "sounds/punch.wav",
};


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
    alDeleteBuffers(SOUND_COUNT, g_sound_buffers);
    
    ALCdevice* Device;
    ALCcontext* Context;
    Context=alcGetCurrentContext();
    Device=alcGetContextsDevice(Context);
    alcMakeContextCurrent(NULL);
    alcDestroyContext(Context);
    alcCloseDevice(Device);
}

void sound_blaster_play_sound(SoundID id)
{
    // Delete old source if it exists
    if (g_test_source != 0) {
        alDeleteSources(1, &g_test_source);
    }
    
    alGenSources(1, &g_test_source);
    
    if (alGetError() != AL_NO_ERROR) {
        return;
    }
    
    alSourcei(g_test_source, AL_BUFFER, g_sound_buffers[id]);
    alSourcef(g_test_source, AL_GAIN, 0.2f);  // Set volume to 50%
    alSourcef(g_test_source, AL_PITCH, 2.0f);
    alSourcePlay(g_test_source);
}

int sound_blaster_init(void)
{
    if (internal_audio_openal_init(NULL)) {
        return 1;
    }

    // Set up the listener!
    alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
    alListener3f(AL_VELOCITY, 0.0f, 0.0f, 0.0f);
    ALfloat orientation[] = {0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f};
    alListenerfv(AL_ORIENTATION, orientation);

    ALenum error;
    alGetError();
    alGenBuffers(SOUND_COUNT, g_sound_buffers);
    if ((error = alGetError()) != AL_NO_ERROR) {
            assert(0 && "[OPEN_AL] alBuffer data failed.");
    }

    for (int sound = 0; sound < SOUND_COUNT; sound++) {
        WAVFile wave = {0};
        if (audio_load_wav(g_sound_paths[sound], &wave)) {
            return 1;
        }

        platform_log_success("Loaded WAV: %s, channels=%d, bits=%d, rate=%d, size=%d", 
                     g_sound_paths[sound], wave.nChannels, 
                     wave.wBitsPerSample, wave.nSamplesPerSec, wave.data_size);

        ALenum format;
        if (wave.nChannels == 1 && wave.wBitsPerSample == 8)        
            format = AL_FORMAT_MONO8;
        else if (wave.nChannels == 1 && wave.wBitsPerSample == 16)
            format = AL_FORMAT_MONO16;
        else if (wave.nChannels == 2 && wave.wBitsPerSample == 8)
            format = AL_FORMAT_STEREO8;
        else if (wave.nChannels == 2 && wave.wBitsPerSample == 16)
            format = AL_FORMAT_STEREO16;
        else assert(0 && "[OPEN_AL] Format not supported.");

        alBufferData(g_sound_buffers[sound], format, wave.data, wave.data_size, wave.nSamplesPerSec);
        if ((error = alGetError()) != AL_NO_ERROR) {
            assert(0 && "[OPEN_AL] alBuffer data failed.");
        }
        free(wave.data);
    }

    return 0;
}

void sound_blaster_shutdown(void)
{
    internal_audio_openal_shutdown();
}





