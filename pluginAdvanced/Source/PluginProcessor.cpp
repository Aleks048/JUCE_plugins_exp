/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PluginAdvancedAudioProcessor::PluginAdvancedAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
	parameters(*this,nullptr)
#endif
{
	initializeParameters();

	initializeDSP();

	mPresetManager = new ASHUMPresetManager(this);
}

PluginAdvancedAudioProcessor::~PluginAdvancedAudioProcessor()
{
}

//==============================================================================
const juce::String PluginAdvancedAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool PluginAdvancedAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool PluginAdvancedAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool PluginAdvancedAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double PluginAdvancedAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PluginAdvancedAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int PluginAdvancedAudioProcessor::getCurrentProgram()
{
    return 0;
}

void PluginAdvancedAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String PluginAdvancedAudioProcessor::getProgramName (int index)
{
    return {};
}

void PluginAdvancedAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void PluginAdvancedAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
	for (int i = 0; i < 2; i++) {
		mDelay[i]->setSampleRate(sampleRate);
		mLfo[i]->setSampleRate(sampleRate);
	}
}

void PluginAdvancedAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
	for (int i = 0; i < 2; i++) {
		mDelay[i]->reset();
		mLfo[i]->reset();
	}
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool PluginAdvancedAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void PluginAdvancedAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);


		inputGain[channel]->process(channelData,
								getParameter(kParameter_InputGain), 
								channelData,
								buffer.getNumSamples());

		float rate = (channel == 0) ? 0 : getParameter(kParameter_ModulationRate);
		mLfo[channel]->process(rate,
								getParameter(kParameter_ModulationDepth), 
								buffer.getNumSamples());

		mDelay[channel]->process(channelData, 
								getParameter(kParameter_DelayTime), 
								getParameter(kParameter_DelayFeedback),
								getParameter(kParameter_DelayWetDry), 
								getParameter(kParameter_DelayFeedback),
								mLfo[channel]->getBuffer(),
								channelData,
								buffer.getNumSamples());
		
		outputGain[channel]->process(channelData,
									getParameter(kParameter_OutputGain),
									channelData,
									buffer.getNumSamples());
        // ..do something to the data...
    }


}

//==============================================================================
bool PluginAdvancedAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* PluginAdvancedAudioProcessor::createEditor()
{
    return new PluginAdvancedAudioProcessorEditor (*this);
}

//==============================================================================
void PluginAdvancedAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.

	XmlElement preset("ASHUM_StateInfo");

	XmlElement* presetBody = new XmlElement("ASHUM_Preset");
	mPresetManager->getXmlForPreset(presetBody);

	preset.addChildElement(presetBody);

	copyXmlToBinary(preset, destData);
}

void PluginAdvancedAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.

	std::unique_ptr<XmlElement> xmlState = getXmlFromBinary(data, sizeInBytes);

	if (xmlState) {
		forEachXmlChildElement(*xmlState, subChild) {
			mPresetManager->loadPresetForXml(subChild);
		}
	}
	else {
		jassertfalse;
	}
}

void PluginAdvancedAudioProcessor::initializeDSP() {
	for (int i = 0; i < 2; i++) {
		inputGain[i] = std::make_unique<ASHUMGain>();
		outputGain[i] = std::make_unique<ASHUMGain>();
		mDelay[i] = std::make_unique<ASHUMDelay>();
		mLfo[i] = std::make_unique<ASHUMLfo>();
	}
	
}

void PluginAdvancedAudioProcessor::initializeParameters() {
	for (int i = 0; i < kParameter_TotalNumParameters; i++) {
		parameters.createAndAddParameter(ASHUMParameterID[i],
										ASHUMParameterID[i],
										ASHUMParameterID[i],
										NormalisableRange<float>(.0f, 1.f),
										.5f, nullptr, nullptr);
	}
	parameters.state = ValueTree("Foo");

}
//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginAdvancedAudioProcessor();
}
