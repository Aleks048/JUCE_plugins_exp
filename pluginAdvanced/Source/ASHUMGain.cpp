/*
  ==============================================================================

    ASHUMGain.cpp
    Created: 24 Dec 2020 3:48:01pm
    Author:  ashum048

  ==============================================================================
*/

#include "ASHUMGain.h"
#include "JuceHeader.h"
ASHUMGain::ASHUMGain() 
{

};
ASHUMGain::~ASHUMGain() 
{

};

void ASHUMGain::process(float* inAudio,
						float inGain,
						float* outAudio,
						int inNumSamplesToRender) 
{
	float gainMapped = juce::jmap(inGain, 0.f, 1.f, -24.0f , 24.0f);
	gainMapped = juce::Decibels::decibelsToGain(gainMapped, -24.f);

	for (int i = 0; i < inNumSamplesToRender; i++) {
		outAudio[i] = inAudio[i] * gainMapped;
	}
};
