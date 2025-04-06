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
    k_warning_none,
    k_warning_frameSize,
    k_warning_NinputCH,
    k_warning_NoutputCH
}SPARTA_WARNINGS;

class PluginEditor  : public AudioProcessorEditor,
                      public Timer,
                      public juce::Slider::Listener,
                      public juce::ComboBox::Listener,
                      public juce::Button::Listener
{
public:
    //==============================================================================
    PluginEditor (PluginProcessor* ownerFilter);
    ~PluginEditor() override;

    //==============================================================================
    void timerCallback() override;

    void paint (juce::Graphics& g) override;
    void resized() override;
    void sliderValueChanged (juce::Slider* sliderThatWasMoved) override;
    void comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged) override;
    void buttonClicked (juce::Button* buttonThatWasClicked) override;

private:
    PluginProcessor* hVst;
    void* hAmbi;
#ifndef PLUGIN_EDITOR_DISABLE_OPENGL
    std::unique_ptr<OpenGLGraphicsContextCustomShader> shader;
    OpenGLContext openGLContext;
#endif

    /* Look and Feel */
    SPARTALookAndFeel LAF;

    /* source coordinates viewport */
    std::unique_ptr<Viewport> sourceCoordsVP;
    inputCoordsView* sourceCoordsView_handle;

    /* receiver coordinates viewport */
    std::unique_ptr<Viewport> receiverCoordsVP;
    outputCoordsView* receiverCoordsView_handle;

    /* panning window */
    std::unique_ptr<pannerView> panWindow;
    bool refreshPanViewWindow;

    /* warnings */
    SPARTA_WARNINGS currentWarning;

    /* tooltips */
    SharedResourcePointer<TooltipWindow> tipWindow;
    std::unique_ptr<juce::ComboBox> pluginDescription; /* Dummy combo box to provide plugin description tooltip */

    //==============================================================================
    std::unique_ptr<juce::Slider> SL_num_sources;
    std::unique_ptr<juce::ComboBox> CBoutputFormat;
    std::unique_ptr<juce::ComboBox> CBnormalisation;
    std::unique_ptr<juce::ComboBox> CBorder;
    std::unique_ptr<juce::Slider> SL_num_receivers;
    std::unique_ptr<juce::Slider> SL_max_reflection_order;
    std::unique_ptr<juce::Slider> s_attenCoeff_pX;
    std::unique_ptr<juce::Slider> s_attenCoeff_nX;
    std::unique_ptr<juce::Slider> s_attenCoeff_nY;
    std::unique_ptr<juce::Slider> s_attenCoeff_nZ;
    std::unique_ptr<juce::Slider> s_attenCoeff_pZ;
    std::unique_ptr<juce::Slider> s_attenCoeff_pY;
    std::unique_ptr<juce::Slider> s_roomLenZ;
    std::unique_ptr<juce::Slider> s_roomLenY;
    std::unique_ptr<juce::Slider> s_roomLenX;
    std::unique_ptr<juce::ToggleButton> TB_enableIMS;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};
