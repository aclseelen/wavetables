#include <math.h>
#include "wavetables.h"

void sawtooth(double wave_table[], int n_partials, int n_samples) {

    for (int i = 0; i < n_samples; i++) {
        double sample_value = 0;
        for (int p = 1; p <= n_partials; p++) {
            sample_value += sin(p * 2.0 * M_PI * i / n_samples) / p;
        }
        wave_table[i] = sample_value;
    }
}

void square(double wave_table[], int n_partials, int n_samples) {

    for (int i = 0; i < n_samples; i++) {
        double sample_value = 0;
        for (int p = 1; p <= n_partials; p++) {
            if (p % 2 == 0) {
                sample_value += 0;
            } else {
                sample_value += sin(p * 2.0 * M_PI * i / n_samples) / p;
            }
        }
        wave_table[i] = sample_value;
    }
}

void triangle2(double wave_table[], int n_partials, int n_samples) {

    for (int i = 0; i < n_samples; i++) {
        double sample_value = 0;
        for (int p = 1; p <= n_partials; p++) {
            if (p % 2 == 0) {
                sample_value += 0;
            } else {
                sample_value += sin(p * 2.0 * M_PI * i / n_samples) / p * p;
            }
        }
        wave_table[i] = sample_value;
    }
}

PolarComplex car2pol(CartesianComplex cartesian) {

    PolarComplex polar;
    polar.magn = sqrt(cartesian.real * cartesian.real + cartesian.imag * cartesian.imag);
    polar.angl = atan2(cartesian.imag, cartesian.real);
    return polar;
}

CartesianComplex pol2car(PolarComplex polar) {

    CartesianComplex cartesian;
    cartesian.real = polar.magn * cos(polar.angl);
    cartesian.imag  = polar.magn * sin(polar.angl);
    return cartesian;
}

void car2pol_array(CartesianComplex *cartesian_in, PolarComplex *polar_out, int length) {

    for (int i = 0; i < length; i++) {
        polar_out[i] = car2pol(cartesian_in[i]);
    }
}

void pol2car_array(PolarComplex *polar_in, CartesianComplex *cartesian_out, int length) {

    for (int i = 0; i < length; i++) {
        cartesian_out[i] = pol2car(polar_in[i]);
    }
}

void dft(double *wave_table, CartesianComplex *cartesian_table, int N) {

    for (int k = 0; k < N; k++) {
        cartesian_table[k].real = 0;
        cartesian_table[k].imag = 0;

        for (int n = 0; n < N; n++) {

            double theta = (2 * M_PI * k * n) / N;
            cartesian_table[k].real += wave_table[n] * cos(theta);
            cartesian_table[k].imag -= wave_table[n] * sin(theta);
        }
    }
}
