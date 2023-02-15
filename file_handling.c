#include <stdio.h>
#include <stdlib.h>
#include "wavetables.h"

void write_to_text_file(double array[], int len, char *filename) {

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

void write_to_text_files(CartesianComplex array[], int len, char *filename_real, char *filename_imag) {

    FILE *f_real = fopen(filename_real, "w");
    if (f_real == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    FILE *f_imag = fopen(filename_imag, "w");
    if (f_imag == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    for (int i = 0; i < len; i++) {
        fprintf(f_real, "%.20f\n", array[i].real);
        fprintf(f_imag, "%.20f\n", array[i].imag);
    }

    fclose(f_real);
    fclose(f_imag);
}