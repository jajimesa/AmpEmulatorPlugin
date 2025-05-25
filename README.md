# AmpEmulatorPlugin
Este proyecto académico contiene la implementación de una aplicación *standalone* y plugin VST3 que emplea inteligencia artificial, concretamente un modelo tipo WaveNet [1], para emular en tiempo real amplificadores y pedales de guitarra eléctrica (*overdrive*, distorsión y compresión). Implementado mediante el *framework* JUCE, empleando el modelo WaveNet de C++ llamado [WaveNetVA](https://github.com/damskaggep/WaveNetVA). Basado en los trabajos [1,2,5]. 

#### Créditos
Desarrollado originalmente como parte de mi [Trabajo Fin de Grado](https://zenodo.org/records/15490785) para la titulación de Ingeniería Informática de la Universidad de La Rioja (España), titulado *Aprendizaje profundo para la emulación en tiempo real de equipamiento de guitarra eléctrica con Raspberry Pi 5*. Basado conceptualmente en los repositorios [WaveNetVA](https://github.com/damskaggep/WaveNetVA) de Damskägg, Eero-Pekka y [SmartGuitarAmp](https://github.com/GuitarML/SmartGuitarAmp), de Keith Bloemer [3]. Agradezco mucho sus contribuciones a la comunidad, gracias a las cuales no solo he aprendido mucho, sino que he podido testear mi proyecto empleando sus plugins [4].

## Funcionamiento
La aplicación cuenta con dos versiones para Windows/x86.
- Versión *standalone* o de escritorio compatible con las interfaces de audio [Focusrite Scarlett SOLO 3rd Gen](https://shop.plastic.es/estudio/interfaces-de-audio/focusrite-interfaces-de-audio/focusrite-scarlett-solo-3rd-gen/). 
- Versión plugin VST3 compatible con cualquier DAW (*Digital Audio Workstation*). Testeada correctamente sobre [Reaper](https://www.reaper.fm/).   

La versión *standalone* para Linux/aarch64 pronto tendrá una *release*.
<p float="left">
  <img src="AmpEmulatorStandalone.png" width="400" />
  <img src="AmpEmulatorPlugin.png" width="400" /> 
</p>

> (Izq.) Interfaz de usuario de la aplicación *standalone*   
> (Der.) Plugin VST3 embebido desde Reaper

## Compilación
El repositorio contiene el código de un proyecto del *framework* [JUCE](https://juce.com/), concretamente de la versión 5.4.2. Se trata de una versión actualmente obsoleta y que no se puede descargar desde los repositorios oficiales, porque fue eliminada, aunque todavía existen *forks* no oficiales. El proyecto tuvo que ser compilado con esta versión debido a las dependencias introducidas por [WaveNetVA](https://github.com/damskaggep/WaveNetVA). **No recomiendo compilarlo manualmente, en nuestro caso fue muy complicado configurar el entorno de desarrollo correctamente**. En caso de querer hacerlo igualmente, a continuación damos algunos *tips* para ello.

> Una vez obtenido JUCE 5.4.2 hay que compilarlo también. Este *framework* se acopla a Visual Studio, desde el cual puede lanzarse y compilar el proyecto. La versión de `gcc` necesaria para compilar todo debe ser necesariamente < 9.
> El proyecto depende de dos librerías externas: [Eigen](https://eigen.tuxfamily.org/index.php?title=Main_Page) y el [SDK de ASIO de Steinberg](https://www.steinberg.net/es/developers/), en las versiones 3.3.7 y 2.3.3 respectivamente. Para que JUCE las detecte, debe crearse una carpeta `./Libraries`.
> Es probable que muchas dependencias estén rotas, debido a la recién instalada versión de JUCE, en cuyo caso no queda otra que arreglarlas manualmente desde JUCE.

#### Windows/x86
Una vez instalado JUCE, abrir el proyecto mediante el fichero `AmpEmulatorPlugin.jucer` y lanzarlo con Visual Studio. Desde el IDE, es tan sencillo como compilar en versión *release* (en caso contrario, no se aplicarán las optimizaciones necesarias y no funcionará en tiempo real). 

#### Linux/aarch64
Crear el MakeFile mediante JUCE. Instalar las siguientes dependencias:
```bash
sudo apt-get install libtiff-dev
sudo apt-get libwebkit2gtk-4.0-dev
```
Ir a la carpeta recién creada `./Builds/LinuxMakefile` y hacer `make`. Es necesario modificar el linkado de las dependencias desde el `Makefile` y poner `make config = Release`. 

## Referencias
[1]	Wright, A. et al.: "Real-Time Guitar Amplifier Emulation with Deep Learning". *Applied Sciences* (2020). (https://doi.org/10.3390/app10030766)   
[2]	Van den Oord, A. et al.: "WaveNet: A Generative Model for Raw Audio". *arXiv* (2016). (https://doi.org/10.48550/arXiv.1609.03499)   
[3]	Bloemer, K.: PedalNetRT, GitHub (https://github.com/GuitarML/PedalNetRT). (2020).   
[4]	Damskägg, E.-P.: WaveNetVA, GitHub (https://github.com/damskaggep/WaveNetVA). (2019).   
[5]	Bloemer, K.: SmartPluginAmp, Github (https://github.com/GuitarML/SmartGuitarAmp). (2020).

Autor: *Javier Jiménez Santana*   
Tutores: *Jose Divasón Mallagaray, Silvano Nájera Canal*
