/*
  ==============================================================================

    GUIposition.h
    Created: 15 Jan 2023 2:21:18pm
    Author:  Raul

  ==============================================================================
*/
#include <JuceHeader.h>
#pragma once

class GUIposition : public Component
{
public:
    /** Rectangles to divide the whole Plug-in area in smaller areas to place the different components*/
   
    /*@return the whole area minus some borders at the edges*/
    juce::Rectangle<int> getWorkingArea();
    juce::Rectangle<int> getAnalyserArea();
    juce::Rectangle<int> getKnobsArea();
private:
};