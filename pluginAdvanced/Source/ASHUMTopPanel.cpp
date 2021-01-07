/*
  ==============================================================================

    ASHUMTopPanel.cpp
    Created: 6 Jan 2021 5:10:06pm
    Author:  ashum048

  ==============================================================================
*/

#include "ASHUMTopPanel.h"

ASHUMTopPanel::ASHUMTopPanel(PluginAdvancedAudioProcessor* inProcessor):
	ASHUMPanelBase(inProcessor)
{
	setSize(TOP_PANEL_WIDTH, TOP_PANEL_HEIGHT);
}
ASHUMTopPanel::~ASHUMTopPanel() {}

void ASHUMTopPanel::paint(juce::Graphics& g) {
	ASHUMPanelBase::paint(g);
	g.drawFittedText("My audio plugin", 0, 0, getWidth()-10, getHeight(), juce::Justification::centredRight, 1);
}