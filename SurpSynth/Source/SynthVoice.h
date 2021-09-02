/*
  ==============================================================================

    SynthVoice.h
    Created: 27 Jun 2021 8:16:21pm
    Author:  Hunter Krasa

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"


class SynthVoice : public juce::SynthesiserVoice
{
public:
    bool canPlaySound (juce::SynthesiserSound* sound) override;
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
    void stopNote (float velocity, bool allowTailOff) override;
    void controllerMoved (int controllerNumber, int newControllerValue) override;
    void pitchWheelMoved (int newPitchWheelValue) override;
    void prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels);
    void renderNextBlock (juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override;
    void setGain (float g);
    void setAttack (float a);
    void setDecay (float d);
    void setSustain (float s);
    void setRelease (float r);
    void setWave (int w);
    float gainVolume;
    float attackInput;
    float decayInput;
    float sustainInput;
    float releaseInput;
    float waveInput;
    
private:
    
    juce::ADSR adsr;
    juce::ADSR::Parameters adsrParams;
    juce::dsp::Oscillator<float> sineOsc { [](float x) { return std::sin(x); }};
    juce::dsp::Oscillator<float> sawOsc { [](float x) { return x / juce::MathConstants<float>::pi; }};
    juce::dsp::Oscillator<float> squareOsc { [](float x) { return x < 0.0f ? -1.0f : 1.0f; }};
    juce::dsp::Gain<float> gain;
    bool isPrepared {false};
    
    // return std::sin(x);                  // sine wave
    // return x / MathConstants<float>::pi  // saw wave
    // return x < 0.0f ? -1.0f : 1.0f       //square wave

    
    
};
