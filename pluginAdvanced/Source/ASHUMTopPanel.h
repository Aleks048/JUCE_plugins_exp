/*
  ==============================================================================

    ASHUMTopPanel.h
    Created: 6 Jan 2021 5:10:06pm
    Author:  ashum048

  ==============================================================================
*/
#include "ASHUMPanelBase.h"
#pragma once
class ASHUMTopPanel: 
	public ASHUMPanelBase,
	public juce::Button::Listener,
	public juce::ComboBox::Listener
{
public:
	ASHUMTopPanel(PluginAdvancedAudioProcessor* inProcessor);
	~ASHUMTopPanel();

	void paint(juce::Graphics& g) override;

	
	void buttonClicked(Button*) override;

	void comboBoxChanged(ComboBox* comboBoxThatHasChanged) override;
private:

	void displaySaveAsPopup();
	void updatePresetComboBox();

	juce::ScopedPointer<TextButton> mNewPreset, mSavePreset, mSaveAsPreset;
	juce::ScopedPointer<ComboBox> mPresetDisplay;
};