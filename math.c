#include <math.h>
#include "wavetables.h"

void sawtooth(double *waveTable, int nPartials, int nSamples) {

    for (int i = 0; i < nSamples; i++) {
        double sample_value = 0;
        for (int p = 1; p <= nPartials; p++) {
            sample_value += sin(p * 2.0 * M_PI * i / nSamples) / p;
        }
        waveTable[i] = sample_value;
    }
}

void sawtoothNonAliased(double *waveTable, int nSamples) {

    for (int i = 0; i < nSamples; i++) {
        int nSamplesMinusOne = nSamples - 1; // to really go from 1 to -1
        waveTable[i] = ((nSamplesMinusOne - i) / (0.5 * nSamplesMinusOne)) - 1;
    }
}

void square(double *waveTable, int nPartials, int nSamples) {

    for (int i = 0; i < nSamples; i++) {
        double sample_value = 0;
        for (int p = 1; p <= nPartials; p++) {
            if (p % 2 == 0) {
                sample_value += 0;
            } else {
                sample_value += sin(p * 2.0 * M_PI * i / nSamples) / p;
            }
        }
        waveTable[i] = sample_value;
    }
}

void triangle2(double *waveTable, int nPartials, int nSamples) {

    for (int i = 0; i < nSamples; i++) {
        double sample_value = 0;
        for (int p = 1; p <= nPartials; p++) {
            if (p % 2 == 0) {
                sample_value += 0;
            } else {
                sample_value += sin(p * 2.0 * M_PI * i / nSamples) / p * p;
            }
        }
        waveTable[i] = sample_value;
    }
}

PolarComplex car2pol(CartesianComplex cartesian) {

    PolarComplex polar;
    polar.magn = sqrt(cartesian.real * cartesian.real + cartesian.imag * cartesian.imag);
    polar.angl = atan2(cartesian.imag, cartesian.real);
    return polar;
}

CartesianComplex pol2car(PolarComplex polar) {

    CartesianComplex cartesian;
    cartesian.real = polar.magn * cos(polar.angl);
    cartesian.imag = polar.magn * sin(polar.angl);
    return cartesian;
}

void car2PolArray(const CartesianComplex *carArr, PolarComplex *polArr, int length) {

    for (int i = 0; i < length; i++) {
        polArr[i] = car2pol(carArr[i]);
    }
}

void pol2CarArray(const PolarComplex *polarIn, CartesianComplex *cartesianOut, int length) {

    for (int i = 0; i < length; i++) {
        cartesianOut[i] = pol2car(polarIn[i]);
    }
}

void dftCartesian(const double *waveTable, CartesianComplex *dftCar, int N) {

    for (int k = 0; k < N; k++) {
        dftCar[k].real = 0;
        dftCar[k].imag = 0;

        for (int n = 0; n < N; n++) {

            double theta = (2 * M_PI * k * n) / N;
            dftCar[k].real += waveTable[n] * cos(theta);
            dftCar[k].imag -= waveTable[n] * sin(theta);
        }
    }
}

void dftPolar(const double *waveTable, PolarComplex *dftPol, int N) {

    for (int k = 0; k < N; k++) {

        CartesianComplex cartesian;

        cartesian.real = 0;
        cartesian.imag = 0;

        for (int n = 0; n < N; n++) {

            double theta = (2 * M_PI * k * n) / N;
            cartesian.real += waveTable[n] * cos(theta);
            cartesian.imag -= waveTable[n] * sin(theta);
        }
        dftPol[k] = car2pol(cartesian);
    }
}

void idftCartesian(const CartesianComplex *dftCar, double *waveTable, int N) {

    for (int n = 0; n < N; n++) {
        waveTable[n] = 0;

        for (int k = 0; k < N; k++) {
            double theta = (2 * M_PI * k * n) / N;
            waveTable[n] += dftCar[k].real * cos(theta) + dftCar[k].imag * sin(theta);
        }
        waveTable[n] /= N;
    }
}

void idftPolar(const PolarComplex *dftPol, double *waveTable, int N) {

    for (int n = 0; n < N; n++) {
        waveTable[n] = 0;

        for (int k = 0; k < N; k++) {
            double theta = (2 * M_PI * k * n) / N;
            CartesianComplex cartesian = pol2car(dftPol[k]);
            waveTable[n] += cartesian.real * cos(theta) + cartesian.imag * sin(theta);
        }
        waveTable[n] /= N;
    }
}

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

        dftPol[i+1].magn = 0;
        dftPol[i+1].angl = 0;
        dftPol[N-1-i].magn = 0;
        dftPol[N-1-i].angl = 0;
    }
}