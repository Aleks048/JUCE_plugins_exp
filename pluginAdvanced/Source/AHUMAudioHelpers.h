/*
  ==============================================================================

    AHUMAudioHelpers.h
    Created: 24 Dec 2020 3:46:46pm
    Author:  ashum048

  ==============================================================================
*/

#pragma once
#define kParameterSmoothingCoeff_Generic 0.04
#define kParameterSmoothingCoeff_Fine 0.002

static const int maxBufferDelaySize = 192000;

const static double kPI = 3.14159265359;
const static double k2PI = 6.28318530718;

inline float ashum_linear_interp(float v0, float v1, float t) {
	return (1 - t) * v0 + t*v1;
}