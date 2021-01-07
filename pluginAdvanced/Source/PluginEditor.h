/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "ASHUMMainPanel.h"
//==============================================================================
/**
*/
class PluginAdvancedAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    PluginAdvancedAudioProcessorEditor (PluginAdvancedAudioProcessor&);
    ~PluginAdvancedAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PluginAdvancedAudioProcessor& audioProcessor;

	std::unique_ptr <ASHUMMainPanel> mMainPanel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginAdvancedAudioProcessorEditor)
};
