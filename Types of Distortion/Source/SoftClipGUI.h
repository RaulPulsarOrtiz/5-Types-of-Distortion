/*
  ==============================================================================

    SoftClipGUI.h
    Created: 6 Jan 2023 12:55:33pm
    Author:  Raul

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SoftClipProcessor.h"

class SoftClipGUI : public Component,
                    public Slider::Listener
{
public:
    SoftClipGUI();
    ~SoftClipGUI() {};

    void sliderValueChanged(Slider* slider) override;
    void resized() override; 

    Slider softCurveSldr;

    void setSoftClip(SoftClipProcessor*);
private:
    SoftClipProcessor* softClipProcessPtr {nullptr};
    
    juce::Rectangle<int> getWorkingArea();
    juce::Rectangle<int> getAnalyserArea();
    juce::Rectangle<int> getKnobsArea();
};