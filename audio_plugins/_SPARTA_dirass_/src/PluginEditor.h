/*
 ==============================================================================
 
 This file is part of SPARTA; a suite of spatial audio plug-ins.
 Copyright (c) 2019 - Leo McCormack.
 
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
#include "overlay.h"
#include "../../resources/SPARTALookAndFeel.h"

#ifndef M_PI
# define M_PI (3.14159265359f)
#endif

typedef enum _SPARTA_WARNINGS{
    /* Problematic warnings (shown in red) */
    k_warning_none,
    k_warning_NinputCH,
    
    /* Less severe warnings (shown in yellow) */
    k_warning_supported_fs
}SPARTA_WARNINGS;

class PluginEditor  : public AudioProcessorEditor,
                      public Timer,
                      private CameraDevice::Listener,
                      public AsyncUpdater,
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
    void* hDir;
    void timerCallback() override;
    double progress = 0.0;
    ProgressBar progressbar;

    /* Look and Feel */
    SPARTALookAndFeel LAF;

    /* for openGL speed-ups */
#ifndef PLUGIN_EDITOR_DISABLE_OPENGL
    std::unique_ptr<OpenGLGraphicsContextCustomShader> shader;
    OpenGLContext openGLContext;
#endif

    /* for the powermap overlay */
    Rectangle<int> previewArea;
    std::unique_ptr<overlay> overlayIncluded;
    bool resolutionHasChanged;

    /* for webcam support */
    void updateCameraList();
    void imageReceived(const Image& image) override;
    void handleAsyncUpdate() override;
    std::unique_ptr<CameraDevice> cameraDevice;
    std::unique_ptr<Component> cameraPreviewComp;
    ImageComponent lastSnapshot;
    Image incomingImage;
    void cameraChanged();
    void cameraDeviceOpenResult (CameraDevice* device, const String& error);

    /* warnings */
    SPARTA_WARNINGS currentWarning;

    /* tooltips */
    SharedResourcePointer<TooltipWindow> tipWindow;
    std::unique_ptr<juce::ComboBox> pluginDescription; /* Dummy combo box to provide plugin description tooltip */
    HyperlinkButton publicationLink { "(Related Publication)", { "https://leomccormack.github.io/sparta-site/docs/help/related-publications/mccormack2019applications.pdf" } };

    std::unique_ptr<ComboBoxWithAttachment> CBbeamType;
    std::unique_ptr<ComboBoxWithAttachment> CBchFormat;
    std::unique_ptr<ComboBoxWithAttachment> CBnormScheme;
    std::unique_ptr<ComboBoxWithAttachment> CB_hfov;
    std::unique_ptr<ComboBoxWithAttachment> CB_aspectRatio;
    std::unique_ptr<SliderWithAttachment> SLmapAvg;
    std::unique_ptr<ComboBoxWithAttachment> CBinputOrder;
    std::unique_ptr<SliderWithAttachment> s_minFreq;
    std::unique_ptr<SliderWithAttachment> s_maxFreq;
    std::unique_ptr<ComboBoxWithAttachment> CBgridOption;
    std::unique_ptr<ComboBoxWithAttachment> CBupscaleOrder;
    std::unique_ptr<ComboBoxWithAttachment> CBdirassMode;
    std::unique_ptr<SliderWithAttachment> s_interpWidth;
    std::unique_ptr<juce::ComboBox> CB_webcam;
    std::unique_ptr<juce::ToggleButton> TB_greyScale;
    std::unique_ptr<juce::ToggleButton> TB_flipUD;
    std::unique_ptr<juce::ToggleButton> TB_flipLR;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};


