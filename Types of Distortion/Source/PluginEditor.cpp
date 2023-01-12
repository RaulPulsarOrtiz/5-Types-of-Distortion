/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TypesofDistortionAudioProcessorEditor::TypesofDistortionAudioProcessorEditor(TypesofDistortionAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(647, 400);

    hardClipGUI.setHardClip(audioProcessor.getHardClip());
    softClipGUI.setSoftClip(audioProcessor.getSoftClip());
   //No GUI for QuarterCicle?
    asymmetricalGUI.setAsymmetrical(audioProcessor.getAsymmetrical());

    distortionTypeMenu.addItem("Off", 1);
    distortionTypeMenu.addItem("Hard Clipping", 2);
    distortionTypeMenu.addItem("Soft Clipping", 3);
    distortionTypeMenu.addItem("Quarter Circle", 4);
    distortionTypeMenu.addItem("Asymmetrical", 5);
    distortionTypeMenu.setText("Distortion Type", dontSendNotification);
    distortionTypeMenu.addListener(this);
    addAndMakeVisible(distortionTypeMenu);
   
    addAndMakeVisible(hardClipGUI);
    addAndMakeVisible(softClipGUI);
    //QuarterCicle
    addAndMakeVisible(asymmetricalGUI);

    outputGainSldr.setSliderStyle(Slider::Rotary);
    outputGainSldr.setRange(0.f, 2.5f);
    outputGainSldr.setValue(1.f);
    outputGainSldr.setTextBoxStyle(Slider::TextBoxAbove, true, 60, 15);
    //outputGainSldr.mouseDoubleClick(MouseEvent mouse);
    outputGainSldr.addListener(this);
    addAndMakeVisible(outputGainSldr);

    
    cutoffSldr.setSliderStyle(Slider::Rotary);
    cutoffSldr.setRange(20, 20000, 1);
    cutoffSldr.setValue(20000);
    cutoffSldr.setTextBoxStyle(Slider::TextBoxAbove, true, 60, 15);
    //cutoffSldr.mouseDoubleClick(MouseEvent mouse);
    cutoffSldr.setTextValueSuffix("Hz");
    cutoffSldr.addListener(this);
    addAndMakeVisible(cutoffSldr);

    dryWetSldr.setSliderStyle(Slider::Rotary);
    dryWetSldr.setRange(0, 100, 1);
    dryWetSldr.setValue(100);
    dryWetSldr.setTextBoxStyle(Slider::TextBoxAbove, true, 40, 15);
    //cutoffSldr.mouseDoubleClick(MouseEvent mouse);
    dryWetSldr.setTextValueSuffix("%");
    dryWetSldr.addListener(this);
    addAndMakeVisible(dryWetSldr);

    outputGainText.setText("Output Gain", dontSendNotification);
    outputGainText.setColour(Label::ColourIds::outlineColourId, Colours::wheat);
    addAndMakeVisible(outputGainText);
    
    filterTypeMenu.addItem("LPF", 1);
    filterTypeMenu.addItem("HPF", 2);
    filterTypeMenu.setText("Filter Type:", dontSendNotification);
    filterTypeMenu.addListener(this);
    addAndMakeVisible(filterTypeMenu);

    cutoffText.setText("Cutoff Freq", dontSendNotification);
    cutoffText.setColour(Label::ColourIds::outlineColourId, Colours::wheat);
    addAndMakeVisible(cutoffText);

    dryWetText.setText("Dry/Wet", dontSendNotification);
    dryWetText.setColour(Label::ColourIds::outlineColourId, Colours::wheat);
    addAndMakeVisible(dryWetText);
}

TypesofDistortionAudioProcessorEditor::~TypesofDistortionAudioProcessorEditor()
{
}

//==============================================================================
void TypesofDistortionAudioProcessorEditor::paint(juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

}

juce::Rectangle<int> TypesofDistortionAudioProcessorEditor::getWorkingArea()
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

juce::Rectangle<int> TypesofDistortionAudioProcessorEditor::getAnalyserArea()
{
    auto analyserAreaHeight = 300;
    auto analyserAreaWidth = 300;
    auto analyserArea = getWorkingArea().removeFromTop(analyserAreaHeight);
    analyserArea = getWorkingArea().removeFromTop(analyserAreaWidth);
    return analyserArea;
}

juce::Rectangle<int> TypesofDistortionAudioProcessorEditor::getKnobsArea()
{
    auto knobsAreaHeight = 170;
    auto knobsArea = getWorkingArea().removeFromBottom(knobsAreaHeight);
  
    return knobsArea;
}

void TypesofDistortionAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    auto area = getWorkingArea();
    auto knobsArea = getKnobsArea();
    auto analyserArea = getAnalyserArea();
    auto menuArea = analyserArea.removeFromLeft(130);
    menuArea = menuArea.removeFromTop(40);

    hardClipGUI.setBounds(knobsArea.removeFromLeft(150));
    softClipGUI.setBounds(knobsArea.removeFromLeft(150));
    asymmetricalGUI.setBounds(knobsArea.removeFromLeft(150));
    outputGainSldr.setBounds(knobsArea.removeFromLeft(150));
    outputGainSldr.setSize(100, 100);
  
    Rectangle <int> outputSldrPos = outputGainSldr.getBounds();
    int outPosX = outputSldrPos.getCentreX();
    int outPosY = outputSldrPos.getCentreY();
    outputGainText.setBounds((outPosX - 40), (outPosY + 50), 80, 15);

    distortionTypeMenu.setBounds(menuArea);
       
    cutoffSldr.setBounds(analyserArea.removeFromRight(100));
    cutoffSldr.setSize(100, 100);
    Rectangle <int> cutoffSldrPos = cutoffSldr.getBounds();
    int cutPosX = cutoffSldrPos.getCentreX();
    int cutPosY = cutoffSldrPos.getCentreY();
    cutoffText.setBounds((cutPosX - 40), (cutPosY + 50), 80, 15);

    filterTypeMenu.setBounds(analyserArea.removeFromRight(100));
    filterTypeMenu.setSize(100, 40);

    dryWetSldr.setBounds(analyserArea.removeFromTop(100));
   
    Rectangle <int> dryWetSldrPos = dryWetSldr.getBounds();
    int dryPosX = dryWetSldrPos.getCentreX();
    int dryPosY = dryWetSldrPos.getCentreY();
    dryWetText.setBounds((dryPosX - 30), (dryPosY + 50), 60, 15);
}

void TypesofDistortionAudioProcessorEditor::sliderValueChanged(Slider* slider)
{

    if (slider == &outputGainSldr)
    {
        audioProcessor.setOutputGain(outputGainSldr.getValue());
    }
    
    else if (slider == &cutoffSldr)
    {
        audioProcessor.setFilterFreqCutoff(cutoffSldr.getValue());
    }
    
    else if (slider == &dryWetSldr)
    {
        audioProcessor.setDryWetAmount(dryWetSldr.getValue());
    }
}

void TypesofDistortionAudioProcessorEditor::comboBoxChanged(ComboBox* comboBoxThatHasChanged)
{
    if (comboBoxThatHasChanged == &distortionTypeMenu)
    {
        if (distortionTypeMenu.getSelectedId() == 1) //Off
        {
            audioProcessor.setDistortionType(audioProcessor.Off);
            softClipGUI.softCurveSldr.setVisible(false);
            softClipGUI.softCurveText.setVisible(false);
            asymmetricalGUI.asymVariableSldr.setVisible(false);
            asymmetricalGUI.asymVariableText.setVisible(false);
        }

        else if (distortionTypeMenu.getSelectedId() == 2) //HardClipping
        {
            audioProcessor.setDistortionType(audioProcessor.HardClipType);
            softClipGUI.softCurveSldr.setVisible(false);
            softClipGUI.softCurveText.setVisible(false);
            asymmetricalGUI.asymVariableSldr.setVisible(false);
            asymmetricalGUI.asymVariableText.setVisible(false);
        }

        else if (distortionTypeMenu.getSelectedId() == 3) //SoftClipping
        {
            audioProcessor.setDistortionType(audioProcessor.SoftClipType); 
            softClipGUI.softCurveSldr.setVisible(true);
            softClipGUI.softCurveText.setVisible(true);
            asymmetricalGUI.asymVariableSldr.setVisible(false);
            asymmetricalGUI.asymVariableText.setVisible(false);
        }

        else if (distortionTypeMenu.getSelectedId() == 4) //QuarterCicle
        {
            audioProcessor.setDistortionType(audioProcessor.QuarterCicleType);
            softClipGUI.softCurveSldr.setVisible(false);
            softClipGUI.softCurveText.setVisible(false);
            asymmetricalGUI.asymVariableSldr.setVisible(false);
            asymmetricalGUI.asymVariableText.setVisible(false);
        }
       
        else if (distortionTypeMenu.getSelectedId() == 5) //Asymmetrical
        {
            audioProcessor.setDistortionType(audioProcessor.AsymmetricType);
            asymmetricalGUI.asymVariableSldr.setVisible(true);
            asymmetricalGUI.asymVariableText.setVisible(true);
            softClipGUI.softCurveSldr.setVisible(false);
            softClipGUI.softCurveText.setVisible(false);
        }
    }
    if (comboBoxThatHasChanged == &filterTypeMenu)
    {
        if (filterTypeMenu.getSelectedId() == 1) //LPF
        {
            audioProcessor.setFilterType(audioProcessor.LowPass);
            cutoffSldr.setValue(20000);
        }

        else if (filterTypeMenu.getSelectedId() == 2) //HPF
        {
            audioProcessor.setFilterType(audioProcessor.HighPass);
            cutoffSldr.setValue(20);
        }
    }
}

void TypesofDistortionAudioProcessorEditor::mouseDoubleClick(const MouseEvent& event) //Doesnt Work
{
   // clippingGainSldr.setValue(1);
   // softCurveSldr.setValue(10);
   // asymVariableSldr.setValue(1.f);
   // outputGainSldr.setValue(1.f);
}