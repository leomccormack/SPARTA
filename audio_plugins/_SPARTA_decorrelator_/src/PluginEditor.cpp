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
    : AudioProcessorEditor(ownerFilter), progressbar(progress)
{
    SL_nChannels.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (SL_nChannels.get());
    SL_nChannels->setRange (1, 128, 1);
    SL_nChannels->setSliderStyle (juce::Slider::LinearHorizontal);
    SL_nChannels->setTextBoxStyle (juce::Slider::TextBoxLeft, false, 80, 20);
    SL_nChannels->addListener (this);

    SL_nChannels->setBounds (171, 50, 65, 16);

    SL_decorAmount.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (SL_decorAmount.get());
    SL_decorAmount->setRange (0, 1, 0.01);
    SL_decorAmount->setSliderStyle (juce::Slider::LinearHorizontal);
    SL_decorAmount->setTextBoxStyle (juce::Slider::TextBoxRight, false, 50, 20);
    SL_decorAmount->addListener (this);

    SL_decorAmount->setBounds (128, 73, 108, 18);

    tb_compLevel.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (tb_compLevel.get());
    tb_compLevel->setButtonText (juce::String());
    tb_compLevel->addListener (this);

    tb_compLevel->setBounds (393, 47, 23, 24);

    tb_bypassTransients.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (tb_bypassTransients.get());
    tb_bypassTransients->setButtonText (juce::String());
    tb_bypassTransients->addListener (this);

    tb_bypassTransients->setBounds (393, 72, 23, 24);

    setSize (440, 110);

    /* handles */
	hVst = ownerFilter;
    hDecor = hVst->getFXHandle();

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
    LAF.setDefaultColours();
    setLookAndFeel(&LAF);

    /* ProgressBar */
    progress = 0.0;
    progressbar.setBounds(getLocalBounds().getCentreX()-175, getLocalBounds().getCentreY()-17, 350, 35);
    progressbar.ProgressBar::setAlwaysOnTop(true);
    progressbar.setColour(ProgressBar::backgroundColourId, Colours::gold);
    progressbar.setColour(ProgressBar::foregroundColourId, Colours::white);

    /* grab current parameter settings */
    SL_nChannels->setValue(decorrelator_getNumberOfChannels(hDecor), dontSendNotification);
    SL_decorAmount->setValue(decorrelator_getDecorrelationAmount(hDecor), dontSendNotification);
    tb_compLevel->setToggleState((bool)decorrelator_getLevelCompensationFlag(hDecor), dontSendNotification);
    tb_bypassTransients->setToggleState((bool)decorrelator_getTransientBypassFlag(hDecor), dontSendNotification);

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

    startTimer(TIMER_GUI_RELATED, 20);

    /* warnings */
    currentWarning = k_warning_none;
}

PluginEditor::~PluginEditor()
{
    SL_nChannels = nullptr;
    SL_decorAmount = nullptr;
    tb_compLevel = nullptr;
    tb_bypassTransients = nullptr;

    setLookAndFeel(nullptr);
}

void PluginEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::white);

    {
        int x = 0, y = 70, width = 440, height = 40;
        juce::Colour fillColour1 = juce::Colour (0xff19313f), fillColour2 = juce::Colour (0xff041518);
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             16.0f - 0.0f + x,
                                             120.0f - 70.0f + y,
                                             fillColour2,
                                             16.0f - 0.0f + x,
                                             88.0f - 70.0f + y,
                                             false));
        g.fillRect (x, y, width, height);
    }

    {
        int x = 0, y = 30, width = 440, height = 40;
        juce::Colour fillColour1 = juce::Colour (0xff19313f), fillColour2 = juce::Colour (0xff041518);
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             8.0f - 0.0f + x,
                                             32.0f - 30.0f + y,
                                             fillColour2,
                                             8.0f - 0.0f + x,
                                             64.0f - 30.0f + y,
                                             false));
        g.fillRect (x, y, width, height);
    }

    {
        float x = 1.0f, y = 2.0f, width = 438.0f, height = 31.0f;
        juce::Colour fillColour1 = juce::Colour (0xff041518), fillColour2 = juce::Colour (0xff19313f);
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             0.0f - 1.0f + x,
                                             32.0f - 2.0f + y,
                                             fillColour2,
                                             592.0f - 1.0f + x,
                                             32.0f - 2.0f + y,
                                             false));
        g.fillRoundedRectangle (x, y, width, height, 5.000f);
        g.setColour (strokeColour);
        g.drawRoundedRectangle (x, y, width, height, 5.000f, 2.000f);
    }

    {
        int x = 12, y = 44, width = 412, height = 54;
        juce::Colour fillColour = juce::Colour (0x08f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x35a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 18, y = 43, width = 173, height = 30;
        juce::String text (TRANS ("Number of Channels:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (14.50f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 16, y = 1, width = 196, height = 32;
        juce::String text (TRANS ("SPARTA|"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (18.80f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 92, y = 1, width = 184, height = 32;
        juce::String text (TRANS ("Decorrelator"));
        juce::Colour fillColour = juce::Colour (0xffbeffba);
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (18.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 0, y = 0, width = 440, height = 2;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 438, y = 0, width = 2, height = 120;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 0, width = 2, height = 120;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 108, width = 440, height = 2;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 18, y = 67, width = 173, height = 30;
        juce::String text (TRANS ("Decorrelation:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (14.50f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 266, y = 67, width = 134, height = 30;
        juce::String text (TRANS ("Bypass Transients:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (14.50f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 266, y = 43, width = 158, height = 30;
        juce::String text (TRANS ("Compensate Level:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (14.50f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

	g.setColour(Colours::white);
	g.setFont(juce::FontOptions (11.00f, Font::plain));
	g.drawText(TRANS("Ver ") + JucePlugin_VersionString + BUILD_VER_SUFFIX + TRANS(", Build Date ") + __DATE__ + TRANS(" "),
		198, 16, 530, 11,
		Justification::centredLeft, true);

    /* display warning message */
    g.setColour(Colours::red);
    g.setFont(juce::FontOptions (11.00f, Font::plain));
    switch (currentWarning){
        case k_warning_none:
            break;
        case k_warning_frameSize:
            g.drawText(TRANS("Set frame size to multiple of ") + String(decorrelator_getFrameSize()),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_supported_fs:
            g.drawText(TRANS("Sample rate (") + String(decorrelator_getDAWsamplerate(hDecor)) + TRANS(") is unsupported"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NinputCH:
            g.drawText(TRANS("Insufficient number of input channels (") + String(hVst->getTotalNumInputChannels()) +
                       TRANS("/") + String(decorrelator_getNumberOfChannels(hDecor)) + TRANS(")"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NoutputCH:
            g.drawText(TRANS("Insufficient number of output channels (") + String(hVst->getTotalNumOutputChannels()) +
                       TRANS("/") + String(decorrelator_getNumberOfChannels(hDecor)) + TRANS(")"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
    }
}

void PluginEditor::resized()
{
}

void PluginEditor::sliderValueChanged (juce::Slider* sliderThatWasMoved)
{
    if (sliderThatWasMoved == SL_nChannels.get())
    {
        decorrelator_setNumberOfChannels(hDecor, (int)SL_nChannels->getValue());
    }
    else if (sliderThatWasMoved == SL_decorAmount.get())
    {
        decorrelator_setDecorrelationAmount(hDecor, (float)SL_decorAmount->getValue());
    }
}

void PluginEditor::buttonClicked (juce::Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == tb_compLevel.get())
    {
        decorrelator_setLevelCompensationFlag(hDecor, (int)tb_compLevel->getToggleState());
    }
    else if (buttonThatWasClicked == tb_bypassTransients.get())
    {
        decorrelator_setTransientBypassFlag(hDecor, (int)tb_bypassTransients->getToggleState());
    }
}

void PluginEditor::timerCallback(int timerID)
{
    switch(timerID){
        case TIMER_PROCESSING_RELATED:
            /* Handled in PluginProcessor */
            break;

        case TIMER_GUI_RELATED:
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
            if ((hVst->getCurrentBlockSize() % decorrelator_getFrameSize()) != 0){
                currentWarning = k_warning_frameSize;
                repaint(0,0,getWidth(),32);
            }
            else if ( !((decorrelator_getDAWsamplerate(hDecor) == 44.1e3) || (decorrelator_getDAWsamplerate(hDecor) == 48e3)) ){
                currentWarning = k_warning_supported_fs;
                repaint(0,0,getWidth(),32);
            }
            else if ((hVst->getCurrentNumInputs() < decorrelator_getNumberOfChannels(hDecor))){
                currentWarning = k_warning_NinputCH;
                repaint(0,0,getWidth(),32);
            }
            else if ((hVst->getCurrentNumOutputs() < decorrelator_getNumberOfChannels(hDecor))){
                currentWarning = k_warning_NoutputCH;
                repaint(0,0,getWidth(),32);
            }
            else if(currentWarning){
                currentWarning = k_warning_none;
                repaint(0,0,getWidth(),32);
            }
            break;
    }
}
