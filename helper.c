#include <stdio.h>
#include <string.h>

#include "wavetables.h"

int getWaveform(char *waveform, double *waveTable, int nSamples, int nPartials) {
    if (strcmp(waveform, "sawtooth") == 0 || strcmp(waveform, "saw") == 0) {
        if (nPartials == 0) {
            sawtoothNonAliased(waveTable, nSamples);
        } else {
            sawtooth(waveTable, nPartials, nSamples);
        }
    } else if (strcmp(waveform, "square") == 0) {
        square(waveTable, nPartials, nSamples);
    } else if (strcmp(waveform, "pulse") == 0) {
        pulse(waveTable, nPartials, nSamples);
    } else if (strcmp(waveform, "sawLowPass") == 0) {
        sawtoothLowPass(waveTable, nPartials, nSamples);
    } else if (strcmp(waveform, "triangle") == 0) {
        triangle(waveTable, nPartials, nSamples);
    } else if (strcmp(waveform, "triangle2") == 0) {
        triangle2(waveTable, nPartials, nSamples);
    } else {
        printf("Waveform '%s' not recognized. Use 'sawtooth, 'square', or 'triangle2' instead", waveform);
        return 1;
    }
    return 0;
}