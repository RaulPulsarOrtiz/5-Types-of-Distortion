/*
  ==============================================================================

    AsymmetricalGUI.cpp
    Created: 6 Jan 2023 2:42:24pm
    Author:  Raul

  ==============================================================================
*/

#include "AsymmetricalGUI.h"

AsymmetricalGUI::AsymmetricalGUI()
{
    asymVariableSldr.setSliderStyle(Slider::Rotary);
    asymVariableSldr.setRange(0.f, 1.f);
    asymVariableSldr.setValue(1.f);
    asymVariableSldr.setTextBoxStyle(Slider::TextBoxAbove, true, 60, 15);
    asymVariableSldr.addListener(this);
    addAndMakeVisible(asymVariableSldr);
    asymVariableSldr.setVisible(false);

    asymVariableText.setText("Asymmetric Value", dontSendNotification);
    asymVariableText.setColour(Label::ColourIds::outlineColourId, Colours::wheat);
    addAndMakeVisible(asymVariableText);
    asymVariableText.setVisible(false);
}

void AsymmetricalGUI::sliderValueChanged(Slider* slider)
{
     if (slider == &asymVariableSldr)
    {
         asymmetricProcessPtr->setAsymVariable(asymVariableSldr.getValue());
    }
}

juce::Rectangle<int> AsymmetricalGUI::getWorkingArea()
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

juce::Rectangle<int> AsymmetricalGUI::getAnalyserArea()
{
    auto analyserAreaHeight = 300;
    auto analyserAreaWidth = 300;
    auto analyserArea = getWorkingArea().removeFromTop(analyserAreaHeight);
    analyserArea = getWorkingArea().removeFromTop(analyserAreaWidth);
    return analyserArea;
}

juce::Rectangle<int> AsymmetricalGUI::getKnobsArea()
{
    auto knobsAreaHeight = 170;
    auto knobsArea = getWorkingArea().removeFromBottom(knobsAreaHeight);

    return knobsArea;
}

void AsymmetricalGUI::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    auto area = getWorkingArea();
    auto knobsArea = getKnobsArea();
    auto analyserArea = getAnalyserArea();
    auto menuArea = analyserArea.removeFromLeft(130);
    menuArea = menuArea.removeFromTop(40);

    asymVariableSldr.setBounds(knobsArea.removeFromLeft(150));
    asymVariableSldr.setSize(100, 100);

    Rectangle <int> asymmetricSldrPos = asymVariableSldr.getBounds();
    int posX = asymmetricSldrPos.getCentreX();
    int posY = asymmetricSldrPos.getCentreY();

    asymVariableText.setBounds((posX - 60), (posY + 50), 115, 15);
}


void AsymmetricalGUI::setAsymmetrical(AsymmetricalProcessor* asymmetricProcessptr)
{
    asymmetricProcessPtr = asymmetricProcessptr;
}