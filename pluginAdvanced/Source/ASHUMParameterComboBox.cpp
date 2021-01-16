/*
  ==============================================================================

    ASHUMParameterComboBox.cpp
    Created: 13 Jan 2021 12:13:59pm
    Author:  ashum048

  ==============================================================================
*/

#include "ASHUMParameterComboBox.h"

ASHUMParameterComboBox::ASHUMParameterComboBox(juce::AudioProcessorValueTreeState& stateToControl,
	const juce::String& parameterID):
	juce::ComboBox(parameterID)
{
	mAttachment = 
		std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>
		(stateToControl, parameterID, *this);
};
ASHUMParameterComboBox::~ASHUMParameterComboBox() {};