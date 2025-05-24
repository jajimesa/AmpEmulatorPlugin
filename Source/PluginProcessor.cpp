/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


// Constructor (condicionado a directivas de preprocesador)
AmpEmulatorPluginAudioProcessor::AmpEmulatorPluginAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations   // Si la directiva no está definida...
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
      waveNet(1, 1, 1, 1, "linear", { 1 })  // ...construye waveNet
#endif
{
}

// Destructor
AmpEmulatorPluginAudioProcessor::~AmpEmulatorPluginAudioProcessor()
{
}

const String AmpEmulatorPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool AmpEmulatorPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool AmpEmulatorPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool AmpEmulatorPluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double AmpEmulatorPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int AmpEmulatorPluginAudioProcessor::getNumPrograms()
{
    return 1;
}

int AmpEmulatorPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void AmpEmulatorPluginAudioProcessor::setCurrentProgram (int index)
{
}

const String AmpEmulatorPluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void AmpEmulatorPluginAudioProcessor::changeProgramName (int index, const String& newName)
{
}

// Inicializa todo lo necesario antes del play-back
void AmpEmulatorPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    waveNet.prepareToPlay(samplesPerBlock);
}

void AmpEmulatorPluginAudioProcessor::releaseResources()
{
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool AmpEmulatorPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

// Procesa los bloques de audio conforme le llegan las llamadas (callbacks)
void AmpEmulatorPluginAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;

    if (juce::JUCEApplicationBase::isStandaloneApp())
    {
        // Lógica para standalone
        if (selectedInputChannel >= buffer.getNumChannels())
            return;

        AudioBuffer<float> singleChannelBuffer(1, buffer.getNumSamples());
        singleChannelBuffer.copyFrom(0, 0, buffer, selectedInputChannel, 0, buffer.getNumSamples());

        singleChannelBuffer.applyGain(10.0f); // Ganancia inicial para ayudar al modelo
        singleChannelBuffer.applyGain(preGain);

        waveNet.process(singleChannelBuffer.getArrayOfReadPointers(), singleChannelBuffer.getArrayOfWritePointers(), singleChannelBuffer.getNumSamples());

        singleChannelBuffer.applyGain(postGain);

        buffer.copyFrom(selectedInputChannel, 0, singleChannelBuffer, 0, 0, buffer.getNumSamples());

        for (int ch = 0; ch < buffer.getNumChannels(); ++ch)
        {
            if (ch != selectedInputChannel)
                buffer.copyFrom(ch, 0, buffer, selectedInputChannel, 0, buffer.getNumSamples());
        }
    }
    else
    {
        // Lógica para VST3 en DAW
        ScopedNoDenormals noDenormals;

        buffer.applyGain(10.0f); // Ganancia inicial para ayudar al modelo

        buffer.applyGain(preGain);
        waveNet.process(buffer.getArrayOfReadPointers(),
            buffer.getArrayOfWritePointers(),
            buffer.getNumSamples());
        buffer.applyGain(postGain);
        for (int ch = 1; ch < buffer.getNumChannels(); ++ch)
        {
            buffer.copyFrom(ch, 0, buffer, 0, 0, buffer.getNumSamples());
        }
    }
}

bool AmpEmulatorPluginAudioProcessor::hasEditor() const
{
    return true;
}

AudioProcessorEditor* AmpEmulatorPluginAudioProcessor::createEditor()
{
    return new AmpEmulatorPluginAudioProcessorEditor (*this);
}

void AmpEmulatorPluginAudioProcessor::getStateInformation (MemoryBlock& destData)
{
}

void AmpEmulatorPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
}

// Carga el modelo WaveNet contenido en file (.json)
void AmpEmulatorPluginAudioProcessor::loadModel(File file)
{
    this->suspendProcessing(true);  // Desactiva la callback de procesamiento

    WaveNetLoader loader(file);
    int numChannels = loader.numChannels;
    int inputChannels = loader.inputChannels;
    int outputChannels = loader.outputChannels;
    int filterWidth = loader.filterWidth;
    std::vector<int> dilations = loader.dilations;
    std::string activation = loader.activation;
    waveNet.setParams(inputChannels,
                      outputChannels,
                      numChannels,
                      filterWidth, 
                      activation,
                      dilations);
    loader.loadVariables(waveNet);

    this->suspendProcessing(false); // Reactiva la callback de procesamiento
}

void AmpEmulatorPluginAudioProcessor::setPreGain(float dbValue)
{
    preGain = decibelToLinear(dbValue);
}

void AmpEmulatorPluginAudioProcessor::setPostGain(float dbValue)
{
    postGain = decibelToLinear(dbValue);
}

float AmpEmulatorPluginAudioProcessor::decibelToLinear(float dbValue)
{
    return powf(10.0, dbValue / 20.0);  // 10 ^ (dbValue/20)
}

AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AmpEmulatorPluginAudioProcessor();
}

void AmpEmulatorPluginAudioProcessor::setSelectedInputChannel(int channel)
{
    selectedInputChannel = channel;
}

int AmpEmulatorPluginAudioProcessor::getSelectedInputChannel() const
{
    return selectedInputChannel;
}
