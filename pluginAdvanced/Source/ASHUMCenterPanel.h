/*
  ==============================================================================

    ASHUMCenterPanel.h
    Created: 6 Jan 2021 5:07:58pm
    Author:  ashum048

  ==============================================================================
*/

#pragma once
#include "ASHUMPanelBase.h"
#include "ASHUMCenterPanelMenuBar.h"
#include "ASHUMFxPanel.h"

class ASHUMCenterPanel :public ASHUMPanelBase{
public:
	ASHUMCenterPanel(PluginAdvancedAudioProcessor* inProcessor);
	~ASHUMCenterPanel();
private:
	std::unique_ptr<ASHUMCenterPanelMenuBar> mMenuBar;
	std::unique_ptr<ASHUMFxPanel> mFxPanel;
};