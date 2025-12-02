#ifndef DG_SOUND_BLASTER_H_
#define DG_SOUND_BLASTER_H_

#include <AL/al.h>
#include <AL/alc.h>

// // sound_blaster.h
// #ifndef SOUND_BLASTER_H
// #define SOUND_BLASTER_H

// // Initialize audio system
// int audio_sound_blaster_init(void);

// // Shutdown audio system
// void audio_sound_blaster_shutdown(void);

// // Load a WAV file
// int audio_load_wav(const char* filename, unsigned int* buffer_id);

// // Play a sound
// int audio_play_sound(unsigned int buffer_id, float volume, int loop);

// // Stop a sound
// void audio_stop_sound(unsigned int source_id);

// // Set listener position (player position)
// void audio_set_listener_position(float x, float y, float z);

// // Set listener orientation (which way player is facing)
// void audio_set_listener_orientation(float forward_x, float forward_y, float forward_z);

// #endif


int audio_sound_blaster_init(void);


#endif /*DG_SOUND_BLASTER_H_*/
