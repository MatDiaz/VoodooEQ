/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "BiquadFilter.h"
#include "midSideProcess.h"


//==============================================================================
/**
*/
class NuevoEqAudioProcessor  : public AudioProcessor,
                               public AudioProcessorValueTreeState::Listener
{
public:
    //==============================================================================
    NuevoEqAudioProcessor();
    ~NuevoEqAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    double getTailLengthSeconds() const override;
    //==============================================================================
    
    static String invertInputToText (float value);
    
    static String invertGainToText (float value);
    
    static String invertFrequencyOneToText (float value);
    
    static String invertFrequencyTwoToText (float value);
    
    static String invertFrequencyThreeToText (float value);
    
    static String invertFrequencyFourToText (float value);
    
    static String invertFrequencyFiveToText (float value);
    
    static String invertFrequencySixToText (float value);
    
    static String invertFrequencySevenToText (float value);
    
    static String invertQToText (float value);
    
    static String invertActiveToText (float value);
    
    static String invertMidSideToText (float value);

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;
    
    //==============================================================================    
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    //================================PARAMETERS_METHODS============================
    
    virtual void parameterChanged (const String& parameterID, float newValue) override;

private:
    
    BiquadFilter bandOne;
    BiquadFilter bandTwo;
    BiquadFilter bandThree; 
    BiquadFilter bandFour;
    BiquadFilter bandFive; 
    BiquadFilter bandSix;
    BiquadFilter bandSeven;
    
    midSideProcess midSideObject;
    
    float newGain, outGain;
    
    bool shouldProcess;
    
    bool isProcess, isMid;
    
    AudioProcessorValueTreeState parameters;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NuevoEqAudioProcessor)
};


#endif  // PLUGINPROCESSOR_H_INCLUDED
