/*
  ==============================================================================

    ASHUMDelay.cpp
    Created: 24 Dec 2020 3:48:16pm
    Author:  ashum048

  ==============================================================================
*/

#include "ASHUMDelay.h"
#include "JuceHeader.h"
#include "AHUMAudioHelpers.h"


ASHUMDelay::ASHUMDelay() :
					mSampleRate(-1),
					mFeedbackSample(0.0),
					mTimeSmoothed(0.f),
					mDelayIndex(0)
{

}
ASHUMDelay::~ASHUMDelay() {}

void ASHUMDelay::setSampleRate(double inSampleRate){
	mSampleRate = inSampleRate;
}

void ASHUMDelay::reset(){
	juce::zeromem(mBuffer, sizeof(double) * maxBufferDelaySize);
	mTimeSmoothed = 0.f;
}

void ASHUMDelay::process(float* inAudio,
						float inTime,
						float inFeedback,
						float inWetDry,
						float* inModulationBuffer,
						float* outAudio,
						int inNumSamplesToRender){
	
	const float wet = inWetDry;
	const float dry = 1.f - wet;

	const float feedbackMapped = juce::jmap(inFeedback, 0.f, 1.f, 0.f, 0.95f);

	
	for (int i = 0; i < inNumSamplesToRender; i++) {
		
		const double delayTimeModulation = (inTime + (0.002*inModulationBuffer[i]));//modulating the delay time

		mTimeSmoothed = mTimeSmoothed - kParameterSmoothingCoeff_Generic * (mTimeSmoothed - delayTimeModulation);

		const double delayTimeInSamples = mTimeSmoothed * mSampleRate;//delay time in smamples
		const double sample = getInterpolatedSample(delayTimeInSamples);
		//DBG(sample<<" "<<inAudio[i]);

		mBuffer[mDelayIndex] = inAudio[i] + (mFeedbackSample * feedbackMapped);

		mFeedbackSample = sample;

		outAudio[i] = inAudio[i] * dry + sample * wet;

		mDelayIndex++;
		if (mDelayIndex >= maxBufferDelaySize) { mDelayIndex -= maxBufferDelaySize; }
	}
}

double ASHUMDelay::getInterpolatedSample(float inDelayTimeInSamples) {
	//determine the read position
	double readPosition = (double)mDelayIndex - inDelayTimeInSamples;
	if (readPosition < 0.f) {readPosition += maxBufferDelaySize;}

	//get the indexes
	int index_y0 = (int)readPosition - 1;
	if (index_y0 <= 0) { index_y0 += maxBufferDelaySize; }
	int index_y1 = readPosition;
	if (index_y1 >= maxBufferDelaySize) { index_y1 -= maxBufferDelaySize; }

	//get the samples
	const float sample_y0 = mBuffer[index_y0];
	const float sample_y1 = mBuffer[index_y1];
	const float t = readPosition - int(readPosition);

	//linear interpolate the samples
	double outSmaple = ashum_linear_interp(sample_y0, sample_y1, t);

	return outSmaple;
}