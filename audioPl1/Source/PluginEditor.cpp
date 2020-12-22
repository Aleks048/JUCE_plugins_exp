/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPl1AudioProcessorEditor::AudioPl1AudioProcessorEditor (AudioPl1AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

	auto& params = processor.getParameters();
	juce::AudioParameterFloat* gain = (juce::AudioParameterFloat*)params.getUnchecked(0);

	mGainControlSlider.setBounds(0, 0, 100, 100);
	mGainControlSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
	mGainControlSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);

	mGainControlSlider.setRange(gain->range.start, gain->range.end);
	mGainControlSlider.setValue(*gain);

	//mGainControlSlider.addListener(this);
	mGainControlSlider.onValueChange = [this, gain] {
		*gain = mGainControlSlider.getValue();
	};

	mGainControlSlider.onDragStart = [gain] {
		gain->beginChangeGesture();
	};
	mGainControlSlider.onDragEnd = [gain] {
		gain->endChangeGesture();
	};

	addAndMakeVisible(mGainControlSlider);


}

AudioPl1AudioProcessorEditor::~AudioPl1AudioProcessorEditor()
{
}

//==============================================================================
void AudioPl1AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void AudioPl1AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

//void AudioPl1AudioProcessorEditor::sliderValueChanged(juce::Slider* slider) {
//	auto& params = processor.getParameters();
//
//	if (slider == &mGainControlSlider) {
//		juce::AudioParameterFloat* gain = (juce::AudioParameterFloat*)params.getUnchecked(0);
//		*gain = mGainControlSlider.getValue();
//		DBG("gain slider changed");
//	}
//}
