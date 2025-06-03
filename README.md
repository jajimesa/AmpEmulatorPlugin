# AmpEmulatorPlugin [(🇪🇸)](README_es.md)

This academic project [1] contains the implementation of a *standalone* application and VST3 plugin that uses artificial intelligence to emulate electric guitar amplifiers and pedals (*overdrive*, distortion, and compression) in real time. It is implemented using the JUCE *framework*, leveraging the C++ WaveNet model called [WaveNetVA](https://github.com/damskaggep/WaveNetVA). Based on the works [2,3,6].

#### Credits

Originally developed as part of my [Bachelor's Thesis](https://zenodo.org/records/15490785) for the Computer Engineering degree at the University of La Rioja (Spain), titled *Deep Learning for Real-Time Emulation of Electric Guitar Equipment with Raspberry Pi 5*. Conceptually based on the repositories [WaveNetVA](https://github.com/damskaggep/WaveNetVA) by Damskägg, Eero-Pekka, and [SmartGuitarAmp](https://github.com/GuitarML/SmartGuitarAmp) by Keith Bloemer [4]. Complementary hardware developed as a deployment platform based on [Proteus](https://www.youtube.com/watch?v=dFMsWW0uC7w) by Keith Bloemer [7]. I am very grateful for their contributions to the community, which not only helped me learn a lot but also allowed me to test my project using their plugins [5].

## Functionality

The application has two versions for Windows/x86:
- A *standalone* or desktop version compatible with the [Focusrite Scarlett SOLO 3rd Gen](https://shop.plastic.es/estudio/interfaces-de-audio/focusrite-interfaces-de-audio/focusrite-scarlett-solo-3rd-gen/) audio interfaces.
- A VST3 plugin version compatible with any DAW (*Digital Audio Workstation*). Successfully tested with [Reaper](https://www.reaper.fm/).

A *standalone* version for Linux/aarch64 will soon have a *release*.

<p float="left">
  <img src="AmpEmulatorStandalone.png" width="400" />
  <img src="AmpEmulatorPlugin.png" width="400" /> 
</p>

> (Left) User interface of the *standalone* application  
> (Right) VST3 plugin embedded in Reaper

## Compilation

The repository contains the code for a project using the [JUCE](https://juce.com/) *framework*, specifically version 5.4.2. This is an outdated version that is no longer available for download from official repositories, as it has been removed, though unofficial *forks* still exist. The project had to be compiled with this version due to dependencies introduced by [WaveNetVA](https://github.com/damskaggep/WaveNetVA). **I do not recommend compiling it manually; in our case, setting up the development environment correctly was very challenging**. If you still wish to do so, below are some tips to help.

> After obtaining JUCE 5.4.2, it must also be compiled. This *framework* integrates with Visual Studio, from which the project can be launched and compiled. The required `gcc` version for compiling everything must be strictly < 9.  
> The project depends on two external libraries: [Eigen](https://eigen.tuxfamily.org/index.php?title=Main_Page) and the [Steinberg ASIO SDK](https://www.steinberg.net/es/developers/), in versions 3.3.7 and 2.3.3, respectively. For JUCE to detect them, you must create a `./Libraries` folder.  
> It is likely that many dependencies will be broken due to the newly installed JUCE version, in which case you’ll need to fix them manually within JUCE.

#### Windows/x86

Once JUCE is installed, open the project using the `AmpEmulatorPlugin.jucer` file and launch it with Visual Studio. From the IDE, it’s as simple as compiling in *release* mode (otherwise, the necessary optimizations won’t be applied, and it won’t work in real time).

#### Linux/aarch64

Generate the Makefile using JUCE. Install the following dependencies:
```bash
sudo apt-get install libtiff-dev
sudo apt-get libwebkit2gtk-4.0-dev
```

Navigate to the newly created `./Builds/LinuxMakefile` folder and run make. You’ll need to modify the dependency linking in the Makefile and set make config=Release.

## Deployment on Raspberry Pi 5

The *standalone* application for Linux/aarch64 has been tested and works in real time on the [Raspberry Pi 5](https://www.raspberrypi.com/products/raspberry-pi-5/) with the default operating system, Raspberry OS. In the project this repository is part of [1], a fully functional digital pedal is built, and a list of the materials and circuit used is provided. Using this application or others like [6,7], you can easily build a fully operational, high-fidelity homemade pedal or amplifier. The pedal concept is based on the [Proteus](https://www.youtube.com/watch?v=dFMsWW0uC7w) pedal by Keith Bloemer [7].

<p float="left">
  <img src="pedal.png" height="250" />
  <img src="pedal-circuit.png" height="250" /> 
</p>

## References

[1] Jiménez Santana, J.: "Aprendizaje profundo para la emulación en tiempo real de equipamiento de guitarra eléctrica con Raspberry Pi 5." *Zenodo* (2025). [DOI](https://doi.org/10.5281/zenodo.15490785)  
[2] Wright, A. et al.: "Real-Time Guitar Amplifier Emulation with Deep Learning." *Applied Sciences* (2020). [DOI](https://doi.org/10.3390/app10030766)  
[3] Van den Oord, A. et al.: "WaveNet: A Generative Model for Raw Audio." *arXiv* (2016). [DOI](https://doi.org/10.48550/arXiv.1609.03499)  
[4] Bloemer, K.: PedalNetRT, [GitHub](https://github.com/GuitarML/PedalNetRT). (2020).  
[5] Damskägg, E.-P.: WaveNetVA, [GitHub](https://github.com/damskaggep/WaveNetVA). (2019).  
[6] Bloemer, K.: SmartPluginAmp, [GitHub](https://github.com/GuitarML/SmartGuitarAmp). (2020).  
[7] Bloemer, K.: Proteus, [GitHub](https://github.com/GuitarML/Proteus). (2023).

Author: *Javier Jiménez Santana*  
Supervisors: *Jose Divasón Mallagaray, Silvano Nájera Canal*
