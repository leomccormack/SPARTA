/*
 ==============================================================================
 
 This file is part of SPARTA; a suite of spatial audio plug-ins.
 Copyright (c) 2018 - Leo McCormack.
 
 SPARTA is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 SPARTA is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with SPARTA.  If not, see <http://www.gnu.org/licenses/>.
 
 ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "PluginProcessor.h"
#include "../../resources/SPARTALookAndFeel.h"

typedef enum _SPARTA_WARNINGS{
    k_warning_none,
    k_warning_sampleRate_missmatch,
    k_warning_nInputs_more_than_64,
    k_warning_nOutputs_more_than_64

}SPARTA_WARNINGS;

class PluginEditor  : public AudioProcessorEditor,
                      public Timer,
                      private FilenameComponentListener,
                      public juce::Button::Listener,
                      public juce::Slider::Listener
{
public:
    PluginEditor (PluginProcessor* ownerFilter);
    ~PluginEditor() override;

    void paint (juce::Graphics& g) override;
    void resized() override;
    void buttonClicked (juce::Button* buttonThatWasClicked) override;
    void sliderValueChanged (juce::Slider* sliderThatWasMoved) override;

private:
    PluginProcessor* hVst;
    void* hMC;
    void timerCallback() override;

    /* Look and Feel */
    SPARTALookAndFeel LAF;

    /* sofa loading */
    FilenameComponent fileChooser;

    /* warnings */
    SPARTA_WARNINGS currentWarning;

    /* wav file loading */
    void filenameComponentChanged (FilenameComponent*) override  {
        String wavFilePath = fileChooser.getCurrentFile().getFullPathName();
        hVst->setWavDirectory(wavFilePath);
        hVst->loadWavFile();
    }

    /* tooltips */
    SharedResourcePointer<TooltipWindow> tipWindow;
    std::unique_ptr<juce::ComboBox> pluginDescription; /* Dummy combo box to provide plugin description tooltip */

    std::unique_ptr<juce::ToggleButton> TBenablePartConv;
    std::unique_ptr<juce::Label> label_hostBlockSize;
    std::unique_ptr<juce::Label> label_NFilters;
    std::unique_ptr<juce::Label> label_filterLength;
    std::unique_ptr<juce::Label> label_hostfs;
    std::unique_ptr<juce::Label> label_filterfs;
    std::unique_ptr<juce::Slider> SL_num_inputs;
    std::unique_ptr<juce::Label> label_MatrixNInputs;
    std::unique_ptr<juce::Label> label_MatrixNoutputs;
    std::unique_ptr<juce::Label> label_NOutputs;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};

