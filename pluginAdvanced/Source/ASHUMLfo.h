/*
  ==============================================================================

    ASHUMLfo.h
    Created: 24 Dec 2020 3:47:40pm
    Author:  ashum048

  ==============================================================================
*/

#pragma once
#include "AHUMAudioHelpers.h";
class ASHUMLfo {
public:
	ASHUMLfo();
	~ASHUMLfo();

	void reset();
	void setSampleRate(double inSampleRate);

	void process(float inRate,float inDepth,int inNumSamples);

	float* getBuffer();
private:
	double mSampleRate;
	float mPhase;

	float mBuffer[maxBufferDelaySize];
};