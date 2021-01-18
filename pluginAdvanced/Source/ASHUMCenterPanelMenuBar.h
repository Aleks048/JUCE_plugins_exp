/*
  ==============================================================================

    ASHUMCenterPanelMenuBar.h
    Created: 6 Jan 2021 5:08:34pm
    Author:  ashum048

  ==============================================================================
*/

#pragma once
#include "ASHUMPAnelBase.h"
#include "ASHUMParameterComboBox.h"

class ASHUMCenterPanelMenuBar :public ASHUMPanelBase{
public:
	ASHUMCenterPanelMenuBar(PluginAdvancedAudioProcessor* inProcessor);
	~ASHUMCenterPanelMenuBar();

	void addFxTypeListener(ComboBox::Listener* inListener);
	void removeFxTypeListener(ComboBox::Listener* inListener);
private:
	std::unique_ptr<ASHUMParameterComboBox> mFxTypeComboBox;
};