/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 6.1.6

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
#include "NatNetTools/AdHocActionListener.h"

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
                      public juce::TextEditor::Listener,
                      public juce::Button::Listener,
                      public juce::ComboBox::Listener
{
public:
    //==============================================================================
    PluginEditor (PluginProcessor* ownerFilter);
    ~PluginEditor() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void refreshMidiDevices();
    void textEditorTextChanged(TextEditor& textEditor) override;
    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void buttonClicked (juce::Button* buttonThatWasClicked) override;
    void comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    PluginProcessor* hVst;
    void timerCallback() override;
    String originalConnectButtonText;
    StringArray midiInputs;

    /* Look and Feel */
    SPARTALookAndFeel LAF;

    /* warnings */
    SPARTA_WARNINGS currentWarning;
    SharedResourcePointer<TooltipWindow> tipWindow;
    std::unique_ptr<juce::ComboBox> pluginDescription; /* Dummy combo box to provide plugin description tooltip */

    /* NatNet */
    AdHocActionListener natNetConnListener;
    void natNetconnListenerCallback(const String& message);

    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::Label> label_hostBlockSize;
    std::unique_ptr<juce::Label> label_hostfs;
    std::unique_ptr<juce::TextEditor> te_oscport;
    std::unique_ptr<juce::TextEditor> te_myip;
    std::unique_ptr<juce::TextEditor> te_serverip;
    std::unique_ptr<juce::TextButton> bt_connect;
    std::unique_ptr<juce::Label> te_connectionlabel;
    std::unique_ptr<juce::ToggleButton> tb_unicast;
    std::unique_ptr<juce::Label> label_x;
    std::unique_ptr<juce::Label> label_y;
    std::unique_ptr<juce::Label> label_z;
    std::unique_ptr<juce::Label> label_yaw;
    std::unique_ptr<juce::Label> label_pitch;
    std::unique_ptr<juce::Label> label_roll;
    std::unique_ptr<juce::ToggleButton> tb_unmute;
    std::unique_ptr<juce::ComboBox> juce__comboBox;
    std::unique_ptr<juce::ComboBox> cb_sourceMode;
    std::unique_ptr<juce::TextEditor> te_midiCcCoarse;
    std::unique_ptr<juce::TextEditor> te_midiCcFine;
    std::unique_ptr<juce::ToggleButton> tb_midiQuaternions;
    std::unique_ptr<juce::TextEditor> te_midiChannel;
    std::unique_ptr<juce::ComboBox> cb_midiDevice;
    std::unique_ptr<juce::TextButton> bt_midiRescan;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

