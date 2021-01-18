/*
  ==============================================================================

    ASHUMGainPanel.h
    Created: 6 Jan 2021 5:09:22pm
    Author:  ashum048

  ==============================================================================
*/

#pragma once
#include "ASHUMPanelBase.h"
#include "ASHUMParameterSlider.h"

class ASHUMGainPanel: public ASHUMPanelBase {
public:
	ASHUMGainPanel(PluginAdvancedAudioProcessor* inProcessor);
	~ASHUMGainPanel();

	void paint(juce::Graphics& g) override;

	void setParameterID(int iParameterID);
private:
	juce::ScopedPointer<ASHUMParameterSlider> mSlider;
};