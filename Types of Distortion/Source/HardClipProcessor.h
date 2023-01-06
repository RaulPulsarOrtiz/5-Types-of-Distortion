/*
  ==============================================================================

    HardClipProcessor.h
    Created: 6 Jan 2023 11:57:45am
    Author:  Raul

  ==============================================================================
*/

#pragma once

class HardClipProcessor
{
public:
	HardClipProcessor() {};
	~HardClipProcessor() {};

	float hardClipping(float input); //Declaration of the HardClip distortion process
	void setClippingGain(int newClippingGain);
	int getClippingGain();
	
private:
	int clippingGain = 1;
};
