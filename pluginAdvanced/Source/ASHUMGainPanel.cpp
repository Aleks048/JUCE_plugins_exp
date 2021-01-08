/*
  ==============================================================================

    ASHUMGainPanel.cpp
    Created: 6 Jan 2021 5:09:22pm
    Author:  ashum048

  ==============================================================================
*/

#include "ASHUMGainPanel.h"
ASHUMGainPanel::ASHUMGainPanel(PluginAdvancedAudioProcessor* inProcessor) :
	ASHUMPanelBase(inProcessor)
{
	setSize(GAIN_PANEL_WIDTH, GAIN_PANEL_HEIGHT);
}
ASHUMGainPanel::~ASHUMGainPanel() {}