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

## Build & Install

The project uses the `CMake` build system for multiple
platform usage. Your IDE might recognize it and configure and build
automatically. You can then install the binary called `wavetables`
wherever your OS and you like it best.

### Windows and Mac

You're on your own there, unfortunately. I'm not familiar with
command line applications on Windows nor Mac.

I did however choose
`CMake` as build system in order to make it multi-platform. Any
information is appreciated, so I can publish it here and help other
users.

### Linux 

I'm new to `CMake` and the reason for not using `Makefile` is because
of users of other platforms. From here, I did not figure out exactly
how to create a simple install method Linux users are used to, like
`make clean && make install`, since `cmake` generates a dependent
`Makefile` in the (excluded) `build` directory, instead of in the
project's main directory.

So, for Linux users I wrote a simple build and install script, which
requires `cmake` (minimum version `3.22`) to be available as
command line application. It should be run as superuser in order
to install it in `/usr/local/bin/`.

First, navigate to the project main directory (where you found this
README.md), for example:

`$ cd ~/src/wavetables/`

Then run the script as follows:

`$ sudo ./scripts/linux_build_install_script.sh`

If for some reason the script is not executable, alter permissions
first, like for example:

`$ chmod 755 ./scripts/linux_build_install_script.sh`

#### Uninstall | Delete

Check whether and/or where `wavetables` was installed 

To remove it just delete the file `wavetables` where it was installed,
most likely `/usr/local/bin/`. Nothing else was installed.

`$ sudo rm -i /usr/local/bin/wavetables`

---

## Usage

### Options

`-e` external file  
`-s` number of samples  
`-p` number of partials  
`-w` waveform
`-f` file output (reduction)

### Examples

To generate a sawtooth with 20 partials in 1024 samples:

`$ ./wavetables -w sawtooth -p 20 -s 1024`

To show your own wave table and create analysis files
(by default only polar: magnitude and angle (phase)):

`$ ./wavetables -e my-wave-table.txt -s 1024`

To load your own wave table of 1024 samples (as a text file)
and strip all partials except the first 40:

`$ ./wavetables -e my-wave-table.txt -s 1024 -p 40`

### `-f`

By default (`-f 15`) all output files are generated. To select only
certain output files, sum their numbers and use that value with the
`-f` option. The others will then be suppressed.

* `8` &rarr; Cartesian DFT files (real & imaginary)
* `4` &rarr; Polar DFT files (magnitude & angle)
* `2` &rarr; Cartesian IDFT file
* `1` &rarr; Polar IDFT file

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