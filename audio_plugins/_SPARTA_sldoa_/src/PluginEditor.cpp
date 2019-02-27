/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.4.1

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...

//[/Headers]

#include "PluginEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...

//[/MiscUserDefs]

//==============================================================================
PluginEditor::PluginEditor (PluginProcessor* ownerFilter)
    : AudioProcessorEditor(ownerFilter)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    avgSlider.reset (new Slider ("new slider"));
    addAndMakeVisible (avgSlider.get());
    avgSlider->setRange (0, 2000, 0.1);
    avgSlider->setSliderStyle (Slider::LinearHorizontal);
    avgSlider->setTextBoxStyle (Slider::TextBoxRight, false, 45, 20);
    avgSlider->addListener (this);

    avgSlider->setBounds (80, 465, 118, 24);

    CB_CHorder.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (CB_CHorder.get());
    CB_CHorder->setEditableText (false);
    CB_CHorder->setJustificationType (Justification::centredLeft);
    CB_CHorder->setTextWhenNothingSelected (TRANS("ACN"));
    CB_CHorder->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CB_CHorder->addItem (TRANS("ACN"), 1);
    CB_CHorder->addListener (this);

    CB_CHorder->setBounds (66, 439, 62, 18);

    CB_Norm.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (CB_Norm.get());
    CB_Norm->setEditableText (false);
    CB_Norm->setJustificationType (Justification::centredLeft);
    CB_Norm->setTextWhenNothingSelected (TRANS("N3D"));
    CB_Norm->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CB_Norm->addItem (TRANS("N3D"), 1);
    CB_Norm->addItem (TRANS("SN3D"), 2);
    CB_Norm->addListener (this);

    CB_Norm->setBounds (131, 439, 68, 18);

    slider_anaOrder.reset (new Slider ("new slider"));
    addAndMakeVisible (slider_anaOrder.get());
    slider_anaOrder->setRange (0, 1, 1);
    slider_anaOrder->setSliderStyle (Slider::LinearVertical);
    slider_anaOrder->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    slider_anaOrder->setColour (Slider::textBoxTextColourId, Colours::white);
    slider_anaOrder->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    slider_anaOrder->addListener (this);

    slider_anaOrder->setBounds (576, 416, 40, 66);

    CBinputTypePreset.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (CBinputTypePreset.get());
    CBinputTypePreset->setEditableText (false);
    CBinputTypePreset->setJustificationType (Justification::centredLeft);
    CBinputTypePreset->setTextWhenNothingSelected (TRANS("Default"));
    CBinputTypePreset->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBinputTypePreset->addItem (TRANS("Ideal SH"), 1);
    CBinputTypePreset->addListener (this);

    CBinputTypePreset->setBounds (96, 409, 103, 18);

    s_minFreq.reset (new Slider ("new slider"));
    addAndMakeVisible (s_minFreq.get());
    s_minFreq->setRange (0, 24000, 0.1);
    s_minFreq->setSliderStyle (Slider::LinearHorizontal);
    s_minFreq->setTextBoxStyle (Slider::TextBoxRight, false, 45, 20);
    s_minFreq->addListener (this);

    s_minFreq->setBounds (312, 372, 96, 24);

    s_maxFreq.reset (new Slider ("new slider"));
    addAndMakeVisible (s_maxFreq.get());
    s_maxFreq->setRange (0, 24000, 0.1);
    s_maxFreq->setSliderStyle (Slider::LinearHorizontal);
    s_maxFreq->setTextBoxStyle (Slider::TextBoxRight, false, 45, 20);
    s_maxFreq->addListener (this);

    s_maxFreq->setBounds (520, 372, 96, 24);

    CBmasterOrder.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (CBmasterOrder.get());
    CBmasterOrder->setEditableText (false);
    CBmasterOrder->setJustificationType (Justification::centredLeft);
    CBmasterOrder->setTextWhenNothingSelected (TRANS("Default"));
    CBmasterOrder->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBmasterOrder->addListener (this);

    CBmasterOrder->setBounds (96, 376, 103, 18);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (634, 502);


    //[Constructor] You can add your own custom stuff here..
	hVst = ownerFilter;
	openGLContext.setMultisamplingEnabled(true);
    openGLContext.attachTo(*this);

    addAndMakeVisible (overlayIncluded = new overlay(ownerFilter));
    overlayIncluded->setAlwaysOnTop(true);
    overlayIncluded->setBounds(17, 48, 600, 300);

    /* create 2d Slider for the decoding order parameter */
    int nPoints;
    float* pX_vector;
    int* pY_values_int;
    addAndMakeVisible (anaOrder2dSlider = new log2dSlider(360, 54, 100, 20e3, 1, sldoa_getMasterOrder(hVst->hSld), 0));
    anaOrder2dSlider->setAlwaysOnTop(true);
    anaOrder2dSlider->setTopLeftPosition(218, 422);
    sldoa_getAnaOrderHandle(hVst->hSld, &pX_vector, &pY_values_int, &nPoints);
    anaOrder2dSlider->setDataHandlesInt(pX_vector, pY_values_int, nPoints);

    /* add master analysis order options */
    CBmasterOrder->addItem (TRANS("1st order"), MASTER_ORDER_FIRST);
    CBmasterOrder->addItem (TRANS("2nd order"), MASTER_ORDER_SECOND);
    CBmasterOrder->addItem (TRANS("3rd order"), MASTER_ORDER_THIRD);
    CBmasterOrder->addItem (TRANS("4th order"), MASTER_ORDER_FOURTH);
    CBmasterOrder->addItem (TRANS("5th order"), MASTER_ORDER_FIFTH);
    CBmasterOrder->addItem (TRANS("6th order"), MASTER_ORDER_SIXTH);
    CBmasterOrder->addItem (TRANS("7th order"), MASTER_ORDER_SEVENTH);

    /* add microphone preset options */
#ifdef ENABLE_ZYLIA_MIC_PRESET
    CBinputTypePreset->addItem(TRANS("Zylia"), MIC_PRESET_ZYLIA);
#endif
#ifdef ENABLE_EIGENMIKE32_MIC_PRESET
    CBinputTypePreset->addItem(TRANS("Eigenmike"), MIC_PRESET_EIGENMIKE32);
#endif
#ifdef ENABLE_DTU_MIC_MIC_PRESET
    CBinputTypePreset->addItem(TRANS("DTU mic"), MIC_PRESET_DTU_MIC);
#endif

	/* fetch current configuration */
    CBmasterOrder->setSelectedId(sldoa_getMasterOrder(hVst->hSld), dontSendNotification);
    avgSlider->setValue((float)sldoa_getAvg(hVst->hSld), dontSendNotification);
    CB_CHorder->setSelectedId(sldoa_getChOrder(hVst->hSld), dontSendNotification);
    CB_Norm->setSelectedId(sldoa_getNormType(hVst->hSld), dontSendNotification);
    slider_anaOrder->setRange(1, sldoa_getMasterOrder(hVst->hSld), 1);
    slider_anaOrder->setValue(sldoa_getAnaOrderAllBands(hVst->hSld), dontSendNotification);
    s_minFreq->setRange(0.0f, sldoa_getSamplingRate(hVst->hSld)/2.0f, 1.0f);
    s_maxFreq->setRange(0.0f, sldoa_getSamplingRate(hVst->hSld)/2.0f, 1.0f);
    s_minFreq->setSkewFactor(0.5f);
    s_maxFreq->setSkewFactor(0.5f);
    s_minFreq->setValue(sldoa_getMinFreq(hVst->hSld));
    s_maxFreq->setValue(sldoa_getMaxFreq(hVst->hSld));

	/* Specify screen refresh rate */
    startTimer(100);//80); /*ms (40ms = 25 frames per second) */

    /* warnings */
    currentWarning = k_warning_none;

    //[/Constructor]
}

PluginEditor::~PluginEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    avgSlider = nullptr;
    CB_CHorder = nullptr;
    CB_Norm = nullptr;
    slider_anaOrder = nullptr;
    CBinputTypePreset = nullptr;
    s_minFreq = nullptr;
    s_maxFreq = nullptr;
    CBmasterOrder = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    overlayIncluded = nullptr;
    anaOrder2dSlider = nullptr;
    //[/Destructor]
}

//==============================================================================
void PluginEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    {
        int x = 0, y = 30, width = 634, height = 472;
        Colour fillColour1 = Colour (0xff5b6d76), fillColour2 = Colour (0xff073642);
        Colour strokeColour = Colour (0xffa3a4a5);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (ColourGradient (fillColour1,
                                       312.0f - 0.0f + x,
                                       200.0f - 30.0f + y,
                                       fillColour2,
                                       576.0f - 0.0f + x,
                                       464.0f - 30.0f + y,
                                       true));
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 8, y = 366, width = 197, height = 128;
        Colour fillColour = Colour (0x13f4f4f4);
        Colour strokeColour = Colour (0x67a0a0a0);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 204, y = 366, width = 422, height = 34;
        Colour fillColour = Colour (0x13f4f4f4);
        Colour strokeColour = Colour (0x67a0a0a0);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 8, y = 366, width = 197, height = 34;
        Colour fillColour = Colour (0x08f4f4f4);
        Colour strokeColour = Colour (0x32a0a0a0);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 204, y = 399, width = 422, height = 95;
        Colour fillColour = Colour (0x13f4f4f4);
        Colour strokeColour = Colour (0x67a0a0a0);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 0, y = 0, width = 634, height = 32;
        Colour fillColour = Colour (0xff073642);
        Colour strokeColour = Colour (0xdcbdbdbd);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 3);

    }

    {
        int x = 14, y = 402, width = 96, height = 30;
        String text (TRANS("Mic Preset:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (14.0f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 14, y = 460, width = 112, height = 30;
        String text (TRANS("Avg (ms):"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (14.0f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 14, y = 432, width = 127, height = 30;
        String text (TRANS("Format:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (14.0f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 216, y = 396, width = 312, height = 30;
        String text (TRANS("Analysis Order Per Frequency Band"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.0f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 611, y = 458, width = 13, height = 30;
        String text (TRANS("1"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.0f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 211, y = 470, width = 37, height = 30;
        String text (TRANS("100"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (12.0f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 366, y = 470, width = 37, height = 30;
        String text (TRANS("1k"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (12.0f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 520, y = 470, width = 37, height = 30;
        String text (TRANS("10k"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (12.0f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 402, y = 470, width = 93, height = 30;
        String text (TRANS("Frequency (Hz)"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (12.0f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 563, y = 470, width = 37, height = 30;
        String text (TRANS("20k"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (12.0f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 216, y = 368, width = 152, height = 30;
        String text (TRANS("Min Freq (Hz):"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.0f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 422, y = 368, width = 104, height = 30;
        String text (TRANS("Max Freq (Hz):"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.0f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 14, y = 368, width = 104, height = 30;
        String text (TRANS("Max Order:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.0f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 16, y = 0, width = 100, height = 32;
        String text (TRANS("SPARTA|"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (18.8f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 92, y = 0, width = 112, height = 32;
        String text (TRANS("SLDoA"));
        Colour fillColour = Colour (0xffff4848);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (18.0f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    //[UserPaint] Add your own custom painting code here..

	g.setColour(Colours::white);
	g.setFont(Font(11.00f, Font::plain));
	g.drawText(TRANS("Ver ") + JucePlugin_VersionString + BUILD_VER_SUFFIX + TRANS(", Build Date ") + __DATE__ + TRANS(" "),
		166, 16, 530, 11,
		Justification::centredLeft, true);

    Colour strokeColour = Colour (0x86a3a4a5);
    g.setColour (strokeColour);
    g.setOpacity(0.8f);
    g.drawRect (17, 48, 600, 300, 1);


    /* label for max ORDER */
    {
        int x = 610, y = 412, width = 13, height = 30;
        String text = String(sldoa_getMasterOrder(hVst->hSld));
        Colour fillColour = Colours::white;
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    /* display warning message */
    g.setColour(Colours::red);
    g.setFont(Font(11.00f, Font::plain));
    switch (currentWarning){
        case k_warning_none:
            break;
        case k_warning_frameSize:
            g.drawText(TRANS("Set frame size to multiple of ") + String(FRAME_SIZE),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_supported_fs:
            g.drawText(TRANS("Sample rate (") + String(sldoa_getSamplingRate(hVst->hSld)) + TRANS(") is unsupported"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NinputCH:
            g.drawText(TRANS("Insufficient number of input channels (") + String(hVst->getTotalNumInputChannels()) +
                       TRANS("/") + String(sldoa_getNSHrequired(hVst->hSld)) + TRANS(")"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
    }

    //[/UserPaint]
}

void PluginEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..

	repaint();
    //[/UserResized]
}

void PluginEditor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == avgSlider.get())
    {
        //[UserSliderCode_avgSlider] -- add your slider handling code here..
        sldoa_setAvg(hVst->hSld, (float)avgSlider->getValue());
        //[/UserSliderCode_avgSlider]
    }
    else if (sliderThatWasMoved == slider_anaOrder.get())
    {
        //[UserSliderCode_slider_anaOrder] -- add your slider handling code here..
        sldoa_setAnaOrderAllBands(hVst->hSld, (int)(slider_anaOrder->getValue()+0.5));
        anaOrder2dSlider->setRefreshValuesFLAG(true);
        //[/UserSliderCode_slider_anaOrder]
    }
    else if (sliderThatWasMoved == s_minFreq.get())
    {
        //[UserSliderCode_s_minFreq] -- add your slider handling code here..
        sldoa_setMinFreq(hVst->hSld, (float)s_minFreq->getValue());


        //[/UserSliderCode_s_minFreq]
    }
    else if (sliderThatWasMoved == s_maxFreq.get())
    {
        //[UserSliderCode_s_maxFreq] -- add your slider handling code here..
        sldoa_setMaxFreq(hVst->hSld, (float)s_maxFreq->getValue());
        //[/UserSliderCode_s_maxFreq]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void PluginEditor::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == CB_CHorder.get())
    {
        //[UserComboBoxCode_CB_CHorder] -- add your combo box handling code here..
        sldoa_setChOrder(hVst->hSld, CB_CHorder->getSelectedId());
        //[/UserComboBoxCode_CB_CHorder]
    }
    else if (comboBoxThatHasChanged == CB_Norm.get())
    {
        //[UserComboBoxCode_CB_Norm] -- add your combo box handling code here..
        sldoa_setNormType(hVst->hSld, CB_Norm->getSelectedId());
        //[/UserComboBoxCode_CB_Norm]
    }
    else if (comboBoxThatHasChanged == CBinputTypePreset.get())
    {
        //[UserComboBoxCode_CBinputTypePreset] -- add your combo box handling code here..
        sldoa_setSourcePreset(hVst->hSld, CBinputTypePreset->getSelectedId());
        anaOrder2dSlider->setRefreshValuesFLAG(true);
        //[/UserComboBoxCode_CBinputTypePreset]
    }
    else if (comboBoxThatHasChanged == CBmasterOrder.get())
    {
        //[UserComboBoxCode_CBmasterOrder] -- add your combo box handling code here..
        sldoa_setMasterOrder(hVst->hSld, CBmasterOrder->getSelectedId());
        CBinputTypePreset->setSelectedId(1);
        anaOrder2dSlider->setYrange(1, CBmasterOrder->getSelectedId());
        sldoa_setAnaOrderAllBands(hVst->hSld, CBmasterOrder->getSelectedId());
        anaOrder2dSlider->setRefreshValuesFLAG(true);
        slider_anaOrder->setRange(1, CBmasterOrder->getSelectedId(), 1);
        slider_anaOrder->setValue(CBmasterOrder->getSelectedId());
        repaint();
        //[/UserComboBoxCode_CBmasterOrder]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void PluginEditor::timerCallback()
{
	if ((overlayIncluded != nullptr) && (hVst->isPlaying))
		overlayIncluded->repaint();
    if (anaOrder2dSlider->getRefreshValuesFLAG())
        anaOrder2dSlider->repaint();

    s_minFreq->setValue(sldoa_getMinFreq(hVst->hSld));
    s_maxFreq->setValue(sldoa_getMaxFreq(hVst->hSld));

    /* display warning message, if needed */
    if ((hVst->getCurrentBlockSize() % FRAME_SIZE) != 0){
        currentWarning = k_warning_frameSize;
        repaint(0,0,getWidth(),32);
    }
    else if ( !((sldoa_getSamplingRate(hVst->hSld) == 44.1e3) || (sldoa_getSamplingRate(hVst->hSld) == 48e3)) ){
        currentWarning = k_warning_supported_fs;
        repaint(0,0,getWidth(),32);
    }
    else if ((hVst->getCurrentNumInputs() < sldoa_getNSHrequired(hVst->hSld))){
        currentWarning = k_warning_NinputCH;
        repaint(0,0,getWidth(),32);
    }
    else if(currentWarning){
        currentWarning = k_warning_none;
        repaint(0,0,getWidth(),32);
    }
}



//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="PluginEditor" componentName=""
                 parentClasses="public AudioProcessorEditor, public Timer" constructorParams="PluginProcessor* ownerFilter"
                 variableInitialisers="AudioProcessorEditor(ownerFilter)" snapPixels="8"
                 snapActive="1" snapShown="1" overlayOpacity="0.33" fixedSize="1"
                 initialWidth="634" initialHeight="502">
  <BACKGROUND backgroundColour="ffffffff">
    <RECT pos="0 30 634 472" fill=" radial: 312 200, 576 464, 0=ff5b6d76, 1=ff073642"
          hasStroke="1" stroke="1.9, mitered, butt" strokeColour="solid: ffa3a4a5"/>
    <RECT pos="8 366 197 128" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="204 366 422 34" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="8 366 197 34" fill="solid: 8f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 32a0a0a0"/>
    <RECT pos="204 399 422 95" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="0 0 634 32" fill="solid: ff073642" hasStroke="1" stroke="2.7, mitered, butt"
          strokeColour="solid: dcbdbdbd"/>
    <TEXT pos="14 402 96 30" fill="solid: ffffffff" hasStroke="0" text="Mic Preset:"
          fontname="Default font" fontsize="14.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="14 460 112 30" fill="solid: ffffffff" hasStroke="0" text="Avg (ms):"
          fontname="Default font" fontsize="14.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="14 432 127 30" fill="solid: ffffffff" hasStroke="0" text="Format:"
          fontname="Default font" fontsize="14.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="216 396 312 30" fill="solid: ffffffff" hasStroke="0" text="Analysis Order Per Frequency Band"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="611 458 13 30" fill="solid: ffffffff" hasStroke="0" text="1"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="211 470 37 30" fill="solid: ffffffff" hasStroke="0" text="100"
          fontname="Default font" fontsize="12.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="366 470 37 30" fill="solid: ffffffff" hasStroke="0" text="1k"
          fontname="Default font" fontsize="12.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="520 470 37 30" fill="solid: ffffffff" hasStroke="0" text="10k"
          fontname="Default font" fontsize="12.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="402 470 93 30" fill="solid: ffffffff" hasStroke="0" text="Frequency (Hz)"
          fontname="Default font" fontsize="12.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="563 470 37 30" fill="solid: ffffffff" hasStroke="0" text="20k"
          fontname="Default font" fontsize="12.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="216 368 152 30" fill="solid: ffffffff" hasStroke="0" text="Min Freq (Hz):"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="422 368 104 30" fill="solid: ffffffff" hasStroke="0" text="Max Freq (Hz):"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="14 368 104 30" fill="solid: ffffffff" hasStroke="0" text="Max Order:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="16 0 100 32" fill="solid: ffffffff" hasStroke="0" text="SPARTA|"
          fontname="Default font" fontsize="18.80000000000000071054" kerning="0.0"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="92 0 112 32" fill="solid: ffff4848" hasStroke="0" text="SLDoA"
          fontname="Default font" fontsize="18.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
  </BACKGROUND>
  <SLIDER name="new slider" id="86d1295f97e935ba" memberName="avgSlider"
          virtualName="" explicitFocusOrder="0" pos="80 465 118 24" min="0.0"
          max="2000.0" int="0.10000000000000000555" style="LinearHorizontal"
          textBoxPos="TextBoxRight" textBoxEditable="1" textBoxWidth="45"
          textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <COMBOBOX name="new combo box" id="3d1c447f9542fa94" memberName="CB_CHorder"
            virtualName="" explicitFocusOrder="0" pos="66 439 62 18" editable="0"
            layout="33" items="ACN" textWhenNonSelected="ACN" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box" id="d046f2696f3a4a04" memberName="CB_Norm"
            virtualName="" explicitFocusOrder="0" pos="131 439 68 18" editable="0"
            layout="33" items="N3D&#10;SN3D" textWhenNonSelected="N3D" textWhenNoItems="(no choices)"/>
  <SLIDER name="new slider" id="50ea77f60aadeeca" memberName="slider_anaOrder"
          virtualName="" explicitFocusOrder="0" pos="576 416 40 66" textboxtext="ffffffff"
          textboxbkgd="ffffff" min="0.0" max="1.0" int="1.0" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <COMBOBOX name="new combo box" id="932ca035edce041d" memberName="CBinputTypePreset"
            virtualName="" explicitFocusOrder="0" pos="96 409 103 18" editable="0"
            layout="33" items="Ideal SH" textWhenNonSelected="Default" textWhenNoItems="(no choices)"/>
  <SLIDER name="new slider" id="905f4ab0adab1f4f" memberName="s_minFreq"
          virtualName="" explicitFocusOrder="0" pos="312 372 96 24" min="0.0"
          max="24000.0" int="0.10000000000000000555" style="LinearHorizontal"
          textBoxPos="TextBoxRight" textBoxEditable="1" textBoxWidth="45"
          textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <SLIDER name="new slider" id="3aad5000f228ef1b" memberName="s_maxFreq"
          virtualName="" explicitFocusOrder="0" pos="520 372 96 24" min="0.0"
          max="24000.0" int="0.10000000000000000555" style="LinearHorizontal"
          textBoxPos="TextBoxRight" textBoxEditable="1" textBoxWidth="45"
          textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <COMBOBOX name="new combo box" id="346a30a1bf8969e9" memberName="CBmasterOrder"
            virtualName="" explicitFocusOrder="0" pos="96 376 103 18" editable="0"
            layout="33" items="" textWhenNonSelected="Default" textWhenNoItems="(no choices)"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
