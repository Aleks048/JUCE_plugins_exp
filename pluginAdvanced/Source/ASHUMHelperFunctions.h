/*
  ==============================================================================

    ASHUMHelperFunctions.h
    Created: 18 Jan 2021 2:52:25pm
    Author:  ashum048

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
inline void paintComponentLabel(juce::Graphics& g, juce::Component* inComponent) 
{
	const int x = inComponent->getX() - (inComponent->getWidth()*0.25f);
	const int y = inComponent->getY()+inComponent->getHeight();
	const int w = inComponent->getWidth()*1.5f;
	const int h = 20;

	const juce::String label = inComponent->getName();
	const float cornerSize = 3.f;

	g.setColour(juce::Colours::darkgreen);
	g.drawFittedText(label, x, y, w, h, juce::Justification::centred, 1);

}