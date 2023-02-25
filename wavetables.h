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

/* Fourier */
void car2PolArray(const CartesianComplex *carArr, PolarComplex *polArr, int length);
void pol2CarArray(const PolarComplex *polarIn, CartesianComplex *cartesianOut, int length);
void dftCartesian(const double *waveTable, CartesianComplex *dftCar, int N);
void dftPolar(const double *waveTable, PolarComplex *dftPol, int N);
void idftCartesian(const CartesianComplex *dftCar, double *waveTable, int N);
void idftPolar(const PolarComplex *dftPol, double *waveTable, int N);

/* operations */
void stripHarmonics(PolarComplex *dftPol, int nHarmonicsToKeep, int N);

/* helper */
int generateWaveTable(char *waveformName, double *waveTable, int nSamples, int nPartials);
int loadWaveTable(char *inputFilename, double *waveTable, int nSamples);

/* waveforms */
void sawtoothNonAliased(double *waveTable, int nSamples);
void sawtooth(double *waveTable, int nPartials, int nSamples);
void sawtoothLowPass(double *waveTable, int nPartials, int nSamples);
void pulse(double *waveTable, int nPartials, int nSamples);
void square(double *waveTable, int nPartials, int nSamples);
void triangle(double *waveTable, int nPartials, int nSamples);
void triangle2(double *waveTable, int nPartials, int nSamples);

/* file handling */
void writeToTextFile(const double *array, int len, const char *filename);
void writeCartesianToTextFiles(const CartesianComplex *carArr, int len, const char *filenameReal, const char *filenameImag);
void writePolarToTextFiles(const PolarComplex *polArr, int len, const char *filenameMagn, const char *filenameAngl);
void writePolarToPlotFile(const PolarComplex *polArr, int len);
void readFrom(const char *inputFilename, double *waveTable, const int nSamples, const int maxLineLength);

#endif //WAVETABLES_WAVETABLES_H
