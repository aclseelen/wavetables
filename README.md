# Wavetables

---

## About

`Wavetables` is an application written in C.
The project was started by Alfons Seelen in February 2023.

---

## Description
`Wavetables` can be used to generate wave tables of certain shapes,
e.g. sawtooth, square, and triangle.
Furthermore, it can be used to generate a Discrete Fourier Transform
or the inverse, in order to quickly review the harmonic
characteristics of a waveform entered by the user.
The spectral analysis can then be edited to recreate
an altered version of the original waveform, for example to prevent
aliasing.

---

## Usage

### Options

`-e` external file  
`-s` number of samples  
`-p` number of partials  
`-w` waveform

### Examples

To generate a sawtooth with 20 partials in 1024 samples:

`$ ./wavetables -w sawtooth -p 20 -s 1024`

To show your own wave table and create analysis files
(by default only polar: magnitude and angle (phase)):

`$ ./wavetables -e my-wave-table.txt -s 1024`

To load your own wave table of 1024 samples (as a text file)
and strip all partials except the first 40:

`$ ./wavetables -e my-wave-table.txt -s 1024 -p 40`

---

## Waveforms

Currently, waveforms are implemented for the following
keywords for the `-w` option:

* `sawtooth` | `saw`
* `square`
* `pulse`
* `sawLowPass` | `saw-lp`
* `triangle`
* `triangle2`
* `mute4` | `stair4`

Choosing a sawtooth wave with `-p 0` returns a non-aliased
sawtooth wave.

### `Triangle2`

`Triangle2` is a triangular waveform, but with all partials in phase,
resulting in a different (round) shape, but the same sound.
It's essentially a square wave with weaker overtones.
It has the advantage that it is louder than a regular triangular
waveform when normalized, i.e. it has lower peaks.

### Non-aliased

Currently, the `sawtooth` also has a non-aliased version implemented,
that is achieved by setting `0` for the partial option `-p`,
resulting in the "traditional" waveform, i.e. just a straight line.

## Plotting

TXT wave table files can then be plotted with GNU Plot for example.
There are no specific plans yet for integration of plotting
application, except for bash scripts.

---

## Releases

No releases yet