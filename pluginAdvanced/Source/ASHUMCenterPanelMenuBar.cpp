/*
  ==============================================================================

    ASHUMCenterPanelMenuBar.cpp
    Created: 6 Jan 2021 5:08:34pm
    Author:  ashum048

  ==============================================================================
*/

#include "ASHUMCenterPanelMenuBar.h"
ASHUMCenterPanelMenuBar::ASHUMCenterPanelMenuBar(PluginAdvancedAudioProcessor* inProcessor) :
	ASHUMPanelBase(inProcessor)
{
	setSize(CENTER_PANEL_MENU_BAR_WIDTH, CENTER_PANEL_MENU_BAR_HEIGHT);
}
ASHUMCenterPanelMenuBar::~ASHUMCenterPanelMenuBar() {}