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
class AudioPl1AudioProcessorEditor  : public juce::AudioProcessorEditor
									//  public juce::Slider::Listener
{
public:
    AudioPl1AudioProcessorEditor (AudioPl1AudioProcessor&);
    ~AudioPl1AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

	//void sliderValueChanged(juce::Slider* slider);

private:
	juce::Slider mGainControlSlider;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    AudioPl1AudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPl1AudioProcessorEditor)
};
