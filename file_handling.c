#include <stdio.h>
#include <stdlib.h>
#include "wavetables.h"

void writeToTextFile(const double array[], int len, char *filename) {

    FILE *f = fopen(filename, "w");
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

    FILE *f_real = fopen(filenameReal, "w");
    if (f_real == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    FILE *f_imag = fopen(filenameImag, "w");
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

    FILE *f_magn = fopen(filenameMagn, "w");
    if (f_magn == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    FILE *f_angl = fopen(filenameAngl, "w");
    if (f_angl == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    for (int i = 0; i < len; i++) {
        fprintf(f_magn, "%.20f\n", polArr[i].magn);
        fprintf(f_angl, "%.20f\n", polArr[i].angl);
    }

    fclose(f_magn);
    fclose(f_angl);
}