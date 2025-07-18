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
    k_warning_NinputCH,
    k_warning_NoutputCH,
    k_warning_osc_connection_fail
}SPARTA_WARNINGS;

class PluginEditor  : public AudioProcessorEditor,
                      public Timer,
                      public juce::Slider::Listener,
                      public juce::Button::Listener,
                      public juce::ComboBox::Listener
{
public:
    PluginEditor (PluginProcessor& p);
    ~PluginEditor() override;

    void paint (juce::Graphics& g) override;
    void resized() override;
    void sliderValueChanged (juce::Slider* sliderThatWasMoved) override;
    void buttonClicked (juce::Button* buttonThatWasClicked) override;
    void comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged) override;

private:
    PluginProcessor& processor;
    void* hRot;
    void timerCallback() override;

    /* Look and Feel */
    SPARTALookAndFeel LAF;

    /* warnings */
    SPARTA_WARNINGS currentWarning;

    /* tooltips */
    SharedResourcePointer<TooltipWindow> tipWindow;
    std::unique_ptr<juce::ComboBox> pluginDescription; /* Dummy combo box to provide plugin description tooltip */

    std::unique_ptr<SliderWithAttachment> s_yaw;
    std::unique_ptr<SliderWithAttachment> s_pitch;
    std::unique_ptr<SliderWithAttachment> s_roll;
    std::unique_ptr<ToggleButtonWithAttachment> t_flipYaw;
    std::unique_ptr<ToggleButtonWithAttachment> t_flipPitch;
    std::unique_ptr<ToggleButtonWithAttachment> t_flipRoll;
    std::unique_ptr<juce::TextEditor> te_oscport;
    std::unique_ptr<ComboBoxWithAttachment> CBoutputFormat;
    std::unique_ptr<ComboBoxWithAttachment> CBnorm;
    std::unique_ptr<ComboBoxWithAttachment> CBorder;
    std::unique_ptr<ToggleButtonWithAttachment> TBrpyFlag;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};

