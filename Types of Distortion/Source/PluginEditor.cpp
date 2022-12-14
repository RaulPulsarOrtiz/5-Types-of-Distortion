/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TypesofDistortionAudioProcessorEditor::TypesofDistortionAudioProcessorEditor(TypesofDistortionAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p), menu("menu")
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(600, 400);

    menu.addItem("Off", 1);
    menu.addItem("Hard Clipping", 2);
    menu.addItem("Soft Clipping", 3);
    menu.addItem("Quarter Circle", 4);
    menu.addItem("Asymmetrical ", 5);
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
    softCurve.setRange(10.0, 10000.0);
    softCurve.setValue(10.0);
    softCurve.addListener(this);
    addAndMakeVisible(softCurve);

    
    asymVariable.setSliderStyle(Slider::Rotary);
    //setTextBoxStyle()
    asymVariable.setRange(0.0, 1.0);
    asymVariable.setValue(1.0);
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

void TypesofDistortionAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    clippingGainSldr.setBounds(10, 10, getWidth() / 3, getHeight() / 6);
    softCurve.setBounds(150, 10, getWidth() / 3, getHeight() / 6);
    asymVariable.setBounds(290, 10, getWidth() / 3, getHeight() / 6);
    menu.setBounds(10, 70, getWidth() / 3, getHeight() / 10);
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
        if (menu.getSelectedId() == 1)
        {
            audioProcessor.typeOfDistortion = 0;
        }

        else if (menu.getSelectedId() == 2)
        {
            audioProcessor.typeOfDistortion = 1;
        }

        else if (menu.getSelectedId() == 3)
        {
            audioProcessor.typeOfDistortion = 2;
        }

        else if (menu.getSelectedId() == 4)
        {
            audioProcessor.typeOfDistortion = 3;
        }
       
        else if (menu.getSelectedId() == 5)
        {
            audioProcessor.typeOfDistortion = 4;
        }
    }
}