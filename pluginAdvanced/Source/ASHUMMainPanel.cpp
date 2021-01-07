/*
  ==============================================================================

    ASHUMMainPanel.cpp
    Created: 6 Jan 2021 5:07:05pm
    Author:  ashum048

  ==============================================================================
*/

#include "ASHUMMainPanel.h"
ASHUMMainPanel::ASHUMMainPanel(PluginAdvancedAudioProcessor* inProcessor) 
	:ASHUMPanelBase(inProcessor)
{
	setSize(MAIN_PANEL_WIDTH, MAIN_PANEL_HEIGHT);
	mTopPanel = std::make_unique<ASHUMTopPanel>(inProcessor);
	mTopPanel->setTopLeftPosition(0, 0);
	addAndMakeVisible(*mTopPanel);
}
ASHUMMainPanel::~ASHUMMainPanel() {

}