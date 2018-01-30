/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "filmStrip.h"
#include "BiquadFilter.h"

//==============================================================================
/**
*/
class NuevoEqAudioProcessorEditor  : public AudioProcessorEditor,                                    
                                     public ButtonListener,
                                     public SliderListener,
                                     public LabelListener
{
public:
    NuevoEqAudioProcessorEditor (NuevoEqAudioProcessor&, AudioProcessorValueTreeState&);
    ~NuevoEqAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

    void buttonClicked (Button* buttonThatWasClicked) override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;
    void labelTextChanged (Label* labelThatHasChanged) override;
    
    // Binary resources:
    static const char* baselayer_jpg;
    static const int baselayer_jpgSize;
    static const char* secondlayer_png;
    static const int secondlayer_pngSize;
    static const char* frame_png;
    static const int frame_pngSize;
    static const char* freqKnobFilmstri_png;
    static const int freqKnobFilmstri_pngSize;
    static const char* qknobFilmStrip_png;
    static const int qknobFilmStrip_pngSize;
    static const char* gainFilmStrip_png;
    static const int gainFilmStrip_pngSize;
    
private:
    
    AudioProcessorValueTreeState& valueTreeState;
    
    const String frequencyStringFormat (float newValue);
    
    const String gainStringFormat (float newValue);
    
    const String gainValueStringFormat (float newValue);
    
    const String QStringFormat (float newValue);
    
    void curveCalculation (String Band, String Parameter, float newValue);
    
    void updateCurvePaint();
    
    float* summedCurve;
    
    float* FFTCurve;
    
    BiquadFilter bandOne, bandTwo, bandThree, bandFour, bandFive, bandSix, bandSeven;
    
    typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    typedef AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;
    
    // INPUT/OUTPUT KNOBS
    ScopedPointer<FilmStripKnob> inputGainKnob;
    ScopedPointer<FilmStripKnob> outputGainKnob;
    
    ScopedPointer<Label> outputLevel;
    ScopedPointer<Label> inputLabel;
    
    ScopedPointer<FilmStripKnob> freqKnobBandOne;
    ScopedPointer<FilmStripKnob> freqKnobBandTwo;
    ScopedPointer<FilmStripKnob> freqKnobBandThree;
    ScopedPointer<FilmStripKnob> freqKnobBandFour;
    ScopedPointer<FilmStripKnob> freqKnobBandFive;
    ScopedPointer<FilmStripKnob> freqKnobBandSix;
    ScopedPointer<FilmStripKnob> freqKnobBandSeven;
    
    ScopedPointer<FilmStripKnob> gainKnobBandTwo;
    ScopedPointer<FilmStripKnob> gainKnobBandThree;
    ScopedPointer<FilmStripKnob> gainKnobBandFour;
    ScopedPointer<FilmStripKnob> gainKnobBandFive;
    ScopedPointer<FilmStripKnob> gainKnobBandSix;
    
    ScopedPointer<FilmStripKnob> QKnobBandOne;
    ScopedPointer<FilmStripKnob> QKnobBandTwo;
    ScopedPointer<FilmStripKnob> QKnobBandThree;
    ScopedPointer<FilmStripKnob> QKnobBandFour;
    ScopedPointer<FilmStripKnob> QKnobBandFive;
    ScopedPointer<FilmStripKnob> QKnobBandSix;
    ScopedPointer<FilmStripKnob> QKnobBandSeven;
    
    ScopedPointer<ToggleButton> bandOneToggle;
    ScopedPointer<ToggleButton> bandTwoToggle;
    ScopedPointer<ToggleButton> bandThreeToggle;
    ScopedPointer<ToggleButton> bandFourToggle;
    ScopedPointer<ToggleButton> bandFiveToggle;
    ScopedPointer<ToggleButton> bandSixToggle;
    ScopedPointer<ToggleButton> bandSevenToggle;
    
    ScopedPointer<Label> bandOneFreqLabel;
    ScopedPointer<Label> bandTwoFreqLabel;
    ScopedPointer<Label> bandThreeFreqLabel;
    ScopedPointer<Label> bandFourFreqLabel;
    ScopedPointer<Label> bandFiveFreqLabel;
    ScopedPointer<Label> bandSixFreqLabel;
    ScopedPointer<Label> bandSevenFreqLabel;
    ScopedPointer<Label> bandOneQLabel;
    
    ScopedPointer<ToggleButton> midSideToggle;
    ScopedPointer<TextButton> midSideButton;
    
    ScopedPointer<Label> bandTwoQLabel;
    ScopedPointer<Label> bandThreeQLabel;
    ScopedPointer<Label> bandFourQLabel;
    ScopedPointer<Label> bandFiveQLabel;
    ScopedPointer<Label> gainSixQLabel;
    ScopedPointer<Label> bandSevenQLabel;

    ScopedPointer<Label> gainTwoLabel;
    ScopedPointer<Label> gainThreeLabel;
    ScopedPointer<Label> gainFourLabel;
    ScopedPointer<Label> gainFiveLabel;
    ScopedPointer<Label> bandSixQLabel;
    
    Image cachedImage_baselayer_jpg_1;
    Image cachedImage_frame_png_2;
    Image cachedImage_secondlayer_png_3;
    
    Image cachedImage_knobGain;
    Image cachedImage_knobFreq;
    Image cachedImage_knobQ;
    
    ScopedPointer<SliderAttachment> inputGainAttachment;
    ScopedPointer<SliderAttachment> outputGainAttachment;
    
    ScopedPointer<ButtonAttachment> bandOneToggleAttachment;
    ScopedPointer<SliderAttachment> bandOneFrequencyAttachment;
    ScopedPointer<SliderAttachment> bandOneQAttachment;
    
    ScopedPointer<ButtonAttachment> bandTwoToggleAttachment;
    ScopedPointer<SliderAttachment> bandTwoFrequencyAttachment;
    ScopedPointer<SliderAttachment> bandTwoQAttachment;
    ScopedPointer<SliderAttachment> bandTwoGainAttachment;
    
    ScopedPointer<ButtonAttachment> bandThreeToggleAttachment;
    ScopedPointer<SliderAttachment> bandThreeFrequencyAttachment;
    ScopedPointer<SliderAttachment> bandThreeQAttachment;
    ScopedPointer<SliderAttachment> bandThreeGainAttachment;
    
    ScopedPointer<ButtonAttachment> bandFourToggleAttachment;
    ScopedPointer<SliderAttachment> bandFourFrequencyAttachment;
    ScopedPointer<SliderAttachment> bandFourQAttachment;
    ScopedPointer<SliderAttachment> bandFourGainAttachment;
    
    ScopedPointer<ButtonAttachment> bandFiveToggleAttachment;
    ScopedPointer<SliderAttachment> bandFiveFrequencyAttachment;
    ScopedPointer<SliderAttachment> bandFiveQAttachment;
    ScopedPointer<SliderAttachment> bandFiveGainAttachment;
    
    ScopedPointer<ButtonAttachment> bandSixToggleAttachment;
    ScopedPointer<SliderAttachment> bandSixFrequencyAttachment;
    ScopedPointer<SliderAttachment> bandSixQAttachment;
    ScopedPointer<SliderAttachment> bandSixGainAttachment;
    
    ScopedPointer<ButtonAttachment> bandSevenToggleAttachment;
    ScopedPointer<SliderAttachment> bandSevenFrequencyAttachment;
    ScopedPointer<SliderAttachment> bandSevenQAttachment;
    
    ScopedPointer<ButtonAttachment> midSideActiveAttachment;
    ScopedPointer<ButtonAttachment> midSideAttachment;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    NuevoEqAudioProcessor& processor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NuevoEqAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED
