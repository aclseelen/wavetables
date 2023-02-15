#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "wavetables.h"

int main(int argc, char *argv[]) {

    int n_partials = 32;
    int n_samples = 512;

    char *waveform = malloc(16 * sizeof(char));

    int opt;
    while ((opt = getopt(argc, argv, "p:s:w:")) != -1) {
        switch (opt) {
            case 'p':
                n_partials = atoi(optarg);
                break;
            case 's':
                n_samples = atoi(optarg);
                break;
            case 'w':
                strcpy(waveform, optarg);
                break;
        }
    }

    /** create wave table*/

    double *wave_table = malloc(sizeof(double) * n_samples);
    if (strcmp(waveform, "sawtooth") == 0 || strcmp(waveform, "saw") == 0)
        sawtooth(wave_table, n_partials, n_samples);
    else if (strcmp(waveform, "square" ) == 0)
        square(wave_table, n_partials, n_samples);
    else if (strcmp(waveform, "triangle2" ) == 0)
        triangle2(wave_table, n_partials, n_samples);
    else {
        printf("Waveform '%s' not recognized. Use 'sawtooth, 'square', or 'triangle2' instead", waveform);
        return 1;
    }

    size_t char64size = sizeof(char) * 64;
    char *output_filename = malloc(char64size);
    snprintf(output_filename, char64size, "%s-%d-%d.txt", waveform, n_partials, n_samples);

    write_to_text_file(wave_table, n_samples, output_filename);

    /** DFT analysis */

    CartesianComplex *cartesian_table = malloc(sizeof(CartesianComplex) * n_samples);
    dft(wave_table, cartesian_table, n_samples);

    char *filename_real = malloc(char64size);
    char *filename_imag = malloc(char64size);
    snprintf(filename_real, char64size, "%s-%d-%d-dft-real.txt", waveform, n_partials, n_samples);
    snprintf(filename_imag, char64size, "%s-%d-%d-dft-imag.txt", waveform, n_partials, n_samples);

    write_to_text_files(cartesian_table, n_samples, filename_real, filename_imag);

    /** free memory */

    free(output_filename);
    free(waveform);
    free(wave_table);
    free(cartesian_table);

    return 0;
}
