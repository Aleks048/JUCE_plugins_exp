/*
  ==============================================================================

    ASHUMGainPanel.cpp
    Created: 6 Jan 2021 5:09:22pm
    Author:  ashum048

  ==============================================================================
*/

#include "ASHUMGainPanel.h"
#include "ASHUMParameters.h"

ASHUMGainPanel::ASHUMGainPanel(PluginAdvancedAudioProcessor* inProcessor) :
	ASHUMPanelBase(inProcessor)
{
	setSize(GAIN_PANEL_WIDTH, GAIN_PANEL_HEIGHT);
}
ASHUMGainPanel::~ASHUMGainPanel() {}

void ASHUMGainPanel::setParameterID(int inParameterID) {
	mSlider = std::make_unique<ASHUMParameterSlider>(mProcessor->parameters,ASHUMParameterID[inParameterID]);

	const int slider_size = 54;

	mSlider->setBounds((getWidth()*.5) - (slider_size*.5), 
						(getHeight()*.5) - (slider_size*.5), 
						slider_size, 
						slider_size);
	addAndMakeVisible(*mSlider);
};