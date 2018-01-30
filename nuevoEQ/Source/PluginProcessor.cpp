
/*  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <string>

//==============================================================================
NuevoEqAudioProcessor::NuevoEqAudioProcessor(): shouldProcess(true), isProcess(false), parameters(*this, nullptr)
, isMid (false)
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    //==============================================================================
    // INPUT GAIN
    parameters.createAndAddParameter ("inputGain", "Input Gain", String(), NormalisableRange<float> (0.0001f, 2.0f), 1.0f, invertInputToText, nullptr);
    parameters.addParameterListener ("inputGain", this); // input Listener
    

    // OUTPUT GAIN
    parameters.createAndAddParameter ("outputGain", "Output Gain", String(), NormalisableRange<float> (0.0001f, 2.0f), 1.0f, invertInputToText, nullptr);
    parameters.addParameterListener ("outputGain", this); // output Listener
    
    //==============================================================================
    // BAND ONE
    parameters.createAndAddParameter("bandOneToggle", "Band One Active", String(), NormalisableRange<float> (0.0f, 1.0f, 1.0f), 0.0f, invertActiveToText, nullptr);
    parameters.addParameterListener("bandOneToggle", this); // Band One Toggle Listener
    
    parameters.createAndAddParameter("bandOneFrequency", "Band One Frequency", String(), NormalisableRange<float>(0.0f, 1.0f, 0.001f, 0.5f, false), 0.01f, invertFrequencyOneToText, nullptr);
    parameters.addParameterListener("bandOneFrequency", this); // Band One Frequency Listener
    
    parameters.createAndAddParameter("bandOneQ", "Band One Q", String(), NormalisableRange<float>(0.1f, 1.0f), 0.75f, nullptr, nullptr);
    parameters.addParameterListener("BandOneQ", this);  // Band One Q Listener
    
    // BAND TWO
    parameters.createAndAddParameter("bandTwoToggle", "Band Two Active", String(), NormalisableRange<float> (0.0f, 1.0f, 1.0f), 0.0f, invertActiveToText, nullptr);
    parameters.addParameterListener("bandTwoToggle", this); // Band Two Toggle Listener
    
    parameters.createAndAddParameter("bandTwoFrequency", "Band Two Frequency", String(), NormalisableRange<float>(0.0f, 1.0f), 0.5f, invertFrequencyTwoToText, nullptr);
    parameters.addParameterListener("bandTwoFrequency", this); // Band Two Frequency Listener
    
    parameters.createAndAddParameter("bandTwoQ", "Band Two Q", String(), NormalisableRange<float>(0.1f, 10.0f), 0.75f, invertQToText, nullptr);
    parameters.addParameterListener("bandTwoQ", this);  // Band Two Q Listener
    
    parameters.createAndAddParameter("bandTwoGain", "Band Two Gain", String(), NormalisableRange<float>(-18.0f, 18.0f), 0.0f, invertGainToText, nullptr);
    parameters.addParameterListener("bandTwoGain", this);  // Band Two Gain Listener
    
    // BAND Three
    parameters.createAndAddParameter("bandThreeToggle", "Band Three Active", String(), NormalisableRange<float> (0.0f, 1.0f, 1.0f), 0.0f, invertActiveToText, nullptr);
    parameters.addParameterListener("bandThreeToggle", this); // Band Three Toggle Listener
    
    parameters.createAndAddParameter("bandThreeFrequency", "Band Three Frequency", String(), NormalisableRange<float>(0.0f, 1.0f), 0.5f, invertFrequencyThreeToText, nullptr);
    parameters.addParameterListener("bandThreeFrequency", this); // Band Three Frequency Listener
    
    parameters.createAndAddParameter("bandThreeQ", "Band Three Q", String(), NormalisableRange<float>(0.1f, 10.0f), 0.75f, invertQToText, nullptr);
    parameters.addParameterListener("bandThreeQ", this);  // Band Three Q Listener
    
    parameters.createAndAddParameter("bandThreeGain", "Band Three Gain", String(), NormalisableRange<float>(-18.0f, 18.0f), 0.0f, invertGainToText, nullptr);
    parameters.addParameterListener("bandThreeGain", this);  // Band Three Gain Listener
    
    // BAND Four
    parameters.createAndAddParameter("bandFourToggle", "Band Four Active", String(), NormalisableRange<float> (0.0f, 1.0f, 1.0f), 0.0f, invertActiveToText, nullptr);
    parameters.addParameterListener("bandFourToggle", this); // Band Four Toggle Listener
    
    parameters.createAndAddParameter("bandFourFrequency", "Band Four Frequency", String(), NormalisableRange<float>(0.0f, 1.0f), 0.5f, invertFrequencyFourToText, nullptr);
    parameters.addParameterListener("bandFourFrequency", this); // Band Four Frequency Listener
    
    parameters.createAndAddParameter("bandFourQ", "Band Four Q", String(), NormalisableRange<float>(0.1f, 10.0f), 0.75f, invertQToText, nullptr);
    parameters.addParameterListener("bandFourQ", this);  // Band Four Q Listener
    
    parameters.createAndAddParameter("bandFourGain", "Band Four Gain", String(), NormalisableRange<float>(-18.0f, 18.0f), 0.0f, invertGainToText, nullptr);
    parameters.addParameterListener("bandFourGain", this);  // Band Four Gain Listener
    
    // BAND Five
    parameters.createAndAddParameter("bandFiveToggle", "Band Five Active", String(), NormalisableRange<float> (0.0f, 1.0f, 1.0f), 0.0f, invertActiveToText, nullptr);
    parameters.addParameterListener("bandFiveToggle", this); // Band Five Toggle Listener
    
    parameters.createAndAddParameter("bandFiveFrequency", "Band Five Frequency", String(), NormalisableRange<float>(0.0f, 1.0f), 0.5f, invertFrequencyFiveToText, nullptr);
    parameters.addParameterListener("bandFiveFrequency", this); // Band Five Frequency Listener
    
    parameters.createAndAddParameter("bandFiveQ", "Band Five Q", String(), NormalisableRange<float>(0.1f, 10.0f), 0.75f, invertQToText, nullptr);
    parameters.addParameterListener("bandFiveQ", this);  // Band Five Q Listener
    
    parameters.createAndAddParameter("bandFiveGain", "Band Five Gain", String(), NormalisableRange<float>(-18.0f, 18.0f), 0.0f, invertGainToText, nullptr);
    parameters.addParameterListener("bandFiveGain", this);  // Band Five Gain Listener
    
    // BAND Seven
    parameters.createAndAddParameter("bandSevenToggle", "Band Seven Active", String(), NormalisableRange<float> (0.0f, 1.0f, 1.0f), 0.0f, invertActiveToText, nullptr);
    parameters.addParameterListener("bandSevenToggle", this); // Band Seven Toggle Listener
    
    parameters.createAndAddParameter("bandSevenFrequency", "Band Seven Frequency", String(), NormalisableRange<float>(0.0f, 1.0f), 0.5f, invertFrequencySevenToText, nullptr);
    parameters.addParameterListener("bandSevenFrequency", this); // Band Seven Frequency Listener
    
    parameters.createAndAddParameter("bandSevenQ", "Band Seven Q", String(), NormalisableRange<float>(0.1f, 1.0f), 0.75f, nullptr, nullptr);
    parameters.addParameterListener("bandSevenQ", this);  // Band Seven Q Listener
    
    
    // BAND Six
    parameters.createAndAddParameter("bandSixToggle", "Band Six Active", String(), NormalisableRange<float> (0.0f, 1.0f, 1.0f), 0.0f, invertActiveToText, nullptr);
    parameters.addParameterListener("bandSixToggle", this); // Band Six Toggle Listener
    
    parameters.createAndAddParameter("bandSixFrequency", "Band Six Frequency", String(), NormalisableRange<float>(0.0f, 1.0f), 0.5f, invertFrequencySixToText, nullptr);
    parameters.addParameterListener("bandSixFrequency", this); // Band Six Frequency Listener
    
    parameters.createAndAddParameter("bandSixQ", "Band Six Q", String(), NormalisableRange<float>(0.1f, 10.0f), 0.75f, invertQToText, nullptr);
    parameters.addParameterListener("bandSixQ", this);  // Band Six Q Listener
    
    parameters.createAndAddParameter("bandSixGain", "Band Six Gain", String(), NormalisableRange<float>(-18.0f, 18.0f), 0.0f, invertGainToText, nullptr);
    parameters.addParameterListener("bandSixGain", this);  // Band Six Gain Listener
    
    // Mid Side Active
    
    parameters.createAndAddParameter("midSideActive", "Mid Side Active", String(), NormalisableRange<float> (0.0f, 1.0f, 1.0f), 0.0f, invertActiveToText, nullptr);
    parameters.addParameterListener("midSideActive", this);
    
    // Mid Side State
    
    parameters.createAndAddParameter("midSideState", "Mid Side State", String(), NormalisableRange<float> (0.0f, 1.0f, 1.0f), 0.0f, invertMidSideToText, nullptr);
    parameters.addParameterListener("midSideState", this);

    //==============================================================================
    
    parameters.state = ValueTree (Identifier ("VoodooEQParameters"));
}
NuevoEqAudioProcessor::~NuevoEqAudioProcessor()
{
}

//==============================================================================
const String NuevoEqAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool NuevoEqAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool NuevoEqAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double NuevoEqAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int NuevoEqAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int NuevoEqAudioProcessor::getCurrentProgram()
{
    return 0;
}

void NuevoEqAudioProcessor::setCurrentProgram (int index)
{
}

const String NuevoEqAudioProcessor::getProgramName (int index)
{
    return String();
}

void NuevoEqAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
// Parameter Setup
void NuevoEqAudioProcessor::parameterChanged(const String& parameterID, float newValue)
{
    if (parameterID == "inputGain") newGain = *parameters.getRawParameterValue("inputGain");
    
    else if (parameterID == "outputGain") outGain = *parameters.getRawParameterValue("outputGain");
    
    else if (parameterID == "bandOneToggle" || parameterID == "bandOneQ" || parameterID == "bandOneFrequency")
    {
        bandOne.Active = *parameters.getRawParameterValue("bandOneToggle");
        bandOne.Q = *parameters.getRawParameterValue("bandOneQ");
        bandOne.Frequency = (*parameters.getRawParameterValue("bandOneFrequency") * 7980) + 20;
        bandOne.highPassCoeff();
    }
    else if (parameterID == "bandTwoToggle" || parameterID == "bandTwoQ" || parameterID == "bandTwoFrequency" || parameterID == "bandTwoGain")
    {
        bandTwo.Active = *parameters.getRawParameterValue("bandTwoToggle");
        bandTwo.Gain = *parameters.getRawParameterValue("bandTwoGain");
        bandTwo.Frequency = (*parameters.getRawParameterValue("bandTwoFrequency") * 480) + 20;
        bandTwo.Q = *parameters.getRawParameterValue("bandTwoQ");
        bandTwo.peakingCoeff();
    }
    else if (parameterID == "bandThreeToggle" || parameterID == "bandThreeQ" || parameterID == "bandThreeFrequency" || parameterID == "bandThreeGain")
    {
        bandThree.Active = *parameters.getRawParameterValue("bandThreeToggle");
        bandThree.Gain = *parameters.getRawParameterValue("bandThreeGain");
        bandThree.Frequency = (*parameters.getRawParameterValue("bandThreeFrequency") * 960) + 40;
        bandThree.Q = *parameters.getRawParameterValue("bandThreeQ");
        bandThree.peakingCoeff();
    }
    else if (parameterID == "bandFourToggle" || parameterID == "bandFourQ" || parameterID == "bandFourFrequency" || parameterID == "bandFourGain")
    {
        bandFour.Active = *parameters.getRawParameterValue("bandFourToggle");
        bandFour.Gain = *parameters.getRawParameterValue("bandFourGain");
        bandFour.Frequency = (*parameters.getRawParameterValue("bandFourFrequency") * 7875) + 125;
        bandFour.Q = *parameters.getRawParameterValue("bandFourQ");
        bandFour.peakingCoeff();
    }
    else if (parameterID == "bandFiveToggle" || parameterID == "bandFiveQ" || parameterID == "bandFiveFrequency" || parameterID == "bandFiveGain")
    {
        bandFive.Active = *parameters.getRawParameterValue("bandFiveToggle");
        bandFive.Gain = *parameters.getRawParameterValue("bandFiveGain");
        bandFive.Frequency = (*parameters.getRawParameterValue("bandFiveFrequency") * 11800) + 200;
        bandFive.Q = *parameters.getRawParameterValue("bandFiveQ");
        bandFive.peakingCoeff();
    }
    else if (parameterID == "bandSixToggle" || parameterID == "bandSixQ" || parameterID == "bandSixFrequency" || parameterID == "bandSixGain")
    {
        bandSix.Active = *parameters.getRawParameterValue("bandSixToggle");
        bandSix.Gain = *parameters.getRawParameterValue("bandSixGain");
        bandSix.Frequency = (*parameters.getRawParameterValue("bandSixFrequency") * 18200) + 1800;
        bandSix.Q = *parameters.getRawParameterValue("bandSixQ");
        bandSix.peakingCoeff();
    }
    else if (parameterID == "bandSevenToggle" || parameterID == "bandSevenQ" || parameterID == "bandSevenFrequency")
    {
        bandSeven.Active = *parameters.getRawParameterValue("bandSevenToggle");
        bandSeven.Q = *parameters.getRawParameterValue("bandSevenQ");
        bandSeven.Frequency = (*parameters.getRawParameterValue("bandSevenFrequency") * 19880) + 120;
        bandSeven.lowPassCoeff();
    }
    else if (parameterID == "midSideActive") { isProcess = *parameters.getRawParameterValue("midSideActive");}
    else if (parameterID == "midSideState") { isMid = *parameters.getRawParameterValue("midSideState"); }
}

//==============================================================================
void NuevoEqAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    
    newGain = *parameters.getRawParameterValue("inputGain");
    
    outGain = *parameters.getRawParameterValue("outputGain");
    
    // Band One
    bandOne.initBiquad ((float) sampleRate, true);
    bandOne.Frequency = 120.0f;
    bandOne.Q = 0.7;
    bandOne.highPassCoeff();
    
    // Band Two
    bandTwo.initBiquad ((float) sampleRate, true);
    bandTwo.Frequency = 100.0f;
    bandTwo.Q = 1.0f;
    bandTwo.Gain = 0.0f;
    bandTwo.peakingCoeff();
    
    // Band Three
    bandThree.initBiquad ((float) sampleRate, true);
    bandThree.Frequency = 200.0f;
    bandThree.Q = 1.0f;
    bandThree.Gain = 0.0f;
    bandThree.peakingCoeff();
    
    // Band Four
    bandFour.initBiquad ((float) sampleRate, true);
    bandFour.Frequency = 1000.0f;
    bandFour.Q = 1.0f;
    bandFour.Gain = 0.0f;
    bandFour.peakingCoeff();
    
    // Band Five
    bandFive.initBiquad ((float) sampleRate, true);
    bandFive.Frequency = 2000.0f;
    bandFive.Q = 1.0f;
    bandFive.Gain = 0.0f;
    bandFive.peakingCoeff();
    
    // Band Six
    bandSix.initBiquad ((float) sampleRate, true);
    bandSix.Frequency = 6000.0f;
    bandSix.Q = 1.0f;
    bandSix.Gain = 0.0f;
    bandSix.peakingCoeff();
    
    // Band Seven
    bandSeven.initBiquad ((float) sampleRate, true);
    bandSeven.Frequency = 16000.0;
    bandSeven.Q = 0.7;
    bandSeven.lowPassCoeff();
    
    shouldProcess = true;
}

void NuevoEqAudioProcessor::releaseResources()
{
    bandOne.resetCoeff();
    bandTwo.resetCoeff();
    bandThree.resetCoeff();
    bandFour.resetCoeff();
    bandFive.resetCoeff();
    bandSix.resetCoeff();
    bandSeven.resetCoeff();
    
    shouldProcess = false;
}

String NuevoEqAudioProcessor::invertInputToText (float value)
{
    if (value > 0.0001)
    {
        float nValue = 20 * log10 (value);
    
        std::string sValue = std::to_string (nValue);
    
        sValue.erase (sValue.end() - 4, sValue.end());
        
        sValue += " dB";
        
        return sValue;
    }
    else
        return "-inf";
    
}

String NuevoEqAudioProcessor::invertGainToText (float value)
{
    std::string sValue = std::to_string ((int) value);
    
    sValue += " dB";
    
    return sValue;
}

// Frequency Conversion
// ========================================================================

String NuevoEqAudioProcessor::invertFrequencyOneToText (float value) // Band One
{
    float nValue = (value * 7980) + 20;
    
    std::string sValue  = std::to_string ((int) nValue);
    
    sValue += " Hz";
    
    return sValue;
}

String NuevoEqAudioProcessor::invertFrequencyTwoToText (float value) // Band Two
{
    float nValue = (value * 480) + 20;
    
    std::string sValue  = std::to_string ((int) nValue);
    
    sValue += " Hz";
    
    return sValue;
}

String NuevoEqAudioProcessor::invertFrequencyThreeToText (float value) // Band Three
{
    float nValue = (value * 960) + 40;
    
    std::string sValue  = std::to_string ((int) nValue);
    
    sValue += " Hz";
    
    return sValue;
}

String NuevoEqAudioProcessor::invertFrequencyFourToText (float value) // Band Four
{
    float nValue = (value * 7875) + 125;
    
    std::string sValue  = std::to_string ((int) nValue);
    
    sValue += " Hz";
    
    return sValue;
}

String NuevoEqAudioProcessor::invertFrequencyFiveToText (float value) // Band Five
{
    float nValue = (value * 11800) + 200;
    
    std::string sValue  = std::to_string ((int) nValue);
    
    sValue += " Hz";
    
    return sValue;
}

String NuevoEqAudioProcessor::invertFrequencySixToText (float value) // Band Six
{
    float nValue = (value * 18200) + 1800;
    
    std::string sValue  = std::to_string ((int) nValue);
    
    sValue += " Hz";
    
    return sValue;
}

String NuevoEqAudioProcessor::invertFrequencySevenToText (float value) // Band Seven
{
    float nValue = (value * 19880) + 120;
    
    std::string sValue  = std::to_string ((int) nValue);
    
    sValue += " Hz";
    
    return sValue;
}
// ========================================================================

String NuevoEqAudioProcessor::invertQToText (float value)
{
    std::string sValue = std::to_string (value);
    
    sValue.erase (sValue.end() - 4, sValue.end());
    
    return sValue;
}

String NuevoEqAudioProcessor::invertActiveToText (float value)
{
    if (value) return "Active";
    else return "Inactive";
}

String NuevoEqAudioProcessor::invertMidSideToText (float value)
{
    if (value) return "Mid";
    else return "Side";
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool NuevoEqAudioProcessor::setPreferredBusArrangement (bool isInput, int bus, const AudioChannelSet& preferredSet)
{
    // Reject any bus arrangements that are not compatible with your plugin

    const int numChannels = preferredSet.size();

   #if JucePlugin_IsMidiEffect
    if (numChannels != 0)
        return false;
   #elif JucePlugin_IsSynth
    if (isInput || (numChannels != 1 && numChannels != 2))
        return false;
   #else
    if (numChannels != 1 && numChannels != 2)
        return false;

    if (! AudioProcessor::setPreferredBusArrangement (! isInput, bus, preferredSet))
        return false;
   #endif

    return AudioProcessor::setPreferredBusArrangement (isInput, bus, preferredSet);
}
#endif

void NuevoEqAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    if (totalNumInputChannels != 2)
    {    
        float* channelData = buffer.getWritePointer (0);
        
        if (*channelData != 0 && shouldProcess)
        for (int i = 0; i < buffer. getNumSamples(); i++)
        {
            channelData[i] *= newGain;
            
            bandOne.filterSignalMono (&channelData[i]);
            bandTwo.filterSignalMono (&channelData[i]);
            bandThree.filterSignalMono (&channelData[i]);
            bandFour.filterSignalMono (&channelData[i]);
            bandFive.filterSignalMono (&channelData[i]);
            bandSix.filterSignalMono (&channelData[i]);
            bandSeven.filterSignalMono (&channelData[i]);
            
            channelData[i] *= outGain;
        }
    }
    else if (totalNumInputChannels == 2)
    {
        float* channelDataL = buffer.getWritePointer (0);
        float* channelDataR = buffer.getWritePointer (1);
        
        if (*channelDataL != 0 && *channelDataR != 0 && shouldProcess)
        for (int i = 0; i < buffer. getNumSamples(); i++)
        {
            channelDataL[i] *= newGain;
            channelDataR[i] *= newGain;
            
            midSideObject.processMidSide(isProcess, isMid, &channelDataL[i], &channelDataR[i]);
            
            bandOne.filterSignalStereo (&channelDataL[i], &channelDataR[i]);
            bandTwo.filterSignalStereo (&channelDataL[i], &channelDataR[i]);
            bandThree.filterSignalStereo (&channelDataL[i], &channelDataR[i]);
            bandFour.filterSignalStereo (&channelDataL[i], &channelDataR[i]);
            bandFive.filterSignalStereo (&channelDataL[i], &channelDataR[i]);
            bandSix.filterSignalStereo (&channelDataL[i], &channelDataR[i]);
            bandSeven.filterSignalStereo (&channelDataL[i], &channelDataR[i]);
            
            channelDataL[i] *= outGain;
            channelDataR[i] *= outGain;
        }
    }
}

//==============================================================================
bool NuevoEqAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* NuevoEqAudioProcessor::createEditor()
{
    return new NuevoEqAudioProcessorEditor (*this, parameters);
}

//==============================================================================
void NuevoEqAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    ScopedPointer<XmlElement> xml (parameters.state.createXml());
    copyXmlToBinary (*xml, destData);
}

void NuevoEqAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    ScopedPointer<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    
    if (xmlState != nullptr)
        if (xmlState->hasTagName (parameters.state.getType()))
            parameters.state = ValueTree::fromXml(*xmlState);
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new NuevoEqAudioProcessor();
}
