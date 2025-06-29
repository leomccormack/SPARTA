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
: AudioProcessorEditor(p), processor(p)
{
    CBsourceDirsPreset.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (CBsourceDirsPreset.get());
    CBsourceDirsPreset->setEditableText (false);
    CBsourceDirsPreset->setJustificationType (juce::Justification::centredLeft);
    CBsourceDirsPreset->setTextWhenNothingSelected (juce::String());
    CBsourceDirsPreset->setTextWhenNoChoicesAvailable (TRANS ("(no choices)"));
    CBsourceDirsPreset->addListener (this);

    CBsourceDirsPreset->setBounds (88, 96, 112, 20);

    SL_num_sources = std::make_unique<SliderWithAttachment>(p.parameters, "numSources");
    addAndMakeVisible (SL_num_sources.get());
    SL_num_sources->setSliderStyle (juce::Slider::LinearHorizontal);
    SL_num_sources->setTextBoxStyle (juce::Slider::TextBoxRight, false, 60, 20);
    SL_num_sources->addListener (this);

    SL_num_sources->setBounds (152, 126, 48, 20);

    CBoutputFormat = std::make_unique<ComboBoxWithAttachment>(p.parameters, "channelOrder");
    addAndMakeVisible (CBoutputFormat.get());
    CBoutputFormat->setEditableText (false);
    CBoutputFormat->setJustificationType (juce::Justification::centredLeft);
    CBoutputFormat->setTextWhenNothingSelected (TRANS ("ACN"));
    CBoutputFormat->setTextWhenNoChoicesAvailable (TRANS ("(no choices)"));
    CBoutputFormat->addListener (this);

    CBoutputFormat->setBounds (343, 316, 112, 20);

    CBnormalisation = std::make_unique<ComboBoxWithAttachment>(p.parameters, "normType");
    addAndMakeVisible (CBnormalisation.get());
    CBnormalisation->setEditableText (false);
    CBnormalisation->setJustificationType (juce::Justification::centredLeft);
    CBnormalisation->setTextWhenNothingSelected (TRANS ("N3D"));
    CBnormalisation->setTextWhenNoChoicesAvailable (TRANS ("(no choices)"));
    CBnormalisation->addListener (this);

    CBnormalisation->setBounds (578, 316, 112, 20);

    CBorder = std::make_unique<ComboBoxWithAttachment>(p.parameters, "outputOrder");
    addAndMakeVisible (CBorder.get());
    CBorder->setEditableText (false);
    CBorder->setJustificationType (juce::Justification::centredLeft);
    CBorder->setTextWhenNothingSelected (juce::String());
    CBorder->setTextWhenNoChoicesAvailable (TRANS ("(no choices)"));
    CBorder->addListener (this);

    CBorder->setBounds (88, 64, 112, 20);

    tb_loadJSON.reset (new juce::TextButton ("new button"));
    addAndMakeVisible (tb_loadJSON.get());
    tb_loadJSON->setButtonText (TRANS ("Import"));
    tb_loadJSON->setConnectedEdges (juce::Button::ConnectedOnRight);
    tb_loadJSON->addListener (this);
    tb_loadJSON->setColour (juce::TextButton::buttonColourId, juce::Colour (0xff14889e));

    tb_loadJSON->setBounds (140, 40, 34, 14);

    tb_saveJSON.reset (new juce::TextButton ("new button"));
    addAndMakeVisible (tb_saveJSON.get());
    tb_saveJSON->setButtonText (TRANS ("Export"));
    tb_saveJSON->setConnectedEdges (juce::Button::ConnectedOnLeft);
    tb_saveJSON->addListener (this);
    tb_saveJSON->setColour (juce::TextButton::buttonColourId, juce::Colour (0xff224d97));
    tb_saveJSON->setColour (juce::TextButton::buttonOnColourId, juce::Colour (0xff181f9a));

    tb_saveJSON->setBounds (174, 40, 34, 14);

    setSize (712, 356);

    /* handle to DSP object */
    hAmbi = processor.getFXHandle();

    /* init OpenGL */
#ifndef PLUGIN_EDITOR_DISABLE_OPENGL
    openGLContext.setMultisamplingEnabled(true);
    openGLContext.attachTo(*this);
#endif

    /* Look and Feel */
    LAF.setDefaultColours();
    setLookAndFeel(&LAF);

    /* remove slider bit of these sliders */
    SL_num_sources->setColour(Slider::trackColourId, Colours::transparentBlack);
    SL_num_sources->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    SL_num_sources->setSliderSnapsToMousePosition(false);

    /* add combo box options */
    CBsourceDirsPreset->addItem (TRANS("Mono"), SOURCE_CONFIG_PRESET_MONO);
    CBsourceDirsPreset->addItem (TRANS("Stereo"), SOURCE_CONFIG_PRESET_STEREO);
    CBsourceDirsPreset->addItem (TRANS("5.x"), SOURCE_CONFIG_PRESET_5PX);
    CBsourceDirsPreset->addItem (TRANS("7.x"), SOURCE_CONFIG_PRESET_7PX);
    CBsourceDirsPreset->addItem (TRANS("8.x"), SOURCE_CONFIG_PRESET_8PX);
    CBsourceDirsPreset->addItem (TRANS("9.x"), SOURCE_CONFIG_PRESET_9PX);
    CBsourceDirsPreset->addItem (TRANS("10.x"), SOURCE_CONFIG_PRESET_10PX);
    CBsourceDirsPreset->addItem (TRANS("11.x"), SOURCE_CONFIG_PRESET_11PX);
    CBsourceDirsPreset->addItem (TRANS("11.x (7+4)"), SOURCE_CONFIG_PRESET_11PX_7_4);
    CBsourceDirsPreset->addItem (TRANS("13.x"), SOURCE_CONFIG_PRESET_13PX);
    CBsourceDirsPreset->addItem (TRANS("22.x"), SOURCE_CONFIG_PRESET_22PX);
    CBsourceDirsPreset->addItem (TRANS("Aalto MCC"), SOURCE_CONFIG_PRESET_AALTO_MCC);
    CBsourceDirsPreset->addItem (TRANS("Aalto MCC-subset"), SOURCE_CONFIG_PRESET_AALTO_MCC_SUBSET);
    CBsourceDirsPreset->addItem (TRANS("Aalto Apaja"), SOURCE_CONFIG_PRESET_AALTO_APAJA);
    CBsourceDirsPreset->addItem (TRANS("Aalto LR"), SOURCE_CONFIG_PRESET_AALTO_LR);
    CBsourceDirsPreset->addItem (TRANS("DTU AVIL"), SOURCE_CONFIG_PRESET_DTU_AVIL);
    CBsourceDirsPreset->addItem (TRANS("T-design (4)"), SOURCE_CONFIG_PRESET_T_DESIGN_4);
    CBsourceDirsPreset->addItem (TRANS("T-design (12)"), SOURCE_CONFIG_PRESET_T_DESIGN_12);
    CBsourceDirsPreset->addItem (TRANS("T-design (24)"), SOURCE_CONFIG_PRESET_T_DESIGN_24);
    CBsourceDirsPreset->addItem (TRANS("T-design (36)"), SOURCE_CONFIG_PRESET_T_DESIGN_36);
    CBsourceDirsPreset->addItem (TRANS("T-design (48)"), SOURCE_CONFIG_PRESET_T_DESIGN_48);
    CBsourceDirsPreset->addItem (TRANS("T-design (60)"), SOURCE_CONFIG_PRESET_T_DESIGN_60);
    CBsourceDirsPreset->addItem (TRANS("SphCov (9)"), SOURCE_CONFIG_PRESET_SPH_COV_9);
    CBsourceDirsPreset->addItem (TRANS("SphCov (16)"), SOURCE_CONFIG_PRESET_SPH_COV_16);
    CBsourceDirsPreset->addItem (TRANS("SphCov (25)"), SOURCE_CONFIG_PRESET_SPH_COV_25);
    CBsourceDirsPreset->addItem (TRANS("SphCov (49)"), SOURCE_CONFIG_PRESET_SPH_COV_49);
    CBsourceDirsPreset->addItem (TRANS("SphCov (64)"), SOURCE_CONFIG_PRESET_SPH_COV_64);

    /* source coordinates viewport */
    sourceCoordsVP.reset (new Viewport ("new viewport"));
    addAndMakeVisible (sourceCoordsVP.get());
    sourceCoordsView_handle = new inputCoordsView(p, MAX_NUM_CHANNELS, ambi_enc_getNumSources(hAmbi));
    sourceCoordsVP->setViewedComponent (sourceCoordsView_handle);
    sourceCoordsVP->setScrollBarsShown (true, false);
    sourceCoordsVP->setAlwaysOnTop(true);
    sourceCoordsVP->setBounds(22, 183, 184, 155);
    sourceCoordsView_handle->setNCH(ambi_enc_getNumSources(hAmbi));

    /* grab current parameter settings */
    CBoutputFormat->setItemEnabled(CH_FUMA, ambi_enc_getOutputOrder(hAmbi)==SH_ORDER_FIRST ? true : false);
    CBnormalisation->setItemEnabled(NORM_FUMA, ambi_enc_getOutputOrder(hAmbi)==SH_ORDER_FIRST ? true : false);

    /* create panning window */
    panWindow.reset (new pannerView(p, 480, 240));
    addAndMakeVisible (panWindow.get());
    panWindow->setBounds (220, 58, 480, 240);
    refreshPanViewWindow = true;

    /* tooltips */
    CBorder->setTooltip("The encoding order. Note that the plug-in will output (order+1)^2 Ambisonic (spherical harmonic) signals.");
    CBoutputFormat->setTooltip("Ambisonic channel ordering convention (Note that AmbiX: ACN/SN3D).");
    CBnormalisation->setTooltip("Ambisonic normalisation scheme (Note that AmbiX: ACN/SN3D).");
    CBsourceDirsPreset->setTooltip("Presets for source encoding directions.");
    tb_loadJSON->setTooltip("Loads source encoding directions from a JSON file. The JSON file format follows the same convention as the one employed by the IEM plugin suite (https://plugins.iem.at/docs/configurationfiles/).");
    tb_saveJSON->setTooltip("Saves the current source encoding directions to a JSON file. The JSON file format follows the same convention as the one employed by the IEM plugin suite (https://plugins.iem.at/docs/configurationfiles/).");

    /* Plugin description */
    pluginDescription.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (pluginDescription.get());
    pluginDescription->setBounds (0, 0, 200, 32);
    pluginDescription->setAlpha(0.0f);
    pluginDescription->setEnabled(false);
    pluginDescription->setTooltip(TRANS("A simple Ambisonic encoder which takes input signals (up to 64 channels) and encodes them into Ambisonic signals at specified directions. Essentially, these Ambisonic signals describe a synthetic sound scene, where the spatial resolution of this encoding is determined by the transform order. Unlike Ambisonic signals derived from microphone arrays, the output Ambisonic signals from this plugin are considered to be perfect/\"ideal\"; i.e. without sensor noise or spatial aliasing (which is an order-dependent phenomenon determined by the physical design of the array), which results in order-dependent frequency limits above/below which the Ambisonic signals do not exhibit the correct patterns or are corrupted by excessive noise."));

	/* Specify screen refresh rate */
    startTimer(40);//80); /*ms (40ms = 25 frames per second) */

    /* warnings */
    currentWarning = k_warning_none;
}

PluginEditor::~PluginEditor()
{
    CBsourceDirsPreset = nullptr;
    SL_num_sources = nullptr;
    CBoutputFormat = nullptr;
    CBnormalisation = nullptr;
    CBorder = nullptr;
    tb_loadJSON = nullptr;
    tb_saveJSON = nullptr;

    setLookAndFeel(nullptr);
    sourceCoordsVP = nullptr;
    panWindow = nullptr;
}

void PluginEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::white);

    {
        int x = 0, y = 193, width = 712, height = 163;
        juce::Colour fillColour1 = juce::Colour (0xff19313f), fillColour2 = juce::Colour (0xff041518);
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             8.0f - 0.0f + x,
                                             360.0f - 193.0f + y,
                                             fillColour2,
                                             8.0f - 0.0f + x,
                                             280.0f - 193.0f + y,
                                             false));
        g.fillRect (x, y, width, height);
    }

    {
        int x = 0, y = 30, width = 712, height = 163;
        juce::Colour fillColour1 = juce::Colour (0xff19313f), fillColour2 = juce::Colour (0xff041518);
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             8.0f - 0.0f + x,
                                             32.0f - 30.0f + y,
                                             fillColour2,
                                             8.0f - 0.0f + x,
                                             128.0f - 30.0f + y,
                                             false));
        g.fillRect (x, y, width, height);
    }

    {
        float x = 1.0f, y = 2.0f, width = 710.0f, height = 31.0f;
        juce::Colour fillColour1 = juce::Colour (0xff041518), fillColour2 = juce::Colour (0xff19313f);
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             0.0f - 1.0f + x,
                                             32.0f - 2.0f + y,
                                             fillColour2,
                                             656.0f - 1.0f + x,
                                             24.0f - 2.0f + y,
                                             false));
        g.fillRoundedRectangle (x, y, width, height, 5.000f);
        g.setColour (strokeColour);
        g.drawRoundedRectangle (x, y, width, height, 5.000f, 2.000f);
    }

    {
        int x = 12, y = 89, width = 196, height = 64;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 20, y = 90, width = 67, height = 30;
        juce::String text (TRANS ("Presets: "));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (14.50f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 220, y = 58, width = 480, height = 240;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 12, y = 152, width = 196, height = 194;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 20, y = 120, width = 180, height = 30;
        juce::String text (TRANS ("Number of Inputs:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (14.50f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 72, y = 32, width = 96, height = 30;
        juce::String text (TRANS ("Encoding"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 405, y = 32, width = 163, height = 30;
        juce::String text (TRANS ("Panning Window"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 220, y = 306, width = 480, height = 40;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 231, y = 311, width = 145, height = 30;
        juce::String text (TRANS ("Channel Order:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 471, y = 311, width = 145, height = 30;
        juce::String text (TRANS ("Normalisation:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
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
        int x = 20, y = 60, width = 67, height = 30;
        juce::String text (TRANS ("Order: "));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 12, y = 58, width = 196, height = 32;
        juce::Colour fillColour = juce::Colour (0x08f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
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
        int x = 92, y = 1, width = 112, height = 32;
        juce::String text (TRANS ("AmbiENC"));
        juce::Colour fillColour = juce::Colour (0xfffb6f54);
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (18.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 66, y = 154, width = 108, height = 28;
        juce::String text (juce::CharPointer_UTF8 ("Azi\xc2\xb0   #   Elev\xc2\xb0"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 0, y = 0, width = 714, height = 2;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 354, width = 714, height = 2;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 0, width = 2, height = 356;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 710, y = 0, width = 2, height = 356;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

	g.setColour(Colours::white);
	g.setFont(juce::FontOptions(11.00f, Font::plain));
	g.drawText(TRANS("Ver ") + JucePlugin_VersionString + BUILD_VER_SUFFIX + TRANS(", Build Date ") + __DATE__ + TRANS(" "),
		185, 16, 530, 11,
		Justification::centredLeft, true);

    /* display warning message */
    g.setColour(Colours::red);
    g.setFont(juce::FontOptions(11.00f, Font::plain));
    switch (currentWarning){
        case k_warning_none:
            break;
        case k_warning_frameSize:
            g.drawText(TRANS("Set frame size to multiple of ") + String(ambi_enc_getFrameSize()),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NinputCH:
            g.drawText(TRANS("Insufficient number of input channels (") + String(processor.getTotalNumInputChannels()) +
                       TRANS("/") + String(ambi_enc_getNumSources(hAmbi)) + TRANS(")"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NoutputCH:
            g.drawText(TRANS("Insufficient number of output channels (") + String(processor.getTotalNumOutputChannels()) +
                       TRANS("/") + String(ambi_enc_getNSHrequired(hAmbi)) + TRANS(")"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
    }
}

void PluginEditor::resized()
{
}

void PluginEditor::comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged)
{
    if (comboBoxThatHasChanged == CBsourceDirsPreset.get())
    {
        ambi_enc_setInputConfigPreset(hAmbi, CBsourceDirsPreset->getSelectedId());
        
        processor.setParameterValue("numSources", ambi_enc_getNumSources(hAmbi));
        for(int i=0; i<ambi_enc_getNumSources(hAmbi); i++){
            processor.setParameterValue("azim" + juce::String(i), ambi_enc_getSourceAzi_deg(hAmbi,i));
            processor.setParameterValue("elev" + juce::String(i), ambi_enc_getSourceElev_deg(hAmbi,i));
        }
        
        refreshPanViewWindow = true;
    }
}

void PluginEditor::sliderValueChanged (juce::Slider* sliderThatWasMoved)
{
    if (sliderThatWasMoved == SL_num_sources.get())
    {
        for(int i=0; i<SL_num_sources->getValue(); i++){
            processor.setParameterValue("azim" + juce::String(i), ambi_enc_getSourceAzi_deg(hAmbi,i));
            processor.setParameterValue("elev" + juce::String(i), ambi_enc_getSourceElev_deg(hAmbi,i));
        }
        
        refreshPanViewWindow = true;
    }
}

void PluginEditor::buttonClicked (juce::Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == tb_loadJSON.get())
    {
        chooser = std::make_unique<juce::FileChooser> ("Load configuration...",
                                                       processor.getLastDir().exists() ? processor.getLastDir() : File::getSpecialLocation (File::userHomeDirectory),
                                                       "*.json");
        auto chooserFlags = juce::FileBrowserComponent::openMode
                                  | juce::FileBrowserComponent::canSelectFiles;
        chooser->launchAsync (chooserFlags, [this] (const FileChooser& fc) {
            auto file = fc.getResult();
            if (file != File{}){
                processor.setLastDir(file.getParentDirectory());
                processor.loadConfiguration (file);
            }
        });
    }
    else if (buttonThatWasClicked == tb_saveJSON.get())
    {
        chooser = std::make_unique<juce::FileChooser> ("Save configuration...",
                                                       processor.getLastDir().exists() ? processor.getLastDir() : File::getSpecialLocation (File::userHomeDirectory),
                                                       "*.json");
        auto chooserFlags = juce::FileBrowserComponent::saveMode;
        chooser->launchAsync (chooserFlags, [this] (const FileChooser& fc) {
            auto file = fc.getResult();
            if (file != File{}) {
                processor.setLastDir(file.getParentDirectory());
                processor.saveConfigurationToFile (file);
            }
        });
    }
}


void PluginEditor::timerCallback()
{
    /* parameters whos values can change internally should be periodically refreshed */
    sourceCoordsView_handle->setNCH(ambi_enc_getNumSources(hAmbi));
    CBoutputFormat->setSelectedId(ambi_enc_getChOrder(hAmbi), dontSendNotification);
    CBnormalisation->setSelectedId(ambi_enc_getNormType(hAmbi), sendNotification);
    CBoutputFormat->setItemEnabled(CH_FUMA, ambi_enc_getOutputOrder(hAmbi)==SH_ORDER_FIRST ? true : false);
    CBnormalisation->setItemEnabled(NORM_FUMA, ambi_enc_getOutputOrder(hAmbi)==SH_ORDER_FIRST ? true : false);

    /* refresh pan view */
    if((refreshPanViewWindow == true) || (panWindow->getSourceIconIsClicked()) || processor.getRefreshWindow()){
        panWindow->refreshPanView();
        refreshPanViewWindow = false;
        processor.setRefreshWindow(false);
    }

    /* display warning message, if needed */
    if ((processor.getCurrentBlockSize() % ambi_enc_getFrameSize()) != 0){
        currentWarning = k_warning_frameSize;
        repaint(0,0,getWidth(),32);
    }
    else if ((processor.getCurrentNumInputs() < ambi_enc_getNumSources(hAmbi))){
        currentWarning = k_warning_NinputCH;
        repaint(0,0,getWidth(),32);
    }
    else if ((processor.getCurrentNumOutputs() < ambi_enc_getNSHrequired(hAmbi))){
        currentWarning = k_warning_NoutputCH;
        repaint(0,0,getWidth(),32);
    }
    else if(currentWarning){
        currentWarning = k_warning_none;
        repaint(0,0,getWidth(),32);
    }
}

