/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
using namespace juce;
//==============================================================================
Chorus_flangerAudioProcessorEditor::Chorus_flangerAudioProcessorEditor (Chorus_flangerAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 300);
	
	auto& params = processor.getParameters();

	AudioParameterFloat* dryWetParameter = (AudioParameterFloat* )params.getUnchecked(0);
	AudioParameterFloat* mDepthParameter = (AudioParameterFloat* )params.getUnchecked(1);
	AudioParameterFloat* mRateParameter = (AudioParameterFloat* )params.getUnchecked(2);
	AudioParameterFloat* mPhaseOffsetParameter = (AudioParameterFloat* )params.getUnchecked(3);
	AudioParameterFloat* mFeedbackParameter = (AudioParameterFloat* )params.getUnchecked(4);
	AudioParameterInt* mTypeParameter = (AudioParameterInt* )params.getUnchecked(5);

	mDryWetSlider.setBounds(0, 0, 100, 100);
	mDryWetSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
	mDryWetSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
	mDryWetSlider.setRange(dryWetParameter->range.start, dryWetParameter->range.end);
	mDryWetSlider.setValue(*dryWetParameter);
	mDryWetSlider.onValueChange = [this, dryWetParameter] {*dryWetParameter = mDryWetSlider.getValue(); };
	mDryWetSlider.onDragStart = [dryWetParameter] {dryWetParameter->beginChangeGesture(); };
	mDryWetSlider.onDragEnd = [dryWetParameter] {dryWetParameter->endChangeGesture(); };
	addAndMakeVisible(mDryWetSlider);
	
	mDepthSlider.setBounds(100, 0, 100, 100);
	mDepthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
	mDepthSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
	mDepthSlider.setRange(mDepthParameter->range.start, mDepthParameter->range.end);
	mDepthSlider.setValue(*mDepthParameter);
	mDepthSlider.onValueChange = [this, mDepthParameter] {*mDepthParameter = mDepthSlider.getValue(); };
	mDepthSlider.onDragStart = [mDepthParameter] {mDepthParameter->beginChangeGesture(); };
	mDepthSlider.onDragEnd = [mDepthParameter] {mDepthParameter->endChangeGesture(); };
	addAndMakeVisible(mDepthSlider);
	
	mRateSlider.setBounds(200, 0, 100, 100);
	mRateSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
	mRateSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
	mRateSlider.setRange(mRateParameter->range.start, mRateParameter->range.end);
	mRateSlider.setValue(*mRateParameter);
	mRateSlider.onValueChange = [this, mRateParameter] {*mRateParameter = mRateSlider.getValue(); };
	mRateSlider.onDragStart = [mRateParameter] {mRateParameter->beginChangeGesture(); };
	mRateSlider.onDragEnd = [mRateParameter] {mRateParameter->endChangeGesture(); };
	addAndMakeVisible(mRateSlider);
	
	mPhaseOffsetSlider.setBounds(300, 0, 100, 100);
	mPhaseOffsetSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
	mPhaseOffsetSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
	mPhaseOffsetSlider.setRange(mPhaseOffsetParameter->range.start, mPhaseOffsetParameter->range.end);
	mPhaseOffsetSlider.setValue(*mPhaseOffsetParameter);
	mPhaseOffsetSlider.onValueChange = [this, mPhaseOffsetParameter] {*mPhaseOffsetParameter = mPhaseOffsetSlider.getValue(); };
	mPhaseOffsetSlider.onDragStart = [mPhaseOffsetParameter] {mPhaseOffsetParameter->beginChangeGesture(); };
	mPhaseOffsetSlider.onDragEnd = [mPhaseOffsetParameter] {mPhaseOffsetParameter->endChangeGesture(); };
	addAndMakeVisible(mPhaseOffsetSlider);

	mFeedbackSlider.setBounds(400, 0, 100, 100);
	mFeedbackSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
	mFeedbackSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
	mFeedbackSlider.setRange(mFeedbackParameter->range.start, mFeedbackParameter->range.end);
	mFeedbackSlider.setValue(*mFeedbackParameter);
	mFeedbackSlider.onValueChange = [this, mFeedbackParameter] {*mFeedbackParameter = mFeedbackSlider.getValue(); };
	mFeedbackSlider.onDragStart = [mFeedbackParameter] {mFeedbackParameter->beginChangeGesture(); };
	mFeedbackSlider.onDragEnd = [mFeedbackParameter] {mFeedbackParameter->endChangeGesture(); };
	addAndMakeVisible(mFeedbackSlider);

	mTypeBox.setBounds(500, 0, 100, 30);
	mTypeBox.addItem("Chorus", 1);
	mTypeBox.addItem("Flanger", 2);
	addAndMakeVisible(mTypeBox);

	mTypeBox.onChange = [this, mTypeParameter] {
		mTypeParameter->beginChangeGesture();
		*mTypeParameter = mTypeBox.getSelectedItemIndex();
		mTypeParameter->endChangeGesture();
	};
	mTypeBox.setSelectedItemIndex(*mTypeParameter);

}

Chorus_flangerAudioProcessorEditor::~Chorus_flangerAudioProcessorEditor()
{
}

//==============================================================================
void Chorus_flangerAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void Chorus_flangerAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
