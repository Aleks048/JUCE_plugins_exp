/*
  ==============================================================================

    ASHUMFxPanel.h
    Created: 6 Jan 2021 5:08:57pm
    Author:  ashum048

  ==============================================================================
*/

#pragma once
#include "ASHUMPanelBase.h"

enum ASHUMFxPanelStyle {
	kASHUMFxPanelStyle_Delay,
	kASHUMFxPanelStyle_Chorus,
	kASHUMFxPanelStyle_TotalNUmStyles,

};

class ASHUMFxPanel :public ASHUMPanelBase {
public:
	ASHUMFxPanel(PluginAdvancedAudioProcessor* inProcessor);
	~ASHUMFxPanel();

	void paint(Graphics& g) override;

	void setFxPanelStyle(ASHUMFxPanelStyle inStyle);
private:
	ASHUMFxPanelStyle mStyle;
};