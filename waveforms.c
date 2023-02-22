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

void sawtoothLowPass(double *waveTable, int nPartials, int nSamples) {

    for (int i = 0; i < nSamples; i++) {
        double sample_value = 0;
        for (int p = 1; p <= nPartials; p++) {
            sample_value += sin(p * 2.0 * M_PI * i / nSamples) / pow(p, 2);
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

void pulse(double *waveTable, int nPartials, int nSamples) {

    for (int i = 0; i < nSamples; i++) {
        double sample_value = 0;
        for (int p = 1; p <= nPartials; p++) {
            sample_value += sin(p * 2.0 * M_PI * i / nSamples) / nPartials;
        }
        waveTable[i] = sample_value;
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
                sample_value += sin(p * 2.0 * M_PI * i / nSamples) / pow(p, 2);
            }
        }
        waveTable[i] = sample_value;
    }
}

void triangle(double *waveTable, int nPartials, int nSamples) {

    for (int i = 0; i < nSamples; i++) {
        double sample_value = 0;
        for (int p = 1; p <= nPartials; p++) {
            if (p % 2 == 0) {
                sample_value += 0;
            } else if ((p-1) % 4 == 0) {
                sample_value += sin(p * 2.0 * M_PI * i / nSamples) / pow(p, 2);
            } else {
                sample_value -= sin(p * 2.0 * M_PI * i / nSamples) / pow(p, 2);
            }
        }
        waveTable[i] = sample_value;
    }
}