/*
  ==============================================================================

    SoftClipProcessor.cpp
    Created: 6 Jan 2023 12:55:22pm
    Author:  Raul

  ==============================================================================
*/

#include "SoftClipProcessor.h"


float SoftClipProcessor::softClipping(float input, int a)
{
    float output = 0;
    if (input > 0)
    {
        output = (a / (a - 1)) * (1 - pow(a, -input));
    }
    else
    {
        output = (a / (a - 1)) * (-1 + pow(a, input));
    }
    return output;
}

//void SoftClipProcessor::setSoftClippingGain(int newClippingGain)
//{
//    softClippingGain = newClippingGain;
//}

void SoftClipProcessor::setSoftCurve(int newSoftCurve)
{
       softCurveValue = newSoftCurve;
}

int SoftClipProcessor::getSoftCurve()
{
    return softCurveValue.load();
}