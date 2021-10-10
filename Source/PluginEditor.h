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
class JuceSynthAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    JuceSynthAudioProcessorEditor (JuceSynthAudioProcessor&);
    ~JuceSynthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider attackSlider;
    juce::Slider decaySlider;
    juce::Slider sustainSlider;
    juce::Slider releaseSlider;
    juce::ComboBox oscSelector;

    using SliderAttachement = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    std::unique_ptr<SliderAttachement> attackAttachment;
    std::unique_ptr<SliderAttachement> decayAttachment;
    std::unique_ptr<SliderAttachement> sustainAttachment;
    std::unique_ptr<SliderAttachement> releaseAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscSelectorAttachment;
    
    JuceSynthAudioProcessor& audioProcessor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceSynthAudioProcessorEditor)
};
