/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

#define _USE_MATH_DEFINES
#include "math.h"
using namespace juce;

//==============================================================================
Chorus_flangerAudioProcessor::Chorus_flangerAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
	addParameter(mDryWetParameter = new AudioParameterFloat("drywet", "Dry wet", 0.0, 1.0, 0.5));
	addParameter(mDepthParameter = new AudioParameterFloat("depth","Depth",0.0,1.0,0.5));
	addParameter(mRateParameter = new AudioParameterFloat("rate", "Rate", 0.1f,20.f,10.f));
	addParameter(mPhaseOffsetParameter = new AudioParameterFloat("phaseoffset","Phase Offset",0.0f,1.f,0.f));
	addParameter(mFeedbackParameter = new AudioParameterFloat("feddback","Feedback",0.f,0.98f,0.5f));
	addParameter(mTypeParameter = new AudioParameterInt("type","Type",0,1,0));

	mCircularBufferLeft = nullptr;
	mCircularBufferRight = nullptr;
	mCircularBufferWriteHead = 0;
	mCircularBufferLength = 0;
	
	mFeedbackLeft = 0;
	mFeedbackRight = 0;
	
	mLFOPhase = 0;
}

Chorus_flangerAudioProcessor::~Chorus_flangerAudioProcessor()
{
}

//==============================================================================
const juce::String Chorus_flangerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Chorus_flangerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Chorus_flangerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Chorus_flangerAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Chorus_flangerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Chorus_flangerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Chorus_flangerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void Chorus_flangerAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String Chorus_flangerAudioProcessor::getProgramName (int index)
{
    return {};
}

void Chorus_flangerAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void Chorus_flangerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

	mLFOPhase = 0;


	mCircularBufferLength = sampleRate * MAX_DELAY_TIME;

	if (mCircularBufferLeft == nullptr) {
		mCircularBufferLeft = new float[mCircularBufferLength];
	}
	zeromem(mCircularBufferLeft, mCircularBufferLength * sizeof(float));

	if (mCircularBufferRight == nullptr) {
		mCircularBufferRight = new float[mCircularBufferLength];
	}
	zeromem(mCircularBufferRight, mCircularBufferLength * sizeof(float));

	mCircularBufferWriteHead = 0;
}

void Chorus_flangerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Chorus_flangerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void Chorus_flangerAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
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

        // ..do something to the data...
    }

	/** get left and right audio data pointers*/
	float* leftChannel = buffer.getWritePointer(0);
	float* rightChannel = buffer.getWritePointer(1);

	
	for (int i = 0; i < buffer.getNumSamples(); i++) {

		/** write into the circular buffer*/
		mCircularBufferLeft[mCircularBufferWriteHead] = leftChannel[i] + mFeedbackLeft;
		mCircularBufferRight[mCircularBufferWriteHead] = rightChannel[i] + mFeedbackRight;

		
		/** genrate the left LFO output*/
		float lfoOutLeft = sin(2 * M_PI * mLFOPhase);
		
		/** generate right lfo phase*/
		float lfoPhaseRight = mLFOPhase + *mPhaseOffsetParameter;
		if (lfoPhaseRight > 1) { lfoPhaseRight -= 1; }
		/** generate the right channel LFO output*/
		float lfoOutRight = sin(2 * M_PI* lfoPhaseRight);

		/** moving LFO phase forward*/
		mLFOPhase += *mRateParameter / getSampleRate();
		if (mLFOPhase > 1) { mLFOPhase -= 1; }

		/** control the LFO depth*/
		lfoOutLeft *= *mDepthParameter;
		lfoOutRight *= *mDepthParameter;

		/** map the lfo to the desired delay times*/
		float lfoOutMappedLeft = 0;
		float lfoOutMappedRight = 0;
		/** chorus*/
		if (*mTypeParameter == 0) {
			lfoOutMappedLeft = jmap(lfoOutLeft, -1.f, 1.f, 0.005f, 0.03f);
			lfoOutMappedRight = jmap(lfoOutRight, -1.f, 1.f, 0.005f, 0.03f);
		}
		/** flanger*/
		else {
			lfoOutMappedLeft = jmap(lfoOutLeft, -1.f, 1.f, 0.001f, 0.005f);
			lfoOutMappedRight = jmap(lfoOutRight, -1.f, 1.f, 0.001f, 0.005f);
		}




		/** calculate left and right delay lengths in samples*/
		float delayTimeInSamplesLeft = getSampleRate() * lfoOutMappedLeft;
		float delayTimeInSamplesRight = getSampleRate() * lfoOutMappedRight;

	
		/** calculate the delay left and right read head position*/
		float delayReadHeadLeft = mCircularBufferWriteHead - delayTimeInSamplesLeft;
		if (delayReadHeadLeft < 0) { delayReadHeadLeft += mCircularBufferLength; }
		float delayReadHeadRight = mCircularBufferWriteHead - delayTimeInSamplesRight;
		if (delayReadHeadRight < 0) { delayReadHeadRight += mCircularBufferLength; }

		/** canculate laft and right linear interpolation for the samples*/
		int readHeadLeft_x = (int)delayReadHeadLeft;
		int readHeadLeft_x1 = (readHeadLeft_x + 1 >= mCircularBufferLength) ? 
										readHeadLeft_x + 1 - mCircularBufferLength : 
										readHeadLeft_x + 1;
		float readHeadLeftFloat = delayReadHeadLeft - readHeadLeft_x;
		int readHeadRight_x = (int)delayReadHeadRight;
		int readHeadRight_x1 = (readHeadRight_x + 1 >= mCircularBufferLength) ?
										readHeadRight_x + 1 - mCircularBufferLength :
										readHeadRight_x + 1;
		float readHeadRightFloat = delayReadHeadRight - readHeadRight_x;

		/** generate the actual samples*/
		float delay_sample_left = lin_interp(mCircularBufferLeft[readHeadLeft_x], mCircularBufferLeft[readHeadLeft_x1], readHeadLeftFloat);
		float delay_sample_right = lin_interp(mCircularBufferRight[readHeadRight_x], mCircularBufferRight[readHeadRight_x1], readHeadRightFloat);

		/** store the feedback results*/
		mFeedbackLeft = delay_sample_left * *mFeedbackParameter;
		mFeedbackRight = delay_sample_right * *mFeedbackParameter;

		
		/** adding dryWet to the signal*/
		buffer.setSample(0, i, buffer.getSample(0, i)*(1 - *mDryWetParameter) + delay_sample_left* *mDryWetParameter);
		buffer.setSample(1, i, buffer.getSample(1, i)*(1 - *mDryWetParameter) + delay_sample_right* *mDryWetParameter);
		
		mCircularBufferWriteHead++;

		if (mCircularBufferWriteHead >= mCircularBufferLength) {
			mCircularBufferWriteHead -= mCircularBufferLength;
		}
	}
}

//==============================================================================
bool Chorus_flangerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Chorus_flangerAudioProcessor::createEditor()
{
    return new Chorus_flangerAudioProcessorEditor (*this);
}

//==============================================================================
void Chorus_flangerAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
	std::unique_ptr<XmlElement> xml(new XmlElement("ChorusFlanger"));

	xml->setAttribute("DryWet", *mDryWetParameter);
	xml->setAttribute("Depth", *mDepthParameter);
	xml->setAttribute("Rate", *mRateParameter);
	xml->setAttribute("PhaseOffset", *mPhaseOffsetParameter);
	xml->setAttribute("Feedback", *mFeedbackParameter);
	xml->setAttribute("Type", *mTypeParameter);

	copyXmlToBinary(*xml, destData);
}

void Chorus_flangerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
	std::unique_ptr<XmlElement> xml(getXmlFromBinary(data, sizeInBytes));

	if (xml.get() != nullptr && xml->hasTagName("ChorusFlanger")) {
		*mDryWetParameter = xml->getDoubleAttribute("DryWet");
		*mDepthParameter = xml->getDoubleAttribute("Depth");
		*mRateParameter = xml->getDoubleAttribute("Rate");
		*mPhaseOffsetParameter = xml->getDoubleAttribute("PhaseOffset");
		*mFeedbackParameter = xml->getDoubleAttribute("Feedback");
		*mTypeParameter = xml->getIntAttribute("Type");
	}
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Chorus_flangerAudioProcessor();
}
float Chorus_flangerAudioProcessor::lin_interp(float x, float x1, float phase) {
	return (1 - phase)*x + phase * x1;
}
