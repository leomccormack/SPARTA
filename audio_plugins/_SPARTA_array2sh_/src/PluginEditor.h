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
#include "eqview.h"
#include "anaview.h"
#include "sensorCoordsView.h"
#include "../../resources/SPARTALookAndFeel.h"

typedef enum {
    SHOW_EQ = 1,
    SHOW_SPATIAL_COH,
    SHOW_LEVEL_DIFF
}DISP_WINDOW;

typedef enum _SPARTA_WARNINGS{
    k_warning_none,
    k_warning_frameSize,
    k_warning_supported_fs,
    k_warning_NinputCH,
    k_warning_NoutputCH
}SPARTA_WARNINGS;

class PluginEditor  : public AudioProcessorEditor,
                      public MultiTimer,
                      public juce::ComboBox::Listener,
                      public juce::Slider::Listener,
                      public juce::Button::Listener
{
public:
    PluginEditor (PluginProcessor* ownerFilter);
    ~PluginEditor() override;

    void paint (juce::Graphics& g) override;
    void resized() override;
    void comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged) override;
    void sliderValueChanged (juce::Slider* sliderThatWasMoved) override;
    void buttonClicked (juce::Button* buttonThatWasClicked) override;

private:
    PluginProcessor* hVst;
    void* hA2sh;
    void timerCallback(int timerID) override;
#ifndef PLUGIN_EDITOR_DISABLE_OPENGL
    std::unique_ptr<OpenGLGraphicsContextCustomShader> shader;
    OpenGLContext openGLContext;
#endif
    double progress = 0.0;
    ProgressBar progressbar;

    /* Look and Feel */
    SPARTALookAndFeel LAF;

    /* Custom components */
    std::unique_ptr<Viewport> sensorCoordsVP;
    sensorCoordsView* sensorCoordsView_handle;
    std::unique_ptr<eqview> eqviewIncluded;
    std::unique_ptr<anaview> cohviewIncluded;
    std::unique_ptr<anaview> ldiffviewIncluded;
    DISP_WINDOW dispID;

    bool needScreenRefreshFLAG;
    bool showDegreesInstead;

    /* json file loading/saving */
    std::unique_ptr<juce::FileChooser> chooser;

    /* warnings */
    SPARTA_WARNINGS currentWarning;

    /* tooltips */
    SharedResourcePointer<TooltipWindow> tipWindow;
    std::unique_ptr<juce::ComboBox> pluginDescription; /* Dummy combo box to provide plugin description tooltip */
    HyperlinkButton publicationLink { "(Related Publication)", { "https://leomccormack.github.io/sparta-site/docs/help/related-publications/mccormack2018real.pdf" } };

    std::unique_ptr<juce::ComboBox> presetCB;
    std::unique_ptr<juce::ComboBox> arrayTypeCB;
    std::unique_ptr<juce::Slider> QSlider;
    std::unique_ptr<juce::Slider> rSlider;
    std::unique_ptr<juce::Slider> RSlider;
    std::unique_ptr<juce::Slider> cSlider;
    std::unique_ptr<juce::ComboBox> weightTypeCB;
    std::unique_ptr<juce::ComboBox> filterTypeCB;
    std::unique_ptr<juce::Slider> regAmountSlider;
    std::unique_ptr<juce::ComboBox> CHOrderingCB;
    std::unique_ptr<juce::ComboBox> normalisationCB;
    std::unique_ptr<juce::Slider> gainSlider;
    std::unique_ptr<juce::ToggleButton> degRadTB;
    std::unique_ptr<juce::TextButton> textButton;
    std::unique_ptr<juce::ComboBox> dispWindow;
    std::unique_ptr<juce::TextButton> tb_loadJSON;
    std::unique_ptr<juce::TextButton> tb_saveJSON;
    std::unique_ptr<juce::ComboBox> CBencodingOrder;
    std::unique_ptr<juce::ToggleButton> applyDiffEQ;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};
