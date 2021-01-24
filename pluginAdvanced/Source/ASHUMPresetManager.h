/*
  ==============================================================================

    ASHUMPresetManager.h
    Created: 23 Jan 2021 2:19:26pm
    Author:  ashum048

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

#define PRESET_FILE_EXTENSION ".aspf"

class ASHUMPresetManager{
public:
	ASHUMPresetManager(juce::AudioProcessor* inProcessor);
	~ASHUMPresetManager();

	void getXmlForPreset(juce::XmlElement* inElement);
	void loadPresetForXml(juce::XmlElement* inElement);

	int getNumberOfPresets();

	juce::String getPresetName(int inPresetIndex);
	
	void createNewPreset();
	
	void savePreset();
	
	void saveAsPreset(juce::String inPresetName);
	
	void loadPreset(int inPresetIndex);
	
	bool getIsCurrentPresetSaved();
	
	juce::String getCurrentPresetName();

private:
	void storeLocalPreset();
	
	bool mCurrentPresetIsSaved();
	
	juce::File mCurrentlyLoadedPreset();
	
	juce::Array<juce::File> mLocalPresets;
	
	juce::String mCurrentPresetName;
	
	juce::String mPresentDirectory;



	juce::XmlElement* mCurrentPresetXml;

	juce::AudioProcessor* mProcessor;
};