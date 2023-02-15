#ifndef WAVETABLES_WAVETABLES_H
#define WAVETABLES_WAVETABLES_H

typedef struct {
    double real;
    double imag;
} CartesianComplex;

typedef struct {
    double magn;
    double angl;
} PolarComplex;

void car2pol_array(CartesianComplex *cartesian_in, PolarComplex *polar_out, int length);
void pol2car_array(PolarComplex *polar_in, CartesianComplex *cartesian_out, int length);

void dft(double *wave_table, CartesianComplex *cartesian_table, int N);

void sawtooth(double wave_table[], int n_partials, int n_samples);
void square(double wave_table[], int n_partials, int n_samples);
void triangle2(double wave_table[], int n_partials, int n_samples);

void write_to_text_file(double array[], int len, char *filename);
void write_to_text_files(CartesianComplex array[], int len, char *filename_real, char *filename_imag);

#endif //WAVETABLES_WAVETABLES_H
