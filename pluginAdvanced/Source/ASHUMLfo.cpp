/*
  ==============================================================================

    ASHUMLfo.cpp
    Created: 24 Dec 2020 3:47:40pm
    Author:  ashum048

  ==============================================================================
*/

#include "ASHUMLfo.h"
#include "JuceHeader.h"
ASHUMLfo::ASHUMLfo(): mSampleRate(-1){
	reset();
}
ASHUMLfo::~ASHUMLfo() {}

void ASHUMLfo::reset() {
	mPhase = 0.f;
	juce::zeromem(mBuffer, sizeof(float)*maxBufferDelaySize);
}
void ASHUMLfo::setSampleRate(double inSampleRate) {
	mSampleRate = inSampleRate;
}

void ASHUMLfo::process(float inRate, float inDepth, int inNumSamples) {
	const float rate = juce::jmap(inRate, 0.f, 1.f, 0.01f,10.f);
	for (int i = 0; i < inNumSamples; i++) {
		mPhase += (rate / mSampleRate);

		if (mPhase > 1.f) { mPhase -= 1.f; }

		const float lfoPosition = sinf(mPhase*k2PI)*inDepth;
		mBuffer[i] = lfoPosition;
	}
}

float* ASHUMLfo::getBuffer(){
	return mBuffer;
}