/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TypesofDistortionAudioProcessor::TypesofDistortionAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

TypesofDistortionAudioProcessor::~TypesofDistortionAudioProcessor()
{
}

//==============================================================================
const juce::String TypesofDistortionAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool TypesofDistortionAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool TypesofDistortionAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool TypesofDistortionAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double TypesofDistortionAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int TypesofDistortionAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int TypesofDistortionAudioProcessor::getCurrentProgram()
{
    return 0;
}

void TypesofDistortionAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String TypesofDistortionAudioProcessor::getProgramName (int index)
{
    return {};
}

void TypesofDistortionAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void TypesofDistortionAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void TypesofDistortionAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool TypesofDistortionAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

float TypesofDistortionAudioProcessor::hardClipping(float input)
{
    float output = 0;
    if (input > 1)
    {
        return 1.f;
    }
    else if (input < -1)
    {
        return -1.f;
    }
    else
        return input;
}

float TypesofDistortionAudioProcessor::softClipping(float input, int a)
{
    float output = 0;
    if (input > 0)
    {
        output = (a / (a - 1)) * (1 - pow(a, -input));
    }
    else
    {
        output = (a / (a - 1)) * (-1 + pow(a, input));
    }
    return output;

   // if (input > 0)
   // {
   //     output = 1 - pow(a, -input);
   // }
   // else
   // {
   //     output = -1 + pow(a, input);
   // }
   // output = output * a / (a - 1);
   // return output;
}

float TypesofDistortionAudioProcessor::quarterCircle(float input)
{
    float output = 0;
    if (input > 0)
    {
        output = sqrt(1 - pow((input - 1), 2));
    }
    else
    {
        output = (sqrt((1 - pow((input + 1), 2)))) * -1;
    }
    return output;
}

float TypesofDistortionAudioProcessor::asymmetrical(float input, float c)
{
    float a = 1 / (c + 1);
    float output = 0;

    if (input > 0)
    {
        output = input;
    }
    else
    {
        output = input + (pow(input * -1, a) / a);
    }
    return output;
}

void TypesofDistortionAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    float fMix = 0;
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        
        // ..do something to the data...
          //  juce::dsp::AudioBlock<float> block(buffer);
  //
  //  auto leftBlock = block.getSingleChannelBlock(0);
  //  auto rightBlock = block.getSingleChannelBlock(1);
      //  int hardClip = editor.menu.getItemId(1);
      //  int softClip = editor.menu.getItemId(2);
      //  int quarterCicle = editor.menu.getItemId(3);
      //  int asymmetric = editor.menu.getItemId(4);

        if (typeOfDistortion == 0)
        {
            for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
            {
                channelData[sample] = buffer.getSample(channel, sample);
                fMix = channelData[sample];
                channelData[sample] = fMix;
            }
        }

        if (typeOfDistortion == 1)
        {
            for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
            {
                channelData[sample] = buffer.getSample(channel, sample);
                fMix = channelData[sample] * clippingGain;
                channelData[sample] = hardClipping(fMix);
            }
        }
        
        else if (typeOfDistortion == 2)
        {
            for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
            {
                channelData[sample] = buffer.getSample(channel, sample);
                fMix = channelData[sample] * (clippingGain * 0.17); //Reduce the range of scale from 1 - 30 to 1 - 5.1

                float hardClipped = hardClipping(fMix);
           
                channelData[sample] = softClipping(hardClipped, softCurveValue);
               // channelData[sample] = quarterCircle(hardClipped);
            }
        }

        else if (typeOfDistortion == 3)
        {
            for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
            {
                channelData[sample] = buffer.getSample(channel, sample);
                fMix = channelData[sample] * clippingGain * 0.17; //Reduce the range of scale from 1 - 30 to 1 - 5.1

                float hardClipped = hardClipping(fMix);
                hardClipped *= 0.4;

                channelData[sample] = quarterCircle(hardClipped);
            }
        }

        else if (typeOfDistortion == 4)
        {
            for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
            {
                channelData[sample] = buffer.getSample(channel, sample);
                fMix = channelData[sample] * clippingGain * 0.17; //Reduce the range of scale from 1 - 30 to 1 - 5.1

                float hardClipped = hardClipping(fMix);
                hardClipped *= 0.4;

                channelData[sample] = asymmetrical(hardClipped, asymVariableValue);
            }
        }
    }

}

//==============================================================================
bool TypesofDistortionAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* TypesofDistortionAudioProcessor::createEditor()
{
    return new TypesofDistortionAudioProcessorEditor (*this);
}

//==============================================================================
void TypesofDistortionAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void TypesofDistortionAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
void TypesofDistortionAudioProcessor::setClippingGain(float newClippingGain)
{
    clippingGain = newClippingGain;
}

void TypesofDistortionAudioProcessor::setSoftCurve(double newSoftCurve)
{
    softCurveValue = newSoftCurve;
}

void TypesofDistortionAudioProcessor::setAsymVariable(double newAsymVariableValue)
{
    asymVariableValue = newAsymVariableValue;
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TypesofDistortionAudioProcessor();
}
