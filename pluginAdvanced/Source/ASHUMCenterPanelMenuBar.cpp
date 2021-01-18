/*
  ==============================================================================

    ASHUMCenterPanelMenuBar.cpp
    Created: 6 Jan 2021 5:08:34pm
    Author:  ashum048

  ==============================================================================
*/

#include "ASHUMCenterPanelMenuBar.h"
#include "ASHUMParameters.h"

ASHUMCenterPanelMenuBar::ASHUMCenterPanelMenuBar(PluginAdvancedAudioProcessor* inProcessor) :
	ASHUMPanelBase(inProcessor)
{
	setSize(CENTER_PANEL_MENU_BAR_WIDTH, CENTER_PANEL_MENU_BAR_HEIGHT);

	const int width = 85;

	mFxTypeComboBox = 
		std::make_unique <ASHUMParameterComboBox>(mProcessor->parameters, ASHUMParameterID[kParameter_DelayType]);
	mFxTypeComboBox->setBounds(getWidth() - width,0,width, getHeight());
	mFxTypeComboBox->addItem("Delay", 1);
	mFxTypeComboBox->addItem("Chorus", 2);
	mFxTypeComboBox->setSelectedItemIndex((int)mProcessor->getParameter(kParameter_DelayType),dontSendNotification);
	addAndMakeVisible(*mFxTypeComboBox);
}
ASHUMCenterPanelMenuBar::~ASHUMCenterPanelMenuBar() {}


void ASHUMCenterPanelMenuBar::addFxTypeListener(ComboBox::Listener* inListener) {
	mFxTypeComboBox->addListener(inListener);
}
void ASHUMCenterPanelMenuBar::removeFxTypeListener(ComboBox::Listener* inListener) {
	mFxTypeComboBox->removeListener(inListener);
}