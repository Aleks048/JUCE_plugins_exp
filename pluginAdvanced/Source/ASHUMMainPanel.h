/*
  ==============================================================================

    ASHUMMainPanel.h
    Created: 6 Jan 2021 5:07:05pm
    Author:  ashum048

  ==============================================================================
*/

#pragma once
#include "ASHUMPanelBase.h"
#include "ASHUMTopPanel.h"
class ASHUMMainPanel 
	: public ASHUMPanelBase
{
public:
	ASHUMMainPanel(PluginAdvancedAudioProcessor* inProcessor);
	~ASHUMMainPanel();
private:
	std::unique_ptr<ASHUMTopPanel> mTopPanel;
};