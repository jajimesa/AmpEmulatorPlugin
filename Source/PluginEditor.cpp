/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

// Inicialización de los atributos de clase del editor
String AmpEmulatorPluginAudioProcessorEditor::modelName = String();

// Constructor del editor
AmpEmulatorPluginAudioProcessorEditor::AmpEmulatorPluginAudioProcessorEditor (AmpEmulatorPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Botón de cargar modelo
    addAndMakeVisible(btLoad);
    if (AmpEmulatorPluginAudioProcessorEditor::modelName.isEmpty())
    {
        btLoad.setButtonText("LOAD MODEL");
    }
    else
    {
        btLoad.setButtonText(this->modelName);
    }
    btLoad.addListener(this);

    // Potenciómetro de pre-ganancia y post-ganancia
    addAndMakeVisible(potPreGain);
    potPreGain.addListener(this);
    potPreGain.setRange(-24.0, 24.0);  // rango normalizado
    potPreGain.setValue(0.0);       // comienza en medio
    potPreGain.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    potPreGain.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 20);
    potPreGain.setNumDecimalPlacesToDisplay(1);

    addAndMakeVisible(potPostGain);
    potPostGain.addListener(this);
    potPostGain.setRange(-24.0, 24.0);
    potPostGain.setValue(0.0);
    potPostGain.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    potPostGain.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 20);
    potPostGain.setNumDecimalPlacesToDisplay(1);
    
    // Etiquetas de los potenciómetros
    addAndMakeVisible(lbPreGain);
    lbPreGain.setText("Pre Gain (dB)", juce::NotificationType::dontSendNotification);
    lbPreGain.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(lbPostGain);
    lbPostGain.setText("Post Gain (dB)", juce::NotificationType::dontSendNotification);
    lbPostGain.setJustificationType(juce::Justification::centred);

    // Tamaño del la ventana del editor
    setSize (400, 300);
}

// Destructor
AmpEmulatorPluginAudioProcessorEditor::~AmpEmulatorPluginAudioProcessorEditor()
{
}

// Pinta la interfaz
void AmpEmulatorPluginAudioProcessorEditor::paint (Graphics& g)
{
    // Fondo metálico
    ColourGradient gradient(Colours::grey, 0, 0, Colours::black, 0, getHeight(), false);
    g.setGradientFill(gradient);
    g.fillAll();
}

// Coloca los elementos en la interfaz
void AmpEmulatorPluginAudioProcessorEditor::resized()
{
    int btWidth = floor(this->getWidth() * 0.8);
    btLoad.setBounds((this->getWidth() - btWidth)/2, 40, btWidth, 20);

    int potWidth = 150;
    int potHeight = 150;
    potPreGain.setBounds(40, this->getHeight() / 2 - potHeight / 2, potWidth, potHeight);
    potPostGain.setBounds(this->getWidth() - 40 - potWidth, this->getHeight() / 2 - potHeight / 2, potWidth, potHeight);

    int labelWidth = 100;
    int labelHeight = 20;
    lbPreGain.setBounds(65, this->getHeight() / 2 + potHeight / 2, labelWidth, labelHeight);
    lbPostGain.setBounds(this->getWidth() - 65 - labelWidth, this->getHeight() / 2 + potHeight / 2, labelWidth, labelHeight);
}

// Captura el evento de click de todos los botones
void AmpEmulatorPluginAudioProcessorEditor::buttonClicked(juce::Button* button)
{
    if (button == &btLoad) btLoadClicked();
}

// Maneja el evento de click del botón btLoad
void AmpEmulatorPluginAudioProcessorEditor::btLoadClicked()
{
    FileChooser chooser("Load a trained WaveNet model...", {}, "*.json");
    if (chooser.browseForFileToOpen())
    {
        File file = chooser.getResult();
        processor.loadModel(file);

        AmpEmulatorPluginAudioProcessorEditor::modelName = file.getFileName();
        btLoad.setButtonText(modelName);
    }
}

// Captura y maneja el evento de cambio de valor de los potenciómetros
void AmpEmulatorPluginAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    if (slider == &potPreGain)
        processor.setPreGain(slider->getValue());
    else if (slider == &potPostGain)
        processor.setPostGain(slider->getValue());
}