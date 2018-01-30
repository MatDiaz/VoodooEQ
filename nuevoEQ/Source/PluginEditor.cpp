/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "ImageHolder.h"
#include <string>


//==============================================================================
NuevoEqAudioProcessorEditor::NuevoEqAudioProcessorEditor (NuevoEqAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), valueTreeState (vts), processor (p)
{
    summedCurve = new float [890];
    
    memset (summedCurve, 0, 890 * sizeof (float));
    
    float sampleRate = 44100;
    // Band One
    bandOne.initBiquad ((float) sampleRate, true);
    bandOne.Frequency = 120.0f;
    bandOne.Q = 0.7;
    bandOne.highPassCoeff();
    bandOne.createCurve();
    
    // Band Two
    bandTwo.initBiquad ((float) sampleRate, true);
    bandTwo.Frequency = 100.0f;
    bandTwo.Q = 1.0f;
    bandTwo.Gain = 0.0f;
    bandTwo.peakingCoeff();
    bandTwo.createCurve();
    
    // Band Three
    bandThree.initBiquad ((float) sampleRate, true);
    bandThree.Frequency = 200.0f;
    bandThree.Q = 1.0f;
    bandThree.Gain = 0.0f;
    bandThree.peakingCoeff();
    bandThree.createCurve();
    
    // Band Four
    bandFour.initBiquad ((float) sampleRate, true);
    bandFour.Frequency = 1000.0f;
    bandFour.Q = 1.0f;
    bandFour.Gain = 0.0f;
    bandFour.peakingCoeff();
    bandFour.createCurve();
    
    // Band Five
    bandFive.initBiquad ((float) sampleRate, true);
    bandFive.Frequency = 2000.0f;
    bandFive.Q = 1.0f;
    bandFive.Gain = 0.0f;
    bandFive.peakingCoeff();
    bandFive.createCurve();
    
    // Band Six
    bandSix.initBiquad ((float) sampleRate, true);
    bandSix.Frequency = 6000.0f;
    bandSix.Q = 1.0f;
    bandSix.Gain = 0.0f;
    bandSix.peakingCoeff();
    bandSix.createCurve();
    
    // Band Seven
    bandSeven.initBiquad ((float) sampleRate, true);
    bandSeven.Frequency = 16000.0;
    bandSeven.Q = 0.7;
    bandSeven.lowPassCoeff();
    bandSeven.createCurve();
    // ================================================================================================
    
    // Frequency Knob
    cachedImage_knobFreq = ImageCache::getFromMemory (freqKnobFilmstri_png, freqKnobFilmstri_pngSize);
    
    // Q Knob
    cachedImage_knobQ = ImageCache::getFromMemory (qknobFilmStrip_png, qknobFilmStrip_pngSize);
    
    // Gain Knob
    cachedImage_knobGain = ImageCache::getFromMemory (gainFilmStrip_png, gainFilmStrip_pngSize);
    
    // Input Gain Label
    addAndMakeVisible (inputLabel = new Label ("inputLabel",
                                               TRANS("0 dB\n")));
    inputLabel->setFont (Font ("Helvetica Neue", 12.00f, Font::plain));
    inputLabel->setJustificationType (Justification::centred);
    inputLabel->setColour (Label::textColourId, Colour (0xff858585));
    inputLabel->setColour (TextEditor::textColourId, Colours::black);
    inputLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    inputLabel->setColour (TextEditor::textColourId, Colours::white);
    inputLabel->setEditable (false, true, false);
    inputLabel->addListener (this);
    
    // Output Gain Label
    addAndMakeVisible (outputLevel = new Label ("outputLevel",
                                                TRANS("0 dB")));
    outputLevel->setFont (Font ("Helvetica Neue", 12.00f, Font::plain));
    outputLevel->setJustificationType (Justification::centred);
    outputLevel->setEditable (false, false, false);
    outputLevel->setColour (Label::textColourId, Colour (0xff858585));
    outputLevel->setColour (TextEditor::textColourId, Colours::black);
    outputLevel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    outputLevel->setColour (TextEditor::textColourId, Colours::white);
    outputLevel->setEditable (false, true, false);
    outputLevel->addListener (this);
    
    // Mid Side Toggle
    addAndMakeVisible (midSideToggle = new ToggleButton ("midSideToggle"));
    midSideToggle->setButtonText (String());
    midSideToggle->addListener (this);
    midSideToggle->setColour (ToggleButton::textColourId, Colours::white);
    
    // Mid Side Button
    addAndMakeVisible (midSideButton = new TextButton ("midSideButton"));
    midSideButton->setButtonText (TRANS("Mid"));
    midSideButton->addListener (this);
    midSideButton->setColour (TextButton::buttonColourId, Colour (0xff545151));
    midSideButton->setColour (TextButton::buttonOnColourId, Colour (0xffa3a3a3));
    midSideButton->setColour (TextButton::textColourOffId, Colours::white);
    midSideButton->setEnabled(false);
    midSideButton->setClickingTogglesState(true);
    
    // Band One Frequency Label
    addAndMakeVisible (bandOneFreqLabel = new Label ("bandOneFreqLabel",
                                                     TRANS("20 Hz\n")));
    bandOneFreqLabel->setFont (Font ("Helvetica Neue", 11.00f, Font::plain));
    bandOneFreqLabel->setJustificationType (Justification::centred);
    bandOneFreqLabel->setEditable (false, false, false);
    bandOneFreqLabel->setColour (Label::textColourId, Colour (0xff858585));
    bandOneFreqLabel->setColour (TextEditor::textColourId, Colours::black);
    bandOneFreqLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    bandOneFreqLabel->setColour (TextEditor::textColourId, Colours::white);
    bandOneFreqLabel->setEditable (false, true, false);
    bandOneFreqLabel->addListener (this);
    
    // Band Two Frequency Label
    addAndMakeVisible (bandTwoFreqLabel = new Label ("bandTwoFreqLabel",
                                                     TRANS("100 Hz\n")));
    bandTwoFreqLabel->setFont (Font ("Helvetica Neue", 11.00f, Font::plain));
    bandTwoFreqLabel->setJustificationType (Justification::centred);
    bandTwoFreqLabel->setEditable (false, false, false);
    bandTwoFreqLabel->setColour (Label::textColourId, Colour (0xff858585));
    bandTwoFreqLabel->setColour (TextEditor::textColourId, Colour (0xff615f5f));
    bandTwoFreqLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    bandTwoFreqLabel->setColour (TextEditor::textColourId, Colours::white);
    bandTwoFreqLabel->setEditable (false, true, false);
    bandTwoFreqLabel->addListener (this);
    
    // Band Three Frequency Label
    addAndMakeVisible (bandThreeFreqLabel = new Label ("bandThreeFreqLabel",
                                                       TRANS("200 Hz\n")));
    bandThreeFreqLabel->setFont (Font ("Helvetica Neue", 11.00f, Font::plain));
    bandThreeFreqLabel->setJustificationType (Justification::centred);
    bandThreeFreqLabel->setEditable (false, false, false);
    bandThreeFreqLabel->setColour (Label::textColourId, Colour (0xff858585));
    bandThreeFreqLabel->setColour (TextEditor::textColourId, Colours::black);
    bandThreeFreqLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    bandThreeFreqLabel->setColour (TextEditor::textColourId, Colours::white);
    bandThreeFreqLabel->setEditable (false, true, false);
    bandThreeFreqLabel->addListener (this);
    
    // Band Four Frequency Label
    addAndMakeVisible (bandFourFreqLabel = new Label ("bandFourFreqLabel",
                                                      TRANS("1000 Hz\n")));
    bandFourFreqLabel->setFont (Font (11.00f, Font::plain));
    bandFourFreqLabel->setJustificationType (Justification::centred);
    bandFourFreqLabel->setEditable (false, false, false);
    bandFourFreqLabel->setColour (Label::textColourId, Colour (0xff858585));
    bandFourFreqLabel->setColour (TextEditor::textColourId, Colours::black);
    bandFourFreqLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    bandFourFreqLabel->setColour (TextEditor::textColourId, Colours::white);
    bandFourFreqLabel->setEditable (false, true, false);
    bandFourFreqLabel->addListener (this);
    
    // Band Five Frequency Label
    addAndMakeVisible (bandFiveFreqLabel = new Label ("bandFiveFreqLabel",
                                                      TRANS("2000 Hz\n")));
    bandFiveFreqLabel->setFont (Font (11.00f, Font::plain));
    bandFiveFreqLabel->setJustificationType (Justification::centred);
    bandFiveFreqLabel->setEditable (false, false, false);
    bandFiveFreqLabel->setColour (Label::textColourId, Colour (0xff858585));
    bandFiveFreqLabel->setColour (TextEditor::textColourId, Colours::black);
    bandFiveFreqLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    bandFiveFreqLabel->setColour (TextEditor::textColourId, Colours::white);
    bandFiveFreqLabel->setEditable (false, true, false);
    bandFiveFreqLabel->addListener (this);
    
    // Band Six Frequency Label
    addAndMakeVisible (bandSixFreqLabel = new Label ("bandSixFreqLabel",
                                                     TRANS("6000 Hz\n")));
    bandSixFreqLabel->setFont (Font (11.00f, Font::plain));
    bandSixFreqLabel->setJustificationType (Justification::centred);
    bandSixFreqLabel->setEditable (false, false, false);
    bandSixFreqLabel->setColour (Label::textColourId, Colour (0xff858585));
    bandSixFreqLabel->setColour (TextEditor::textColourId, Colours::black);
    bandSixFreqLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    bandSixFreqLabel->setColour (TextEditor::textColourId, Colours::white);
    bandSixFreqLabel->setEditable (false, true, false);
    bandSixFreqLabel->addListener (this);
    
    // Band Seven Frequency Label
    addAndMakeVisible (bandSevenFreqLabel = new Label ("bandSevenFreqLabel",
                                                       TRANS("20 kHz\n")));
    bandSevenFreqLabel->setFont (Font (11.00f, Font::plain));
    bandSevenFreqLabel->setJustificationType (Justification::centred);
    bandSevenFreqLabel->setEditable (false, false, false);
    bandSevenFreqLabel->setColour (Label::textColourId, Colour (0xff858585));
    bandSevenFreqLabel->setColour (TextEditor::textColourId, Colours::black);
    bandSevenFreqLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    bandSevenFreqLabel->setColour (TextEditor::textColourId, Colours::white);
    bandSevenFreqLabel->setEditable (false, true, false);
    bandSevenFreqLabel->addListener (this);
    
    // Band One Q Label
    addAndMakeVisible (bandOneQLabel = new Label ("bandOneQLabel",
                                                  TRANS("0.1")));
    bandOneQLabel->setFont (Font ("Helvetica Neue", 11.00f, Font::plain));
    bandOneQLabel->setJustificationType (Justification::centred);
    bandOneQLabel->setEditable (false, false, false);
    bandOneQLabel->setColour (Label::textColourId, Colour (0xff858585));
    bandOneQLabel->setColour (TextEditor::textColourId, Colours::black);
    bandOneQLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    bandOneQLabel->setColour (TextEditor::textColourId, Colours::white);
    bandOneQLabel->setEditable (false, true, false);
    bandOneQLabel->addListener (this);
    
     // Band Two Q Label
    addAndMakeVisible (bandTwoQLabel = new Label ("bandTwoQLabel",
                                                  TRANS("0")));
    bandTwoQLabel->setFont (Font ("Helvetica Neue", 11.00f, Font::plain));
    bandTwoQLabel->setJustificationType (Justification::centred);
    bandTwoQLabel->setEditable (false, false, false);
    bandTwoQLabel->setColour (Label::textColourId, Colour (0xff858585));
    bandTwoQLabel->setColour (TextEditor::textColourId, Colours::black);
    bandTwoQLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    bandTwoQLabel->setColour (TextEditor::textColourId, Colours::white);
    bandTwoQLabel->setEditable (false, true, false);
    bandTwoQLabel->addListener (this);
    
    // Band Three Q Label
    addAndMakeVisible (bandThreeQLabel = new Label ("bandThreeQLabel",
                                                    TRANS("0")));
    bandThreeQLabel->setFont (Font (11.00f, Font::plain));
    bandThreeQLabel->setJustificationType (Justification::centred);
    bandThreeQLabel->setEditable (false, false, false);
    bandThreeQLabel->setColour (Label::textColourId, Colour (0xff858585));
    bandThreeQLabel->setColour (TextEditor::textColourId, Colours::black);
    bandThreeQLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    bandThreeQLabel->setColour (TextEditor::textColourId, Colours::white);
    bandThreeQLabel->setEditable (false, true, false);
    bandThreeQLabel->addListener (this);
    
    // Band Four Q Label
    addAndMakeVisible (bandFourQLabel = new Label ("bandFourQLabel",
                                                   TRANS("0")));
    bandFourQLabel->setFont (Font (11.00f, Font::plain));
    bandFourQLabel->setJustificationType (Justification::centred);
    bandFourQLabel->setEditable (false, false, false);
    bandFourQLabel->setColour (Label::textColourId, Colour (0xff858585));
    bandFourQLabel->setColour (TextEditor::textColourId, Colours::black);
    bandFourQLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    bandFourQLabel->setColour (TextEditor::textColourId, Colours::white);
    bandFourQLabel->setEditable (false, true, false);
    bandFourQLabel->addListener (this);
    
    // Band Five Q Label
    addAndMakeVisible (bandFiveQLabel = new Label ("bandFiveQLabel",
                                                   TRANS("0")));
    bandFiveQLabel->setFont (Font (11.00f, Font::plain));
    bandFiveQLabel->setJustificationType (Justification::centred);
    bandFiveQLabel->setEditable (false, false, false);
    bandFiveQLabel->setColour (Label::textColourId, Colour (0xff858585));
    bandFiveQLabel->setColour (TextEditor::textColourId, Colours::black);
    bandFiveQLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    bandFiveQLabel->setColour (TextEditor::textColourId, Colours::white);
    bandFiveQLabel->setEditable (false, true, false);
    bandFiveQLabel->addListener (this);

    // Band Six Q Label
    addAndMakeVisible (gainSixQLabel = new Label ("gainSixQLabel",
                                                  TRANS("0")));
    gainSixQLabel->setFont (Font (11.00f, Font::plain));
    gainSixQLabel->setJustificationType (Justification::centred);
    gainSixQLabel->setColour (Label::textColourId, Colour (0xff858585));
    gainSixQLabel->setColour (TextEditor::textColourId, Colours::black);
    gainSixQLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    gainSixQLabel->setColour (TextEditor::textColourId, Colours::white);
    gainSixQLabel->setEditable (false, true, false);
    gainSixQLabel->addListener (this);
    
    // Band Seven Q Label
    addAndMakeVisible (bandSevenQLabel = new Label ("bandSevenQLabel",
                                                    TRANS("0")));
    bandSevenQLabel->setFont (Font (11.00f, Font::plain));
    bandSevenQLabel->setJustificationType (Justification::centred);
    bandSevenQLabel->setEditable (false, false, false);
    bandSevenQLabel->setColour (Label::textColourId, Colour (0xff858585));
    bandSevenQLabel->setColour (TextEditor::textColourId, Colours::black);
    bandSevenQLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    bandSevenQLabel->setColour (TextEditor::textColourId, Colours::white);
    bandSevenQLabel->setEditable (false, true, false);
    bandSevenQLabel->addListener (this);

    // Band Two Gain Label
    addAndMakeVisible (gainTwoLabel = new Label ("gainTwoLabel",
                                                 TRANS("0 dB\n")));
    gainTwoLabel->setFont (Font ("Helvetica Neue", 11.00f, Font::plain));
    gainTwoLabel->setJustificationType (Justification::centred);
    gainTwoLabel->setColour (Label::textColourId, Colour (0xff858585));
    gainTwoLabel->setColour (TextEditor::textColourId, Colour (0xff858585));
    gainTwoLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    gainTwoLabel->setColour (TextEditor::textColourId, Colours::white);
    gainTwoLabel->setEditable (false, true, false);
    gainTwoLabel->addListener (this);
    
    // Band Three Gain Label
    addAndMakeVisible (gainThreeLabel = new Label ("gainThreeLabel",
                                                   TRANS("0 dB\n")));
    gainThreeLabel->setFont (Font (11.00f, Font::plain));
    gainThreeLabel->setJustificationType (Justification::centred);
    gainThreeLabel->setColour (Label::textColourId, Colour (0xff858585));
    gainThreeLabel->setColour (TextEditor::textColourId, Colours::black);
    gainThreeLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    gainThreeLabel->setColour (TextEditor::textColourId, Colours::white);
    gainThreeLabel->setEditable (false, true, false);
    gainThreeLabel->addListener (this);
    
    // Band Four Gain Label
    addAndMakeVisible (gainFourLabel = new Label ("gainFourLabel",
                                                  TRANS("0 dB\n")));
    gainFourLabel->setFont (Font (11.00f, Font::plain));
    gainFourLabel->setJustificationType (Justification::centred);
    gainFourLabel->setColour (Label::textColourId, Colour (0xff858585));
    gainFourLabel->setColour (TextEditor::textColourId, Colours::black);
    gainFourLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    gainFourLabel->setColour (TextEditor::textColourId, Colours::white);
    gainFourLabel->setEditable (false, true, false);
    gainFourLabel->addListener (this);
    
    // Band Five Gain Label
    addAndMakeVisible (gainFiveLabel = new Label ("gainFiveLabel",
                                                  TRANS("0 dB\n")));
    gainFiveLabel->setFont (Font (11.00f, Font::plain));
    gainFiveLabel->setJustificationType (Justification::centred);
    gainFiveLabel->setColour (Label::textColourId, Colour (0xff858585));
    gainFiveLabel->setColour (TextEditor::textColourId, Colours::black);
    gainFiveLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    gainFiveLabel->setColour (TextEditor::textColourId, Colours::white);
    gainFiveLabel->setEditable (false, true, false);
    gainFiveLabel->addListener (this);
    
    // Band Six Gain Label
    addAndMakeVisible (bandSixQLabel = new Label ("bandSixQLabel",
                                                  TRANS("0 dB")));
    bandSixQLabel->setFont (Font (11.00f, Font::plain));
    bandSixQLabel->setJustificationType (Justification::centred);
    bandSixQLabel->setColour (Label::textColourId, Colour (0xff858585));
    bandSixQLabel->setColour (TextEditor::textColourId, Colours::black);
    bandSixQLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    bandSixQLabel->setColour (TextEditor::textColourId, Colours::white);
    bandSixQLabel->setEditable (false, true, false);
    bandSixQLabel->addListener (this);
    

    cachedImage_baselayer_jpg_1 = ImageCache::getFromMemory (baselayer_jpg, baselayer_jpgSize);
    cachedImage_frame_png_2 = ImageCache::getFromMemory (frame_png, frame_pngSize);
    cachedImage_secondlayer_png_3 = ImageCache::getFromMemory (secondlayer_png, secondlayer_pngSize);
    
    // ================================================================================================
    
    // Band One Toggle
    addAndMakeVisible (bandOneToggle = new ToggleButton ("bandOneToggle"));
    bandOneToggle->setButtonText (String());
    bandOneToggle->addListener (this);
    bandOneToggle->setToggleState (false, dontSendNotification);
    
    // Band Two Toggle
    addAndMakeVisible (bandTwoToggle = new ToggleButton ("bandTwoToggle"));
    bandTwoToggle->setButtonText (String());
    bandTwoToggle->addListener (this);
    bandTwoToggle->setToggleState (true, dontSendNotification);
    
    // Band Three Toggle
    addAndMakeVisible (bandThreeToggle = new ToggleButton ("bandThreeToggle"));
    bandThreeToggle->setButtonText (String());
    bandThreeToggle->addListener (this);
    bandThreeToggle->setToggleState (true, dontSendNotification);
    
    // Band Five Toggle
    addAndMakeVisible (bandFiveToggle = new ToggleButton ("bandFiveToggle"));
    bandFiveToggle->setButtonText (String());
    bandFiveToggle->addListener (this);
    bandFiveToggle->setToggleState (true, dontSendNotification);
    
    // Band Seven Toggle
    addAndMakeVisible (bandSevenToggle = new ToggleButton ("bandSevenToggle"));
    bandSevenToggle->setButtonText (String());
    bandSevenToggle->addListener (this);
    bandSevenToggle->setToggleState (false, dontSendNotification);

    // Band Six Toggle
    addAndMakeVisible (bandSixToggle = new ToggleButton ("bandSixToggle"));
    bandSixToggle->setButtonText (String());
    bandSixToggle->addListener (this);
    bandSixToggle->setToggleState (true, dontSendNotification);
    
    // Band Four Toggle
    addAndMakeVisible (bandFourToggle = new ToggleButton ("bandFourToggle"));
    bandFourToggle->setButtonText (String());
    bandFourToggle->addListener (this);
    bandFourToggle->setToggleState (true, dontSendNotification);
    
    // Toggle Attachments
    bandOneToggleAttachment = new ButtonAttachment (valueTreeState, "bandOneToggle", *bandOneToggle);
    bandTwoToggleAttachment = new ButtonAttachment (valueTreeState, "bandTwoToggle", *bandTwoToggle);
    bandThreeToggleAttachment = new ButtonAttachment (valueTreeState, "bandThreeToggle", *bandThreeToggle);
    bandFourToggleAttachment = new ButtonAttachment (valueTreeState, "bandFourToggle", *bandFourToggle);
    bandFiveToggleAttachment = new ButtonAttachment (valueTreeState, "bandFiveToggle", *bandFiveToggle);
    bandSixToggleAttachment = new ButtonAttachment (valueTreeState, "bandSixToggle", *bandSixToggle);
    bandSevenToggleAttachment = new ButtonAttachment (valueTreeState, "bandSevenToggle", *bandSevenToggle);
    
    
    // ================================================================================================
    
    // Input Gain Knob
    addAndMakeVisible (inputGainKnob = new FilmStripKnob (cachedImage_knobGain, 45, true));
    inputGainKnob->setRange (0.0001f, 2.0f, 0);
    inputGainKnob->setSkewFactorFromMidPoint(1.0f);
    inputGainKnob->setValue (1.0f);
    inputGainKnob->addListener(this);
    
    // Output Gain Knob
    addAndMakeVisible (outputGainKnob = new FilmStripKnob (cachedImage_knobGain, 45, true));
    outputGainKnob->setRange(0.0001f, 2.0f, 0);
    outputGainKnob->setSkewFactorFromMidPoint(1.0f);
    outputGainKnob->addListener(this);

    inputGainAttachment = new SliderAttachment (valueTreeState, "inputGain", *inputGainKnob);
    outputGainAttachment = new SliderAttachment (valueTreeState, "outputGain", *outputGainKnob);
    
    // ================================================================================================
    
    // Frequency Knob Band One
    addAndMakeVisible (freqKnobBandOne = new FilmStripKnob (cachedImage_knobFreq, 45, true));
    freqKnobBandOne->setRange(0.0f, 1.0f, 0); // 20 - 8k - 120 Hz
    freqKnobBandOne->setSkewFactorFromMidPoint(0.01f);
    freqKnobBandOne->addListener(this);
    bandOneFrequencyAttachment = new SliderAttachment (valueTreeState, "bandOneFrequency", *freqKnobBandOne);
    
    // Frequency Knob Band Two
    addAndMakeVisible (freqKnobBandTwo = new FilmStripKnob (cachedImage_knobFreq, 45, true));
    freqKnobBandTwo->setRange(0.0f, 1.0f, 0); // 20 - 500 - 100
    freqKnobBandTwo->setSkewFactorFromMidPoint(0.25f);
    freqKnobBandTwo->addListener(this);
    
    bandTwoFrequencyAttachment = new SliderAttachment (valueTreeState, "bandTwoFrequency", *freqKnobBandTwo);
    
    // Frequency Knob Band Three
    addAndMakeVisible (freqKnobBandThree = new FilmStripKnob (cachedImage_knobFreq, 45, true));
    freqKnobBandThree->setRange(0.0f, 1.0f, 0); // 40 - 1000 - 200
    freqKnobBandThree->setSkewFactorFromMidPoint(0.25f);
    freqKnobBandThree->addListener(this);
    
    bandThreeFrequencyAttachment = new SliderAttachment (valueTreeState, "bandThreeFrequency", *freqKnobBandThree);
    
    // Frequency Knob Band Four
    addAndMakeVisible (freqKnobBandFour = new FilmStripKnob (cachedImage_knobFreq, 45, true));
    freqKnobBandFour->setRange(0.0f, 1.0f, 0); // 125 - 8000 - 1000
    freqKnobBandFour->setSkewFactorFromMidPoint(0.25f);
    freqKnobBandFour->addListener(this);
    
    bandFourFrequencyAttachment = new SliderAttachment (valueTreeState, "bandFourFrequency", *freqKnobBandFour);
    
    // Frequency Knob Band Five
    addAndMakeVisible (freqKnobBandFive = new FilmStripKnob (cachedImage_knobFreq, 45, true));
    freqKnobBandFive->setRange(0.0f, 1.0f, 0); // 200 - 8000  - 2000
    freqKnobBandFive->setSkewFactorFromMidPoint(0.25f);
    freqKnobBandFive->addListener(this);
    
    bandFiveFrequencyAttachment = new SliderAttachment (valueTreeState, "bandFiveFrequency", *freqKnobBandFive);
    
    // Frequency Knob Band Six
    addAndMakeVisible (freqKnobBandSix = new FilmStripKnob (cachedImage_knobFreq, 45, true));
    freqKnobBandSix->setRange(0.0f, 1.0f, 0); // 1800 - 20000 - 6000
    freqKnobBandSix->setSkewFactorFromMidPoint(0.25f);
    freqKnobBandSix->addListener(this);
    
    bandSixFrequencyAttachment = new SliderAttachment (valueTreeState, "bandSixFrequency", *freqKnobBandSix);
    
    // Frequency Knob Band Seven
    addAndMakeVisible (freqKnobBandSeven = new FilmStripKnob (cachedImage_knobFreq, 45, true));
    freqKnobBandSeven->setRange(0.0f, 1.0f, 0); // 120 - 20k
    freqKnobBandSeven->setSkewFactorFromMidPoint(0.25f);
    freqKnobBandSeven->addListener(this);
    
    bandSevenFrequencyAttachment = new SliderAttachment (valueTreeState, "bandSevenFrequency", *freqKnobBandSeven);
    
    // ================================================================================================
    
    // Gain Knob Band Two
    addAndMakeVisible (gainKnobBandTwo = new FilmStripKnob (cachedImage_knobFreq, 45, true));
    gainKnobBandTwo->setRange(-18.0f, 18.0f, 0);
    gainKnobBandTwo->addListener(this);

    // Gain Knob Band Three
    addAndMakeVisible (gainKnobBandThree = new FilmStripKnob (cachedImage_knobFreq, 45, true));
    gainKnobBandThree->setRange(-18.0f, 18.0f, 0);
    gainKnobBandThree->addListener(this);
    
    // Gain Knob Band Four
    addAndMakeVisible (gainKnobBandFour = new FilmStripKnob (cachedImage_knobFreq, 45, true));
    gainKnobBandFour->setRange(-18.0f, 18.0f, 0);
    gainKnobBandFour->addListener(this);
    
    // Gain Knob Band Five
    addAndMakeVisible (gainKnobBandFive = new FilmStripKnob (cachedImage_knobFreq, 45, true));
    gainKnobBandFive->setRange(-18.0f, 18.0f, 0);
    gainKnobBandFive->addListener(this);
    
    // Gain Knob Band Six
    addAndMakeVisible (gainKnobBandSix = new FilmStripKnob (cachedImage_knobFreq, 45, true));
    gainKnobBandSix->setRange(-18.0f, 18.0f, 0);
    gainKnobBandSix->addListener(this);
    
    // Gain Knobs Attachment
    bandTwoGainAttachment = new SliderAttachment (valueTreeState, "bandTwoGain", *gainKnobBandTwo);
    bandThreeGainAttachment = new SliderAttachment (valueTreeState, "bandThreeGain", *gainKnobBandThree);
    bandFourGainAttachment = new SliderAttachment (valueTreeState, "bandFourGain", *gainKnobBandFour);
    bandFiveGainAttachment = new SliderAttachment (valueTreeState, "bandFiveGain", *gainKnobBandFive);
    bandSixGainAttachment = new SliderAttachment (valueTreeState, "bandSixGain", *gainKnobBandSix);
    
    // ================================================================================================
    
    // Q Knob Band One
    addAndMakeVisible (QKnobBandOne = new FilmStripKnob (cachedImage_knobQ, 45, true));
    QKnobBandOne->setRange(0.1f, 1.0f, 0);
    QKnobBandOne->addListener(this);
    
    // Q Knob Band Two
    addAndMakeVisible (QKnobBandTwo = new FilmStripKnob (cachedImage_knobQ, 45, true));
    QKnobBandTwo->setRange(0.1f, 10.0f, 0);
    QKnobBandTwo->addListener(this);
    
    // Q Knob Band Three
    addAndMakeVisible (QKnobBandThree = new FilmStripKnob (cachedImage_knobQ, 45, true));
    QKnobBandThree->setRange(0.1f, 10.0f, 0);
    QKnobBandThree->addListener(this);
    
    // Q Knob Band Four
    addAndMakeVisible (QKnobBandFour = new FilmStripKnob (cachedImage_knobQ, 45, true));
    QKnobBandFour->setRange(0.1f, 10.0f, 0);
    QKnobBandFour->addListener(this);
    
    // Q Knob Band Five
    addAndMakeVisible (QKnobBandFive = new FilmStripKnob (cachedImage_knobQ, 45, true));
    QKnobBandFive->setRange(0.1f, 10.0f, 0);
    QKnobBandFive->addListener(this);
    
    // Q Knob Band Six
    addAndMakeVisible (QKnobBandSix = new FilmStripKnob (cachedImage_knobQ, 45, true));
    QKnobBandSix->setRange(0.1f, 10.0f, 0);
    QKnobBandSix->addListener(this);
    
    
    // Q Knob Band Seven
    addAndMakeVisible (QKnobBandSeven = new FilmStripKnob (cachedImage_knobQ, 45, true));
    QKnobBandSeven->setRange(0.1f, 1.0f, 0);
    QKnobBandSeven->addListener(this);
    
    // Q band Attachments
    bandOneQAttachment = new SliderAttachment (valueTreeState, "bandOneQ", *QKnobBandOne);
    bandTwoQAttachment = new SliderAttachment (valueTreeState, "bandTwoQ", *QKnobBandTwo);
    bandThreeQAttachment = new SliderAttachment (valueTreeState, "bandThreeQ", *QKnobBandThree);
    bandFourQAttachment = new SliderAttachment (valueTreeState, "bandFourQ", *QKnobBandFour);
    bandFiveQAttachment = new SliderAttachment (valueTreeState, "bandFiveQ", *QKnobBandFive);
    bandSixQAttachment = new SliderAttachment (valueTreeState, "bandSixQ", *QKnobBandSix);
    bandSevenQAttachment = new SliderAttachment (valueTreeState, "bandSevenQ", *QKnobBandSeven);
    
    // ================================================================================================
    midSideActiveAttachment = new ButtonAttachment (valueTreeState, "midSideActive", *midSideToggle);
    midSideAttachment = new ButtonAttachment (valueTreeState, "midSideState", *midSideButton);
    
    setSize (900, 550);
}

NuevoEqAudioProcessorEditor::~NuevoEqAudioProcessorEditor()
{
    freqKnobBandOne = nullptr;
    freqKnobBandTwo = nullptr;
    freqKnobBandThree = nullptr;
    freqKnobBandFour = nullptr;
    freqKnobBandFive = nullptr;
    freqKnobBandSix = nullptr;
    freqKnobBandSeven = nullptr;
    
    gainKnobBandTwo = nullptr;
    gainKnobBandThree = nullptr;
    gainKnobBandFour = nullptr;
    gainKnobBandFive = nullptr;
    gainKnobBandSix = nullptr;
    
    QKnobBandOne = nullptr;
    QKnobBandTwo = nullptr;
    QKnobBandThree = nullptr;
    QKnobBandFour = nullptr;
    QKnobBandFive = nullptr;
    QKnobBandSix = nullptr;
    QKnobBandSeven = nullptr;
    
    bandOneToggle = nullptr;
    bandTwoToggle = nullptr;
    bandThreeToggle = nullptr;
    bandFourToggle = nullptr;
    bandFiveToggle = nullptr;
    bandSixToggle = nullptr;
    bandSevenToggle = nullptr;
    bandOneFreqLabel = nullptr;
    bandTwoFreqLabel = nullptr;
    bandThreeFreqLabel = nullptr;
    bandFourFreqLabel = nullptr;
    bandFiveFreqLabel = nullptr;
    bandSixFreqLabel = nullptr;
    bandSevenFreqLabel = nullptr;
    bandOneQLabel = nullptr;
    midSideToggle = nullptr;
    midSideButton = nullptr;
    bandTwoQLabel = nullptr;
    bandThreeQLabel = nullptr;
    bandFourQLabel = nullptr;
    bandFiveQLabel = nullptr;
    gainSixQLabel = nullptr;
    bandSevenQLabel = nullptr;
    outputLevel = nullptr;
    inputLabel = nullptr;
    gainTwoLabel = nullptr;
    gainThreeLabel = nullptr;
    gainFourLabel = nullptr;
    gainFiveLabel = nullptr;
    bandSixQLabel = nullptr;
    
    inputGainKnob = nullptr;
    outputGainKnob = nullptr;
    
    delete[] summedCurve;
}

//===============================================================================================
void NuevoEqAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::white);

    g.setColour (Colours::black);
    g.drawImage (cachedImage_baselayer_jpg_1,
                 0, 0, 900, 550,
                 0, 0, cachedImage_baselayer_jpg_1.getWidth(), cachedImage_baselayer_jpg_1.getHeight());

    g.setColour (Colours::white);

    g.setColour (Colours::white);
    g.fillRect (192, 440, 50, 60);

    g.setColour (Colours::white);
    g.fillRect (291, 440, 50, 60);

    g.setColour (Colours::white);
    g.fillRect (391, 440, 50, 60);

    g.setColour (Colours::white);
    g.fillRect (489, 440, 50, 60);

    g.setColour (Colours::white);
    g.fillRect (588, 440, 50, 60);

    g.setColour (Colours::white);
    g.fillRect (687, 440, 50, 60);

    g.setColour (Colours::white);
    g.fillRect (787, 440, 50, 60);
    
    
    //======================================================================================================
    // EQ LINE
    
    Path wavePath;
    
    wavePath.startNewSubPath (0.0f, 130.5f);
    
    for (float i = 10.0f; i < 900.0f; i++)
        wavePath.lineTo (i, 130.5f - summedCurve[(int) i - 10] );
    
    wavePath.lineTo (900, 241);
    wavePath.lineTo (10, 241);
    
    wavePath.closeSubPath();
    
    g.setColour (Colour (0x97ffffff));
    g.strokePath (wavePath, PathStrokeType(1.0f));
    
    g.setGradientFill (ColourGradient (Colour (0x2effffff),
                                       424.0f, 0.0f,
                                       Colour (0x00ffffff),
                                       424.0f, 296.0f,
                                       false));
    g.fillPath (wavePath);
    
    //======================================================================================================
    
    g.setColour (Colours::black);
    g.drawImage (cachedImage_frame_png_2,
                 0, 0, 900, 550,
                 0, 0, cachedImage_frame_png_2.getWidth(), cachedImage_frame_png_2.getHeight());

    g.setColour (Colours::black);
    g.drawImage (cachedImage_secondlayer_png_3,
                 0, 0, 900, 550,
                 0, 0, cachedImage_secondlayer_png_3.getWidth(), cachedImage_secondlayer_png_3.getHeight());
}

void NuevoEqAudioProcessorEditor::resized()
{   
    // Toggles
    bandOneToggle->setBounds (227, 286, 24, 24);
    bandTwoToggle->setBounds (291, 286, 24, 24);
    bandThreeToggle->setBounds (390, 286, 24, 24);
    bandFourToggle->setBounds (490, 286, 24, 24);
    bandFiveToggle->setBounds (589, 286, 24, 24);
    bandSixToggle->setBounds (687, 286, 24, 24);
    bandSevenToggle->setBounds (816, 286, 24, 24);
    
    // Frequency Labels
    bandOneFreqLabel->setBounds (190, 400, 90, 25);
    bandTwoFreqLabel->setBounds (333, 345, 50, 25);
    bandThreeFreqLabel->setBounds (432, 345, 50, 25);
    bandFourFreqLabel->setBounds (530, 345, 50, 25);
    bandFiveFreqLabel->setBounds (630, 345, 50, 25);
    bandSixFreqLabel->setBounds (730, 345, 50, 25);
    bandSevenFreqLabel->setBounds (786, 400, 90, 25);
    
    // Labels
    bandOneQLabel->setBounds (232, 465, 50, 25);
    midSideToggle->setBounds (48, 476, 72, 24);
    midSideButton->setBounds (45, 504, 88, 24);
    bandTwoQLabel->setBounds (333, 465, 50, 25);
    bandThreeQLabel->setBounds (432, 465, 50, 25);
    bandFourQLabel->setBounds (530, 465, 50, 25);
    bandFiveQLabel->setBounds (630, 465, 50, 25);
    gainSixQLabel->setBounds (730, 400, 50, 25);
    bandSevenQLabel->setBounds (829, 465, 50, 25);
    
    // Input / Output Gain label
    outputLevel->setBounds (104, 408, 60, 16);
    inputLabel->setBounds (104, 336, 60, 16);
    
    gainTwoLabel->setBounds (333, 400, 50, 25);
    gainThreeLabel->setBounds (432, 400, 50, 25);
    gainFourLabel->setBounds (531, 400, 50, 25);
    gainFiveLabel->setBounds (630, 400, 50, 25);
    bandSixQLabel->setBounds (730, 465, 50, 25);
    
    // Input / Output Gain Knobs
    inputGainKnob->setBounds (25, 307, 50, 50);
    outputGainKnob->setBounds (26, 374, 50, 50);
    
    // Frequency Knobs
    freqKnobBandOne->setBounds (213, 316, 50, 50);
    freqKnobBandTwo->setBounds (291, 316, 50, 50);
    freqKnobBandThree->setBounds (391, 316, 50, 50);
    freqKnobBandFour->setBounds (489, 316, 50, 50);
    freqKnobBandFive->setBounds (588, 316, 50, 50);
    freqKnobBandSix->setBounds (687, 316, 50, 50);
    freqKnobBandSeven->setBounds (806, 316, 50, 50);
    
    // Gain Knobs
    gainKnobBandTwo->setBounds (291, 378, 50, 50);
    gainKnobBandThree->setBounds (391, 378, 50, 50);
    gainKnobBandFour->setBounds (489, 378, 50, 50);
    gainKnobBandFive->setBounds (588, 378, 50, 50);
    gainKnobBandSix->setBounds (687, 378, 50, 50);
    
    // Q Knobs
    QKnobBandOne->setBounds (192, 440, 50, 50);
    QKnobBandTwo->setBounds (291, 440, 50, 50);
    QKnobBandThree->setBounds (391, 440, 50, 50);
    QKnobBandFour->setBounds (489, 440, 50, 50);
    QKnobBandFive->setBounds (588, 440, 50, 50);
    QKnobBandSix->setBounds (687, 440, 50, 50);
    QKnobBandSeven->setBounds (787, 440, 50, 50);
    
    updateCurvePaint();
}

// BUTTON LISTENER
//===============================================================================================
void NuevoEqAudioProcessorEditor::buttonClicked (Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == midSideToggle)
    {
        if (midSideToggle->getToggleState()) midSideButton->setEnabled(true);
        else midSideButton->setEnabled(false);
    }
    else if (buttonThatWasClicked == midSideButton)
    {
        if (midSideButton->getToggleState()) midSideButton->setButtonText("Side");
        else midSideButton->setButtonText("Mid");
    }
    updateCurvePaint();
}

// SLIDER LISTENER
//===============================================================================================
void NuevoEqAudioProcessorEditor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    
    if (sliderThatWasMoved == inputGainKnob) // Input Gain Knob
    {
        inputLabel->setText (gainStringFormat (inputGainKnob->getValue()), dontSendNotification);
    }
    else if (sliderThatWasMoved == outputGainKnob) // Output Gain Knob
    {
        outputLevel->setText (gainStringFormat (outputGainKnob->getValue()), dontSendNotification);
    }
    else if (sliderThatWasMoved == freqKnobBandOne) // Frequency Knob One
    {
        float nValue = ((freqKnobBandOne->getValue() * 7980) + 20);
        
        bandOneFreqLabel->setText(frequencyStringFormat (nValue), dontSendNotification);
        curveCalculation("One", "Frequency", nValue);
    }
    else if (sliderThatWasMoved == freqKnobBandTwo) // Frequency Knob Two
    {
        float nValue = ((freqKnobBandTwo->getValue() * 480) + 20);
        
        bandTwoFreqLabel->setText(frequencyStringFormat (nValue), dontSendNotification);
        curveCalculation("Two", "Frequency", nValue);
    }
    else if (sliderThatWasMoved == freqKnobBandThree) // Frequency Knob Three
    {
        float nValue = ((freqKnobBandThree->getValue() * 960) + 40);
        
        bandThreeFreqLabel->setText(frequencyStringFormat (nValue), dontSendNotification);
        
        curveCalculation("Three", "Frequency", nValue);
    }
    else if (sliderThatWasMoved == freqKnobBandFour) // Frequency Knob Four
    {   
        float nValue = ((freqKnobBandFour->getValue() * 7875) + 125);
        
        bandFourFreqLabel->setText(frequencyStringFormat (nValue), dontSendNotification);
        
        curveCalculation("Four", "Frequency", nValue);
    }
    else if (sliderThatWasMoved == freqKnobBandFive) // Frequency Knob Five
    {   
        float nValue = ((freqKnobBandFive->getValue() * 11800) + 200);
        
        bandFiveFreqLabel->setText (frequencyStringFormat (nValue), dontSendNotification);
        
        curveCalculation("Five", "Frequency", nValue);
    }
    else if (sliderThatWasMoved == freqKnobBandSix) // Frequency Knob Six
    {
        float nValue = ((freqKnobBandSix->getValue() * 18200) + 1800);
        
        bandSixFreqLabel->setText(frequencyStringFormat (nValue), dontSendNotification);
        
        curveCalculation("Six", "Frequency", nValue);
    }
    else if (sliderThatWasMoved == freqKnobBandSeven) // Frequency Knob Seven
    {
        float nValue = ((freqKnobBandSeven->getValue() * 19880) + 120);
        bandSevenFreqLabel->setText(frequencyStringFormat (nValue), dontSendNotification);
        curveCalculation("Seven", "Frequency", nValue);
    }
    else if (sliderThatWasMoved == gainKnobBandTwo) // Gain Knob Two
    {
        gainTwoLabel->setText(gainValueStringFormat (gainKnobBandTwo->getValue()), dontSendNotification);
        curveCalculation ("Two", "Gain", gainKnobBandTwo->getValue());
    }
    else if (sliderThatWasMoved == gainKnobBandThree) // Gain Knob Three
    {
        gainThreeLabel->setText(gainValueStringFormat (gainKnobBandThree->getValue()), dontSendNotification);
        curveCalculation ("Three", "Gain", gainKnobBandThree->getValue());
    }
    else if (sliderThatWasMoved == gainKnobBandFour) // Gain Knob Four
    {
        gainFourLabel->setText(gainValueStringFormat (gainKnobBandFour->getValue()), dontSendNotification);
        curveCalculation ("Four", "Gain", gainKnobBandFour->getValue());
    }
    else if (sliderThatWasMoved == gainKnobBandFive) // Gain Knob Five
    {
        gainFiveLabel->setText(gainValueStringFormat (gainKnobBandFive->getValue()), dontSendNotification);
        curveCalculation ("Five", "Gain", gainKnobBandFive->getValue());
    }
    else if (sliderThatWasMoved == gainKnobBandSix) // Gain Knob Six
    {
        gainSixQLabel->setText(gainValueStringFormat (gainKnobBandSix->getValue()), dontSendNotification);
        curveCalculation ("Six", "Gain", gainKnobBandSix->getValue());
    }
    else if (sliderThatWasMoved == QKnobBandOne) // Q knob One
    {
        bandOneQLabel->setText(QStringFormat (QKnobBandOne->getValue()), dontSendNotification);
        curveCalculation("One", "Q", QKnobBandOne->getValue());
    }
    else if (sliderThatWasMoved == QKnobBandTwo) // Q knob Two
    {
        bandTwoQLabel->setText(QStringFormat (QKnobBandTwo->getValue()), dontSendNotification);
        curveCalculation("Two", "Q", QKnobBandTwo->getValue());
    }
    else if (sliderThatWasMoved == QKnobBandThree) // Q knob Three
    {
        bandThreeQLabel->setText(QStringFormat (QKnobBandThree->getValue()), dontSendNotification);
        curveCalculation("Three", "Q", QKnobBandThree->getValue());
    }
    else if (sliderThatWasMoved == QKnobBandFour) // Q knob Four
    {
        bandFourQLabel->setText(QStringFormat (QKnobBandFour->getValue()), dontSendNotification);
        curveCalculation("Four", "Q", QKnobBandFour->getValue());
    }
    else if (sliderThatWasMoved == QKnobBandFive) // Q knob Five
    {
        bandFiveQLabel->setText(QStringFormat (QKnobBandFive->getValue()), dontSendNotification);
        curveCalculation("Five", "Q", QKnobBandFive->getValue());
    }
    else if (sliderThatWasMoved == QKnobBandSix) // Q knob Six
    {
        bandSixQLabel->setText(QStringFormat (QKnobBandSix->getValue()), dontSendNotification);
        curveCalculation("Six", "Q", QKnobBandSix->getValue());
    }
    else if (sliderThatWasMoved == QKnobBandSeven) // Q knob Seven
    {
        bandSevenQLabel->setText(QStringFormat (QKnobBandSeven->getValue()), dontSendNotification);
        curveCalculation("Seven", "Q", QKnobBandSeven->getValue());
    }
    updateCurvePaint();
}
//===============================================================================================

// LABEL LISTENER
//===============================================================================================
void NuevoEqAudioProcessorEditor::labelTextChanged (Label* labelThatHasChanged)
{

    if (labelThatHasChanged == bandOneFreqLabel) // Band One Frequency Label
    {
        String userInputValue;
        userInputValue = bandOneFreqLabel->getText(true);
        
        float stringToTextValue;
        stringToTextValue = ( (userInputValue.getFloatValue() - 20) / 7980);
        
        freqKnobBandOne->setValue(stringToTextValue);
        
        NuevoEqAudioProcessorEditor::sliderValueChanged (freqKnobBandOne);
    }
    else if (labelThatHasChanged == bandTwoFreqLabel) // Band Two Frequency Label
    {
        String userInputValue;
        userInputValue = bandTwoFreqLabel->getText(true);
        
        float stringToTextValue;
        stringToTextValue = ( (userInputValue.getFloatValue() - 20) / 480);
        
        freqKnobBandTwo->setValue(stringToTextValue);
        
        NuevoEqAudioProcessorEditor::sliderValueChanged (freqKnobBandTwo);
    }
    else if (labelThatHasChanged == bandThreeFreqLabel) // Band Three Frequency Label
    {
        String userInputValue;
        userInputValue = bandThreeFreqLabel->getText(true);
        
        float stringToTextValue;
        stringToTextValue = ( (userInputValue.getFloatValue() - 40) / 960);
        
        freqKnobBandThree->setValue(stringToTextValue);
        
        NuevoEqAudioProcessorEditor::sliderValueChanged (freqKnobBandThree);
    }
    else if (labelThatHasChanged == bandFourFreqLabel) // Band Four Frequency Label
    {
        String userInputValue;
        userInputValue = bandFourFreqLabel->getText(true);
        
        float stringToTextValue;
        stringToTextValue = ( (userInputValue.getFloatValue() - 125) / 7875);
        
        freqKnobBandFour->setValue(stringToTextValue);
        
        NuevoEqAudioProcessorEditor::sliderValueChanged (freqKnobBandFour);
    }
    else if (labelThatHasChanged == bandFiveFreqLabel) // Band Five Frequency Label
    {
        String userInputValue;
        userInputValue = bandFiveFreqLabel->getText(true);
        
        float stringToTextValue;
        stringToTextValue = ( (userInputValue.getFloatValue() - 200) / 11800);
        
        freqKnobBandFive->setValue(stringToTextValue);
        
        NuevoEqAudioProcessorEditor::sliderValueChanged (freqKnobBandFive);
    }
    else if (labelThatHasChanged == bandSixFreqLabel) // Band Six Frequency Label
    {
        String userInputValue;
        userInputValue = bandSixFreqLabel->getText(true);
        
        float stringToTextValue;
        stringToTextValue = ( (userInputValue.getFloatValue() - 1800) / 18200);
        
        freqKnobBandSix->setValue(stringToTextValue);
        
        NuevoEqAudioProcessorEditor::sliderValueChanged (freqKnobBandSix);
    }
    else if (labelThatHasChanged == bandSixFreqLabel) // Band Six Frequency Label
    {
        String userInputValue;
        userInputValue = bandSixFreqLabel->getText(true);
        
        float stringToTextValue;
        stringToTextValue = ( (userInputValue.getFloatValue() - 1800) / 18200);
        
        freqKnobBandSix->setValue(stringToTextValue);
        
        NuevoEqAudioProcessorEditor::sliderValueChanged (freqKnobBandSix);
    }
    else if (labelThatHasChanged == bandSevenFreqLabel) // Band Seven Frequency Label
    {
        String userInputValue;
        userInputValue = bandSevenFreqLabel->getText(true);
        
        float stringToTextValue;
        stringToTextValue = ( (userInputValue.getFloatValue() - 120) / 19880);
        
        freqKnobBandSeven->setValue(stringToTextValue);
        
        NuevoEqAudioProcessorEditor::sliderValueChanged (freqKnobBandSeven);
    }
    else if (labelThatHasChanged == gainTwoLabel) // Band Two Gain Label
    {
        String userInputValue;
        userInputValue = gainTwoLabel->getText(true);
        
        float stringToTextValue;
        stringToTextValue = userInputValue.getFloatValue();
        
        gainKnobBandTwo->setValue(stringToTextValue);
        
        NuevoEqAudioProcessorEditor::sliderValueChanged (gainKnobBandTwo);
    }
    else if (labelThatHasChanged == gainThreeLabel) // Band Three Gain Label
    {
        String userInputValue;
        userInputValue = gainThreeLabel->getText(true);
        
        float stringToTextValue;
        stringToTextValue = userInputValue.getFloatValue();
        
        gainKnobBandThree->setValue(stringToTextValue);
        
        NuevoEqAudioProcessorEditor::sliderValueChanged (gainKnobBandThree);
    }
    else if (labelThatHasChanged == gainFourLabel) // Band Four Gain Label
    {
        String userInputValue;
        userInputValue = gainFourLabel->getText(true);
        
        float stringToTextValue;
        stringToTextValue = userInputValue.getFloatValue();
        
        gainKnobBandFour->setValue(stringToTextValue);
        
        NuevoEqAudioProcessorEditor::sliderValueChanged (gainKnobBandFour);
    }
    else if (labelThatHasChanged == gainFiveLabel) // Band Five Gain Label
    {
        String userInputValue;
        userInputValue = gainFiveLabel->getText(true);
        
        float stringToTextValue;
        stringToTextValue = userInputValue.getFloatValue();
        
        gainKnobBandFive->setValue(stringToTextValue);
        
        NuevoEqAudioProcessorEditor::sliderValueChanged (gainKnobBandFive);
    }
    else if (labelThatHasChanged == gainSixQLabel) // Band Six Gain Label
    {
        String userInputValue;
        userInputValue = gainSixQLabel->getText(true);
        
        float stringToTextValue;
        stringToTextValue = userInputValue.getFloatValue();
        
        gainKnobBandSix->setValue(stringToTextValue);
        
        NuevoEqAudioProcessorEditor::sliderValueChanged (gainKnobBandSix);
    }
    else if (labelThatHasChanged == bandOneQLabel) // Band One Q Label
    {
        String userInputValue;
        userInputValue = bandOneQLabel->getText(true);
        
        float stringToTextValue;
        stringToTextValue = userInputValue.getFloatValue();
        
        QKnobBandOne->setValue(stringToTextValue);
        
        NuevoEqAudioProcessorEditor::sliderValueChanged (QKnobBandOne);
    }
    else if (labelThatHasChanged == bandTwoQLabel) // Band Two Q Label
    {
        String userInputValue;
        userInputValue = bandTwoQLabel->getText(true);
        
        float stringToTextValue;
        stringToTextValue = userInputValue.getFloatValue();
        
        QKnobBandTwo->setValue(stringToTextValue);
        
        NuevoEqAudioProcessorEditor::sliderValueChanged (QKnobBandTwo);
    }
    else if (labelThatHasChanged == bandThreeQLabel) // Band Three Q Label
    {
        String userInputValue;
        userInputValue = bandThreeQLabel->getText(true);
        
        float stringToTextValue;
        stringToTextValue = userInputValue.getFloatValue();
        
        QKnobBandThree->setValue(stringToTextValue);
        
        NuevoEqAudioProcessorEditor::sliderValueChanged (QKnobBandThree);
    }
    else if (labelThatHasChanged == bandFourQLabel) // Band Four Q Label
    {
        String userInputValue;
        userInputValue = bandFourQLabel->getText(true);
        
        float stringToTextValue;
        stringToTextValue = userInputValue.getFloatValue();
        
        QKnobBandFour->setValue(stringToTextValue);
        
        NuevoEqAudioProcessorEditor::sliderValueChanged (QKnobBandFour);
    }
    else if (labelThatHasChanged == bandFiveQLabel) // Band Five Q Label
    {
        String userInputValue;
        userInputValue = bandFiveQLabel->getText(true);
        
        float stringToTextValue;
        stringToTextValue = userInputValue.getFloatValue();
        
        QKnobBandFive->setValue(stringToTextValue);
        
        NuevoEqAudioProcessorEditor::sliderValueChanged (QKnobBandFive);
    }
    else if (labelThatHasChanged == bandSixQLabel) // Band Six Q Label
    {
        String userInputValue;
        userInputValue = bandSixQLabel->getText(true);
        
        float stringToTextValue;
        stringToTextValue = userInputValue.getFloatValue();
        
        QKnobBandSix->setValue(stringToTextValue);
        
        NuevoEqAudioProcessorEditor::sliderValueChanged (QKnobBandSix);
    }
    else if (labelThatHasChanged == bandSevenQLabel) // Band Seven Q Label
    {
        String userInputValue;
        userInputValue = bandSevenQLabel->getText(true);
        
        float stringToTextValue;
        stringToTextValue = userInputValue.getFloatValue();
        
        QKnobBandSeven->setValue(stringToTextValue);
        
        NuevoEqAudioProcessorEditor::sliderValueChanged (QKnobBandSeven);
    }
    else if (labelThatHasChanged == inputLabel)
    {
        String userInputValue;
        userInputValue = inputLabel->getText(true);
        
        float stringToTextValue;
        stringToTextValue = userInputValue.getFloatValue();
        
        stringToTextValue = pow(10, (stringToTextValue / 20));
        
        inputGainKnob->setValue(stringToTextValue);
        
        NuevoEqAudioProcessorEditor::sliderValueChanged (inputGainKnob);
    }
    else if (labelThatHasChanged == outputLevel)
    {
        String userInputValue;
        userInputValue = outputLevel->getText(true);
        
        float stringToTextValue;
        stringToTextValue = userInputValue.getFloatValue();
        
        stringToTextValue = pow(10, (stringToTextValue / 20));
        
        outputGainKnob->setValue(stringToTextValue);
        
        NuevoEqAudioProcessorEditor::sliderValueChanged (outputGainKnob);
    }
}

//===============================================================================================

// Method for giving format to Frequency Labels
const String NuevoEqAudioProcessorEditor::frequencyStringFormat (float newValue)
{    
    if (newValue < 10000)
    {
        std::string sValue = std::to_string((int) newValue) + " Hz";
        return sValue;
    }
    else
    {
        newValue /= 1000;
        std::string sValue = std::to_string(newValue);
        sValue.erase (sValue.end() - 5, sValue.end());
        sValue += " kHz";
        
        return sValue;
    }
    return String();
}

// Method for giving format to Input / Output Gain Labels
//===============================================================================================
const String NuevoEqAudioProcessorEditor::gainStringFormat (float newValue)
{   
    if (newValue > 0.0001)
    {   
        float logValue = 20 * log10 (newValue);
        
        std::string sValue = std::to_string (logValue);
        
        sValue.erase (sValue.end() - 4, sValue.end());
        
        sValue += " dB";
        
        return sValue;
    }
    else
    {
        std::string sValue = "-inf";
        
        return sValue;
    }
    
    return String();
}

const String NuevoEqAudioProcessorEditor::gainValueStringFormat (float newValue)
{   
    std::string sValue = std::to_string (newValue);
    
    sValue.erase (sValue.end() - 5, sValue.end());
        
    sValue += " dB";
        
    return sValue;
}

const String NuevoEqAudioProcessorEditor::QStringFormat (float newValue)
{   
    std::string sValue = std::to_string (newValue);
    
    sValue.erase (sValue.end() - 5, sValue.end());
    
    return sValue;
}

// This Method calculates parameters of each band

void NuevoEqAudioProcessorEditor::curveCalculation(String Band, String Parameter, float newValue)
{
    if (Band == "One")
    {
        if (Parameter == "Frequency") bandOne.Frequency = newValue;
        else if (Parameter == "Gain") bandOne.Gain = newValue;
        else if (Parameter == "Q") bandOne.Q = newValue;
        bandOne.highPassCoeff();
        bandOne.createCurve();
    }
    else if (Band == "Two")
    {
        if (Parameter == "Frequency") bandTwo.Frequency = newValue;
        else if (Parameter == "Gain") bandTwo.Gain = newValue;
        else if (Parameter == "Q") bandTwo.Q = newValue;
        bandTwo.peakingCoeff();
        bandTwo.createCurve();
    }
    else if (Band == "Three")
    {
        if (Parameter == "Frequency") bandThree.Frequency = newValue;
        else if (Parameter == "Gain") bandThree.Gain = newValue;
        else if (Parameter == "Q") bandThree.Q = newValue;
        bandThree.peakingCoeff();
        bandThree.createCurve();
    }
    else if (Band == "Four")
    {
        if (Parameter == "Frequency") bandFour.Frequency = newValue;
        else if (Parameter == "Gain") bandFour.Gain = newValue;
        else if (Parameter == "Q") bandFour.Q = newValue;
        bandFour.peakingCoeff();
        bandFour.createCurve();
    }
    else if (Band == "Five")
    {
        if (Parameter == "Frequency") bandFive.Frequency = newValue;
        else if (Parameter == "Gain") bandFive.Gain = newValue;
        else if (Parameter == "Q") bandFive.Q = newValue;
        bandFive.peakingCoeff();
        bandFive.createCurve();
    }
    else if (Band == "Six")
    {
        if (Parameter == "Frequency") bandSix.Frequency = newValue;
        else if (Parameter == "Gain") bandSix.Gain = newValue;
        else if (Parameter == "Q") bandSix.Q = newValue;
        bandSix.peakingCoeff();
        bandSix.createCurve();
    }
    else if (Band == "Seven")
    {
        if (Parameter == "Frequency") bandSeven.Frequency = newValue;
        else if (Parameter == "Gain") bandSeven.Gain = newValue;
        else if (Parameter == "Q") bandSeven.Q = newValue;
        bandSeven.lowPassCoeff();
        bandSeven.createCurve();
    }
    
    updateCurvePaint();
}

// This method draws EQ curve

void NuevoEqAudioProcessorEditor::updateCurvePaint()
{
    for (int i = 0; i < 890; i++)
    {   
        float anyNumber = 0;

        if (bandOneToggle->getToggleState()) {anyNumber += bandOne.curveVector[i];}
        if (bandTwoToggle->getToggleState()) {anyNumber += bandTwo.curveVector[i];}
        if (bandThreeToggle->getToggleState()) {anyNumber += bandThree.curveVector[i];}
        if (bandFourToggle->getToggleState()) {anyNumber += bandFour.curveVector[i];}
        if (bandFiveToggle->getToggleState()) {anyNumber += bandFive.curveVector[i];}
        if (bandSixToggle->getToggleState()) {anyNumber += bandSix.curveVector[i];}
        if (bandSevenToggle->getToggleState()) {anyNumber += bandSeven.curveVector[i];}
        
        if (anyNumber > 0) {summedCurve[i] = anyNumber * 6.6;}
        else {summedCurve[i] = anyNumber * 6.05;}
        
        if (summedCurve[i] < -120) {summedCurve[i] = -122;}
        else if (summedCurve[i] > 120) {summedCurve[i] = 122;}
    }
    
    repaint();
}


