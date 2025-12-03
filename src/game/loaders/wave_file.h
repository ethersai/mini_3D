#ifndef DG_WAVE_FILE_H_
#define DG_WAVE_FILE_H_

#include <stddef.h>

typedef struct {
    unsigned int nSamplesPerSec;
    unsigned short nChannels;
    unsigned short wBitsPerSample;
    unsigned char* data;
    size_t data_size;
} WAVFile;

int audio_parse_wav_file_from_memory(unsigned char* data, size_t data_size, WAVFile* wav);
int audio_load_wav(const char* path, WAVFile* wav);

#endif
