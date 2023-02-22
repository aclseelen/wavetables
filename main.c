#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "wavetables.h"

int main(int argc, char *argv[]) {

    int nPartials = 32;
    int nSamples = 512;

    char *waveform = malloc(16 * sizeof(char));
    char *outputFolder = malloc(16 * sizeof(char));

    int generateOrInput = 0;
    int opt;
    while ((opt = getopt(argc, argv, "p:s:w:o")) != -1) {
        switch (opt) {
            case 'p':
                nPartials = atoi(optarg);
                break;
            case 's':
                nSamples = atoi(optarg);
                break;
            case 'w':
                if (generateOrInput != 0) {
                    break;
                }
                strcpy(waveform, optarg);
                generateOrInput = 1;
                break;
            case 'e':
                if (generateOrInput != 0) {
                    break;
                }
                strcpy(waveform, optarg);
                generateOrInput = 2;
                break;
            case 'o':
                strcpy(outputFolder, optarg);
                break;
            default:
        }
    }
    /** create wave table*/

    double *waveTable = malloc(sizeof(double) * nSamples);

    int waveformSuccess = getWaveform(waveform, waveTable, nSamples, nPartials);
    if (waveformSuccess != 0) {
        return 1;
    }


    size_t char64size = sizeof(char) * 64;
    char *outputFilename = malloc(char64size);
    snprintf(outputFilename, char64size, "%s-%d-%d.txt", waveform, nPartials, nSamples);

    writeToTextFile(waveTable, nSamples, outputFilename);

    /** DFT analysis / decomposition */

    CartesianComplex *cartesianTable = malloc(sizeof(CartesianComplex) * nSamples);
    PolarComplex *polarTable = malloc(sizeof(PolarComplex) * nSamples);

    dftCartesian(waveTable, cartesianTable, nSamples);
    car2PolArray(cartesianTable, polarTable, nSamples);

    double *waveTableIdftCar = malloc(sizeof(double) * nSamples);
    double *waveTableIdftPol = malloc(sizeof(double) * nSamples);

    /** edit DFT before recomposition */

//    stripHarmonics(polarTable, 20, nSamples);

    /** IDFT synthesis */

    idftCartesian(cartesianTable, waveTableIdftCar, nSamples);
    idftPolar(polarTable, waveTableIdftPol, nSamples);

    char *filenameReal = malloc(char64size);
    char *filenameImag = malloc(char64size);
    char *filenameMagn = malloc(char64size);
    char *filenameAngl = malloc(char64size);
    char *filenameIdftCar = malloc(char64size);
    char *filenameIdftPol = malloc(char64size);

    snprintf(filenameReal, char64size, "%s-%d-%d-dft-real.txt", waveform, nPartials, nSamples);
    snprintf(filenameImag, char64size, "%s-%d-%d-dft-imag.txt", waveform, nPartials, nSamples);
    snprintf(filenameMagn, char64size, "%s-%d-%d-dft-magn.txt", waveform, nPartials, nSamples);
    snprintf(filenameAngl, char64size, "%s-%d-%d-dft-angl.txt", waveform, nPartials, nSamples);
    snprintf(filenameIdftCar, char64size, "%s-%d-%d-idft-car.txt", waveform, nPartials, nSamples);
    snprintf(filenameIdftPol, char64size, "%s-%d-%d-idft-pol.txt", waveform, nPartials, nSamples);

    writeCartesianToTextFiles(cartesianTable, nSamples, filenameReal, filenameImag);
    writePolarToTextFiles(polarTable, nSamples, filenameMagn, filenameAngl);
    writeToTextFile(waveTableIdftCar, nSamples, filenameIdftCar);
    writeToTextFile(waveTableIdftPol, nSamples, filenameIdftPol);

//    writePolarToPlotFile(waveTableIdftPol, nSamples);

    /** free memory */

    free(outputFilename);
    free(outputFolder);
    free(waveform);
    free(waveTable);
    free(cartesianTable);

    return 0;
}
