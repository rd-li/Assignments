#include "fftCode.h"

using namespace std;

void fft(CArray& warray)
{
    const size_t size = warray.size();
    if(size == 1)
        return;
    // express A(x) in the form Aeven(x^2) + x*Aodd(x^2)
    CArray even = warray[slice(0, size/2, 2)];
    CArray odd = warray[slice(1, size/2, 2)];

    // recursively call
    fft(even);
    fft(odd);

    // combine
    for(size_t i = 0; i < size/2; i++)
    {
        Complex tmp = polar(1.0, -(2 * PI * i) / size);
        warray[i] = even[i] + tmp * odd[i];
        warray[i + size / 2] = even[i] - tmp * odd[i];
    }
    return;
}

