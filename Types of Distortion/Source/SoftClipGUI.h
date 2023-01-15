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
#include "GUIposition.h"

class SoftClipGUI : public Component,
                    public Slider::Listener
{
public:
    SoftClipGUI();
    ~SoftClipGUI() {};

    void sliderValueChanged(Slider* slider) override;
    void resized() override; 

    Slider softCurveSldr;
    Label softCurveText;

    void setSoftClip(SoftClipProcessor*);
private:
    /** Reference to the SoftClipProcessor class through a pointer to access and control SoftClipProcessor class member functions */
    SoftClipProcessor* softClipProcessPtr {nullptr};
        
    GUIposition guiPosition;
 };