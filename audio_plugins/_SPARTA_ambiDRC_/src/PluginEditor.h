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

#include "PluginProcessor.h"
#include "TFview.h"
#include "colourGradient.h"
#include "../../resources/SPARTALookAndFeel.h"

typedef enum _SPARTA_WARNINGS{
    k_warning_none,
    k_warning_frameSize,
    k_warning_supported_fs,
    k_warning_NinputCH,
    k_warning_NoutputCH
}SPARTA_WARNINGS;

class PluginEditor  : public AudioProcessorEditor,
                      public Timer,
                      public juce::Slider::Listener,
                      public juce::ComboBox::Listener
{
public:
    PluginEditor (PluginProcessor& p);
    ~PluginEditor() override;

    void paint (juce::Graphics& g) override;
    void resized() override;
    void sliderValueChanged (juce::Slider* sliderThatWasMoved) override;
    void comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged) override;

private:
    PluginProcessor& processor;
    void* hAmbi;
    void timerCallback() override;
#ifndef PLUGIN_EDITOR_DISABLE_OPENGL
    std::unique_ptr<OpenGLGraphicsContextCustomShader> shader;
    OpenGLContext openGLContext;
#endif
    std::unique_ptr<TFview> TFviewIncluded;

    /* Look and Feel */
    SPARTALookAndFeel LAF;

    /* warnings */
    SPARTA_WARNINGS currentWarning;

    /* tooltips */
    SharedResourcePointer<TooltipWindow> tipWindow;
    std::unique_ptr<juce::ComboBox> pluginDescription; /* Dummy combo box to provide plugin description tooltip */ 

    std::unique_ptr<SliderWithAttachment> s_ratio;
    std::unique_ptr<SliderWithAttachment> s_knee;
    std::unique_ptr<SliderWithAttachment> s_attack;
    std::unique_ptr<SliderWithAttachment> s_release;
    std::unique_ptr<SliderWithAttachment> s_outgain;
    std::unique_ptr<ComboBoxWithAttachment> presetCB;
    std::unique_ptr<ComboBoxWithAttachment> CHOrderingCB;
    std::unique_ptr<ComboBoxWithAttachment> normalisationCB;
    std::unique_ptr<SliderWithAttachment> s_ingain;
    std::unique_ptr<SliderWithAttachment> s_thresh;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};

