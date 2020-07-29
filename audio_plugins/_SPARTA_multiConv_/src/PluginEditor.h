/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.4.4

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --

#include "JuceHeader.h"
#include "PluginProcessor.h"

typedef enum _SPARTA_WARNINGS{
    k_warning_none,
    k_warning_nCH_nFilters_missmatch,
    k_warning_sampleRate_missmatch

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
                      public Button::Listener,
                      public Slider::Listener
{
public:
    //==============================================================================
    PluginEditor (PluginProcessor* ownerFilter);
    ~PluginEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    PluginProcessor* hVst;
    void* hMC;
    void timerCallback() override;

    /* sofa loading */
    FilenameComponent fileChooser;

    /* warnings */
    SPARTA_WARNINGS currentWarning;

    /* wav file loading */
    AudioFormatManager formatManager;
    AudioSampleBuffer fileBuffer;
    float durationInSeconds;
    void filenameComponentChanged (FilenameComponent*) override  {
        String directory = fileChooser.getCurrentFile().getFullPathName();
        hVst->setWavDirectory(directory);
        loadWavFile();
    }
    void loadWavFile()
    {
        String directory = hVst->getWavDirectory();
        std::unique_ptr<AudioFormatReader> reader (formatManager.createReaderFor (directory));

        if (reader.get() != nullptr) { /* if file exists */
            durationInSeconds = (float)reader->lengthInSamples / (float)reader->sampleRate;

            if (reader->numChannels <= MAX_NUM_CHANNELS) {
                fileBuffer.setSize ((int)reader->numChannels, (int) reader->lengthInSamples);
                reader->read (&fileBuffer, 0, (int) reader->lengthInSamples, 0, true, true);
            }
            const float** H = fileBuffer.getArrayOfReadPointers();
            multiconv_setFilters(hMC, H, fileBuffer.getNumChannels(), fileBuffer.getNumSamples(), (int)reader->sampleRate);
        }
    }

    /* tooltips */
    SharedResourcePointer<TooltipWindow> tipWindow;

    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<ToggleButton> TBenablePartConv;
    std::unique_ptr<Label> label_hostBlockSize;
    std::unique_ptr<Label> label_NFilters;
    std::unique_ptr<Label> label_filterLength;
    std::unique_ptr<Label> label_hostfs;
    std::unique_ptr<Label> label_filterfs;
    std::unique_ptr<Slider> SL_num_inputs;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

