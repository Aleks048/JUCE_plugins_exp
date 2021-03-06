/*
  ==============================================================================

    ASHUMParameters.h
    Created: 7 Jan 2021 7:11:15pm
    Author:  ashum048

  ==============================================================================
*/

#pragma once
enum ASHUMParameter {
	kParameter_InputGain = 0,
	kParameter_DelayTime,
	kParameter_DelayFeedback,
	kParameter_DelayWetDry,
	kParameter_DelayType, //chorus or delay
	kParameter_OutputGain,

	kParameter_ModulationRate,
	kParameter_ModulationDepth,

	kParameter_TotalNumParameters
};

static juce::String ASHUMParameterID [kParameter_TotalNumParameters] =
{
	"Input_Gain",
	"Delay",
	"Feedback",
	"Wet_Dry",
	"Type",
	"Output_Gain",
	"Modulation_Rate",
	"Modulation_Depth",
};