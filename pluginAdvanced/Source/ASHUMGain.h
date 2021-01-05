/*
  ==============================================================================

    ASHUMGain.h
    Created: 24 Dec 2020 3:48:01pm
    Author:  ashum048

  ==============================================================================
*/

#pragma once

class ASHUMGain
{
public:
	ASHUMGain();
	~ASHUMGain();

	void process(float* inAudio,
		float inGain,
		float* outAudio,
		int inNumSamplesToRender);
private:
};