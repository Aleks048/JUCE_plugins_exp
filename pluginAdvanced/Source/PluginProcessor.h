/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "ASHUMGain.h"
#include "ASHUMDelay.h"
#include "ASHUMLfo.h"
#include "ASHUMParameters.h"

using namespace juce;
//==============================================================================
/**
*/
class PluginAdvancedAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    PluginAdvancedAudioProcessor();
    ~PluginAdvancedAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

	AudioProcessorValueTreeState parameters;// to store the value of parameters here

private:
	/** internal*/
	void initializeDSP();
	void initializeParameters();



	std::unique_ptr<ASHUMGain> inputGain[2];
	std::unique_ptr<ASHUMGain> outputGain[2];
	std::unique_ptr<ASHUMDelay> mDelay[2];
	std::unique_ptr<ASHUMLfo> mLfo[2];
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginAdvancedAudioProcessor)
};
