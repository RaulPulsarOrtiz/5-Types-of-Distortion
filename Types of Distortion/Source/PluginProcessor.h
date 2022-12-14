/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class TypesofDistortionAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    TypesofDistortionAudioProcessor();
    ~TypesofDistortionAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    //==============================================================================
    void setClippingGain(float newClippingGain);
    void setSoftCurve(float newSoftCurve);
    void setAsymVariable(float newAsymVariableValue);
    //==============================================================================
    float hardClipping(float input);
    float softClipping(float input, int a);
    float quarterCircle(float input);
    float asymmetrical(float input, float c);

 //   float hardClipProcessor(juce::AudioBuffer<float>& buffer);
    
   // enum typeOfDistortion
   // {
   //     hardClip,
   //     softClip,
   //     quarterCicle,
   //     asymmetric
   // };
    int typeOfDistortion = 0;

private:
  
    float clippingGain;
    float softCurveValue;
    float asymVariableValue;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TypesofDistortionAudioProcessor)
};
