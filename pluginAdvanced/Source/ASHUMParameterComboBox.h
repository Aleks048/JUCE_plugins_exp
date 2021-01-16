/*
  ==============================================================================

    ASHUMParameterComboBox.h
    Created: 13 Jan 2021 12:13:59pm
    Author:  ashum048

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"

class ASHUMParameterComboBox :
	public juce::ComboBox {
public:
	ASHUMParameterComboBox(juce::AudioProcessorValueTreeState& stateToControl,
		const juce::String& parameterID);
	~ASHUMParameterComboBox();

private:
	std::unique_ptr< juce::AudioProcessorValueTreeState::ComboBoxAttachment> mAttachment;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ASHUMParameterComboBox);
};