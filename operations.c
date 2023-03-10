#include "wavetables.h"

void stripHarmonics(PolarComplex *dftPol, int nHarmonicsToKeep, int N) {

    int halfN = N / 2;
    for (int i = nHarmonicsToKeep; i <= halfN; i++) {

        // example: N=32 keeping 10 harmonics
        // sample[0] is frequency zero, so ignore. Starting at index 1...
        // From the other side, starting straight from index N-1
        // So there is always one sample in the middle left that should be included
        // Therefore, i <= halfN, so add the "equals"
        // run through indices
        // [11, 12, 13, 14, 15] + [16]
        // [21, 20, 19, 18, 17] + [16]

        dftPol[i + 1].magn = 0;
        dftPol[i + 1].angl = 0;
        dftPol[N - 1 - i].magn = 0;
        dftPol[N - 1 - i].angl = 0;
    }
}