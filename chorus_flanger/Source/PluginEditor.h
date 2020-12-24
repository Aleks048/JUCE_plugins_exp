/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once
using namespace juce;
#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class Chorus_flangerAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    Chorus_flangerAudioProcessorEditor (Chorus_flangerAudioProcessor&);
    ~Chorus_flangerAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
	Slider mDryWetSlider;
	Slider mDepthSlider;
	Slider mRateSlider;
	Slider mPhaseOffsetSlider;
	Slider mFeedbackSlider;

	ComboBox mTypeBox;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Chorus_flangerAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Chorus_flangerAudioProcessorEditor)
};
