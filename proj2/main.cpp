#include <iostream>
#include <fstream>
#include <cmath>
#include <complex>
#include <valarray>
#include <string>

#include "wavCode.h"
#include "fftCode.h"

using namespace std;

typedef std::complex<double> Complex;
typedef std::valarray<Complex> CArray;

int main() {
    int sampleRate;
    int16_t * wavArray;
    CArray wavCArray (512); 
    int index = 0;

    /* read the data */
    wavArray = wavReader("mystery.wav", sampleRate);

    cout << "\n\n------ First 10 values from .wav file data --------" << endl;
    for(int i = 0; i < 10; i++) {
     	cout << "dec:" << std::dec << wavArray[i] << "\t" 
	     << "hex:" << std::hex << wavArray[i] << std::dec << endl;
    }
    
    // 7 tones
    for(int j = 0; j < 7; j++)
    {
        index = j * 1600;    // index for wavArray
       
        // copy the first 512 value of wavArray to wavCArray
        for(size_t i = 0; i < wavCArray.size(); i++)
            wavCArray[i] = static_cast<Complex>((double)wavArray[i + index]);
        
        // TODO:  call FFT and report results
        fft(wavCArray);
        
        // write into file for plotting out
        fstream outFile("result" + to_string(j+1) + ".txt", ios::out);
        outFile << "Frequency Result Magnitude\n";
        // save the first half since it is symmetric
        for(size_t i = 0; i < wavCArray.size()/2; i++)
            outFile << i*sampleRate/512 << ' ' << wavCArray[i] << ' ' << abs(wavCArray[i]) << endl;
        outFile.close();
    }
    return 0;
}

