#include "wave_file.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define defer(value) do { result = (value); goto defer; } while (0)

int audio_parse_wav_file_from_memory(unsigned char* data, size_t data_size, WAVFile* wav)
{
    //asserts.
    unsigned char* data_ptr = data;

    { // Validate that it's indeed riff wave format.
        if (memcmp(data_ptr, "RIFF", 4) != 0) return 1;
        data_ptr += 8; //skip 8 bytes ahead. // skip riff and size. 
        if (memcmp(data_ptr, "WAVE", 4) != 0) return 1;
        data_ptr += 4;
    }

    int result = 1;
    for (;;) 
    {
        size_t offset = data_ptr - data;
        if (offset >= data_size) { 
            defer(0);
        }
            
        if (memcmp(data_ptr, "fmt ", 4) == 0)
        {
            data_ptr+=4;
            unsigned int chunk_size = 0;
            memcpy(&chunk_size, data_ptr, 4);

            data_ptr+=4;
            unsigned short wFormatTag = 0;  
            memcpy(&wFormatTag, data_ptr, 2);

            if (wFormatTag != 0x0001) {
                defer(1);
            }
            data_ptr+=2;

            memcpy(&wav->nChannels, data_ptr, 2);
            data_ptr+=2;
            memcpy(&wav->nSamplesPerSec, data_ptr, 4);
            data_ptr+=4;
            data_ptr+=6; // skip nAvgBytesPerSec and nBlockAlign
            memcpy(&wav->wBitsPerSample, data_ptr, 2);            
            data_ptr+=2;

            data_ptr+= chunk_size - 16U; // skip the rest of the chunk if not equal to 16. 
        }
        else if (memcmp(data_ptr, "data", 4) == 0)
        {
            data_ptr+=4;
            unsigned int chunk_size = 0;
            memcpy(&chunk_size, data_ptr, 4);
            data_ptr+=4;

            wav->data = malloc(chunk_size); 
            if (wav->data == NULL) {
                defer(1);
            }
            memcpy(wav->data, data_ptr, chunk_size);
            wav->data_size = chunk_size;

            data_ptr += chunk_size;
            if (chunk_size % 2) {
                data_ptr += 1;
            }
        }
        else
        {
            data_ptr+=4; //skip fourCC.
            unsigned int chunk_size;
            memcpy(&chunk_size, data_ptr, 4);
            data_ptr+=4;
            data_ptr += chunk_size;
            if (chunk_size % 2) // if chunk size odd add 1.
                data_ptr += 1;
        }

    }
    
defer:
    return result;
}

int audio_load_wav(const char* path, WAVFile* wav)
{
    size_t size;
    unsigned char* raw_data = read_file_binary(path, &size);
    if (raw_data == NULL) return 1;

    int err = audio_parse_wav_file_from_memory(raw_data, size, wav);
    if (err) {
        return 1;
    }

    free(raw_data);
    return 0;
}
