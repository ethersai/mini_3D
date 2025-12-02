#include "wave_file_loader.h"
#include "platform/file_read.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define wav_defer(value) do { result = (value); goto defer; } while(0)

unsigned char* 
audio_read_wav_file(const char* path, unsigned short* nChannels, unsigned int* nSamplesPerSec, unsigned short* wBitsPerSample)
{
    unsigned char* result = NULL;
    FILE* file = fopen(path, "rb");
    if (file == NULL) return result;
    
    { // Validate that it's indeed riff wave format.
        unsigned char buf[4];
        fread(buf, 1, 4, file);
        if (memcmp(buf, "RIFF", 4) != 0) {
            wav_defer(NULL);
        }
        fseek(file, 4, SEEK_CUR); // skip 4 bytes ahead
        fread(buf, 1, 4, file);
        if (memcmp(buf, "WAVE", 4) != 0) {
            wav_defer(NULL);
        }
    }
    
    while (1) {

        unsigned char chunk_id[4] = {0};
        unsigned int chunk_size = 0;

        fread(chunk_id, 1, 4, file);
        fread(&chunk_size, 4, 1, file);

        if (feof(file)) {
            wav_defer(NULL);
        }

        if (memcmp(chunk_id, "fmt ", 4) == 0) {
            unsigned short wFormatTag = 0;  
            fread(&wFormatTag, 2, 1, file);

            if (wFormatTag != 0x0001) {
                wav_defer(NULL);
            }

            fread(nChannels, 2, 1, file);
            fread(nSamplesPerSec, 4, 1, file);
            fseek(file, 6, SEEK_CUR); // skip nAvgBytesPerSec and nBlockAlign
            fread(wBitsPerSample, 2, 1, file);

            fseek(file, chunk_size - 16U, SEEK_CUR); // skip ahead if not equal to 16.
        }
        
        else if (memcmp(chunk_id, "data", 4) == 0) {
            result = malloc(chunk_size);
            if (result == NULL) wav_defer(NULL);
            
            size_t elements_read = fread(result, 1, chunk_size, file);
            if (elements_read != chunk_size) {
                free(result);
                wav_defer(NULL);
            } 
            
            wav_defer(result);
        }
        else 
        {
            fseek(file, chunk_size, SEEK_CUR); //skip unsupported chunk.
        }
    }

defer:
    if (file) fclose(file);
    return result;
}

int audio_parse_wav_file_from_memory(unsigned char* data, size_t data_size, WAVFile* wav)
{
    return 0;
}

int audio_load_wav(const char* path, WAVFile* wav)
{
    size_t size;
    unsigned char* raw_data = read_file_binary(path, &size);
    if (raw_data == NULL) return 1;

    int err = audio_parse_wav_file_from_memory(raw_data, size, wav);
    
    if (err) {
        free() //defere....
    }

    free(raw_data);
    return 0;
}
