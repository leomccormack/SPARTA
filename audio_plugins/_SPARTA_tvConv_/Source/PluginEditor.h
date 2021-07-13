/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 6.0.8

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --

#include "JuceHeader.h"
#include "PluginProcessor.h"
#include "../../resources/SPARTALookAndFeel.h"

typedef enum _SPARTA_WARNINGS{
    k_warning_none,
    k_warning_sampleRate_missmatch,
    k_warning_nInputs_more_than_64,
    k_warning_nOutputs_more_than_64

}SPARTA_WARNINGS;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class PluginEditor  : public AudioProcessorEditor,
                      public Timer,
                      private FilenameComponentListener,
                      public juce::Slider::Listener
{
public:
    //==============================================================================
    PluginEditor (PluginProcessor* ownerFilter);
    ~PluginEditor() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

    /* Refresh coordinate limits based on loaded sofa files*/
    void refreshCoords();

    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void sliderValueChanged (juce::Slider* sliderThatWasMoved) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    PluginProcessor* hVst;
    void* hTVC;
    void timerCallback() override;

    /* Look and Feel */
    SPARTALookAndFeel LAF;

    /* sofa loading */
    std::unique_ptr<juce::FilenameComponent> fileComp;

    /* sofa file loading */
     void filenameComponentChanged (FilenameComponent*) override  {
         String directory = fileComp->getCurrentFile().getFullPathName();
         const char* new_cstring = (const char*)directory.toUTF8();
         tvconv_setSofaFilePath(hTVC, new_cstring);
         refreshCoords();
     }

    /* warnings */
    SPARTA_WARNINGS currentWarning;
    SharedResourcePointer<TooltipWindow> tipWindow;
    std::unique_ptr<juce::ComboBox> pluginDescription; /* Dummy combo box to provide plugin description tooltip */

    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::Label> label_hostBlockSize;
    std::unique_ptr<juce::Label> label_filterLength;
    std::unique_ptr<juce::Label> label_hostfs;
    std::unique_ptr<juce::Label> label_filterfs;
    std::unique_ptr<juce::Slider> SL_num_inputs;
    std::unique_ptr<juce::Label> label_NOutputs;
    std::unique_ptr<juce::Label> label_nIRpositions;
    std::unique_ptr<juce::Slider> SL_source_y;
    std::unique_ptr<juce::Slider> SL_source_z;
    std::unique_ptr<juce::Slider> SL_source_x;
    std::unique_ptr<juce::Slider> SL_receiver_x;
    std::unique_ptr<juce::Slider> SL_receiver_y;
    std::unique_ptr<juce::Slider> SL_receiver_z;
    std::unique_ptr<juce::Label> label_receiverIdx;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

