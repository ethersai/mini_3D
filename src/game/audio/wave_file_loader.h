#ifndef DG_WAVE_FILE_LOADER_H_
#define DG_WAVE_FILE_LOADER_H_

#include <stddef.h>

typedef struct {
    unsigned int nSamplesPerSec;
    unsigned short nChannels;
    unsigned short wBitsPerSample;
    unsigned char* data;
    size_t data_size;
} WAVFile;

unsigned char* audio_read_wav_file(const char* path, unsigned short* nChannels, unsigned int* nSamplesPerSec, unsigned short* wBitsPerSample);
int audio_parse_wav_file_from_memory(unsigned char* data, size_t data_size, WAVFile* wav);
void audio_load_wav(const char* path, WAVFile* wav);

// wav->data = malloc(data_chunk_size);
// memcpy(wav->data, raw_data + data_offset, data_chunk_size);
// wav->data_size = data_chunk_size;

#endif
