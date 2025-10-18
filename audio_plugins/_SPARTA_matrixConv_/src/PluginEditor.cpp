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
    TBenablePartConv = nullptr;
    label_hostBlockSize = nullptr;
    label_NFilters = nullptr;
    label_filterLength = nullptr;
    label_hostfs = nullptr;
    label_filterfs = nullptr;
    SL_num_inputs = nullptr;
    label_MatrixNInputs = nullptr;
    label_MatrixNoutputs = nullptr;
    label_NOutputs = nullptr;

    setLookAndFeel(nullptr);
}

void PluginEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::white);

    {
        int x = 0, y = 30, width = 530, height = 65;
        juce::Colour fillColour1 = juce::Colour (0xff19313f), fillColour2 = juce::Colour (0xff041518);
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             8.0f - 0.0f + x,
                                             32.0f - 30.0f + y,
                                             fillColour2,
                                             8.0f - 0.0f + x,
                                             88.0f - 30.0f + y,
                                             false));
        g.fillRect (x, y, width, height);
    }

    {
        int x = 0, y = 95, width = 530, height = 89;
        juce::Colour fillColour1 = juce::Colour (0xff19313f), fillColour2 = juce::Colour (0xff041518);
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             8.0f - 0.0f + x,
                                             184.0f - 95.0f + y,
                                             fillColour2,
                                             8.0f - 0.0f + x,
                                             136.0f - 95.0f + y,
                                             false));
        g.fillRect (x, y, width, height);
    }

    {
        int x = 8, y = 39, width = 288, height = 137;
        juce::Colour fillColour = juce::Colour (0x10c7c7c7);
        juce::Colour strokeColour = juce::Colour (0x1fffffff);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 8, y = 39, width = 288, height = 81;
        juce::Colour fillColour = juce::Colour (0x08c7c7c7);
        juce::Colour strokeColour = juce::Colour (0x1fffffff);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 304, y = 40, width = 216, height = 29;
        juce::Colour fillColour = juce::Colour (0x10c7c7c7);
        juce::Colour strokeColour = juce::Colour (0x1fffffff);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        float x = 1.0f, y = 2.0f, width = 528.0f, height = 31.0f;
        juce::Colour fillColour1 = juce::Colour (0xff041518), fillColour2 = juce::Colour (0xff19313f);
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             0.0f - 1.0f + x,
                                             32.0f - 2.0f + y,
                                             fillColour2,
                                             528.0f - 1.0f + x,
                                             32.0f - 2.0f + y,
                                             false));
        g.fillRoundedRectangle (x, y, width, height, 5.000f);
        g.setColour (strokeColour);
        g.drawRoundedRectangle (x, y, width, height, 5.000f, 2.000f);
    }

    {
        int x = 304, y = 68, width = 216, height = 108;
        juce::Colour fillColour = juce::Colour (0x10c7c7c7);
        juce::Colour strokeColour = juce::Colour (0x1fffffff);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 16, y = 1, width = 100, height = 32;
        juce::String text (TRANS ("SPARTA|"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (18.80f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 92, y = 1, width = 124, height = 32;
        juce::String text (TRANS ("MatrixConv"));
        juce::Colour fillColour = juce::Colour (0xffe9ff00);
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (18.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 0, y = 0, width = 532, height = 2;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 0, width = 2, height = 184;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 528, y = 0, width = 2, height = 184;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 182, width = 532, height = 2;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 312, y = 66, width = 115, height = 30;
        juce::String text (TRANS ("Host Block Size:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 16, y = 144, width = 232, height = 30;
        juce::String text (TRANS ("Number of Filters in .wav File:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 312, y = 92, width = 200, height = 30;
        juce::String text (TRANS ("Filter Length (s):"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 312, y = 118, width = 128, height = 30;
        juce::String text (TRANS ("Filter Samplerate:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 312, y = 144, width = 144, height = 30;
        juce::String text (TRANS ("Host Samplerate:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 16, y = 92, width = 232, height = 30;
        juce::String text (TRANS ("Enable Partitioned Convolution:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 16, y = 40, width = 224, height = 30;
        juce::String text (TRANS ("Number of Input Channels:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 16, y = 118, width = 232, height = 31;
        juce::String text (TRANS ("Number of Output Channels:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 312, y = 39, width = 115, height = 30;
        juce::String text (TRANS ("Matrix:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 436, y = 40, width = 115, height = 30;
        juce::String text (TRANS ("x"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (18.00f, juce::Font::plain).withStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

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
