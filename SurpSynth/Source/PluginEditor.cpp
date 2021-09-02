/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SurpSynthAudioProcessorEditor::SurpSynthAudioProcessorEditor (SurpSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (300, 300);
    gainSlider.setSliderStyle(juce::Slider::LinearBarVertical);
    gainSlider.setRange (0.0, 127.0, 1.0);
    gainSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    gainSlider.setPopupDisplayEnabled (true, false, this);
    gainSlider.setTextValueSuffix (" Volume");
    gainSlider.setValue(60);
    addAndMakeVisible(&gainSlider);
    gainSlider.addListener(this);
    
    gainLabel.setText ("Volume", juce::dontSendNotification);
    gainLabel.attachToComponent (&gainSlider, false);
    
    attackSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    attackSlider.setRange (0.0, 5, .1);
    attackSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    attackSlider.setPopupDisplayEnabled (true, false, this);
    attackSlider.setTextValueSuffix (" Seconds");
    attackSlider.setValue(.1);
    addAndMakeVisible(&attackSlider);
    attackSlider.addListener(this);
    
    attackLabel.setText ("  Attack", juce::dontSendNotification);
    attackLabel.attachToComponent (&attackSlider, false);
    
    decaySlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    decaySlider.setRange (0.0, 5, .1);
    decaySlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    decaySlider.setPopupDisplayEnabled (true, false, this);
    decaySlider.setTextValueSuffix (" Seconds");
    decaySlider.setValue(1);
    addAndMakeVisible(&decaySlider);
    decaySlider.addListener(this);
    
    decayLabel.setText ("  Decay", juce::dontSendNotification);
    decayLabel.attachToComponent (&decaySlider, false);
    
    sustainSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    sustainSlider.setRange (0.0, 100, 1);
    sustainSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    sustainSlider.setPopupDisplayEnabled (true, false, this);
    sustainSlider.setTextValueSuffix ("%");
    sustainSlider.setValue(70);
    addAndMakeVisible(&sustainSlider);
    sustainSlider.addListener(this);
    
    sustainLabel.setText ("  Sustain", juce::dontSendNotification);
    sustainLabel.attachToComponent (&sustainSlider, false);
    
    releaseSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    releaseSlider.setRange (0.0, 5, .1);
    releaseSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    releaseSlider.setPopupDisplayEnabled (true, false, this);
    releaseSlider.setTextValueSuffix (" Seconds");
    releaseSlider.setValue(1);
    addAndMakeVisible(&releaseSlider);
    releaseSlider.addListener(this);
    
    releaseLabel.setText ("  Release", juce::dontSendNotification);
    releaseLabel.attachToComponent (&releaseSlider, false);
    
    sineButton.setButtonText("Sine");
    sineButton.setToggleState(true, juce::dontSendNotification);
    sineButton.setClickingTogglesState(true);
    sineButton.setRadioGroupId(1);
    addAndMakeVisible(&sineButton);
    sineButton.addListener(this);
    
    sawButton.setButtonText("Saw");
    sawButton.setClickingTogglesState(true);
    sawButton.setRadioGroupId(1);
    addAndMakeVisible(&sawButton);
    sawButton.addListener(this);
    
    squareButton.setButtonText("Square");
    squareButton.setClickingTogglesState(true);
    squareButton.setRadioGroupId(1);
    addAndMakeVisible(&squareButton);
    squareButton.addListener(this);
}

SurpSynthAudioProcessorEditor::~SurpSynthAudioProcessorEditor()
{
}

//==============================================================================
void SurpSynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (20.0f);
    g.drawFittedText ("SURP Synth", 100, -20, 100, 100, juce::Justification::centred, 1);
    gainSlider.setBounds (30, 80, 60, getHeight() - 100);
    attackSlider.setBounds(120, 80, 60, 60);
    decaySlider.setBounds (200, 80, 60, 60);
    sustainSlider.setBounds (120, 160, 60, 60);
    releaseSlider.setBounds (200, 160, 60, 60);
    sineButton.setBounds(110, 225, 55, 55);
    sawButton.setBounds(165, 225, 55, 55);
    squareButton.setBounds(220, 225, 55, 55);

}

void SurpSynthAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
