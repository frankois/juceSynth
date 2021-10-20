/*
  ==============================================================================

    SynthVoice.cpp
    Created: 30 Sep 2021 4:30:39pm
    Author:  Francois Decourcelle

  ==============================================================================
*/

#include "SynthVoice.h"

bool SynthVoice::canPlaySound (juce::SynthesiserSound* sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr; // makes sure that the sound is a proper SynthesiserSound
}

void SynthVoice::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition)
{
    osc.setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
    adsr.noteOn();
}

void SynthVoice::stopNote (float velocity, bool allowTailOf)
{
    adsr.noteOff();
    
    if (!allowTailOf || !adsr.isActive())
    {
        clearCurrentNote();
    }
}

void SynthVoice::controllerMoved (int controllerNumber, int newControllerValue)
{
    
}

void SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{
    
}

void SynthVoice::prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels)
{
    adsr.setSampleRate(sampleRate);
    
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = outputChannels;
    
    osc.prepare(spec);
    
    gain.prepare(spec);
    gain.setGainLinear(0.01f);
    
    adsrParams.attack = 0.8f;
    adsrParams.decay = 0.08f;
    adsrParams.sustain = 1.0f;
    adsrParams.release = 1.5f;
    
    adsr.setParameters(adsrParams);
    
    isPrepared = true;
}

void SynthVoice::renderNextBlock (juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
{
    jassert(isPrepared);
    
    if (! isVoiceActive())
        return;
    
    synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, false);
    synthBuffer.clear();
    
    juce::dsp::AudioBlock<float> audioBlock {synthBuffer};
    osc.process(juce::dsp::ProcessContextReplacing<float> (audioBlock));
    gain.process(juce::dsp::ProcessContextReplacing<float> (audioBlock));
    
    adsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());
    // audioBlock is the outputBuffer (now th synthBuffer)
    // outputBuffer contains all audio data
    
    if (startSample != 0)
        jassertfalse;
    
    for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
    {
        outputBuffer.addFrom(channel, startSample, synthBuffer, channel, 0, numSamples);
        
        if (!adsr.isActive())
            clearCurrentNote();
    }
    
//    osc.setFrequency(mFreq);
//
//    for (int channel = 0; channel < totalNumInputChannels; ++channel)
//    {
//        auto* channelData = buffer.getWritePointer (channel);
//
//        for (int sample=0; sample < buffer.getNumSamples(); ++sample)
//        {
//            channelData[sample] = channelData[sample] * juce::Decibels::decibelsToGain(mGain);
//        }
//    }
}
