/*
  ==============================================================================

    SynthSound.h
    Created: 30 Sep 2021 4:30:57pm
    Author:  Francois Decourcelle

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class SynthSound: public juce::SynthesiserSound
{
public:
    bool appliesToNote (int midiNoteNumber) override { return true; }
    bool appliesToChannel (int midiChannel) override { return true; }
};
