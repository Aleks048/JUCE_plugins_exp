/*
  ==============================================================================

    ASHUMMainPanel.cpp
    Created: 6 Jan 2021 5:07:05pm
    Author:  ashum048

  ==============================================================================
*/

#include "ASHUMMainPanel.h"
#include "ASHUMParameters.h"

ASHUMMainPanel::ASHUMMainPanel(PluginAdvancedAudioProcessor* inProcessor) 
	:ASHUMPanelBase(inProcessor)
{
	setSize(MAIN_PANEL_WIDTH, MAIN_PANEL_HEIGHT);
	mTopPanel = std::make_unique<ASHUMTopPanel>(inProcessor);
	mTopPanel->setTopLeftPosition(0, 0);
	addAndMakeVisible(*mTopPanel);

	mInputGain = std::make_unique<ASHUMGainPanel>(inProcessor);
	mInputGain->setTopLeftPosition(0, TOP_PANEL_HEIGHT);
	mInputGain->setParameterID(kParameter_InputGain);
	addAndMakeVisible(*mInputGain);

	mOutputGain = std::make_unique<ASHUMGainPanel>(inProcessor);
	mOutputGain->setTopLeftPosition(MAIN_PANEL_WIDTH-GAIN_PANEL_WIDTH, TOP_PANEL_HEIGHT);
	mOutputGain->setParameterID(kParameter_OutputGain);
	addAndMakeVisible(*mOutputGain);

	mCenterPanel = std::make_unique<ASHUMCenterPanel>(inProcessor);
	mCenterPanel->setTopLeftPosition(GAIN_PANEL_WIDTH, TOP_PANEL_HEIGHT);
	addAndMakeVisible(*mCenterPanel);
}
ASHUMMainPanel::~ASHUMMainPanel() {

}