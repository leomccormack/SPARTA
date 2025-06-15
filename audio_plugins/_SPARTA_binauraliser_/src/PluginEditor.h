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
#include "inputCoordsView.h"
#include "pannerView.h"
#include "../../resources/SPARTALookAndFeel.h"

typedef enum _SPARTA_WARNINGS{
    k_warning_none,
    k_warning_frameSize,
    k_warning_supported_fs,
    k_warning_mismatch_fs,
    k_warning_NinputCH,
    k_warning_NoutputCH,
    k_warning_osc_connection_fail
}SPARTA_WARNINGS;

class PluginEditor  : public AudioProcessorEditor,
                      public MultiTimer,
                      private FilenameComponentListener,
                      public juce::ComboBox::Listener,
                      public juce::Slider::Listener,
                      public juce::Button::Listener
{
public:
    PluginEditor (PluginProcessor& p);
    ~PluginEditor() override;

    void paint (juce::Graphics& g) override;
    void resized() override;
    void comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged) override;
    void sliderValueChanged (juce::Slider* sliderThatWasMoved) override;
    void buttonClicked (juce::Button* buttonThatWasClicked) override;

private:
    PluginProcessor& processor;
    void* hBin;
    void timerCallback(int timerID) override;
#ifndef PLUGIN_EDITOR_DISABLE_OPENGL
    std::unique_ptr<OpenGLGraphicsContextCustomShader> shader;
    OpenGLContext openGLContext;
#endif
    double progress = 0.0;
    ProgressBar progressbar;

    /* Look and Feel */
    SPARTALookAndFeel LAF;

    /* source coordinates viewport */
    std::unique_ptr<Viewport> sourceCoordsVP;
    inputCoordsView* sourceCoordsView_handle;
    FilenameComponent fileChooser;

    /* json file loading/saving */
    std::unique_ptr<juce::FileChooser> chooser;

    /* sofa file loading */
    void filenameComponentChanged (FilenameComponent*) override  {
        String directory = fileChooser.getCurrentFile().getFullPathName();
        const char* new_cstring = (const char*)directory.toUTF8();
        binauraliser_setSofaFilePath(hBin, new_cstring);
        refreshPanViewWindow = true;
    }

    /* panning window */
    std::unique_ptr<pannerView> panWindow;
    bool refreshPanViewWindow;

    /* warnings */
    SPARTA_WARNINGS currentWarning;

    /* tooltips */
    SharedResourcePointer<TooltipWindow> tipWindow;
    std::unique_ptr<juce::ComboBox> pluginDescription; /* Dummy combo box to provide plugin description tooltip */

    std::unique_ptr<juce::ComboBox> CBsourceDirsPreset;
    std::unique_ptr<ParameterSlider> SL_num_sources;
    std::unique_ptr<juce::Label> label_N_dirs;
    std::unique_ptr<juce::Label> label_HRIR_fs;
    std::unique_ptr<juce::ToggleButton> TBuseDefaultHRIRs;
    std::unique_ptr<juce::Label> label_DAW_fs;
    std::unique_ptr<juce::ToggleButton> TB_showInputs;
    std::unique_ptr<juce::ToggleButton> TB_showOutputs;
    std::unique_ptr<juce::Label> label_N_Tri;
    std::unique_ptr<juce::ComboBox> CBinterpMode;
    std::unique_ptr<juce::TextButton> tb_loadJSON;
    std::unique_ptr<juce::TextButton> tb_saveJSON;
    std::unique_ptr<ParameterSlider> s_yaw;
    std::unique_ptr<ParameterSlider> s_pitch;
    std::unique_ptr<ParameterSlider> s_roll;
    std::unique_ptr<ParameterToggleButton> t_flipYaw;
    std::unique_ptr<ParameterToggleButton> t_flipPitch;
    std::unique_ptr<ParameterToggleButton> t_flipRoll;
    std::unique_ptr<juce::TextEditor> te_oscport;
    std::unique_ptr<ParameterToggleButton> TBrpyFlag;
    std::unique_ptr<ParameterToggleButton> TBenableRotation;
    std::unique_ptr<juce::ToggleButton> TBenablePreProc;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};
