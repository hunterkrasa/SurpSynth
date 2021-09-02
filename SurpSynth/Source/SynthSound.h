/*
  ==============================================================================

    SynthSound.h
    Created: 27 Jun 2021 8:16:35pm
    Author:  Hunter Krasa

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound
{
public:
    bool appliesToNote (int midiNoteNumber) override { return true; }
    bool appliesToChannel (int midiChannel) override { return true; }

    
    
};
