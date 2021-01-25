/*
  ==============================================================================

	ASHUMPresetManager.cpp
	Created: 23 Jan 2021 2:19:26pm
	Author:  ashum048

  ==============================================================================
*/

#include "ASHUMPresetManager.h"

#if JUCE_WINDOWS
	static const juce::String directorySeparator = "\\";
#elif JUCE_MAC
	static const juce::String directorySeparator = "/";
#endif

ASHUMPresetManager::ASHUMPresetManager(juce::AudioProcessor* inProcessor) :
	mCurrentPresetIsSaved(false),
	mCurrentPresetName("Untitled"),
	mProcessor(inProcessor)
{

	const juce::String pluginName = (juce::String) mProcessor->getName();

	/*NEEDS TO BE CHANGED FOR GENERIC. WORKS NOW*/
	mPresetDirectory = "C:" + directorySeparator + "git" + directorySeparator + 
						"juce_projects" + directorySeparator + "pluginAdvanced" + directorySeparator + 
						"Presets";

	if (!juce::File(mPresetDirectory).exists()) {
		juce::File(mPresetDirectory).createDirectory();
	}

	storeLocalPreset();
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

int ASHUMPresetManager::getNumberOfPresets() {
	return mLocalPresets.size();
};

juce::String ASHUMPresetManager::getPresetName(int inPresetIndex) {
	return mLocalPresets[inPresetIndex].getFileNameWithoutExtension();
};

void ASHUMPresetManager::createNewPreset() {
	//set all the pratmeters to default and create a new preset
	const int numParameters = mProcessor->getNumParameters();

	mCurrentPresetIsSaved = false;
	mCurrentPresetName = "Untitled";
};

void ASHUMPresetManager::savePreset() {
	juce::MemoryBlock destinationData;
	mProcessor->getStateInformation(destinationData);

	mCurrentlyLoadedPreset.deleteFile();

	mCurrentlyLoadedPreset.appendData(destinationData.getData(), destinationData.getSize());

	mCurrentPresetIsSaved = true;
};

void ASHUMPresetManager::saveAsPreset(juce::String inPresetName) {
	juce::File presetFile = juce::File(mPresetDirectory + directorySeparator + inPresetName+PRESET_FILE_EXTENSION);

	if (!presetFile.exists()) {
		presetFile.create();
	}
	else {
		presetFile.deleteFile();
	}
	juce::MemoryBlock destinationData;
	mProcessor->getStateInformation(destinationData);//get data to memory block

	presetFile.appendData(destinationData.getData(), destinationData.getSize());//put data into the file

	mCurrentPresetIsSaved = true;
	mCurrentPresetName = inPresetName;

	storeLocalPreset();
};

void ASHUMPresetManager::loadPreset(int inPresetIndex) {
	mCurrentlyLoadedPreset = mLocalPresets[inPresetIndex];

	juce::MemoryBlock presetBinary;

	if (mCurrentlyLoadedPreset.loadFileAsData(presetBinary)) {
		mCurrentPresetIsSaved = true;
		mCurrentPresetName = getPresetName(inPresetIndex);
		mProcessor->setStateInformation(presetBinary.getData(), presetBinary.getSize());
;	}
};

bool ASHUMPresetManager::getIsCurrentPresetSaved() {
	return mCurrentPresetIsSaved;
};

juce::String ASHUMPresetManager::getCurrentPresetName() {
	return mCurrentPresetName;
};

void ASHUMPresetManager::storeLocalPreset() {
	mLocalPresets.clear();

	for (juce::DirectoryIterator di(juce::File(mPresetDirectory), false,
		"*" + (juce::String)PRESET_FILE_EXTENSION,
		juce::File::TypesOfFileToFind::findFiles); di.next();) {

		juce::File preset = di.getFile();
		mLocalPresets.add(preset);
	}
};
