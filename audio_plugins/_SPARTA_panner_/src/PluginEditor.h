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
#include "outputCoordsView.h"
#include "pannerView.h"
#include "../../resources/SPARTALookAndFeel.h"

typedef enum _SPARTA_WARNINGS{
    /* Problematic warnings (shown in red) */
    k_warning_none,
    k_warning_frameSize,
    k_warning_NinputCH,
    k_warning_NoutputCH,
    
    /* Less severe warnings (shown in yellow) */
    k_warning_busContainsLFE,
    k_warning_supported_fs
}SPARTA_WARNINGS;

class PluginEditor  : public AudioProcessorEditor,
                      public Timer,
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
    void* hPan;
    void timerCallback() override;
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

    /* loudspeaker coordinates viewport */
    std::unique_ptr<Viewport> loudspeakerCoordsVP;
    outputCoordsView* loudspeakerCoordsView_handle;

    /* json file loading/saving */
    std::unique_ptr<juce::FileChooser> chooser;

    /* panning window */
    std::unique_ptr<pannerView> panWindow;
    bool refreshPanViewWindow;

    /* warnings */
    SPARTA_WARNINGS currentWarning;

    /* tooltips */
    SharedResourcePointer<TooltipWindow> tipWindow;
    std::unique_ptr<juce::ComboBox> pluginDescription; /* Dummy combo box to provide plugin description tooltip */

    std::unique_ptr<juce::ComboBox> CBsourceDirsPreset;
    std::unique_ptr<SliderWithAttachment> SL_num_sources;
    std::unique_ptr<juce::ToggleButton> TB_showInputs;
    std::unique_ptr<juce::ToggleButton> TB_showOutputs;
    std::unique_ptr<SliderWithAttachment> SL_pValue;
    std::unique_ptr<juce::ComboBox> CBsLoudspeakerDirsPreset;
    std::unique_ptr<SliderWithAttachment> SL_num_loudspeakers;
    std::unique_ptr<juce::TextButton> tb_loadJSON_src;
    std::unique_ptr<juce::TextButton> tb_saveJSON_src;
    std::unique_ptr<juce::TextButton> tb_loadJSON_ls;
    std::unique_ptr<juce::TextButton> tb_saveJSON_ls;
    std::unique_ptr<SliderWithAttachment> SL_spread;
    std::unique_ptr<SliderWithAttachment> s_yaw;
    std::unique_ptr<SliderWithAttachment> s_pitch;
    std::unique_ptr<SliderWithAttachment> s_roll;
    std::unique_ptr<ToggleButtonWithAttachment> t_flipYaw;
    std::unique_ptr<ToggleButtonWithAttachment> t_flipPitch;
    std::unique_ptr<ToggleButtonWithAttachment> t_flipRoll;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};
