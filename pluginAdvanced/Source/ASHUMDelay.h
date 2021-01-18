/*
  ==============================================================================

    ASHUMDelay.h
    Created: 24 Dec 2020 3:48:16pm
    Author:  ashum048

  ==============================================================================
*/

#pragma once

#include "AHUMAudioHelpers.h"

enum ASHUMDelayType {
	kASHUMDelayType_Delay=0,
	kASHUMDelayType_Chorus=1
};

class ASHUMDelay {
public:
	ASHUMDelay();
	~ASHUMDelay();
	void setSampleRate(double inSampleRate);

	void reset();

	void process(float* inAudio,
		float inTime,
		float inFeedback,
		float inWetDry,
		float inType,
		float* inModulationBuffer,
		float* outAudio,
		int inNumSamplesToRender);
private:
	/** internal*/
	double getInterpolatedSample(float inDelayTimeInSamples);

	double mSampleRate;
	double mBuffer[maxBufferDelaySize];
	double mFeedbackSample;

	float mTimeSmoothed;

	int mDelayIndex;
};