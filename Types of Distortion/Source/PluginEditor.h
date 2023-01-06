/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class TypesofDistortionAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                               public Slider::Listener,
                                               public ComboBox::Listener,
                                               public MouseListener
{
public:
    TypesofDistortionAudioProcessorEditor (TypesofDistortionAudioProcessor&);
    ~TypesofDistortionAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(Slider* slider) override;
    void comboBoxChanged(ComboBox* comboBoxThatHasChanged) override;
    void mouseDoubleClick(const MouseEvent& event) override;
    ComboBox menu;
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    TypesofDistortionAudioProcessor& audioProcessor;
    
    Slider clippingGainSldr, softCurveSldr, asymVariableSldr, outputGainSldr, cutoffSldr, dryWetSldr;

    juce::Rectangle<int> getWorkingArea();
    juce::Rectangle<int> getAnalyserArea();
    juce::Rectangle<int> getKnobsArea();
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TypesofDistortionAudioProcessorEditor)
};
