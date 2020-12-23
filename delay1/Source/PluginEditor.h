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
class Delay1AudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    Delay1AudioProcessorEditor (Delay1AudioProcessor&);
    ~Delay1AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
	juce::Slider mDryWetSlider;
	juce::Slider mFeedbackSlider;
	juce::Slider mDelayTimeSlider;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Delay1AudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Delay1AudioProcessorEditor)
};
