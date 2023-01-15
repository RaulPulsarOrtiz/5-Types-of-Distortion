/*
  ==============================================================================

    GUIposition.cpp
    Created: 15 Jan 2023 2:21:18pm
    Author:  Raul

  ==============================================================================
*/

#include "GUIposition.h"

juce::Rectangle<int> GUIposition::getWorkingArea()
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

juce::Rectangle<int> GUIposition::getAnalyserArea()
{
    auto analyserAreaHeight = 300;
    auto analyserAreaWidth = 300;
    auto analyserArea = getWorkingArea().removeFromTop(analyserAreaHeight);
    analyserArea = getWorkingArea().removeFromTop(analyserAreaWidth);
    return analyserArea;
}

juce::Rectangle<int> GUIposition::getKnobsArea()
{
    auto knobsAreaHeight = 170;
    auto knobsArea = getWorkingArea().removeFromBottom(knobsAreaHeight);

    return knobsArea;
}