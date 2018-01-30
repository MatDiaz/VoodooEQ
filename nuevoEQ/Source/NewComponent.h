/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 4.3.1

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_369DD91DB9C1C992__
#define __JUCE_HEADER_369DD91DB9C1C992__

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class NewComponent  : public Component,
                      public ButtonListener,
                      public LabelListener
{
public:
    //==============================================================================
    NewComponent ();
    ~NewComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;
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
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
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
    ScopedPointer<Label> outputLevel;
    ScopedPointer<Label> inputLabel;
    ScopedPointer<Label> gainTwoLabel;
    ScopedPointer<Label> gainThreeLabel;
    ScopedPointer<Label> gainFourLabel;
    ScopedPointer<Label> gainFiveLabel;
    ScopedPointer<Label> bandSixQLabel;
    Image cachedImage_baselayer_jpg_1;
    Image cachedImage_frame_png_2;
    Image cachedImage_secondlayer_png_3;
    Path internalPath4;
    Path internalPath5;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NewComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_369DD91DB9C1C992__
