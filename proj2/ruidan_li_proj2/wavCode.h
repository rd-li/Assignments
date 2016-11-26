#ifndef WAVCODE_H
#define WAVCODE_H

#include <iostream>
#include <fstream>
#include <cstdint>

// struct corresponding to a .wav file header
typedef struct  WAV_HEADER{
    char                RIFF[4];        // "RIFF" Header      Magic header
    uint32_t            ChunkSize;      // RIFF Chunk Size  
    char                WAVE[4];        // "WAV " Header      
    /* "fmt" sub-chunk */
    char                Subchunk1ID[4]; // "fmt " header       
    uint32_t            Subchunk1Size;  // Size of the fmt chunk                                
    uint16_t            AudioFormat;    // Audio format 1=PCM,6=mulaw,7=alaw, 257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM 
    uint16_t            NumOfChan;      // Number of channels 1=Mono 2=Sterio                   
    uint32_t            SamplesPerSec;  // Sampling Frequency in Hz                             
    uint32_t            bytesPerSec;    // bytes per second 
    uint16_t            blockAlign;     // 2=16-bit mono, 4=16-bit stereo 
    uint16_t            bitsPerSample;  // Number of bits per sample      
    /* "data" sub-chunk */
    char                Subchunk2ID[4]; // "data"  string   
    uint32_t            Subchunk2Size;  // Sampled data length    
} wav_hdr; 

/* wavReader allocates space for an array of int16_t values and returns a pointer to it */
/* paramters:  wav file name, samplerate to be returned */
int16_t *wavReader(const char*, int &);

// utility function
int getFileSize(FILE *); 

#endif
