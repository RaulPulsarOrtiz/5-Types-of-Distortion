/*
  ==============================================================================

    AsymmetricalGUI.h
    Created: 6 Jan 2023 2:42:24pm
    Author:  Raul

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "AsymmetricalProcessor.h"

class AsymmetricalGUI : public Component,
                        public Slider::Listener
{
public:
    AsymmetricalGUI();
    ~AsymmetricalGUI() {};

    void sliderValueChanged(Slider* slider) override;
    void resized() override;
   
    Slider asymVariableSldr;
    Label asymVariableText;

    void setAsymmetrical(AsymmetricalProcessor*);
private:
    AsymmetricalProcessor* asymmetricProcessPtr { nullptr };

    juce::Rectangle<int> getWorkingArea();
    juce::Rectangle<int> getAnalyserArea();
    juce::Rectangle<int> getKnobsArea();
};