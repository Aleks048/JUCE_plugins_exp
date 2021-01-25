/*
  ==============================================================================

    ASHUMTopPanel.cpp
    Created: 6 Jan 2021 5:10:06pm
    Author:  ashum048

  ==============================================================================
*/

#include "ASHUMTopPanel.h"

ASHUMTopPanel::ASHUMTopPanel(PluginAdvancedAudioProcessor* inProcessor):
	ASHUMPanelBase(inProcessor)
{
	setSize(TOP_PANEL_WIDTH, TOP_PANEL_HEIGHT);

	int button_x = 15;
	int button_y = 10;
	int button_w = 55;
	int button_h = 25;

	mNewPreset = new juce::TextButton();
	mNewPreset->setButtonText("NEWWW");
	mNewPreset->setBounds(button_x, button_y, button_w, button_h);
	mNewPreset->addListener(this);
	addAndMakeVisible(*mNewPreset);
	button_x += button_w;

	mSavePreset = new juce::TextButton();
	mSavePreset->setButtonText("Save");
	mSavePreset->setBounds(button_x, button_y, button_w, button_h);
	mSavePreset->addListener(this);
	addAndMakeVisible(*mSavePreset);
	button_x += button_w;

	mSaveAsPreset = new juce::TextButton();
	mSaveAsPreset->setButtonText("SaveASS");
	mSaveAsPreset->setBounds(button_x, button_y, button_w, button_h);
	mSaveAsPreset->addListener(this);
	addAndMakeVisible(*mSaveAsPreset);
	button_x += button_w;

	const int comboBox_w = 200;
	const int comboBox_x = TOP_PANEL_WIDTH*.5f-comboBox_w*.5;

	mPresetDisplay = new juce::ComboBox();
	mPresetDisplay->setBounds(comboBox_x, button_y, comboBox_w, button_h);
	mPresetDisplay->addListener(this);
	addAndMakeVisible(*mPresetDisplay);

	updatePresetComboBox();
}
ASHUMTopPanel::~ASHUMTopPanel() {}

void ASHUMTopPanel::paint(juce::Graphics& g) {
	ASHUMPanelBase::paint(g);
	g.drawFittedText("My audio plugin", 0, 0, getWidth()-10, getHeight(), juce::Justification::centredRight, 1);
}

void ASHUMTopPanel::buttonClicked(Button* b) {
	ASHUMPresetManager* presetManager = mProcessor->getPresetManager();

	if (b == mNewPreset) {
		presetManager->createNewPreset();
		updatePresetComboBox();
	}
	else if (b == mSavePreset) {
		presetManager->savePreset();
	}
	else if (b == mSaveAsPreset) {
		displaySaveAsPopup();
	}
};

void ASHUMTopPanel::comboBoxChanged(ComboBox* comboBoxThatHasChanged) {
	if (comboBoxThatHasChanged == mPresetDisplay) {
		ASHUMPresetManager* presetManager = mProcessor->getPresetManager();
		const int index = mPresetDisplay->getSelectedItemIndex();
		presetManager->loadPreset(index);
	}
};

void ASHUMTopPanel::displaySaveAsPopup() {
	ASHUMPresetManager* presetManager = mProcessor->getPresetManager();
	juce::String currentPresetName = presetManager->getCurrentPresetName();

	juce::AlertWindow window("Save ASS", "Please give a preset name",juce::AlertWindow::NoIcon);
	window.centreAroundComponent(this, getWidth(), getHeight());
	window.addTextEditor("presetName", currentPresetName, "preset name: ");
	window.addButton("Confirm", 1);
	window.addButton("Cancel", 0);

	if (window.runModalLoop()) {
		juce::String presetName = window.getTextEditor("presetName")->getText();
		presetManager->saveAsPreset(presetName);
		updatePresetComboBox();
	}

};
void ASHUMTopPanel::updatePresetComboBox() {
	ASHUMPresetManager* presetManager = mProcessor->getPresetManager();
	juce::String presetName = presetManager->getCurrentPresetName();
	
	mPresetDisplay->clear(juce::dontSendNotification);

	
	const int numPresets = presetManager->getNumberOfPresets();

	for (int i = 0; i < numPresets; i++) {
		mPresetDisplay->addItem(presetManager->getPresetName(i), i+1);
	}
	mPresetDisplay->setText(presetManager->getCurrentPresetName());
};