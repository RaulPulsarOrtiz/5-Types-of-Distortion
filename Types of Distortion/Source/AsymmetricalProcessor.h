/*
  ==============================================================================

    AsymmetricalProcessor.h
    Created: 6 Jan 2023 2:42:01pm
    Author:  Raul

  ==============================================================================
*/

#pragma once
#include <atomic>

class AsymmetricalProcessor
{
public:
    AsymmetricalProcessor() {};
    ~AsymmetricalProcessor() {};

    float asymmetrical(float input, float c);
    void setAsymVariable(float newAsymVariableValue);
    float getAsymVariable();

private:
    std::atomic<float> asymVariableValue = 1.f;
};