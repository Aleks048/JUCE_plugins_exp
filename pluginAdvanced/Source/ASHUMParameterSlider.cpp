/*
  ==============================================================================

    ASHUMParameterSlider.cpp
    Created: 13 Jan 2021 12:13:32pm
    Author:  ashum048

  ==============================================================================
*/

#include "ASHUMParameterSlider.h"
ASHUMParameterSlider::ASHUMParameterSlider(juce::AudioProcessorValueTreeState& stateToControl,
	const juce::String& parameterID) 
	: juce::Slider(parameterID)
{
	setSliderStyle(SliderStyle::RotaryHorizontalVerticalDrag);
	setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 0, 0);

	setRange(0.f, 1.f,.001f);

	mAttachment = 
		std::make_unique< juce::AudioProcessorValueTreeState::SliderAttachment>
		(stateToControl,parameterID,*this);
}
ASHUMParameterSlider::~ASHUMParameterSlider() 
{

}