/*
  ==============================================================================

	ASHUMPresetManager.cpp
	Created: 23 Jan 2021 2:19:26pm
	Author:  ashum048

  ==============================================================================
*/

#include "ASHUMPresetManager.h"

ASHUMPresetManager::ASHUMPresetManager(juce::AudioProcessor* inProcessor) :
	mProcessor(inProcessor)
{
};


ASHUMPresetManager::~ASHUMPresetManager() {

};

void ASHUMPresetManager::getXmlForPreset(juce::XmlElement* inElement) {
	const int numParameters = mProcessor->getNumParameters();

	for (int i = 0; i < numParameters; i++) {
		inElement->setAttribute(mProcessor->getParameterName(i), mProcessor->getParameter(i));
	}
};

void ASHUMPresetManager::loadPresetForXml(juce::XmlElement* inElement) {
	mCurrentPresetXml = inElement;

	for (int i = 0; i < mCurrentPresetXml->getNumAttributes(); i++){
		const juce::String name = mCurrentPresetXml->getAttributeName(i);
		const float value = mCurrentPresetXml->getDoubleAttribute(name);

		for (int j = 0; j < mProcessor->getNumParameters(); j++) {
			if (mProcessor->getParameterName(j)==name){
				mProcessor->setParameterNotifyingHost(j, value);
			}
		}
	}
};

int ASHUMPresetManager::getNumberOfPresets() {};

juce::String ASHUMPresetManager::getPresetName(int inPresetIndex) {};

void ASHUMPresetManager::createNewPreset() {};

void ASHUMPresetManager::savePreset() {};

void ASHUMPresetManager::saveAsPreset(juce::String inPresetName) {};

void ASHUMPresetManager::loadPreset(int inPresetIndex) {};

bool ASHUMPresetManager::getIsCurrentPresetSaved() {};

juce::String ASHUMPresetManager::getCurrentPresetName() {};

void ASHUMPresetManager::storeLocalPreset() {};