/*
 ==============================================================================
 
 This file is part of SPARTA; a suite of spatial audio plug-ins.
 Copyright (c) 2021 - Leo McCormack.
 
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
    : AudioProcessorEditor(p), processor(p), progressbar(progress), fileChooser ("File", File(), true, false, false,
      "*.sofa;*.nc;", String(),
      "Load SOFA File")
{
    SL_num_sources = std::make_unique<SliderWithAttachment>(p.parameters, "numInputs");
    addAndMakeVisible (SL_num_sources.get());
    SL_num_sources->setSliderStyle (juce::Slider::LinearHorizontal);
    SL_num_sources->setTextBoxStyle (juce::Slider::TextBoxRight, false, 60, 20);
    SL_num_sources->addListener (this);
    SL_num_sources->setBounds (152, 65, 48, 20);

    label_N_dirs.reset (new juce::Label ("new label", juce::String()));
    addAndMakeVisible (label_N_dirs.get());
    label_N_dirs->setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Regular"));
    label_N_dirs->setJustificationType (juce::Justification::centredLeft);
    label_N_dirs->setEditable (false, false, false);
    label_N_dirs->setBounds (848, 207, 51, 20);

    label_HRIR_fs.reset (new juce::Label ("new label", juce::String()));
    addAndMakeVisible (label_HRIR_fs.get());
    label_HRIR_fs->setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Regular"));
    label_HRIR_fs->setJustificationType (juce::Justification::centredLeft);
    label_HRIR_fs->setEditable (false, false, false);
    label_HRIR_fs->setBounds (848, 255, 51, 20);

    TBuseDefaultHRIRs.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (TBuseDefaultHRIRs.get());
    TBuseDefaultHRIRs->setButtonText (juce::String());
    TBuseDefaultHRIRs->addListener (this);
    TBuseDefaultHRIRs->setBounds (876, 61, 32, 24);

    label_DAW_fs.reset (new juce::Label ("new label", juce::String()));
    addAndMakeVisible (label_DAW_fs.get());
    label_DAW_fs->setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Regular"));
    label_DAW_fs->setJustificationType (juce::Justification::centredLeft);
    label_DAW_fs->setEditable (false, false, false);
    label_DAW_fs->setBounds (848, 279, 51, 20);

    label_N_CH.reset (new juce::Label ("new label", juce::String()));
    addAndMakeVisible (label_N_CH.get());
    label_N_CH->setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Regular"));
    label_N_CH->setJustificationType (juce::Justification::centredLeft);
    label_N_CH->setEditable (false, false, false);
    label_N_CH->setBounds (848, 183, 51, 20);

    CBmode = std::make_unique<ComboBoxWithAttachment>(p.parameters, "procMode");
    addAndMakeVisible (CBmode.get());
    CBmode->setEditableText (false);
    CBmode->setJustificationType (juce::Justification::centredLeft);
    CBmode->setBounds (816, 125, 86, 20);

    label_IR_length.reset (new juce::Label ("new label", juce::String()));
    addAndMakeVisible (label_IR_length.get());
    label_IR_length->setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Regular"));
    label_IR_length->setJustificationType (juce::Justification::centredLeft);
    label_IR_length->setEditable (false, false, false);
    label_IR_length->setBounds (848, 231, 51, 20);

    SL_avgCoeff = std::make_unique<SliderWithAttachment>(p.parameters, "avgCoeff");
    addAndMakeVisible (SL_avgCoeff.get());
    SL_avgCoeff->setSliderStyle (juce::Slider::LinearHorizontal);
    SL_avgCoeff->setTextBoxStyle (juce::Slider::TextBoxRight, false, 45, 20);
    SL_avgCoeff->setBounds (805, 152, 96, 20);

    setSize (920, 316);

    /* handle to object */
    hSpr = processor.getFXHandle();

    /* init OpenGL */
#ifndef PLUGIN_EDITOR_DISABLE_OPENGL
    openGLContext.setMultisamplingEnabled(true);
    openGLContext.attachTo(*this);
#endif

    /* Look and Feel */
    setLookAndFeel(&LAF);

    /* remove slider bit of these sliders */
    SL_num_sources->setColour(Slider::trackColourId, Colours::transparentBlack);
    SL_num_sources->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    SL_num_sources->setSliderSnapsToMousePosition(false);

    /* ProgressBar */
    progress = 0.0;
    progressbar.setBounds(getLocalBounds().getCentreX()-175, getLocalBounds().getCentreY()-17, 350, 35);
    progressbar.ProgressBar::setAlwaysOnTop(true);
    progressbar.setColour(ProgressBar::backgroundColourId, Colours::gold);
    progressbar.setColour(ProgressBar::foregroundColourId, Colours::white);

    /* source coordinate viewport */
    sourceCoordsVP.reset (new Viewport ("new viewport"));
    addAndMakeVisible (sourceCoordsVP.get());
    sourceCoordsView_handle = new inputCoordsView(p, SPREADER_MAX_NUM_SOURCES, spreader_getNumSources(hSpr));
    sourceCoordsVP->setViewedComponent (sourceCoordsView_handle);
    sourceCoordsVP->setScrollBarsShown (true, false);
    sourceCoordsVP->setAlwaysOnTop(true);
    sourceCoordsVP->setBounds(22, 119, 184, 180);
    sourceCoordsView_handle->setNCH(spreader_getNumSources(hSpr));

    /* file loader */
    addAndMakeVisible (fileChooser);
    fileChooser.addListener (this);
    fileChooser.setBounds (718, 89, 180, 20);
    StringArray filenames;
    filenames.add(spreader_getSofaFilePath(hSpr));
    fileChooser.setRecentlyUsedFilenames(filenames);
    fileChooser.setFilenameIsEditable(true);

    /* grab current parameter settings */
    TBuseDefaultHRIRs->setToggleState(spreader_getUseDefaultHRIRsflag(hSpr), dontSendNotification);

    /* create panning window */
    panWindow.reset (new pannerView(p, 492, 246));
    addAndMakeVisible (panWindow.get());
    panWindow->setBounds (214, 58, 492, 246);
    panWindow->setShowInputs(true);
    panWindow->setShowOutputs(true);
    refreshPanViewWindow = true;

    /* tooltips */
    TBuseDefaultHRIRs->setTooltip("If this is 'ticked', the plug-in is using the default HRIR set from the Spatial_Audio_Framework.");
    fileChooser.setTooltip("Optionally, a custom IR set may be loaded via the SOFA standard. Note that if the plug-in fails to load the specified .sofa file, it will revert to the default IR data.");
    label_N_dirs->setTooltip("Number of IR directions in the current IR set.");
    label_N_CH->setTooltip("Number of triangles found when computing the Convex Hull of the IR grid.");
    label_HRIR_fs->setTooltip("Sampling rate used when measuring/modelling the IRs.");
    label_DAW_fs->setTooltip("Current sampling rate, as dictated by the DAW/Host.");
    SL_avgCoeff->setTooltip("Amount of parameter averaging (0: none, 0.99: lots).");

    /* Plugin description */
    pluginDescription.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (pluginDescription.get());
    pluginDescription->setBounds (0, 0, 200, 32);
    pluginDescription->setAlpha(0.0f);
    pluginDescription->setEnabled(false);
    pluginDescription->setTooltip(TRANS("An arbitrary array panner with coherent and incoherent spreading options. Basically, any array (up to 64 channel) that can be desribed based on a number of impulse response (IR) measurements and loaded as a SOFA file can be used (e.g. HRIRs, or microphone array IRs).\n"));
    addAndMakeVisible (publicationLink);
    publicationLink.setColour (HyperlinkButton::textColourId, Colours::lightblue);
    publicationLink.setBounds(getBounds().getWidth()-80, 4, 80, 12);
    publicationLink.setJustificationType(Justification::centredLeft);

	/* Specify screen refresh rate */
    startTimer(TIMER_GUI_RELATED, 40);

    /* warnings */
    currentWarning = k_warning_none;
}

PluginEditor::~PluginEditor()
{
    SL_num_sources = nullptr;
    label_N_dirs = nullptr;
    label_HRIR_fs = nullptr;
    TBuseDefaultHRIRs = nullptr;
    label_DAW_fs = nullptr;
    label_N_CH = nullptr;
    CBmode = nullptr;
    label_IR_length = nullptr;
    SL_avgCoeff = nullptr;

    setLookAndFeel(nullptr);
    panWindow = nullptr;
    sourceCoordsVP = nullptr;
}

void PluginEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::white);

    {
        int x = 0, y = 30, width = 920, height = 163;
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
        int x = 0, y = 193, width = 920, height = 127;
        juce::Colour fillColour1 = juce::Colour (0xff19313f), fillColour2 = juce::Colour (0xff041518);
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             8.0f - 0.0f + x,
                                             312.0f - 193.0f + y,
                                             fillColour2,
                                             8.0f - 0.0f + x,
                                             264.0f - 193.0f + y,
                                             false));
        g.fillRect (x, y, width, height);
    }

    {
        float x = 1.0f, y = 2.0f, width = 918.0f, height = 31.0f;
        juce::Colour fillColour1 = juce::Colour (0xff041518), fillColour2 = juce::Colour (0xff19313f);
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             0.0f - 1.0f + x,
                                             32.0f - 2.0f + y,
                                             fillColour2,
                                             920.0f - 1.0f + x,
                                             32.0f - 2.0f + y,
                                             false));
        g.fillRoundedRectangle (x, y, width, height, 5.000f);
        g.setColour (strokeColour);
        g.drawRoundedRectangle (x, y, width, height, 5.000f, 2.000f);
    }

    {
        int x = 712, y = 176, width = 196, height = 128;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 12, y = 58, width = 196, height = 32;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 214, y = 58, width = 492, height = 246;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 12, y = 89, width = 196, height = 215;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 712, y = 58, width = 196, height = 60;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 712, y = 117, width = 196, height = 60;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 23, y = 58, width = 153, height = 30;
        juce::String text (TRANS ("Number of Inputs:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (14.50f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 84, y = 32, width = 113, height = 30;
        juce::String text (TRANS ("Inputs"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 782, y = 32, width = 113, height = 30;
        juce::String text (TRANS ("Outputs"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 392, y = 32, width = 136, height = 30;
        juce::String text (TRANS ("Panning Window"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 720, y = 58, width = 160, height = 30;
        juce::String text (TRANS ("Use Default IR set:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 722, y = 274, width = 118, height = 30;
        juce::String text (TRANS ("DAW Samplerate:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
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
        int x = 92, y = 1, width = 112, height = 32;
        juce::String text (TRANS ("Spreader"));
        juce::Colour fillColour = juce::Colour (0xfffff973);
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (18.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 16, y = 89, width = 192, height = 28;
        juce::String text (juce::CharPointer_UTF8 ("   #    Azi\xc2\xb0     Elev\xc2\xb0    Spread\xc2\xb0"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 0, y = 0, width = 922, height = 2;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 0, width = 2, height = 360;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 918, y = 0, width = 2, height = 360;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 314, width = 920, height = 2;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 722, y = 250, width = 118, height = 30;
        juce::String text (TRANS ("IR Samplerate:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 722, y = 202, width = 126, height = 30;
        juce::String text (TRANS ("Num Directions:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 722, y = 226, width = 89, height = 30;
        juce::String text (TRANS ("IR length:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 722, y = 118, width = 89, height = 30;
        juce::String text (TRANS ("Spread Mode:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 722, y = 178, width = 142, height = 30;
        juce::String text (TRANS ("Num Channels:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 722, y = 146, width = 89, height = 30;
        juce::String text (TRANS ("Avg Coeff:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

	g.setColour(Colours::white);
	g.setFont(juce::FontOptions (11.00f, Font::plain));
	g.drawText(TRANS("Ver ") + JucePlugin_VersionString + BUILD_VER_SUFFIX + TRANS(", Build Date ") + __DATE__ + TRANS(" "),
		200, 16, 530, 11,
		Justification::centredLeft, true);

    /* display warning message */
    g.setColour(Colours::red);
    g.setFont(juce::FontOptions (11.00f, Font::plain));
    switch (currentWarning){
        case k_warning_none:
            break;
        case k_warning_frameSize:
            g.drawText(TRANS("Set frame size to multiple of ") + String(spreader_getFrameSize()),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_supported_fs:
            g.drawText(TRANS("Sample rate (") + String(spreader_getDAWsamplerate(hSpr)) + TRANS(") is unsupported"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_mismatch_fs:
            g.drawText(TRANS("Sample rate mismatch between DAW/HRIRs"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NinputCH:
            g.drawText(TRANS("Insufficient number of input channels (") + String(processor.getTotalNumInputChannels()) +
                       TRANS("/") + String(spreader_getNumSources(hSpr)) + TRANS(")"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NoutputCH:
            g.drawText(TRANS("Insufficient number of output channels (") + String(processor.getTotalNumOutputChannels()) +
                       TRANS("/") + String(spreader_getNumOutputs(hSpr)) + TRANS(")"),
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
    if (sliderThatWasMoved == SL_num_sources.get())
    {
        refreshPanViewWindow = true;
    }
}

void PluginEditor::buttonClicked (juce::Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == TBuseDefaultHRIRs.get())
    {
        spreader_setUseDefaultHRIRsflag(hSpr, (int)TBuseDefaultHRIRs->getToggleState());
        refreshPanViewWindow = true;
    }
}

void PluginEditor::comboBoxChanged (juce::ComboBox* /*comboBoxThatHasChanged*/)
{
}

void PluginEditor::timerCallback(int timerID)
{
    switch(timerID){
        case TIMER_PROCESSING_RELATED:
            /* handled in PluginProcessor */
            break;

        case TIMER_GUI_RELATED:

            /* labels for HRIR details */
            label_N_dirs->setText(String(spreader_getNDirs(hSpr)), dontSendNotification);
            label_HRIR_fs->setText(String(spreader_getIRsamplerate(hSpr)), dontSendNotification);
            label_DAW_fs->setText(String(spreader_getDAWsamplerate(hSpr)), dontSendNotification);
            label_N_CH->setText(String(spreader_getNumOutputs(hSpr)), dontSendNotification);
            label_IR_length->setText(String(spreader_getIRlength(hSpr)), dontSendNotification);

            /* parameters whos values can change internally should be periodically refreshed */
            sourceCoordsView_handle->setNCH(spreader_getNumSources(hSpr));
            TBuseDefaultHRIRs->setToggleState(spreader_getUseDefaultHRIRsflag(hSpr), dontSendNotification);

            /* Progress bar */
            if(spreader_getCodecStatus(hSpr)==CODEC_STATUS_INITIALISING){
                addAndMakeVisible(progressbar);
                progress = (double)spreader_getProgressBar0_1(hSpr);
                char text[PROGRESSBARTEXT_CHAR_LENGTH];
                spreader_getProgressBarText(hSpr, (char*)text);
                progressbar.setTextToDisplay(String(text));
            }
            else
                removeChildComponent(&progressbar);

            /* disable certain parameters if currently initialising */
            if(spreader_getCodecStatus(hSpr)==CODEC_STATUS_INITIALISING){
                if(SL_num_sources->isEnabled())
                    SL_num_sources->setEnabled(false);
                if(TBuseDefaultHRIRs->isEnabled())
                    TBuseDefaultHRIRs->setEnabled(false);
                if(fileChooser.isEnabled())
                   fileChooser.setEnabled(false);
                if(sourceCoordsVP->isEnabled())
                   sourceCoordsVP->setEnabled(false);
            }
            else{
                if(!SL_num_sources->isEnabled())
                    SL_num_sources->setEnabled(true);
                if(!TBuseDefaultHRIRs->isEnabled())
                    TBuseDefaultHRIRs->setEnabled(true);
                if(!fileChooser.isEnabled())
                    fileChooser.setEnabled(true);
                if(!sourceCoordsVP->isEnabled())
                    sourceCoordsVP->setEnabled(true);
            }

            /* refresh pan view */
            if((refreshPanViewWindow == true) || (panWindow->getSourceIconIsClicked()) || processor.getRefreshWindow()){
                panWindow->refreshPanView();
                refreshPanViewWindow = false;
                processor.setRefreshWindow(false);
            }

            /* display warning message, if needed */
            if ((processor.getCurrentBlockSize() % spreader_getFrameSize()) != 0){
                currentWarning = k_warning_frameSize;
                repaint(0,0,getWidth(),32);
            }
            else if ( !((spreader_getDAWsamplerate(hSpr) == 44.1e3) || (spreader_getDAWsamplerate(hSpr) == 48e3)) ){
                currentWarning = k_warning_supported_fs;
                repaint(0,0,getWidth(),32);
            }
            else if (spreader_getDAWsamplerate(hSpr) != spreader_getIRsamplerate(hSpr)){
                currentWarning = k_warning_mismatch_fs;
                repaint(0,0,getWidth(),32);
            }
            else if ((processor.getCurrentNumInputs() < spreader_getNumSources(hSpr))){
                currentWarning = k_warning_NinputCH;
                repaint(0,0,getWidth(),32);
            }
            else if ((processor.getCurrentNumOutputs() < spreader_getNumOutputs(hSpr))){
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
