/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


class AmpEmulatorPluginAudioProcessorEditor  : public AudioProcessorEditor,
                                               private Button::Listener,    // Para asignar al editor como listener
                                               private Slider::Listener     // de sus propios botones y sliders
{
public:
    AmpEmulatorPluginAudioProcessorEditor (AmpEmulatorPluginAudioProcessor&);
    ~AmpEmulatorPluginAudioProcessorEditor();

    void paint (Graphics&) override;
    void resized() override;

private:
    /* Referencia al procesador de audio */

    AmpEmulatorPluginAudioProcessor& processor;
    
    /* Elementos de la interfaz */

    TextButton btLoad;      // Botón para seleccionar el .json con el modelo
    
    Slider potPreGain;      // Potenciómetro para la ganancia de entrada
    Slider potPostGain;     // ...                           ... salida
    
    Label lbPreGain;        // Etiqueta para la ganancia de entrada
    Label lbPostGain;       // ...                      ... salida

    static String modelName;    // El nombre del modelo al principio es una cadena vacía

    /* Métodos override de la herencia de listener */
    virtual void buttonClicked(Button* button) override;
    virtual void sliderValueChanged(Slider* slider) override;
    void btLoadClicked();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AmpEmulatorPluginAudioProcessorEditor)
};
