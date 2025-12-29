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

#include "PluginEditor.h"

PluginEditor::PluginEditor (PluginProcessor& p)
    : AudioProcessorEditor(p), processor(p), progressbar(progress)
{
    SL_nChannels = std::make_unique<SliderWithAttachment>(p.parameters, "numChannels");
    addAndMakeVisible (SL_nChannels.get());
    SL_nChannels->setSliderStyle (juce::Slider::LinearHorizontal);
    SL_nChannels->setTextBoxStyle (juce::Slider::TextBoxLeft, false, 80, 20);
    SL_nChannels->setBounds (171, 50, 65, 16);

    SL_decorAmount = std::make_unique<SliderWithAttachment>(p.parameters, "decorrelation");
    addAndMakeVisible (SL_decorAmount.get());
    SL_decorAmount->setSliderStyle (juce::Slider::LinearHorizontal);
    SL_decorAmount->setTextBoxStyle (juce::Slider::TextBoxRight, false, 50, 20);
    SL_decorAmount->setBounds (128, 73, 108, 18);

    tb_compLevel = std::make_unique<ToggleButtonWithAttachment>(p.parameters, "energyComp");
    addAndMakeVisible (tb_compLevel.get());
    tb_compLevel->setBounds (393, 47, 23, 24);

    tb_bypassTransients = std::make_unique<ToggleButtonWithAttachment>(p.parameters, "bypassTransients");
    addAndMakeVisible (tb_bypassTransients.get());
    tb_bypassTransients->setBounds (393, 72, 23, 24);

    setSize (440, 110);

    /* handles */
    hDecor = processor.getFXHandle();

    /* remove slider bit of these sliders */
    SL_nChannels->setColour(Slider::trackColourId, Colours::transparentBlack);
    SL_nChannels->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    SL_nChannels->setSliderSnapsToMousePosition(false);

    /* init OpenGL */
#ifndef PLUGIN_EDITOR_DISABLE_OPENGL
    openGLContext.setMultisamplingEnabled(true);
    openGLContext.attachTo(*this);
#endif

    /* Look and Feel */
    setLookAndFeel(&LAF);

    /* ProgressBar */
    progress = 0.0;
    progressbar.setBounds(getLocalBounds().getCentreX()-175, getLocalBounds().getCentreY()-17, 350, 35);
    progressbar.ProgressBar::setAlwaysOnTop(true);
    progressbar.setColour(ProgressBar::backgroundColourId, Colours::gold);
    progressbar.setColour(ProgressBar::foregroundColourId, Colours::white);

    /* tooltips */
    SL_nChannels->setTooltip("Number of input/output channels to decorrelate");
    SL_decorAmount->setTooltip("Amount of decorrelation; 1=fully decorrelated, 0=bypassed.");
    tb_compLevel->setTooltip("Enable/Disable energy compensation, which can help if the loudness is falling off as the decorrelation amount is increased.");
    tb_bypassTransients->setTooltip("Enable/Disable transient extractor. When enabled only the residual is decorrelated, with the extracted transients passed through without decorrelation.");

    /* Plugin description */
    pluginDescription.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (pluginDescription.get());
    pluginDescription->setBounds (0, 0, 200, 32);
    pluginDescription->setAlpha(0.0f);
    pluginDescription->setEnabled(false);
    pluginDescription->setTooltip(TRANS("A basic multi-channel decorrelator plug-in."));

    startTimer(20);

    /* warnings */
    currentWarning = k_warning_none;
}

PluginEditor::~PluginEditor()
{
    stopTimer();
    setLookAndFeel(nullptr);
}

void PluginEditor::paint (juce::Graphics& g)
{
    using namespace ColoursUI;

    drawPluginBackgroundAndBanner(g, getBounds());

    /* Panels */
    drawPanel(g, {12, 44, 412, 54}, panelFillLight, panelStrokeLight);

    /* Labels */
    drawLabel(g, {18, 43,173,30}, "Number of Channels:", 14.5f);
    drawLabel(g, {18, 67,173,30}, "Decorrelation:",      14.5f);
    drawLabel(g, {266,67,134,30}, "Bypass Transients:",  14.5f);
    drawLabel(g, {266,43,158,30}, "Compensate Level:",   14.5f);

    /* Title */
    drawLabel(g, {16, 1,196,32}, "SPARTA|", 18.8f);
    drawLabel(g, {92,  1,184,32}, "Decorrelator", 18.f, juce::Justification::centredLeft, juce::Colour(0xffbeffba));

    g.setColour(Colours::white);
    g.setFont(juce::FontOptions (11.00f, Font::plain));
    g.drawText(TRANS("Ver ") + JucePlugin_VersionString + BUILD_VER_SUFFIX + TRANS(", Build Date ") + __DATE__ + TRANS(" "),
        198, 16, 530, 11,
        Justification::centredLeft, true);

    /* display warning message */
    g.setFont(juce::FontOptions (11.00f, Font::plain));
    switch (currentWarning){
        case k_warning_none:
            break;
        case k_warning_frameSize:
            g.setColour(Colours::red);
            g.drawText(TRANS("Set frame size to multiple of ") + String(decorrelator_getFrameSize()),
                       getBounds().getWidth()-225, 4, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NinputCH:
            g.setColour(Colours::red);
            g.drawText(TRANS("Insufficient number of input channels (") + String(processor.getTotalNumInputChannels()) +
                       TRANS("/") + String(decorrelator_getNumberOfChannels(hDecor)) + TRANS(")"),
                       getBounds().getWidth()-225, 4, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NoutputCH:
            g.setColour(Colours::red);
            g.drawText(TRANS("Insufficient number of output channels (") + String(processor.getTotalNumOutputChannels()) +
                       TRANS("/") + String(decorrelator_getNumberOfChannels(hDecor)) + TRANS(")"),
                       getBounds().getWidth()-225, 4, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_supported_fs:
            g.setColour(Colours::yellow);
            g.drawText(TRANS("Sample rate \"") + String(decorrelator_getDAWsamplerate(hDecor)) + TRANS("\" is not recommended"),
                       getBounds().getWidth()-225, 4, 530, 11,
                       Justification::centredLeft, true);
            break;
    }
}

void PluginEditor::resized()
{
}

void PluginEditor::sliderValueChanged (juce::Slider* /*sliderThatWasMoved*/)
{
}


void PluginEditor::buttonClicked (juce::Button* /*buttonThatWasClicked*/)
{
}

void PluginEditor::timerCallback()
{
    /* Progress bar */
    if(decorrelator_getCodecStatus(hDecor)==CODEC_STATUS_INITIALISING){
        addAndMakeVisible(progressbar);
        progress = (double)decorrelator_getProgressBar0_1(hDecor);
        char text[PROGRESSBARTEXT_CHAR_LENGTH];
        decorrelator_getProgressBarText(hDecor, (char*)text);
        progressbar.setTextToDisplay(String(text));
    }
    else
        removeChildComponent(&progressbar);

    /* display warning message, if needed */
    if ((processor.getCurrentBlockSize() % decorrelator_getFrameSize()) != 0){
        currentWarning = k_warning_frameSize;
        repaint(0,0,getWidth(),32);
    }
    else if ((processor.getCurrentNumInputs() < decorrelator_getNumberOfChannels(hDecor))){
        currentWarning = k_warning_NinputCH;
        repaint(0,0,getWidth(),32);
    }
    else if ((processor.getCurrentNumOutputs() < decorrelator_getNumberOfChannels(hDecor))){
        currentWarning = k_warning_NoutputCH;
        repaint(0,0,getWidth(),32);
    }
    else if ( !((decorrelator_getDAWsamplerate(hDecor) == 44.1e3) || (decorrelator_getDAWsamplerate(hDecor) == 48e3)) ){
        currentWarning = k_warning_supported_fs;
        repaint(0,0,getWidth(),32);
    }
    else if(currentWarning){
        currentWarning = k_warning_none;
        repaint(0,0,getWidth(),32);
    }
}
