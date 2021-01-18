/*
  ==============================================================================

    ASHUMCenterPanel.cpp
    Created: 6 Jan 2021 5:07:58pm
    Author:  ashum048

  ==============================================================================
*/

#include "ASHUMCenterPanel.h"
ASHUMCenterPanel::ASHUMCenterPanel(PluginAdvancedAudioProcessor* inProcessor) :
	ASHUMPanelBase(inProcessor) {
	setSize(CENTER_PANEL_WIDTH, CENTER_PANEL_HEIGHT);
	mMenuBar = std::make_unique<ASHUMCenterPanelMenuBar>(inProcessor);
	mMenuBar->setTopLeftPosition(0, 0);
	addAndMakeVisible(*mMenuBar);

	mFxPanel = new ASHUMFxPanel(inProcessor);
	mFxPanel->setTopLeftPosition(0, CENTER_PANEL_MENU_BAR_HEIGHT);
	addAndMakeVisible(*mFxPanel);

	mMenuBar->addFxTypeListener(mFxPanel);
}
ASHUMCenterPanel::~ASHUMCenterPanel() {
	mMenuBar->removeFxTypeListener(mFxPanel);
}