/*
  ==============================================================================

    ASHUMParameterSlider.h
    Created: 13 Jan 2021 12:13:32pm
    Author:  ashum048

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class ASHUMParameterSlider :
	public juce::Slider
{
public:
	ASHUMParameterSlider(juce::AudioProcessorValueTreeState& stateToControl,
						const juce::String& parameterID);
	~ASHUMParameterSlider();
private:
	std::unique_ptr< juce::AudioProcessorValueTreeState::SliderAttachment> mAttachment;
	
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ASHUMParameterSlider);
};