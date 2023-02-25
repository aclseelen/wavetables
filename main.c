#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include "wavetables.h"

int main(int argc, char *argv[]) {

    const size_t CHAR_64_SIZE = sizeof(char) * 64;
    int generateOrLoad = 0;

    int nPartials = 32;
    int nSamples = 512;

    char *waveformName = malloc(CHAR_64_SIZE);
    char *outputFolder = malloc(CHAR_64_SIZE);

    char *outputFilename = malloc(CHAR_64_SIZE);
    char *inputFilename = malloc(CHAR_64_SIZE);

    int opt;
    while ((opt = getopt(argc, argv, "p:s:w:o:e:")) != -1) {
        switch (opt) {
            case 'p':
                nPartials = strtol(optarg, NULL, 10);
                break;
            case 's':
                nSamples = strtol(optarg, NULL, 10);
                break;
            case 'w':
                if (generateOrLoad != 0) {
                    break;
                }
                strcpy(waveformName, optarg);
                generateOrLoad = 1;
                break;
            case 'e':
                if (generateOrLoad != 0) {
                    break;
                }
                strcpy(inputFilename, optarg);
                generateOrLoad = 2;
                break;
            case 'o':
                strcpy(outputFolder, optarg);
                break;
            default:
        }
    }

    double *waveTable = malloc(sizeof(double) * nSamples);

    switch (generateOrLoad) {

        case 0:
            printf("Nothing to do here... Please choose either option '-w' or '-e' next time.");
            return 0;
        case 1:
            // create wave table
            if (generateWaveTable(waveformName, waveTable, nSamples, nPartials) != 0) {
                return 1;
            }
            snprintf(outputFilename, CHAR_64_SIZE, "%s%s-%d-%d.txt", outputFolder, waveformName, nPartials, nSamples);
            writeToTextFile(waveTable, nSamples, outputFilename);
            break;
        case 2:
            // load wave table
            if (loadWaveTable(inputFilename, waveTable, nSamples) != 0) {
                return 1;
            }
            strcpy(waveformName, basename(inputFilename));
            free(inputFilename);
            break;
        default:
            printf("Exiting..");
            return 1;
    }

    snprintf(outputFilename, CHAR_64_SIZE, "%s%s-%d-%d.txt", outputFolder, waveformName, nPartials, nSamples);
    writeToTextFile(waveTable, nSamples, outputFilename);


    /** DFT analysis / decomposition */

    CartesianComplex *cartesianTable = malloc(sizeof(CartesianComplex) * nSamples);
    PolarComplex *polarTable = malloc(sizeof(PolarComplex) * nSamples);

    dftCartesian(waveTable, cartesianTable, nSamples);
    car2PolArray(cartesianTable, polarTable, nSamples);

    double *waveTableIdftCar = malloc(sizeof(double) * nSamples);
    double *waveTableIdftPol = malloc(sizeof(double) * nSamples);

    /** edit DFT before recomposition */

    if (generateOrLoad == 2 && nPartials > 0) {
        stripHarmonics(polarTable, nPartials, nSamples);
    }

    /** IDFT synthesis */

    idftCartesian(cartesianTable, waveTableIdftCar, nSamples);
    idftPolar(polarTable, waveTableIdftPol, nSamples);

    char *filenameReal = malloc(CHAR_64_SIZE);
    char *filenameImag = malloc(CHAR_64_SIZE);
    char *filenameMagn = malloc(CHAR_64_SIZE);
    char *filenameAngl = malloc(CHAR_64_SIZE);
    char *filenameIdftCar = malloc(CHAR_64_SIZE);
    char *filenameIdftPol = malloc(CHAR_64_SIZE);

    snprintf(filenameReal, CHAR_64_SIZE, "%s%s-%d-%d-dft-real.txt", outputFolder, waveformName, nPartials, nSamples);
    snprintf(filenameImag, CHAR_64_SIZE, "%s%s-%d-%d-dft-imag.txt", outputFolder, waveformName, nPartials, nSamples);
    snprintf(filenameMagn, CHAR_64_SIZE, "%s%s-%d-%d-dft-magn.txt", outputFolder, waveformName, nPartials, nSamples);
    snprintf(filenameAngl, CHAR_64_SIZE, "%s%s-%d-%d-dft-angl.txt", outputFolder, waveformName, nPartials, nSamples);
    snprintf(filenameIdftCar, CHAR_64_SIZE, "%s%s-%d-%d-idft-car.txt", outputFolder, waveformName, nPartials, nSamples);
    snprintf(filenameIdftPol, CHAR_64_SIZE, "%s%s-%d-%d-idft-pol.txt", outputFolder, waveformName, nPartials, nSamples);

    writeCartesianToTextFiles(cartesianTable, nSamples, filenameReal, filenameImag);
    writePolarToTextFiles(polarTable, nSamples, filenameMagn, filenameAngl);
    writeToTextFile(waveTableIdftCar, nSamples, filenameIdftCar);
    writeToTextFile(waveTableIdftPol, nSamples, filenameIdftPol);

    /** free memory */

    free(outputFilename);
    free(outputFolder);
    free(waveformName);
    free(waveTable);
    free(cartesianTable);

    return 0;
}
