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
    k_warning_frameSize,
    k_warning_supported_fs,
    k_warning_mismatch_fs,
    k_warning_osc_connection_fail,
    k_warning_NinputCH,
    k_warning_NoutputCH
}SPARTA_WARNINGS;

class PluginEditor  : public AudioProcessorEditor,
                      public MultiTimer,
                      private FilenameComponentListener,
                      public juce::Button::Listener,
                      public juce::ComboBox::Listener,
                      public juce::Slider::Listener
{
public:
    PluginEditor (PluginProcessor& p);
    ~PluginEditor() override;

    void paint (juce::Graphics& g) override;
    void resized() override;
    void buttonClicked (juce::Button* buttonThatWasClicked) override;
    void comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged) override;
    void sliderValueChanged (juce::Slider* sliderThatWasMoved) override;

private:
    PluginProcessor& processor;
    void* hAmbi;
    void timerCallback(int timerID) override;
#ifndef PLUGIN_EDITOR_DISABLE_OPENGL
    std::unique_ptr<OpenGLGraphicsContextCustomShader> shader;
    OpenGLContext openGLContext;
#endif
    double progress = 0.0;
    ProgressBar progressbar;

    /* Look and Feel */
    SPARTALookAndFeel LAF;

    /* sofa loading */
    FilenameComponent fileChooser;

    /* sofa file loading */
    void filenameComponentChanged (FilenameComponent*) override  {
        String directory = fileChooser.getCurrentFile().getFullPathName();
        const char* new_cstring = (const char*)directory.toUTF8();
        ambi_bin_setSofaFilePath(hAmbi, new_cstring);
    }

    /* warnings */
    SPARTA_WARNINGS currentWarning;

    /* tooltips */
    SharedResourcePointer<TooltipWindow> tipWindow;
    std::unique_ptr<juce::ComboBox> pluginDescription; /* Dummy combo box to provide plugin description tooltip */

    std::unique_ptr<juce::ToggleButton> TBuseDefaultHRIRs;
    std::unique_ptr<ParameterComboBox> CBorderPreset;
    std::unique_ptr<ParameterComboBox> CBchFormat;
    std::unique_ptr<ParameterComboBox> CBnormScheme;
    std::unique_ptr<ParameterToggleButton> TBmaxRE;
    std::unique_ptr<ParameterSlider> s_yaw;
    std::unique_ptr<ParameterSlider> s_pitch;
    std::unique_ptr<ParameterSlider> s_roll;
    std::unique_ptr<juce::TextEditor> te_oscport;
    std::unique_ptr<juce::Label> label_N_dirs;
    std::unique_ptr<juce::Label> label_HRIR_len;
    std::unique_ptr<juce::Label> label_HRIR_fs;
    std::unique_ptr<juce::Label> label_DAW_fs;
    std::unique_ptr<ParameterToggleButton> t_flipPitch;
    std::unique_ptr<ParameterToggleButton> t_flipRoll;
    std::unique_ptr<ParameterToggleButton> t_flipYaw;
    std::unique_ptr<juce::ToggleButton> TBcompEQ;
    std::unique_ptr<ParameterToggleButton> TBrpyFlag;
    std::unique_ptr<ParameterToggleButton> TBenableRot;
    std::unique_ptr<ParameterComboBox> CBdecoderMethod;
    std::unique_ptr<ParameterToggleButton> TBdiffMatching;
    std::unique_ptr<juce::ToggleButton> TBtruncationEQ;
    std::unique_ptr<juce::ComboBox> CBhrirPreProc;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};

