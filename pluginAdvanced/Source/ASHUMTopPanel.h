/*
  ==============================================================================

    ASHUMTopPanel.h
    Created: 6 Jan 2021 5:10:06pm
    Author:  ashum048

  ==============================================================================
*/
#include "ASHUMPanelBase.h"
#pragma once
class ASHUMTopPanel: 
public ASHUMPanelBase
{
public:
	ASHUMTopPanel(PluginAdvancedAudioProcessor* inProcessor);
	~ASHUMTopPanel();

	void paint(juce::Graphics& g) override;
private:

};