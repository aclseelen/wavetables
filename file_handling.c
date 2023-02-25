#include <stdio.h>
#include <stdlib.h>
#include "wavetables.h"

void writeToTextFile(const double array[], int len, const char *filename) {

    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        printf("Error opening file (writeToTextFile())!\n");
        exit(1);
    }

    for (int i = 0; i < len; i++) {
        fprintf(f, "%.20f\n", array[i]);
    }

    fclose(f);
}

void writeCartesianToTextFiles(const CartesianComplex carArr[], int len, const char *filenameReal,
                               const char *filenameImag) {

    FILE *f_real = fopen(filenameReal, "w");
    if (f_real == NULL) {
        printf("Error opening file (writeCartesianToTextFiles())!\n");
        exit(1);
    }

    FILE *f_imag = fopen(filenameImag, "w");
    if (f_imag == NULL) {
        printf("Error opening file (writeCartesianToTextFiles())!\n");
        exit(1);
    }

    for (int i = 0; i < len; i++) {
        fprintf(f_real, "%.20f\n", carArr[i].real);
        fprintf(f_imag, "%.20f\n", carArr[i].imag);
    }

    fclose(f_real);
    fclose(f_imag);
}

void writePolarToTextFiles(const PolarComplex polArr[], int len, const char *filenameMagn, const char *filenameAngl) {

    FILE *f_magn = fopen(filenameMagn, "w");
    if (f_magn == NULL) {
        printf("Error opening file (writePolarToTextFiles())!\n");
        exit(1);
    }

    FILE *f_angl = fopen(filenameAngl, "w");
    if (f_angl == NULL) {
        printf("Error opening file (writePolarToTextFiles())!\n");
        exit(1);
    }

    for (int i = 0; i < len; i++) {
        fprintf(f_magn, "%.20f\n", polArr[i].magn);
        fprintf(f_angl, "%.20f\n", polArr[i].angl);
    }

    fclose(f_magn);
    fclose(f_angl);
}

void writePolarToPlotFile(const PolarComplex polArr[], int len) {
    FILE *gnuplot = popen("gnuplot", "w");
    if (!gnuplot) {
        perror("popen");
        exit(EXIT_FAILURE);
    }

    fprintf(gnuplot, "gnuplot gnuplotscript.plt\n");
    for (int i = 0; i < len; ++i) {
        fprintf(gnuplot, "%.20f \"%.20f\n", polArr[i].magn, polArr[i].angl);
    }
    fprintf(gnuplot, "e\n");
    fprintf(stdout, "Click Ctrl+d to quit...\n");
    fflush(gnuplot);
    getchar();

    pclose(gnuplot);
    exit(EXIT_SUCCESS);
}

void readFrom(const char *inputFilename, double *waveTable, const int nSamples, const int maxLineLength) {

    FILE *f = fopen(inputFilename, "r");
    if (f == NULL) {
        printf("Error opening file (readFrom())!\n");
        exit(1);
    }

    char line[maxLineLength];
    unsigned int index = 0;
    while (fgets(line, maxLineLength, f) != NULL && index < nSamples) {
        waveTable[index] = strtod(line, NULL);
        index++;
    }

    fclose(f);
}
