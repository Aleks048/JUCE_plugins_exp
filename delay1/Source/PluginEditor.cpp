/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Delay1AudioProcessorEditor::Delay1AudioProcessorEditor (Delay1AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
	
	auto& params = processor.getParameters();

	juce::AudioParameterFloat* dryWetParameter = (juce::AudioParameterFloat*)params.getUnchecked(0);

	mDryWetSlider.setBounds(0, 0, 100, 100);
	mDryWetSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
	mDryWetSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
	mDryWetSlider.setRange(dryWetParameter->range.start, dryWetParameter->range.end);
	mDryWetSlider.setValue(*dryWetParameter);
	addAndMakeVisible(mDryWetSlider);

	mDryWetSlider.onValueChange = [this, dryWetParameter] {*dryWetParameter = mDryWetSlider.getValue(); };
	mDryWetSlider.onDragStart = [dryWetParameter] {dryWetParameter->beginChangeGesture(); };
	mDryWetSlider.onDragEnd = [dryWetParameter] {dryWetParameter->endChangeGesture(); };

	juce::AudioParameterFloat* mFeedbackParameter = (juce::AudioParameterFloat*)params.getUnchecked(1);

	mFeedbackSlider.setBounds(100, 0, 100, 100);
	mFeedbackSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
	mFeedbackSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
	mFeedbackSlider.setRange(mFeedbackParameter->range.start, mFeedbackParameter->range.end);
	mFeedbackSlider.setValue(*mFeedbackParameter);
	addAndMakeVisible(mFeedbackSlider);

	mFeedbackSlider.onValueChange = [this, mFeedbackParameter] {*mFeedbackParameter = mFeedbackSlider.getValue(); };
	mFeedbackSlider.onDragStart = [mFeedbackParameter] {mFeedbackParameter->beginChangeGesture(); };
	mFeedbackSlider.onDragEnd = [mFeedbackParameter] {mFeedbackParameter->endChangeGesture(); };

	juce::AudioParameterFloat* mDelayTimeParameter = (juce::AudioParameterFloat*)params.getUnchecked(2);

	mDelayTimeSlider.setBounds(200, 0, 100, 100);
	mDelayTimeSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
	mDelayTimeSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
	mDelayTimeSlider.setRange(mDelayTimeParameter->range.start, mDelayTimeParameter->range.end);
	mDelayTimeSlider.setValue(*mDelayTimeParameter);
	addAndMakeVisible(mDelayTimeSlider);

	mDelayTimeSlider.onValueChange = [this, mDelayTimeParameter] {*mDelayTimeParameter = mDelayTimeSlider.getValue(); };
	mDelayTimeSlider.onDragStart = [mDelayTimeParameter] {mDelayTimeParameter->beginChangeGesture(); };
	mDelayTimeSlider.onDragEnd = [mDelayTimeParameter] {mDelayTimeParameter->endChangeGesture(); };
	//mFeedbackSlider.setBounds(0)
	//mDelayTimeSlider.setBounds();
}

Delay1AudioProcessorEditor::~Delay1AudioProcessorEditor()
{
}

//==============================================================================
void Delay1AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void Delay1AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
