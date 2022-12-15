/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TypesofDistortionAudioProcessorEditor::TypesofDistortionAudioProcessorEditor(TypesofDistortionAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(700, 400);

    menu.addItem("Off", 1);
    menu.addItem("Hard Clipping", 2);
    menu.addItem("Soft Clipping", 3);
    menu.addItem("Quarter Circle", 4);
    menu.addItem("Asymmetrical ", 5);
    menu.setText("Distortion Type", dontSendNotification);
    menu.addListener(this);
    addAndMakeVisible(menu);

    clippingGainSldr.setSliderStyle(Slider::Rotary);
    //setTextBoxStyle()
    clippingGainSldr.setRange(1, 30, 1);
    clippingGainSldr.setValue(1);
    clippingGainSldr.addListener(this);
    addAndMakeVisible(clippingGainSldr);
    
    softCurve.setSliderStyle(Slider::Rotary);
    //setTextBoxStyle()
    softCurve.setRange(10.f, 10000.f);
    softCurve.setValue(10.f);
    softCurve.addListener(this);
    addAndMakeVisible(softCurve);
        
    asymVariable.setSliderStyle(Slider::Rotary);
    //setTextBoxStyle()
    asymVariable.setRange(0.f, 1.f);
    asymVariable.setValue(1.f);
    asymVariable.addListener(this);
    addAndMakeVisible(asymVariable);

}

TypesofDistortionAudioProcessorEditor::~TypesofDistortionAudioProcessorEditor()
{
}

//==============================================================================
void TypesofDistortionAudioProcessorEditor::paint(juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

}

juce::Rectangle<int> TypesofDistortionAudioProcessorEditor::getWorkingArea()
{
    auto bounds = getLocalBounds();
    //  bounds.reduce(15, //JUCE_LIVE_CONSTANT(5),
    //                20); //JUCE_LIVE_CONSTANT(5));
    bounds.removeFromTop(20);
    bounds.removeFromBottom(20);
    bounds.removeFromLeft(20);
    bounds.removeFromRight(20);

    return bounds;
}

juce::Rectangle<int> TypesofDistortionAudioProcessorEditor::getAnalyserArea()
{
    auto analyserAreaHeight = 300;
    auto analyserAreaWidth = 300;
    auto analyserArea = getWorkingArea().removeFromTop(analyserAreaHeight);
    analyserArea = getWorkingArea().removeFromTop(analyserAreaWidth);
    return analyserArea;
}

juce::Rectangle<int> TypesofDistortionAudioProcessorEditor::getKnobsArea()
{
    auto knobsAreaHeight = 100;
    auto knobsArea = getWorkingArea().removeFromBottom(knobsAreaHeight);
  
    return knobsArea;
}

void TypesofDistortionAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    auto area = getWorkingArea();
    auto knobsArea = getKnobsArea();
    auto analyserArea = getAnalyserArea();
    auto menuArea = analyserArea.removeFromLeft(130);
    menuArea = menuArea.removeFromTop(40);
 
    clippingGainSldr.setBounds(knobsArea.removeFromLeft(150));
    softCurve.setBounds(knobsArea.removeFromLeft(150));
    asymVariable.setBounds(knobsArea.removeFromLeft(150));
    menu.setBounds(menuArea);
}

void TypesofDistortionAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    if (slider == &clippingGainSldr)
    {
        audioProcessor.setClippingGain(clippingGainSldr.getValue());
    }

    else if (slider == &softCurve)
    {
        audioProcessor.setSoftCurve(softCurve.getValue());
    }

    else if (slider == &asymVariable)
    {
        audioProcessor.setAsymVariable(asymVariable.getValue());
    }
}

void TypesofDistortionAudioProcessorEditor::comboBoxChanged(ComboBox* comboBoxThatHasChanged)
{
    if (comboBoxThatHasChanged == &menu)
    {
        if (menu.getSelectedId() == 1) //Off
        {
            audioProcessor.setDistortionType(audioProcessor.Off);
        }

        else if (menu.getSelectedId() == 2) //HardClipping
        {
            audioProcessor.setDistortionType(audioProcessor.HardClipType);
        }

        else if (menu.getSelectedId() == 3) //SoftClipping
        {
            audioProcessor.setDistortionType(audioProcessor.SoftClipType); 
        }

        else if (menu.getSelectedId() == 4) //QuarterCicle
        {
            audioProcessor.setDistortionType(audioProcessor.QuarterCicleType);
        }
       
        else if (menu.getSelectedId() == 5) //Asymmetrical
        {
            audioProcessor.setDistortionType(audioProcessor.AsymmetricType);
        }
    }
}