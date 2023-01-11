/*
  ==============================================================================

    HardClipGUI.cpp
    Created: 6 Jan 2023 11:29:09am
    Author:  Raul

  ==============================================================================
*/

#include "HardClipGUI.h"

HardClipGUI::HardClipGUI()
{
    clippingGainSldr.setSliderStyle(Slider::Rotary);
    //setTextBoxStyle()
    clippingGainSldr.setRange(1, 10, 1);
    clippingGainSldr.setValue(1);
    clippingGainSldr.setTextBoxStyle(Slider::TextBoxAbove, true, 40, 15);
    clippingGainSldr.addListener(this);
    addAndMakeVisible(clippingGainSldr);

    clipGainText.setText("Clipping Gain", dontSendNotification);
   // clipGainText.setJustificationType(juce::Justification::centredTop);
    clipGainText.setColour(Label::ColourIds::outlineColourId, Colours::wheat);
    addAndMakeVisible(clipGainText);
   
    clipGainValuesText.setText("1    -    10", dontSendNotification);
    addAndMakeVisible(clipGainValuesText);
}

void HardClipGUI::sliderValueChanged(Slider* slider)
{
    {
        if (slider == &clippingGainSldr)
        {
            hardClipProcessPtr->setClippingGain(clippingGainSldr.getValue());
        }
    }
}


juce::Rectangle<int> HardClipGUI::getWorkingArea()
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

juce::Rectangle<int> HardClipGUI::getAnalyserArea()
{
    auto analyserAreaHeight = 300;
    auto analyserAreaWidth = 300;
    auto analyserArea = getWorkingArea().removeFromTop(analyserAreaHeight);
    analyserArea = getWorkingArea().removeFromTop(analyserAreaWidth);
    return analyserArea;
}

juce::Rectangle<int> HardClipGUI::getKnobsArea()
{
    auto knobsAreaHeight = 170;
    auto knobsArea = getWorkingArea().removeFromBottom(knobsAreaHeight);

    return knobsArea;
}

void HardClipGUI::resized()
{
    auto area = getWorkingArea();
    auto knobsArea = getKnobsArea();
    auto analyserArea = getAnalyserArea();
    auto menuArea = analyserArea.removeFromLeft(130);
    menuArea = menuArea.removeFromTop(40);

    clippingGainSldr.setBounds(knobsArea.removeFromLeft(150));
    clippingGainSldr.setSize(100, 100);

    Rectangle <int> clipGainSldrPos = clippingGainSldr.getBounds();
    int posX = clipGainSldrPos.getCentreX();
    int posY = clipGainSldrPos.getCentreY();
   
    clipGainText.setBounds((posX - 50), (posY + 50), 100, 15);
    clipGainValuesText.setBounds((posX - 32), (posY + 70), 100, 15);
 }

void HardClipGUI::setHardClip(HardClipProcessor* hardClipPorcessorptr)
{
    hardClipProcessPtr = hardClipPorcessorptr;
}