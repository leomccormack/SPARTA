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

PluginEditor::PluginEditor (PluginProcessor* ownerFilter)
    : AudioProcessorEditor(ownerFilter), fileChooser ("File", File(), true, false, false,
      "*.wav;", String(),
      "Load .wav File")
{
    TBenablePartConv.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (TBenablePartConv.get());
    TBenablePartConv->setButtonText (juce::String());
    TBenablePartConv->addListener (this);

    TBenablePartConv->setBounds (261, 121, 26, 26);

    label_hostBlockSize.reset (new juce::Label ("new label",
                                                juce::String()));
    addAndMakeVisible (label_hostBlockSize.get());
    label_hostBlockSize->setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Regular"));
    label_hostBlockSize->setJustificationType (juce::Justification::centredLeft);
    label_hostBlockSize->setEditable (false, false, false);
    label_hostBlockSize->setColour (juce::Label::outlineColourId, juce::Colour (0x68a3a2a2));
    label_hostBlockSize->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    label_hostBlockSize->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    label_hostBlockSize->setBounds (451, 45, 60, 20);

    label_NFilters.reset (new juce::Label ("new label",
                                           juce::String()));
    addAndMakeVisible (label_NFilters.get());
    label_NFilters->setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Regular"));
    label_NFilters->setJustificationType (juce::Justification::centredLeft);
    label_NFilters->setEditable (false, false, false);
    label_NFilters->setColour (juce::Label::outlineColourId, juce::Colour (0x68a3a2a2));
    label_NFilters->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    label_NFilters->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    label_NFilters->setBounds (237, 99, 48, 20);

    label_filterLength.reset (new juce::Label ("new label",
                                               juce::String()));
    addAndMakeVisible (label_filterLength.get());
    label_filterLength->setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Regular"));
    label_filterLength->setJustificationType (juce::Justification::centredLeft);
    label_filterLength->setEditable (false, false, false);
    label_filterLength->setColour (juce::Label::outlineColourId, juce::Colour (0x68a3a2a2));
    label_filterLength->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    label_filterLength->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    label_filterLength->setBounds (451, 72, 60, 20);

    label_hostfs.reset (new juce::Label ("new label",
                                         juce::String()));
    addAndMakeVisible (label_hostfs.get());
    label_hostfs->setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Regular"));
    label_hostfs->setJustificationType (juce::Justification::centredLeft);
    label_hostfs->setEditable (false, false, false);
    label_hostfs->setColour (juce::Label::outlineColourId, juce::Colour (0x68a3a2a2));
    label_hostfs->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    label_hostfs->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    label_hostfs->setBounds (451, 126, 60, 20);

    label_filterfs.reset (new juce::Label ("new label",
                                           juce::String()));
    addAndMakeVisible (label_filterfs.get());
    label_filterfs->setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Regular"));
    label_filterfs->setJustificationType (juce::Justification::centredLeft);
    label_filterfs->setEditable (false, false, false);
    label_filterfs->setColour (juce::Label::outlineColourId, juce::Colour (0x68a3a2a2));
    label_filterfs->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    label_filterfs->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    label_filterfs->setBounds (451, 99, 60, 20);

    SL_num_inputs.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (SL_num_inputs.get());
    SL_num_inputs->setRange (1, 128, 1);
    SL_num_inputs->setSliderStyle (juce::Slider::LinearHorizontal);
    SL_num_inputs->setTextBoxStyle (juce::Slider::TextBoxRight, false, 55, 20);
    SL_num_inputs->addListener (this);

    SL_num_inputs->setBounds (237, 46, 48, 20);

    setSize (530, 160);

	hVst = ownerFilter;
    hMC = hVst->getFXHandle();

    /* Look and Feel */
    LAF.setDefaultColours();
    setLookAndFeel(&LAF);

    /* remove slider bit of these sliders */
    SL_num_inputs->setColour(Slider::trackColourId, Colours::transparentBlack);
    SL_num_inputs->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    SL_num_inputs->setSliderSnapsToMousePosition(false);

    /* file loader */
    addAndMakeVisible (fileChooser);
    fileChooser.addListener (this);
    fileChooser.setBounds (16, 72, 268, 20);
    if(hVst->getWavDirectory() != TRANS("no_file"))
        fileChooser.setCurrentFile(hVst->getWavDirectory(), true);

	/* fetch current configuration */
    TBenablePartConv->setToggleState((bool)multiconv_getEnablePart(hMC), dontSendNotification);
    SL_num_inputs->setValue(multiconv_getNumChannels(hMC), dontSendNotification);
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
    TBenablePartConv = nullptr;
    label_hostBlockSize = nullptr;
    label_NFilters = nullptr;
    label_filterLength = nullptr;
    label_hostfs = nullptr;
    label_filterfs = nullptr;
    SL_num_inputs = nullptr;

    setLookAndFeel(nullptr);
}

void PluginEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::white);

    {
        int x = 0, y = 95, width = 530, height = 65;
        juce::Colour fillColour1 = juce::Colour (0xff19313f), fillColour2 = juce::Colour (0xff041518);
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             8.0f - 0.0f + x,
                                             160.0f - 95.0f + y,
                                             fillColour2,
                                             8.0f - 0.0f + x,
                                             112.0f - 95.0f + y,
                                             false));
        g.fillRect (x, y, width, height);
    }

    {
        int x = 0, y = 30, width = 530, height = 65;
        juce::Colour fillColour1 = juce::Colour (0xff19313f), fillColour2 = juce::Colour (0xff041518);
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             8.0f - 0.0f + x,
                                             32.0f - 30.0f + y,
                                             fillColour2,
                                             8.0f - 0.0f + x,
                                             80.0f - 30.0f + y,
                                             false));
        g.fillRect (x, y, width, height);
    }

    {
        int x = 8, y = 39, width = 288, height = 112;
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
        int x = 304, y = 39, width = 216, height = 112;
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
        juce::String text (TRANS ("MultiConv"));
        juce::Colour fillColour = juce::Colour (0xff7deeff);
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
        int x = 0, y = 0, width = 2, height = 160;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 528, y = 0, width = 2, height = 160;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 158, width = 532, height = 2;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 312, y = 40, width = 115, height = 30;
        juce::String text (TRANS ("Host Block Size:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 16, y = 92, width = 232, height = 30;
        juce::String text (TRANS ("Number of Filters in .wav File:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 312, y = 66, width = 200, height = 30;
        juce::String text (TRANS ("Filter Length (s):"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 312, y = 92, width = 128, height = 30;
        juce::String text (TRANS ("Filter Samplerate:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 312, y = 118, width = 144, height = 30;
        juce::String text (TRANS ("Host Samplerate:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 16, y = 118, width = 288, height = 30;
        juce::String text (TRANS ("Enable Partitioned Convolution:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 16, y = 40, width = 224, height = 30;
        juce::String text (TRANS ("Number of In/Output Channels:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 16, y = 66, width = 208, height = 30;
        juce::String text (TRANS ("Filters:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    /* display version/date built */
	g.setColour(Colours::white);
	g.setFont(juce::FontOptions (11.00f, Font::plain));
	g.drawText(TRANS("Ver ") + JucePlugin_VersionString + BUILD_VER_SUFFIX + TRANS(", Build Date ") + __DATE__ + TRANS(" "),
		190, 16, 530, 11,
		Justification::centredLeft, true);

    /* display warning message */
    g.setColour(Colours::red);
    g.setFont(juce::FontOptions (11.00f, Font::plain));
    switch (currentWarning){
        case k_warning_none:
            break;
        case k_warning_nCH_nFilters_missmatch:
            g.drawText(TRANS("Number of inputs does not match number of filters"),
                       getBounds().getWidth()-250, 5, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_sampleRate_missmatch:
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

void PluginEditor::buttonClicked (juce::Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == TBenablePartConv.get())
    {
        multiconv_setEnablePart(hMC, (int)TBenablePartConv->getToggleState());
    }
}

void PluginEditor::sliderValueChanged (juce::Slider* sliderThatWasMoved)
{
    if (sliderThatWasMoved == SL_num_inputs.get())
    {
        multiconv_setNumChannels(hMC, (int)SL_num_inputs->getValue());
    }
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

