/*
 * function for reading a .wav header file      
 * 
 * Parameters for wavReader:
 *   in: name of file to be read 
 *  out: sampleRate returned by reference
 *       array of type int16_t
 */

#include "wavCode.h"

using namespace std;

// determine the file size using fseek()
int getFileSize(FILE *inFile){
    long fileSize = 0;
    fseek(inFile,0,SEEK_END); // seek to end
    fileSize=ftell(inFile);   // get position of the end
    fseek(inFile,0,SEEK_SET); // seek back to beginning
    return fileSize;
}

// read a .wav file by parsing the header and then
// reading and returning the data chunk;
// also returns the sampleRate by reference
int16_t *wavReader( const char* fileName, int & sampleRate){
    FILE *wavFile;
    wav_hdr wavHeader;  // see .h for type definition
    int headerSize = sizeof(wav_hdr);
    int filelength = 0;

    try{
        wavFile = fopen(fileName, "r");
    }
    catch( std::ios_base::failure& e){
        std::cerr << e.what() << '\n';
    }

    // read the 44 byte header
    // this function assumes the file is a simple .wav file in RIFF format
    filelength = getFileSize(wavFile);
    fread(&wavHeader, 1, headerSize, wavFile);

    cout << "\nFile size is    : " << filelength << " bytes." << endl;
    cout << "RIFF header       : " << wavHeader.RIFF[0] << wavHeader.RIFF[1]
                                           << wavHeader.RIFF[2] << wavHeader.RIFF[3] << endl;
    cout << "Chunk size        : " << wavHeader.ChunkSize << endl;
    cout << "WAVE header       : " << wavHeader.WAVE[0] << wavHeader.WAVE[1]
                                           << wavHeader.WAVE[2] << wavHeader.WAVE[3] << endl;
    cout << "FMT               : " << wavHeader.Subchunk1ID << endl;                               
    cout << "Subchunk 1 size   : " << wavHeader.Subchunk1Size << endl;
    cout << "Audio Format      : " << wavHeader.AudioFormat << endl;
             // Audio format 1=PCM,6=mulaw,7=alaw, 257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM 
    cout << "Number of channels: " << wavHeader.NumOfChan << endl;
    cout << "Sampling Rate     : " << wavHeader.SamplesPerSec << endl; // Sampling Rate
    cout << "Number of bytes per second : " << wavHeader.bytesPerSec << endl;
    cout << "Block align       : " << wavHeader.blockAlign << endl;
    cout << "Bits per sample   : " << wavHeader.bitsPerSample << endl;
    cout << "Data string       : " << wavHeader.Subchunk2ID[0] << wavHeader.Subchunk2ID[1]
                                           << wavHeader.Subchunk2ID[2] << wavHeader.Subchunk2ID[3] << endl;
    cout << "Subchunk 2 size   : " << wavHeader.Subchunk2Size << endl;

    sampleRate = wavHeader.SamplesPerSec;
    unsigned short bytesPerSample = wavHeader.bitsPerSample/8;
    unsigned long numberOfSamples = (wavHeader.ChunkSize-36)/bytesPerSample;
    static int16_t* sampleArray;
    sampleArray = (int16_t *) malloc(numberOfSamples * wavHeader.blockAlign);

    cout << "Bytes per sample  : " << bytesPerSample  << endl;
    cout << "Number of samples : " << numberOfSamples << endl;

    // Read the data - note that data is in little-endian order
    long dataSize = fread(sampleArray, 1, bytesPerSample * numberOfSamples, wavFile);

    if( dataSize != numberOfSamples ){
        cout << "Bytes read     : " << dataSize << endl;
        cout << "# samples      : " << numberOfSamples << endl;
    } 
	
    return sampleArray; 
}

