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
      "Load .wav File Here")
{
    TBenablePartConv = std::make_unique<ToggleButtonWithAttachment>(p.parameters, "enablePartitionedConv");
    addAndMakeVisible (TBenablePartConv.get());
    TBenablePartConv->setBounds (261, 94, 24, 24);

    label_hostBlockSize.reset (new juce::Label ("new label", juce::String()));
    addAndMakeVisible (label_hostBlockSize.get());
    label_hostBlockSize->setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Regular"));
    label_hostBlockSize->setJustificationType (juce::Justification::centredLeft);
    label_hostBlockSize->setEditable (false, false, false);
    label_hostBlockSize->setBounds (451, 73, 60, 20);

    label_NFilters.reset (new juce::Label ("new label", juce::String()));
    addAndMakeVisible (label_NFilters.get());
    label_NFilters->setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Regular"));
    label_NFilters->setJustificationType (juce::Justification::centred);
    label_NFilters->setEditable (false, false, false);
    label_NFilters->setBounds (237, 150, 48, 20);

    label_filterLength.reset (new juce::Label ("new label", juce::String()));
    addAndMakeVisible (label_filterLength.get());
    label_filterLength->setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Regular"));
    label_filterLength->setJustificationType (juce::Justification::centredLeft);
    label_filterLength->setEditable (false, false, false);
    label_filterLength->setBounds (451, 98, 60, 20);

    label_hostfs.reset (new juce::Label ("new label", juce::String()));
    addAndMakeVisible (label_hostfs.get());
    label_hostfs->setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Regular"));
    label_hostfs->setJustificationType (juce::Justification::centredLeft);
    label_hostfs->setEditable (false, false, false);
    label_hostfs->setBounds (451, 150, 60, 20);

    label_filterfs.reset (new juce::Label ("new label", juce::String()));
    addAndMakeVisible (label_filterfs.get());
    label_filterfs->setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Regular"));
    label_filterfs->setJustificationType (juce::Justification::centredLeft);
    label_filterfs->setEditable (false, false, false);
    label_filterfs->setBounds (451, 124, 60, 20);

    SL_num_inputs = std::make_unique<SliderWithAttachment>(p.parameters, "numInputChannels");
    addAndMakeVisible (SL_num_inputs.get());
    SL_num_inputs->setSliderStyle (juce::Slider::LinearHorizontal);
    SL_num_inputs->setTextBoxStyle (juce::Slider::TextBoxRight, false, 55, 20);
    SL_num_inputs->setBounds (237, 46, 48, 20);

    label_MatrixNInputs.reset (new juce::Label ("new label", juce::String()));
    addAndMakeVisible (label_MatrixNInputs.get());
    label_MatrixNInputs->setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Regular"));
    label_MatrixNInputs->setJustificationType (juce::Justification::centred);
    label_MatrixNInputs->setEditable (false, false, false);
    label_MatrixNInputs->setBounds (451, 45, 60, 20);

    label_MatrixNoutputs.reset (new juce::Label ("new label", juce::String()));
    addAndMakeVisible (label_MatrixNoutputs.get());
    label_MatrixNoutputs->setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Regular"));
    label_MatrixNoutputs->setJustificationType (juce::Justification::centred);
    label_MatrixNoutputs->setEditable (false, false, false);
    label_MatrixNoutputs->setBounds (368, 45, 60, 20);

    label_NOutputs.reset (new juce::Label ("new label", juce::String()));
    addAndMakeVisible (label_NOutputs.get());
    label_NOutputs->setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Regular"));
    label_NOutputs->setJustificationType (juce::Justification::centred);
    label_NOutputs->setEditable (false, false, false);
    label_NOutputs->setBounds (237, 124, 48, 20);

    setSize (530, 184);

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
    fileChooser.setTooltip("Load multi-channel *.wav file here. For example, if you want to do a 4 x 8 matrix convolution, then the number of inputs should be set to 8, and you should load a 4 channel .wav file, where the filters are concatenated for each input. This will map the 8 inputs to the 4 outputs, as dictated by your 4 x 8 filter matrix.");
    TBenablePartConv->setTooltip("Enable/Disable partitioned convolution. Try both and use whichever uses less CPU. The end result is the same.");
    label_hostBlockSize->setTooltip("The current host block size. The higher the block size, the less CPU the plug-in will use.");
    label_NFilters->setTooltip("The number of filters in the loaded wav file. (Basically, number of inputs multiplied by the number of outputs).");
    label_filterLength->setTooltip("Filter length in seconds. If this is 0 then something is wrong with the current configuration. (e.g. loaded wav length is not divisable by the number of inputs specified.");
    label_hostfs->setTooltip("The host samplerate. This should match the filter samplerate.");
    label_filterfs->setTooltip("The filter samplerate. This should match the host samplerate.");
    SL_num_inputs->setTooltip("The number of input channels.");
    label_MatrixNInputs->setTooltip("The number of input channels.");
    label_MatrixNoutputs->setTooltip("The number of output channels");
    label_NOutputs->setTooltip("The number of output channels. (number of channels in the loaded wav file)");

    /* Plugin description */
    pluginDescription.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (pluginDescription.get());
    pluginDescription->setBounds (0, 0, 200, 32);
    pluginDescription->setAlpha(0.0f);
    pluginDescription->setEnabled(false);
    pluginDescription->setTooltip(TRANS("A simple matrix convolver with an (optional) partitioned-convolution mode. The matrix of filters should be concatenated for each output channel and loaded as a .wav file. You need only inform the plug-in of the number if input channels, and it will take care of the rest.\n\n")+
                                  TRANS("Example 1, spatial reverberation: if you have a B-Format/Ambisonic room impulse response (RIR), you may convolve it with a monophonic input signal and the output will exhibit (much of) the spatial characteristics of the measured room. Simply load this Ambisonic RIR into the plug-in and set the number of input channels to 1. You may then decode the resulting Ambisonic output to your loudspeaker array (e.g. using sparta_ambiDEC) or to headphones (e.g. using sparta_ambiBIN). However, please note that the limitations of lower-order Ambisonics for signals (namely, colouration and poor spatial accuracy) will also be present with lower-order Ambisonic RIRs; at least, when applied in this manner. Consider referring to Example 3, for a more spatially accurate method of reproducing the spatial characteristics of rooms captured as Ambisonic RIRs.\n\n") +
                                  TRANS(" Example 2, microphone array to Ambisonics encoding: if you have a matrix of filters to go from an Eigenmike (32 channel) recording to 4th order Ambisonics (25 channel), then the plugin requires a 25-channel wav file to be loaded, and the number of input channels to be set to 32. In this case: the first 32 filters will map the input to the first output channel, filters 33-64 will map the input to the second output channel, ... , and the last 32 filters will map the input to the 25th output channel. This may be used as an alternative to sparta_array2sh.\n\n") +
                                  TRANS("Example 3, more advanced spatial reverberation: if you have a monophonic recording and you wish to reproduce it as if it were in your favourite concert hall, first measure a B-Format/Ambisonic room impulse response (RIR) of the hall, and then convert this Ambisonic RIR to your loudspeaker set-up using HOSIRR. Then load the resulting rendered loudspeaker array RIR into the plug-in and set the number of input channels to 1. Note it is recommended to use HOSIRR (which is a parametric renderer), to convert your B-Format/Ambisonic IRs into arbitrary loudspeaker array IRs as the resulting convolved output will generally be more spatially accurate when compared to linear (non-parametric) Ambisonic decoding; as described by Example 1.\n\n") +
                                  TRANS("Example 4, virtual monitoring of a multichannel setup: if you have a set of binaural head-related impulse responses (BRIRs) which correspond to the loudspeaker directions of a measured listening room, you may use this 2 x L matrix of filters to reproduce loudspeaker mixes (L-channels) over headphones. Simply concatenate the BRIRs for each input channel into a two channel wav file and load them into the plugin, then set the number of inputs to be the number of BRIRs/virtual-loudspeakers in the mix.\n"));

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

    /* Background gradients */
    drawVerticalGradient(g, {0,  30, 530, 65}, bgDark1, bgDark2);
    drawVerticalGradient(g, {0,  95, 530, 89}, bgDark2, bgDark1);

    /* Top rounded bar */
    {
        juce::Rectangle<float> r { 1.f, 2.f, 528.f, 31.f };
        g.setGradientFill(juce::ColourGradient(bgDark2,
                                               r.getX(), r.getBottom(),
                                               bgDark1,
                                               r.getRight(), r.getY(),
                                               false));
        g.fillRoundedRectangle(r, 5.f);
        g.setColour(borderGrey);
        g.drawRoundedRectangle(r, 5.f, 2.f);
    }

    /* Panels  */
    drawPanel(g, {  8, 39, 288,137}, panelFill,      panelStrokeLight);
    drawPanel(g, {  8, 39, 288, 81}, panelFillLight, panelStrokeLight);
    drawPanel(g, {304, 40, 216, 29}, panelFill,      panelStrokeLight);
    drawPanel(g, {304, 68, 216,108}, panelFill,      panelStrokeLight);

    /* Borders */
    g.setColour(borderGrey);
    g.drawRect({0,   0, 532, 2}, 2);
    g.drawRect({0,   0,   2,184}, 2);
    g.drawRect({528, 0,   2,184}, 2);
    g.drawRect({0, 182, 532, 2}, 2);

    /* Title */
    drawLabel(g, {16, 1,100,32}, "SPARTA|", 18.8f);
    drawLabel(g, {92,  1,124,32}, "MatrixConv", 18.f, juce::Justification::centredLeft, juce::Colour(0xffe9ff00));

    /* Left‑side labels */
    drawLabel(g, {16, 40,224,30}, "Number of Input Channels:", 15.f);
    drawLabel(g, {16, 92,232,30}, "Enable Partitioned Convolution:", 15.f);
    drawLabel(g, {16,118,232,31}, "Number of Output Channels:", 15.f);
    drawLabel(g, {16,144,232,30}, "Number of Filters in .wav File:", 15.f);

    /* Right‑side labels */
    drawLabel(g, {312, 39,115,30}, "Matrix:", 15.f);
    drawLabel(g, {436, 40,115,30}, "x",      18.f, juce::Justification::centredLeft);

    drawLabel(g, {312, 66,115,30}, "Host Block Size:", 15.f);
    drawLabel(g, {312, 92,200,30}, "Filter Length (s):", 15.f);
    drawLabel(g, {312,118,128,30}, "Filter Samplerate:", 15.f);
    drawLabel(g, {312,144,144,30}, "Host Samplerate:",   15.f);

    /* display version/date built */
    g.setColour(Colours::white);
    g.setFont(juce::FontOptions (11.00f, Font::plain));
    g.drawText(TRANS("Ver ") + JucePlugin_VersionString + BUILD_VER_SUFFIX + TRANS(", Build Date ") + __DATE__ + TRANS(" "),
        196, 16, 530, 11,
        Justification::centredLeft, true);

    /* display warning message */
    g.setFont(juce::FontOptions (11.00f, Font::plain));
    switch (currentWarning){
        case k_warning_none:
            break;
        case k_warning_sampleRate_missmatch:
            g.setColour(Colours::red);
            g.drawText(TRANS("Host samplerate does not match filter samplerate"),
                       getBounds().getWidth()-250, 5, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_nInputs_more_than_64:
            g.setColour(Colours::red);
            g.drawText(TRANS("Number of input channels exceeds VST maximum"),
                       getBounds().getWidth()-250, 5, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_nOutputs_more_than_64:
            g.setColour(Colours::red);
            g.drawText(TRANS("Number of output channels exceeds VST maximum"),
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
    label_hostBlockSize->setText(String(matrixconv_getHostBlockSize(hMC)), dontSendNotification);
    label_NFilters->setText(String(matrixconv_getNfilters(hMC)), dontSendNotification);
    label_filterLength->setText(String((float)matrixconv_getFilterLength(hMC)/MAX((float)matrixconv_getFilterFs(hMC),1/*avoid nan*/)), dontSendNotification);
    //label_filterLength->setText(String(durationInSeconds), dontSendNotification);
    label_hostfs->setText(String(matrixconv_getHostFs(hMC)), dontSendNotification);
    label_filterfs->setText(String(matrixconv_getFilterFs(hMC)), dontSendNotification);
    label_MatrixNInputs->setText(String(matrixconv_getNumInputChannels(hMC)), dontSendNotification);
    label_MatrixNoutputs->setText(String(matrixconv_getNumOutputChannels(hMC)), dontSendNotification);
    label_NOutputs->setText(String(matrixconv_getNumOutputChannels(hMC)), dontSendNotification);

    /* display warning message, if needed */
    if((matrixconv_getNfilters(hMC) != 0) && (matrixconv_getHostFs(hMC)!=matrixconv_getFilterFs(hMC))){
        currentWarning = k_warning_sampleRate_missmatch;
        repaint(0,0,getWidth(),32);
    }
    else if(matrixconv_getNumInputChannels(hMC)>MAX_NUM_CHANNELS){
        currentWarning = k_warning_nInputs_more_than_64;
        repaint(0,0,getWidth(),32);
    }
    else if(matrixconv_getNumOutputChannels(hMC)>MAX_NUM_CHANNELS){
        currentWarning = k_warning_nOutputs_more_than_64;
        repaint(0,0,getWidth(),32);
    }
    else{
        currentWarning = k_warning_none;
        repaint(0,0,getWidth(),32);
    }
}
