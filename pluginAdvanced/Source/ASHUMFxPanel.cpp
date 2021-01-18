/*
  ==============================================================================

    ASHUMFxPanel.cpp
    Created: 6 Jan 2021 5:08:57pm
    Author:  ashum048

  ==============================================================================
*/

#include "ASHUMFxPanel.h"
#include "ASHUMParameters.h"
#include "ASHUMHElperFunctions.h"

ASHUMFxPanel::ASHUMFxPanel(PluginAdvancedAudioProcessor* inProcessor):
	ASHUMPanelBase(inProcessor),
	mStyle(kASHUMFxPanelStyle_Delay) 
{

	setSize(FX_PANEL_WIDTH, FX_PANEL_HEIGHT);

	const ASHUMFxPanelStyle currStyle = (ASHUMFxPanelStyle)(int)mProcessor->getParameter(kParameter_DelayType);
	setFxPanelStyle(currStyle);
}

ASHUMFxPanel::~ASHUMFxPanel(){

}

void ASHUMFxPanel::paint(Graphics& g){
	ASHUMPanelBase::paint(g);

	switch (mStyle) {
		case kASHUMFxPanelStyle_Delay: {
			g.drawFittedText("DEALY", 0, 0, getWidth(), getHeight()*.75f,juce::Justification::centred, 1);
		}break;
		case kASHUMFxPanelStyle_Chorus: {
			g.drawFittedText("CHORUS", 0, 0, getWidth(), getHeight()*.75f, juce::Justification::centred, 1);
		}break;
		default:
		case kASHUMFxPanelStyle_TotalNUmStyles: {
			jassertfalse; 
			g.drawFittedText("noooooo", 0, 0, getWidth(), getHeight(), juce::Justification::centred, 1);
		}break;
	}

	//painting labels
	for (int i = 0; i < mSliders.size(); i++) {
		paintComponentLabel(g, mSliders[i]);
	}
}

void ASHUMFxPanel::setFxPanelStyle(ASHUMFxPanelStyle inStyle) {
	mStyle = inStyle;

	mSliders.clear();

	const int slider_size = 56;
	int x = 130;
	int y = getHeight()*.5 - slider_size * .5;

	switch (mStyle) {
	case kASHUMFxPanelStyle_Delay: {
		ASHUMParameterSlider* time = 
			new ASHUMParameterSlider(mProcessor->parameters, ASHUMParameterID[kParameter_DelayTime]);
		time->setBounds(x, y, slider_size, slider_size);
		addAndMakeVisible(time);
		mSliders.add(time);
		x += (slider_size * 2);

		ASHUMParameterSlider* feedback =
			new ASHUMParameterSlider(mProcessor->parameters, ASHUMParameterID[kParameter_DelayFeedback]);
		feedback->setBounds(x, y, slider_size, slider_size);
		addAndMakeVisible(feedback);
		mSliders.add(feedback);
		x += (slider_size * 2);

		ASHUMParameterSlider* wetDry =
			new ASHUMParameterSlider(mProcessor->parameters, ASHUMParameterID[kParameter_DelayWetDry]);
		wetDry->setBounds(x, y, slider_size, slider_size);
		addAndMakeVisible(wetDry);
		mSliders.add(wetDry);
		//x += (slider_size * 2);


	}break;
	case kASHUMFxPanelStyle_Chorus: {

		ASHUMParameterSlider* rate =
			new ASHUMParameterSlider(mProcessor->parameters, ASHUMParameterID[kParameter_ModulationRate]);
		rate->setBounds(x, y, slider_size, slider_size);
		addAndMakeVisible(rate);
		mSliders.add(rate);
		x += (slider_size * 2);

		ASHUMParameterSlider* depth =
			new ASHUMParameterSlider(mProcessor->parameters, ASHUMParameterID[kParameter_ModulationDepth]);
		depth->setBounds(x, y, slider_size, slider_size);
		addAndMakeVisible(depth);
		mSliders.add(depth);
		x += (slider_size * 2);

		ASHUMParameterSlider* wetDry =
			new ASHUMParameterSlider(mProcessor->parameters, ASHUMParameterID[kParameter_DelayWetDry]);
		wetDry->setBounds(x, y, slider_size, slider_size);
		addAndMakeVisible(wetDry);
		mSliders.add(wetDry);


	}break;
	default:
	case kASHUMFxPanelStyle_TotalNUmStyles: {
		jassertfalse;//something is wrong
	}break;
	}
	juce::Component::repaint();
}


void ASHUMFxPanel::comboBoxChanged(ComboBox* comboBoxThatHasChanged) {
	ASHUMFxPanelStyle style = (ASHUMFxPanelStyle)comboBoxThatHasChanged->getSelectedItemIndex();
	setFxPanelStyle(style);
}