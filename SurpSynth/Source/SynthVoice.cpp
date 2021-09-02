/*
  ==============================================================================

    SynthVoice.cpp
    Created: 27 Jun 2021 8:16:21pm
    Author:  Hunter Krasa

  ==============================================================================
*/

#include "SynthVoice.h"
#include "PluginProcessor.h"
#include "PluginEditor.h"

bool SynthVoice::canPlaySound (juce::SynthesiserSound* sound) {
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
    
}
void SynthVoice::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) {
    
    
    if (waveInput == 0) {
        sineOsc.setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
    } else if (waveInput == 1) {
        sawOsc.setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
    } else {
        squareOsc.setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
    }

    
//    std::cout << velocity;
    adsrParams.attack = attackInput;
    adsrParams.decay = decayInput;
    adsrParams.sustain = sustainInput;
    adsrParams.release = releaseInput;
    adsr.setParameters(adsrParams);

    gain.setGainLinear(velocity * .95 * (gainVolume/127));
    adsr.noteOn();
}
void SynthVoice::stopNote (float velocity, bool allowTailOff) {
    adsr.noteOff();
    
    
}
void SynthVoice::controllerMoved (int controllerNumber, int newControllerValue) {
        
}
void SynthVoice::pitchWheelMoved (int newPitchWheelValue) {
    
    
}
void SynthVoice::setGain (float g) {
    
    gainVolume = g;
    
}
void SynthVoice::setAttack (float a) {
    
    attackInput = a;
}
void SynthVoice::setDecay (float d) {
    
    decayInput = d;
}
void SynthVoice::setSustain(float s) {
    
    sustainInput = s / 100;
}
void SynthVoice::setRelease(float r) {
    
    releaseInput = r;
}
void SynthVoice::setWave(int w) {
    waveInput = w;
}
void SynthVoice::prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels) {
        adsr.setSampleRate(sampleRate);
        juce::dsp::ProcessSpec spec;
        spec.maximumBlockSize = samplesPerBlock;
        spec.sampleRate = sampleRate;
        spec.numChannels = outputChannels;

        sineOsc.prepare(spec);
        sawOsc.prepare(spec);
        squareOsc.prepare(spec);
        gain.prepare(spec);
        gain.setGainLinear(.1f);
        isPrepared = true;
        adsrParams.attack = attackInput;
        adsr.setParameters(adsrParams);
}
void SynthVoice::renderNextBlock (juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples) {
    
    jassert(isPrepared);
    
    juce::dsp::AudioBlock<float> audioBlock {outputBuffer};
    
    if (waveInput == 0) {
        sineOsc.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    } else if (waveInput == 1) {
        sawOsc.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    } else {
        squareOsc.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    }
    
    gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    
    adsr.applyEnvelopeToBuffer(outputBuffer, startSample, numSamples);
    
}

