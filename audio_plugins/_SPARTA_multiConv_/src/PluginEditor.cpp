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
    : AudioProcessorEditor(p), processor(p), fileChooser ("File", File(), true, false, false,
      "*.wav;", String(),
      "Load .wav File")
{
    TBenablePartConv = std::make_unique<ToggleButtonWithAttachment>(p.parameters, "enablePartitionedConv");
    addAndMakeVisible (TBenablePartConv.get());
    TBenablePartConv->setBounds (261, 121, 24, 24);

    label_hostBlockSize.reset (new juce::Label ("new label", juce::String()));
    addAndMakeVisible (label_hostBlockSize.get());
    label_hostBlockSize->setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Regular"));
    label_hostBlockSize->setJustificationType (juce::Justification::centredLeft);
    label_hostBlockSize->setEditable (false, false, false);
    label_hostBlockSize->setBounds (451, 45, 60, 20);

    label_NFilters.reset (new juce::Label ("new label", juce::String()));
    addAndMakeVisible (label_NFilters.get());
    label_NFilters->setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Regular"));
    label_NFilters->setJustificationType (juce::Justification::centredLeft);
    label_NFilters->setEditable (false, false, false);
    label_NFilters->setBounds (237, 99, 48, 20);

    label_filterLength.reset (new juce::Label ("new label", juce::String()));
    addAndMakeVisible (label_filterLength.get());
    label_filterLength->setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Regular"));
    label_filterLength->setJustificationType (juce::Justification::centredLeft);
    label_filterLength->setEditable (false, false, false);
    label_filterLength->setBounds (451, 72, 60, 20);

    label_hostfs.reset (new juce::Label ("new label", juce::String()));
    addAndMakeVisible (label_hostfs.get());
    label_hostfs->setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Regular"));
    label_hostfs->setJustificationType (juce::Justification::centredLeft);
    label_hostfs->setEditable (false, false, false);
    label_hostfs->setBounds (451, 126, 60, 20);

    label_filterfs.reset (new juce::Label ("new label", juce::String()));
    addAndMakeVisible (label_filterfs.get());
    label_filterfs->setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Regular"));
    label_filterfs->setJustificationType (juce::Justification::centredLeft);
    label_filterfs->setEditable (false, false, false);
    label_filterfs->setBounds (451, 99, 60, 20);

    SL_num_inputs = std::make_unique<SliderWithAttachment>(p.parameters, "numChannels");
    addAndMakeVisible (SL_num_inputs.get());
    SL_num_inputs->setSliderStyle (juce::Slider::LinearHorizontal);
    SL_num_inputs->setTextBoxStyle (juce::Slider::TextBoxRight, false, 55, 20);
    SL_num_inputs->setBounds (237, 46, 48, 20);

    setSize (530, 160);

    hMC = processor.getFXHandle();

    /* Look and Feel */
    setLookAndFeel(&LAF);

    /* remove slider bit of these sliders */
    SL_num_inputs->setColour(Slider::trackColourId, Colours::transparentBlack);
    SL_num_inputs->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    SL_num_inputs->setSliderSnapsToMousePosition(false);

    /* file loader */
    addAndMakeVisible (fileChooser);
    fileChooser.addListener (this);
    fileChooser.setBounds (16, 72, 268, 20);
    if(processor.getWavDirectory() != TRANS("no_file"))
        fileChooser.setCurrentFile(processor.getWavDirectory(), true);

    /* fetch current configuration */
    label_NFilters->setJustificationType (Justification::centred);

    /* tooltips */
    fileChooser.setTooltip("Load multi-channel *.wav file here, which should have 1 filter for each input channel.");
    TBenablePartConv->setTooltip("Enable/Disable partitioned convolution. Try both and use whichever uses less CPU. The end result is the same.");
    label_hostBlockSize->setTooltip("The current host block size. The higher the block size, the less CPU the plug-in will use.");
    label_NFilters->setTooltip("The number of filters in the loaded wav file. The filters are applied to each respective input channel. i.e. filter 3 is applied to channel 3 etc.");
    label_filterLength->setTooltip("Filter length in seconds. the longer this is the more your CPU will cry.");
    label_hostfs->setTooltip("The host samplerate. This should match the filter samplerate.");
    label_filterfs->setTooltip("The filter samplerate. This should match the host samplerate.");
    SL_num_inputs->setTooltip("The number of channels. The filters are applied to each respective input channel. i.e. filter 3 is applied to channel 3 etc.");

    /* Plugin description */
    pluginDescription.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (pluginDescription.get());
    pluginDescription->setBounds (0, 0, 200, 32);
    pluginDescription->setAlpha(0.0f);
    pluginDescription->setEnabled(false);
    pluginDescription->setTooltip(TRANS("A simple multi-channel convolver with an (optional) partitioned-convolution mode. The plugin will convolve each input channel with the respective filter up to the maximum of 128 channels/filters.\n\nNote that this is not to be confused with the sparta_matrixconv plug-in. For this plug-in, the number inputs = the number of filters = the number of outputs. i.e. no matrixing is applied."));

    /* Specify screen refresh rate */
    startTimer(30); /*ms (40ms = 25 frames per second) */

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
    drawPanel(g, {  8, 39, 288,112}, panelFill,      panelStrokeLight);
    drawPanel(g, {304, 39, 216,112}, panelFill,      panelStrokeLight);

    /* Title */
    drawLabel(g, {16, 1,100,32}, "SPARTA|", 18.f);
    drawLabel(g, {92,  1,124,32}, "MultiConv", 18.f, juce::Justification::centredLeft, juce::Colour(0xff7deeff));

    /* Left‑side labels */
    drawLabel(g, {16, 40,224,30}, "Number of In/Output Channels:", 15.f);
    drawLabel(g, {16, 66,208,30}, "Filters:",                      15.f);
    drawLabel(g, {16, 92,232,30}, "Number of Filters in .wav File:", 15.f);
    drawLabel(g, {16,118,288,30}, "Enable Partitioned Convolution:", 15.f);

    /* Right‑side labels */
    drawLabel(g, {312, 40,115,30}, "Host Block Size:", 15.f);
    drawLabel(g, {312, 66,200,30}, "Filter Length (s):", 15.f);
    drawLabel(g, {312, 92,128,30}, "Filter Samplerate:", 15.f);
    drawLabel(g, {312,118,144,30}, "Host Samplerate:",   15.f);

    /* display version/date built */
    g.setColour(Colours::white);
    g.setFont(juce::FontOptions (11.00f, Font::plain));
    g.drawText(TRANS("Ver ") + JucePlugin_VersionString + BUILD_VER_SUFFIX + TRANS(", Build Date ") + __DATE__ + TRANS(" "),
        190, 16, 530, 11,
        Justification::centredLeft, true);

    /* display warning message */
    g.setFont(juce::FontOptions (11.00f, Font::plain));
    switch (currentWarning){
        case k_warning_none:
            break;
        case k_warning_nCH_nFilters_missmatch:
            g.setColour(Colours::red);
            g.drawText(TRANS("Number of inputs does not match number of filters"),
                       getBounds().getWidth()-250, 5, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_sampleRate_missmatch:
            g.setColour(Colours::red);
            g.drawText(TRANS("Host samplerate does not match filter samplerate"),
                       getBounds().getWidth()-250, 5, 530, 11,
                       Justification::centredLeft, true);
            break;
    }
}

void PluginEditor::resized()
{
    repaint();
}

void PluginEditor::buttonClicked (juce::Button* /*buttonThatWasClicked*/)
{
}

void PluginEditor::sliderValueChanged (juce::Slider* /*sliderThatWasMoved*/)
{
}

void PluginEditor::timerCallback()
{
    /* parameters whos values can change internally should be periodically refreshed */
    label_hostBlockSize->setText(String(multiconv_getHostBlockSize(hMC)), dontSendNotification);
    label_NFilters->setText(String(multiconv_getNfilters(hMC)), dontSendNotification);
    label_filterLength->setText(String((float)multiconv_getFilterLength(hMC)/MAX((float)multiconv_getFilterFs(hMC),1/*avoid nan*/)), dontSendNotification);
    //label_filterLength->setText(String(multiconv_getFilterLength(hMC)), dontSendNotification);
    //label_filterLength->setText(String(durationInSeconds), dontSendNotification);
    label_hostfs->setText(String(multiconv_getHostFs(hMC)), dontSendNotification);
    label_filterfs->setText(String(multiconv_getFilterFs(hMC)), dontSendNotification);

    /* display warning message, if needed */
    if ((multiconv_getNfilters(hMC) != 0) && (multiconv_getNfilters(hMC) != multiconv_getNumChannels(hMC))){
        currentWarning = k_warning_nCH_nFilters_missmatch;
        repaint(0,0,getWidth(),32);
    }
    else if((multiconv_getNfilters(hMC) != 0) && (multiconv_getHostFs(hMC)!=multiconv_getFilterFs(hMC))){
        currentWarning = k_warning_sampleRate_missmatch;
        repaint(0,0,getWidth(),32);
    }
    else{
        currentWarning = k_warning_none;
        repaint(0,0,getWidth(),32);
    }
}

