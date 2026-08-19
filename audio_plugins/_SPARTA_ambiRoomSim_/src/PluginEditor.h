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
#include "pannerView.h"
#include "pathTimelineView.h"
#include "RoomSettingsView.h"
#include "PathEditView.h"
#include "../../resources/SPARTALookAndFeel.h"

typedef enum _SPARTA_WARNINGS{
    k_warning_none,
    k_warning_NinputCH,
    k_warning_NoutputCH,
    k_warning_frameSize
}SPARTA_WARNINGS;

class PluginEditor  : public AudioProcessorEditor,
                       public Timer,
                       public juce::Button::Listener,
                       public juce::FilenameComponentListener
{
public:
    PluginEditor (PluginProcessor& p);
    ~PluginEditor() override;

    void timerCallback() override;
    void paint (juce::Graphics& g) override;
    void resized() override;
    void buttonClicked(juce::Button* buttonThatWasClicked) override;
    void filenameComponentChanged(juce::FilenameComponent*) override;

private:
    PluginProcessor& processor;
    void* hAmbi;
#ifndef PLUGIN_EDITOR_DISABLE_OPENGL
    std::unique_ptr<OpenGLGraphicsContextCustomShader> shader;
    OpenGLContext openGLContext;
#endif
    SPARTALookAndFeel LAF;

    std::unique_ptr<RoomSettingsView> roomSettingsView;
    std::unique_ptr<PathEditView> pathEditView;
    std::unique_ptr<pannerView> panWindow;
    std::unique_ptr<pathTimelineView> pathTimeline;
    std::unique_ptr<juce::ToggleButton> RB_moveSR;
    std::unique_ptr<juce::ToggleButton> RB_drawPath;
    juce::FilenameComponent trackChooser{"Track", juce::File(), true, false, false,
                                         "*.wav;*.aiff;*.aif;*.mp3", juce::String(),
                                         "Load track file..."};

    SPARTA_WARNINGS currentWarning;
    SharedResourcePointer<TooltipWindow> tipWindow;
    std::unique_ptr<juce::ComboBox> pluginDescription;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};
