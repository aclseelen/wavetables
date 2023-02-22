#include <stdio.h>
#include <stdlib.h>
#include "wavetables.h"

void writeToTextFile(const double array[], int len, char *filename) {

    size_t char70size = sizeof(char) * 70;
    char *outputFilename = malloc(char70size);
    snprintf(outputFilename, char70size, "../output/txt/%s", filename);

    FILE *f = fopen(outputFilename, "w");
    free(outputFilename);
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    for (int i = 0; i < len; i++) {
        fprintf(f, "%.20f\n", array[i]);
    }

    fclose(f);
}

void writeCartesianToTextFiles(const CartesianComplex carArr[], int len, char *filenameReal, char *filenameImag) {

    size_t char70size = sizeof(char) * 70;
    char *outputFilename = malloc(char70size);
    snprintf(outputFilename, char70size, "../output/txt/%s", filenameReal);

    FILE *f_real = fopen(outputFilename, "w");
    if (f_real == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    snprintf(outputFilename, char70size, "../output/txt/%s", filenameImag);

    FILE *f_imag = fopen(outputFilename, "w");
    free(outputFilename);
    if (f_imag == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    for (int i = 0; i < len; i++) {
        fprintf(f_real, "%.20f\n", carArr[i].real);
        fprintf(f_imag, "%.20f\n", carArr[i].imag);
    }

    fclose(f_real);
    fclose(f_imag);
}

void writePolarToTextFiles(const PolarComplex polArr[], int len, char *filenameMagn, char *filenameAngl) {

    size_t char70size = sizeof(char) * 70;
    char *outputFilename = malloc(char70size);
    snprintf(outputFilename, char70size, "../output/txt/%s", filenameMagn);

    FILE *f_magn = fopen(outputFilename, "w");
    if (f_magn == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    snprintf(outputFilename, char70size, "../output/txt/%s", filenameAngl);

    FILE *f_angl = fopen(outputFilename, "w");
    if (f_angl == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    free(outputFilename);

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