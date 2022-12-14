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
                                               public ComboBox::Listener
{
public:
    TypesofDistortionAudioProcessorEditor (TypesofDistortionAudioProcessor&);
    ~TypesofDistortionAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(Slider* slider) override;
    void comboBoxChanged(ComboBox* comboBoxThatHasChanged) override;
    ComboBox menu;
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    TypesofDistortionAudioProcessor& audioProcessor;
    
    Slider clippingGainSldr;
    Slider softCurve;
    Slider asymVariable;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TypesofDistortionAudioProcessorEditor)
};
