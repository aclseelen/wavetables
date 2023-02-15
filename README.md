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
an altered version of the orginal waveform, for example to prevent
aliasing.

---

## Usage

Intended use, somewhat like:

`$ ./wavetables -w sawtooth -p 20 -n 1024`

to generate a sawtooth with 20 partials in 1024 samples, or:

`$ ./wavetables -e my-wave-table.txt -n 1024`

to show your own wave table and create analysis files
(by default only polar: magnitude and angle (phase))

`$ ./wavetables -e my-wave-table.txt -n 1024 -p 40`

to load your own wave table of 1024 samples (as a text file)
and strip all partials except the first 40.

`-e` external file
`-n` number of samples
`-p` number of partials
`-w` waveform

---

## Plotting

TXT wave table files can then be plotted with GNU Plot for example.
There are no specific plans yet for integration of plotting
application, except for bash scripts.

---

## Releases

No releases yet