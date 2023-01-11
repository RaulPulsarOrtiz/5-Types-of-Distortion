/*
  ==============================================================================

    SoftClipProcessor.h
    Created: 6 Jan 2023 12:55:22pm
    Author:  Raul

  ==============================================================================
*/

#pragma once
//#include <JuceHeader.h>
#include <cmath>
#include <atomic>

class SoftClipProcessor
{
public:
    SoftClipProcessor() {};
    ~SoftClipProcessor() {};

    float softClipping(float input, int a); //Declaration of the SoftClip distortion process
    //void setSoftClippingGain(int newClippingGain); //Gain needs to apply the SoftClip distortion
    void setSoftCurve(int newSoftCurve); // Set the SoftClip distortion curve value wanted
    int getSoftCurve();

private:
    //std::atomic<int> softClippingGain = 1;
    std::atomic<int> softCurveValue = 10;
};