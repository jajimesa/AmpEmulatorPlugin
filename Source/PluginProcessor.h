/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "WaveNet.h"
#include "WaveNetLoader.h"


class AmpEmulatorPluginAudioProcessor  : public AudioProcessor
{
public:
    AmpEmulatorPluginAudioProcessor();
    ~AmpEmulatorPluginAudioProcessor();

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    /* Métodos propios */
    void loadModel(File file);
    void setPreGain(float dbValue);
    void setPostGain(float dbValue);
    float decibelToLinear(float dbValue);

    void setSelectedInputChannel(int channel);
    int getSelectedInputChannel() const;

private:
    WaveNet waveNet;        // Modelo WaveNet encargado de la inferencia en tiempor real

    /* Valores iniciales de los potenciómetros */
    float preGain = 1.0;    
    float postGain = 1.0;

    int selectedInputChannel = 1;   // Para seleccionar el input 2 de mi Analogue Input 1 + 2

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AmpEmulatorPluginAudioProcessor)
};
