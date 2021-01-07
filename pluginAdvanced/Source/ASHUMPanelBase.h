/*
  ==============================================================================

    ASHUMPanelBase.h
    Created: 6 Jan 2021 5:06:22pm
    Author:  ashum048

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "PluginProcessor.h"
#include "ASHUMInterfaceDefines.h"
class ASHUMPanelBase: public juce::Component {
public:
	ASHUMPanelBase(PluginAdvancedAudioProcessor* inProcessor);
	~ASHUMPanelBase();

	void paint(juce::Graphics& g) override;
protected:
	PluginAdvancedAudioProcessor* mProcessor;
};