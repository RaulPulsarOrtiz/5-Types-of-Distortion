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
    setSize(647, 400);

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
    clippingGainSldr.setTextBoxStyle(Slider::TextBoxBelow, true, 40, 15);
    clippingGainSldr.addListener(this);
    addAndMakeVisible(clippingGainSldr);
    
    softCurveSldr.setSliderStyle(Slider::Rotary);
    softCurveSldr.setRange(10, 10000);
    softCurveSldr.setValue(10);
    softCurveSldr.setTextBoxStyle(Slider::TextBoxBelow, true, 60, 15);
    softCurveSldr.addListener(this);
    addAndMakeVisible(softCurveSldr);
    softCurveSldr.setVisible(false);
        
    asymVariableSldr.setSliderStyle(Slider::Rotary);
    asymVariableSldr.setRange(0.f, 1.f);
    asymVariableSldr.setValue(1.f);
    asymVariableSldr.setTextBoxStyle(Slider::TextBoxBelow, true, 60, 15);
    asymVariableSldr.addListener(this);
    addAndMakeVisible(asymVariableSldr);
    asymVariableSldr.setVisible(false);
   
    outputGainSldr.setSliderStyle(Slider::Rotary);
    outputGainSldr.setRange(0.f, 2.5f);
    outputGainSldr.setValue(1.f);
    outputGainSldr.setTextBoxStyle(Slider::TextBoxBelow, true, 60, 15);
    //outputGainSldr.mouseDoubleClick(MouseEvent mouse);
    outputGainSldr.addListener(this);
    addAndMakeVisible(outputGainSldr);

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
    softCurveSldr.setBounds(knobsArea.removeFromLeft(150));
    asymVariableSldr.setBounds(knobsArea.removeFromLeft(150));
    outputGainSldr.setBounds(knobsArea.removeFromLeft(150));
    menu.setBounds(menuArea);
}

void TypesofDistortionAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    if (slider == &clippingGainSldr)
    {
        audioProcessor.setClippingGain(clippingGainSldr.getValue());
    }

    else if (slider == &softCurveSldr)
    {
        audioProcessor.setSoftCurve(softCurveSldr.getValue());
    }

    else if (slider == &asymVariableSldr)
    {
        audioProcessor.setAsymVariable(asymVariableSldr.getValue());
    }

    else if (slider == &outputGainSldr)
    {
        audioProcessor.setOutputGain(outputGainSldr.getValue());
    }
}

void TypesofDistortionAudioProcessorEditor::comboBoxChanged(ComboBox* comboBoxThatHasChanged)
{
    if (comboBoxThatHasChanged == &menu)
    {
        if (menu.getSelectedId() == 1) //Off
        {
            audioProcessor.setDistortionType(audioProcessor.Off);
            softCurveSldr.setVisible(false);
            asymVariableSldr.setVisible(false);
        }

        else if (menu.getSelectedId() == 2) //HardClipping
        {
            audioProcessor.setDistortionType(audioProcessor.HardClipType);
            softCurveSldr.setVisible(false);
            asymVariableSldr.setVisible(false);
        }

        else if (menu.getSelectedId() == 3) //SoftClipping
        {
            audioProcessor.setDistortionType(audioProcessor.SoftClipType); 
            softCurveSldr.setVisible(true);
            asymVariableSldr.setVisible(false);
        }

        else if (menu.getSelectedId() == 4) //QuarterCicle
        {
            audioProcessor.setDistortionType(audioProcessor.QuarterCicleType);
            softCurveSldr.setVisible(false);
            asymVariableSldr.setVisible(false);
        }
       
        else if (menu.getSelectedId() == 5) //Asymmetrical
        {
            audioProcessor.setDistortionType(audioProcessor.AsymmetricType);
            asymVariableSldr.setVisible(true);
            softCurveSldr.setVisible(false);
        }
    }
}

void TypesofDistortionAudioProcessorEditor::mouseDoubleClick(const MouseEvent& event) //Doesnt Work
{
    clippingGainSldr.setValue(1);
    softCurveSldr.setValue(10);
    asymVariableSldr.setValue(1.f);
    outputGainSldr.setValue(1.f);
}