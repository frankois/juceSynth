/*
  ==============================================================================

    SynthVoice.h
    Created: 30 Sep 2021 4:30:39pm
    Author:  Francois Decourcelle

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:
    bool canPlaySound (juce::SynthesiserSound* sound) override;
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition) override;
    void stopNote (float velocity, bool allowTailOf) override;
    void controllerMoved (int controllerNumber, int newControllerValue) override;
    void pitchWheelMoved (int newPitchWheelValue) override;
    void prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels);
    void renderNextBlock (juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override;
    
private:
    juce::ADSR adsr;
    juce::ADSR::Parameters adsrParams;
    juce::AudioBuffer<float> synthBuffer;
    
    //    juce::dsp::Oscillator<float> osc { [](float x) {return std::sin (x);}};
    //    juce::dsp::Oscillator<float> osc { [](float x) {return x/juce::MathConstants<float>::pi; }};
    juce::dsp::Oscillator<float> osc { [](float x) {return x<0.0f ? -1.0f : 1.0f;}, 200};
    
    // Different kind of waveforms:
    // return std::sin (x); // Sine
    // return x/juce::MathConstants<float>::pi; // Saw
    // return x<0.0f ? -1.0f : 1.0f; // Square
    
    juce::dsp::Gain<float> gain;
    
    juce::Slider frequencySlider;
    juce::Label frequencyLabel;
    
    bool isPrepared {false};
};
