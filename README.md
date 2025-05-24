# AmpEmulatorPlugin
Este proyecto académico contiene la implementación de una aplicación *standalone* y plugin VST3 que emplea inteligencia artificial, concretamente un modelo tipo WaveNet [1], para emular en tiempo real amplificadores y pedales de guitarra eléctrica (*overdrive*, distorsión y compresión). Implementado mediante el *framework* JUCE. Basado en los trabajos [1,2,5]. 

#### Créditos
Desarrollado originalmente como parte de mi [Trabajo Fin de Grado](https://zenodo.org/records/15490785) para la titulación de Ingeniería Informática de la Universidad de La Rioja (España), titulado *Aprendizaje profundo para la emulación en tiempo real de equipamiento de guitarra eléctrica con Raspberry Pi 5*. Basado conceptualmente en los repositorios [WaveNetVA](https://github.com/damskaggep/WaveNetVA) de Damskägg, Eero-Pekka y [SmartGuitarAmp](https://github.com/GuitarML/SmartGuitarAmp), de Keith Bloemer [3]. Agradezco mucho sus contribuciones a la comunidad, gracias a las cuales no solo he aprendido mucho, sino que he podido testear mi proyecto empleando sus plugins [4].

## Referencias
[1]	Wright, A. et al.: "Real-Time Guitar Amplifier Emulation with Deep Learning". *Applied Sciences* (2020). (https://doi.org/10.3390/app10030766)   
[2]	Van den Oord, A. et al.: "WaveNet: A Generative Model for Raw Audio". *arXiv* (2016). (https://doi.org/10.48550/arXiv.1609.03499)   
[3]	Bloemer, K.: PedalNetRT, GitHub (https://github.com/GuitarML/PedalNetRT). (2020).   
[4]	Damskägg, E.-P.: WaveNetVA, GitHub (https://github.com/damskaggep/WaveNetVA). (2019).   
[5]	Bloemer, K.: SmartPluginAmp, Github (https://github.com/GuitarML/SmartGuitarAmp). (2020).

Autor: *Javier Jiménez Santana*   
Tutores: *Jose Divasón Mallagaray, Silvano Nájera Canal*
