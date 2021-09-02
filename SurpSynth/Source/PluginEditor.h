/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class SurpSynthAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                       public juce::Slider::Listener,
                                       public juce::Button::Listener
{
public:
    SurpSynthAudioProcessorEditor (SurpSynthAudioProcessor&);
    ~SurpSynthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    juce::Slider gainSlider;
    juce::Label gainLabel;
    juce::Slider attackSlider;
    juce::Label attackLabel;
    juce::Slider decaySlider;
    juce::Label decayLabel;
    juce::Slider sustainSlider;
    juce::Label sustainLabel;
    juce::Slider releaseSlider;
    juce::Label releaseLabel;
    juce::TextButton sineButton;
    juce::TextButton sawButton;
    juce::TextButton squareButton;
    
    void sliderValueChanged (juce::Slider* slider) override {
        audioProcessor.gainValue = gainSlider.getValue();
        std::cout << audioProcessor.gainValue;
        
        audioProcessor.attackValue = attackSlider.getValue();
        audioProcessor.sustainValue = sustainSlider.getValue();
        audioProcessor.decayValue = decaySlider.getValue();
        audioProcessor.releaseValue = releaseSlider.getValue();
    }
    
    void buttonClicked(juce::Button* button) override {
        if (sineButton.getToggleState() == true) {
            audioProcessor.waveNumber = 0;
        } else if (sawButton.getToggleState() == true) {
            audioProcessor.waveNumber = 1;
        } else {
            audioProcessor.waveNumber = 2;
        }
        
    }
    

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SurpSynthAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SurpSynthAudioProcessorEditor)
};
