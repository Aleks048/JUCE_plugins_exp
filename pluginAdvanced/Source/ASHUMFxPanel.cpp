/*
  ==============================================================================

    ASHUMFxPanel.cpp
    Created: 6 Jan 2021 5:08:57pm
    Author:  ashum048

  ==============================================================================
*/

#include "ASHUMFxPanel.h"
ASHUMFxPanel::ASHUMFxPanel(PluginAdvancedAudioProcessor* inProcessor):
	ASHUMPanelBase(inProcessor),mStyle(kASHUMFxPanelStyle_Delay) {

	setSize(FX_PANEL_WIDTH, FX_PANEL_HEIGHT);
}

ASHUMFxPanel::~ASHUMFxPanel(){

}

void ASHUMFxPanel::paint(Graphics& g){
	ASHUMPanelBase::paint(g);

	switch (mStyle) {
		case kASHUMFxPanelStyle_Delay: {
			g.drawFittedText("DEALY", 0, 0, getWidth(), getHeight(),juce::Justification::centred, 1);
		}break;
		case kASHUMFxPanelStyle_Chorus: {
			g.drawFittedText("CHORUS", 0, 0, getWidth(), getHeight(), juce::Justification::centred, 1);
		}break;
		default:
		case kASHUMFxPanelStyle_TotalNUmStyles: {
			jassertfalse; 
			g.drawFittedText("noooooo", 0, 0, getWidth(), getHeight(), juce::Justification::centred, 1);
		}break;
	}
}

void ASHUMFxPanel::setFxPanelStyle(ASHUMFxPanelStyle inStyle) {
	mStyle = inStyle;
}