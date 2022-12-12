/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TypesofDistortionAudioProcessorEditor::TypesofDistortionAudioProcessorEditor (TypesofDistortionAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 400);

    clippingGainSldr.setSliderStyle(Slider::Rotary);
    //setTextBoxStyle()
    clippingGainSldr.setRange(1, 30, 1);
    clippingGainSldr.setValue(1);
    clippingGainSldr.addListener(this);
    addAndMakeVisible(clippingGainSldr);
}

TypesofDistortionAudioProcessorEditor::~TypesofDistortionAudioProcessorEditor()
{
}

//==============================================================================
void TypesofDistortionAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

}

void TypesofDistortionAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    clippingGainSldr.setBounds(10, 10, getWidth()/3, getHeight()/6);
   // clippingGainSldr.setSize(100, 100);
}

void TypesofDistortionAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    if (slider == &clippingGainSldr)
    {
        audioProcessor.setClippingGain(clippingGainSldr.getValue());
    }
}