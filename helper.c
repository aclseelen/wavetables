#include <stdio.h>
#include <string.h>

#include "wavetables.h"

int generateWaveTable(char *waveformName, double *waveTable, int nSamples, int nPartials) {
    if (strcmp(waveformName, "sawtooth") == 0 || strcmp(waveformName, "saw") == 0) {
        if (nPartials == 0) {
            sawtoothNonAliased(waveTable, nSamples);
        } else {
            sawtooth(waveTable, nPartials, nSamples);
        }
    } else if (strcmp(waveformName, "square") == 0) {
        square(waveTable, nPartials, nSamples);
    } else if (strcmp(waveformName, "pulse") == 0) {
        pulse(waveTable, nPartials, nSamples);
    } else if (strcmp(waveformName, "sawLowPass") == 0 || strcmp(waveformName, "saw-lp") == 0) {
        sawtoothLowPass(waveTable, nPartials, nSamples);
    } else if (strcmp(waveformName, "triangle") == 0) {
        triangle(waveTable, nPartials, nSamples);
    } else if (strcmp(waveformName, "triangle2") == 0) {
        triangle2(waveTable, nPartials, nSamples);
    } else if (strcmp(waveformName, "mute4") == 0 || strcmp(waveformName, "stair4") == 0) {
        muteFourth(waveTable, nPartials, nSamples);
    } else {
        printf("Waveform '%s' not recognized. Use 'sawtooth, 'square', or 'triangle2' instead", waveformName);
        return 1;
    }
    return 0;
}

int loadTable(char *inputFilename, double *table, int nSamples) {

    readFrom(inputFilename, table, nSamples, 32);
    return 0;
}
