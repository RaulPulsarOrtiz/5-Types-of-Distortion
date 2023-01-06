/*
  ==============================================================================

    HardClipGUI.h
    Created: 6 Jan 2023 11:29:09am
    Author:  Raul

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "HardClipProcessor.h"

class HardClipGUI : public Component,
                    public Slider::Listener
{
public:
    HardClipGUI();
    ~HardClipGUI() {};
    void sliderValueChanged(Slider* slider) override;
    void resized() override;

    void setHardClip(HardClipProcessor*);
private:
    HardClipProcessor* hardClipProcessPtr{ nullptr };

    Slider clippingGainSldr;

    juce::Rectangle<int> getWorkingArea();
    juce::Rectangle<int> getAnalyserArea();
    juce::Rectangle<int> getKnobsArea();
};