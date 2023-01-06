/*
  ==============================================================================

    SoftClipGUI.cpp
    Created: 6 Jan 2023 12:55:33pm
    Author:  Raul

  ==============================================================================
*/

#include "SoftClipGUI.h"

SoftClipGUI::SoftClipGUI()
{
    softCurveSldr.setSliderStyle(Slider::Rotary);
    softCurveSldr.setRange(10, 10000);
    softCurveSldr.setValue(10);
    softCurveSldr.setTextBoxStyle(Slider::TextBoxBelow, true, 60, 15);
    softCurveSldr.addListener(this);
    addAndMakeVisible(softCurveSldr);
    softCurveSldr.setVisible(false);
   }

void SoftClipGUI::sliderValueChanged(Slider* slider)
{
    //if (slider == &clippingGainSldr)
    //{
    //    SoftClipProcessPtr->setSoftClippingGain(clippingGainSldr.getValue());
    //}

    if (slider == &softCurveSldr)
    {
        softClipProcessPtr->setSoftCurve(softCurveSldr.getValue());
    }

}

juce::Rectangle<int> SoftClipGUI::getWorkingArea()
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

juce::Rectangle<int> SoftClipGUI::getAnalyserArea()
{
    auto analyserAreaHeight = 300;
    auto analyserAreaWidth = 300;
    auto analyserArea = getWorkingArea().removeFromTop(analyserAreaHeight);
    analyserArea = getWorkingArea().removeFromTop(analyserAreaWidth);
    return analyserArea;
}

juce::Rectangle<int> SoftClipGUI::getKnobsArea()
{
    auto knobsAreaHeight = 100;
    auto knobsArea = getWorkingArea().removeFromBottom(knobsAreaHeight);

    return knobsArea;
}

void SoftClipGUI::resized()
{
    auto area = getWorkingArea();
    auto knobsArea = getKnobsArea();
    auto analyserArea = getAnalyserArea();
    auto menuArea = analyserArea.removeFromLeft(130);
    menuArea = menuArea.removeFromTop(40);

    softCurveSldr.setBounds(knobsArea.removeFromLeft(150));
}


void SoftClipGUI::setSoftClip(SoftClipProcessor* softClipPorcessorptr)
{
    softClipProcessPtr = softClipPorcessorptr;    
}