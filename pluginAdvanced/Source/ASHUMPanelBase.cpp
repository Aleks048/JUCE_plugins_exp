/*
  ==============================================================================

    ASHUMPanelBase.cpp
    Created: 6 Jan 2021 5:06:22pm
    Author:  ashum048

  ==============================================================================
*/

#include "ASHUMPanelBase.h"
ASHUMPanelBase::ASHUMPanelBase(PluginAdvancedAudioProcessor* inProcessor) 
	:mProcessor(inProcessor)
{

}

ASHUMPanelBase::~ASHUMPanelBase() {

}

void ASHUMPanelBase::paint(juce::Graphics& g){
	g.setColour(juce::Colours::white);
	g.fillAll();

	g.setColour(juce::Colours::black);
	g.drawRect(0, 0, getWidth(), getHeight());
}