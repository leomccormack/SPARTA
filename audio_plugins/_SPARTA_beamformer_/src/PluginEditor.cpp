/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.0.1

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

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

    addAndMakeVisible (BFmodeCB = new ComboBox (String()));
    BFmodeCB->setEditableText (false);
    BFmodeCB->setJustificationType (Justification::centredLeft);
    BFmodeCB->setTextWhenNothingSelected (TRANS("Dolph-Cheby"));
    BFmodeCB->setTextWhenNoChoicesAvailable (String());
    BFmodeCB->addItem (TRANS("Basic"), 1);
    BFmodeCB->addItem (TRANS("Dolph-Cheby"), 2);
    BFmodeCB->addItem (TRANS("MaxRE"), 3);
    BFmodeCB->addItem (TRANS("MVDR"), 4);
    BFmodeCB->addListener (this);

    addAndMakeVisible (cameraCB = new ComboBox (String()));
    cameraCB->setEditableText (false);
    cameraCB->setJustificationType (Justification::centredLeft);
    cameraCB->setTextWhenNothingSelected (String());
    cameraCB->setTextWhenNoChoicesAvailable (String());
    cameraCB->addListener (this);

    addAndMakeVisible (aspectRatioCB = new ComboBox (String()));
    aspectRatioCB->setEditableText (false);
    aspectRatioCB->setJustificationType (Justification::centredLeft);
    aspectRatioCB->setTextWhenNothingSelected (TRANS("16:9"));
    aspectRatioCB->setTextWhenNoChoicesAvailable (String());
    aspectRatioCB->addItem (TRANS("2:1"), 1);
    aspectRatioCB->addItem (TRANS("16:9"), 2);
    aspectRatioCB->addItem (TRANS("4:3"), 3);
    aspectRatioCB->addItem (TRANS("1:1"), 4);
    aspectRatioCB->addListener (this);

    addAndMakeVisible (fovCB = new ComboBox (String()));
    fovCB->setEditableText (false);
    fovCB->setJustificationType (Justification::centredLeft);
    fovCB->setTextWhenNothingSelected (CharPointer_UTF8 ("360\xc2\xb0"));
    fovCB->setTextWhenNoChoicesAvailable (String());
    fovCB->addItem (CharPointer_UTF8 ("360\xc2\xb0"), 1);
    fovCB->addItem (CharPointer_UTF8 ("180\xc2\xb0"), 2);
    fovCB->addItem (CharPointer_UTF8 ("90\xc2\xb0"), 3);
    fovCB->addItem (CharPointer_UTF8 ("60\xc2\xb0"), 4);
    fovCB->addListener (this);

    addAndMakeVisible (mirrorLR_TB = new ToggleButton ("new toggle button"));
    mirrorLR_TB->setButtonText (String());
    mirrorLR_TB->addListener (this);

    addAndMakeVisible (mirrorUD_TB = new ToggleButton ("new toggle button"));
    mirrorUD_TB->setButtonText (String());
    mirrorUD_TB->addListener (this);

    addAndMakeVisible (azi_SL = new Slider ("new slider"));
    azi_SL->setRange (-180, 180, 0.1);
    azi_SL->setSliderStyle (Slider::LinearHorizontal);
    azi_SL->setTextBoxStyle (Slider::TextBoxAbove, false, 80, 20);
    azi_SL->setColour (Slider::textBoxTextColourId, Colours::white);
    azi_SL->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    azi_SL->addListener (this);

    addAndMakeVisible (elev_SL = new Slider ("new slider"));
    elev_SL->setRange (-90, 90, 0.1);
    elev_SL->setSliderStyle (Slider::LinearVertical);
    elev_SL->setTextBoxStyle (Slider::TextBoxAbove, false, 40, 20);
    elev_SL->setColour (Slider::textBoxTextColourId, Colours::white);
    elev_SL->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    elev_SL->addListener (this);

    addAndMakeVisible (auto_TB = new ToggleButton ("new toggle button"));
    auto_TB->setButtonText (String());
    auto_TB->addListener (this);

    addAndMakeVisible (bin_TB = new ToggleButton ("new toggle button"));
    bin_TB->setButtonText (String());
    bin_TB->addListener (this);

    addAndMakeVisible (PFmodeCB = new ComboBox (String()));
    PFmodeCB->setEditableText (false);
    PFmodeCB->setJustificationType (Justification::centredLeft);
    PFmodeCB->setTextWhenNothingSelected (TRANS("CroPaC Legacy"));
    PFmodeCB->setTextWhenNoChoicesAvailable (String());
    PFmodeCB->addItem (TRANS("Off"), 1);
    PFmodeCB->addItem (TRANS("CroPaC Legacy"), 2);
    PFmodeCB->addItem (TRANS("CroPaC LCMV"), 3);
    PFmodeCB->addListener (this);

    addAndMakeVisible (lambda_SL = new Slider ("new slider"));
    lambda_SL->setRange (0, 1, 0.01);
    lambda_SL->setSliderStyle (Slider::LinearHorizontal);
    lambda_SL->setTextBoxStyle (Slider::TextBoxAbove, false, 80, 20);
    lambda_SL->setColour (Slider::textBoxTextColourId, Colours::white);
    lambda_SL->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    lambda_SL->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (840, 575);


    //[Constructor] You can add your own custom stuff here..
	hVst = ownerFilter;
	openGLContext.setMultisamplingEnabled(true);
    //openGLContext.xg
    openGLContext.attachTo(*this);

    /* Overlay */
    int OverlayWidth = OVERLAY_HEIGHT*sfcropaclib_getAspectRatio(hVst->hSfcropac);
    previewArea.setBounds((getWidth()-OverlayWidth)/2, 40, OverlayWidth, OVERLAY_HEIGHT);
    addAndMakeVisible (overlayIncluded = new overlay(ownerFilter));
    overlayIncluded->setAlwaysOnTop(true);
    overlayIncluded->setBounds(previewArea);

    /* camera options */
	updateCameraList();
	cameraCB->addListener(this);
	addAndMakeVisible(lastSnapshot);
    bMirrorImageLR = false;
	bMirrorImageUD = false;

	/* fetch current configuration */
	BFmodeCB->setSelectedId(sfcropaclib_getBFtype(hVst->hSfcropac), dontSendNotification);
	PFmodeCB->setSelectedId(sfcropaclib_getPFtype(hVst->hSfcropac), dontSendNotification);
	azi_SL->setValue(sfcropaclib_getBeamAzi(hVst->hSfcropac), dontSendNotification);
	elev_SL->setValue(sfcropaclib_getBeamElev(hVst->hSfcropac), dontSendNotification);
	auto_TB->setToggleState(sfcropaclib_getAutoFLAG(hVst->hSfcropac), dontSendNotification);
	bin_TB->setToggleState(sfcropaclib_getBinFLAG(hVst->hSfcropac), dontSendNotification);
	lambda_SL->setValue(sfcropaclib_getLambda(hVst->hSfcropac), dontSendNotification);

    if(sfcropaclib_getAspectRatio(hVst->hSfcropac)==2.0f/1.0f)
        aspectRatioCB->setSelectedId(1, dontSendNotification);
    else if(sfcropaclib_getAspectRatio(hVst->hSfcropac) == 16.0f / 9.0f)
        aspectRatioCB->setSelectedId(2, dontSendNotification);
	else if (sfcropaclib_getAspectRatio(hVst->hSfcropac) == 4.0f / 3.0f)
		aspectRatioCB->setSelectedId(3, dontSendNotification);
	else if (sfcropaclib_getAspectRatio(hVst->hSfcropac) == 1.0f / 1.0f)
		aspectRatioCB->setSelectedId(4, dontSendNotification);

    if(sfcropaclib_getFOV(hVst->hSfcropac) == 360.0f)
        fovCB->setSelectedId(1, dontSendNotification);
    else if (sfcropaclib_getFOV(hVst->hSfcropac) == 180.0f)
        fovCB->setSelectedId(2, dontSendNotification);
	else if (sfcropaclib_getFOV(hVst->hSfcropac) == 90.0f)
		fovCB->setSelectedId(3, dontSendNotification);
	else if (sfcropaclib_getFOV(hVst->hSfcropac) == 60.0f)
		fovCB->setSelectedId(4, dontSendNotification);


    cameraCB->setSelectedId(1, dontSendNotification);
    mirrorLR_TB->setToggleState(bMirrorImageLR, dontSendNotification);
	mirrorUD_TB->setToggleState(bMirrorImageUD, dontSendNotification);

	/* Specify screen refresh rate */
    startTimer(100);//80); /*ms (40ms = 25 frames per second) */

    /* aesthetics */
	BFmodeCB->setColour (ComboBox::backgroundColourId, Colour (0x00ffffff));
	PFmodeCB->setColour(ComboBox::backgroundColourId, Colour(0x00ffffff));
    cameraCB->setColour (ComboBox::backgroundColourId, Colour (0x00ffffff));
    aspectRatioCB->setColour (ComboBox::backgroundColourId, Colour (0x00ffffff));
    fovCB->setColour (ComboBox::backgroundColourId, Colour (0x00ffffff));
	BFmodeCB->setColour (ComboBox::textColourId, Colours::white);
	PFmodeCB->setColour(ComboBox::textColourId, Colours::white);
    cameraCB->setColour (ComboBox::textColourId, Colours::white);
    aspectRatioCB->setColour (ComboBox::textColourId, Colours::white);
    fovCB->setColour (ComboBox::textColourId, Colours::white);

	if ((fovCB->getSelectedId() == 1) || (fovCB->getSelectedId() == 2))
		aspectRatioCB->setEnabled(false);
	else
		aspectRatioCB->setEnabled(true);

    //[/Constructor]
}

PluginEditor::~PluginEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    BFmodeCB = nullptr;
    cameraCB = nullptr;
    aspectRatioCB = nullptr;
    fovCB = nullptr;
    mirrorLR_TB = nullptr;
    mirrorUD_TB = nullptr;
    azi_SL = nullptr;
    elev_SL = nullptr;
    auto_TB = nullptr;
    bin_TB = nullptr;
    PFmodeCB = nullptr;
    lambda_SL = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    overlayIncluded = nullptr;
    //[/Destructor]
}

//==============================================================================
void PluginEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    g.setGradientFill (ColourGradient (Colour (0xff839496),
                                       432.0f, 256.0f,
                                       Colour (0xff073642),
                                       840.0f, 576.0f,
                                       true));
    g.fillRect (0, 30, 840, 545);

    g.setColour (Colour (0xffa3a4a5));
    g.drawRect (0, 30, 840, 545, 2);

    g.setGradientFill (ColourGradient (Colour (0x5b000000),
                                       280.0f, 568.0f,
                                       Colour (0x0a000000),
                                       104.0f, 496.0f,
                                       true));
    g.fillRect (24, 454, 216, 104);

    g.setColour (Colour (0x86a3a4a5));
    g.drawRect (24, 454, 216, 104, 2);

    g.setGradientFill (ColourGradient (Colour (0x5b000000),
                                       464.0f, 504.0f,
                                       Colour (0x0a000000),
                                       696.0f, 504.0f,
                                       true));
    g.fillRect (256, 454, 560, 48);

    g.setColour (Colour (0x86a3a4a5));
    g.drawRect (256, 454, 560, 48, 2);

    g.setColour (Colour (0xff073642));
    g.fillRect (0, 0, 840, 32);

    g.setColour (Colour (0xdcbdbdbd));
    g.drawRect (0, 0, 840, 32, 3);

    g.setColour (Colours::white);
    g.setFont (Font (18.80f, Font::plain).withTypefaceStyle ("Bold"));
    g.drawText (TRANS("sfCroPaC"),
                -19, 0, 190, 32,
                Justification::centred, true);

    g.setGradientFill (ColourGradient (Colour (0x5b000000),
                                       464.0f, 504.0f,
                                       Colour (0x0a000000),
                                       696.0f, 504.0f,
                                       true));
    g.fillRect (256, 510, 560, 48);

    g.setColour (Colour (0x86a3a4a5));
    g.drawRect (256, 510, 560, 48, 2);

    g.setColour (Colours::white);
    g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
    g.drawText (TRANS("AR:"),
                713, 519, 33, 30,
                Justification::centredLeft, true);

    g.setColour (Colours::white);
    g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
    g.drawText (TRANS("Camera:"),
                264, 519, 60, 30,
                Justification::centredLeft, true);

    g.setColour (Colours::white);
    g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
    g.drawText (TRANS("FOV:"),
                608, 519, 35, 30,
                Justification::centredLeft, true);

    g.setColour (Colours::white);
    g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
    g.drawText (TRANS("MLR:"),
                472, 519, 39, 30,
                Justification::centredLeft, true);

    g.setColour (Colours::white);
    g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
    g.drawText (TRANS("MUD:"),
                540, 519, 41, 30,
                Justification::centredLeft, true);

    g.setColour (Colours::white);
    g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
    g.drawText (TRANS("Auto:"),
                31, 521, 41, 42,
                Justification::centredLeft, true);

    g.setColour (Colours::white);
    g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
    g.drawText (TRANS("Bin:"),
                104, 521, 48, 42,
                Justification::centredLeft, true);

    g.setColour (Colours::white);
    g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
    g.drawText (TRANS("PF mode:"),
                455, 462, 69, 30,
                Justification::centredLeft, true);

    g.setColour (Colours::white);
    g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
    g.drawText (TRANS("Lambda:"),
                655, 462, 69, 30,
                Justification::centredLeft, true);

    g.setColour (Colours::white);
    g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
    g.drawText (TRANS("BF mode:"),
                267, 463, 69, 30,
                Justification::centredLeft, true);

    g.setColour (Colours::white);
    g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
    g.drawText (TRANS("Beam Dir"),
                71, 457, 81, 30,
                Justification::centredLeft, true);

    //[UserPaint] Add your own custom painting code here..

	g.setColour(Colours::white);
	g.setFont(Font(11.00f, Font::plain));
	g.drawText(TRANS("Ver ") + JucePlugin_VersionString + BUILD_VER_SUFFIX + TRANS(", Build Date ") + __DATE__ + TRANS(" "),
		150, 16, 530, 11,
		Justification::centredLeft, true);

	g.setColour(Colours::white);
	g.setOpacity(0.25f);
	g.fillRect(previewArea.expanded(2));
	g.setColour(Colours::white);
	g.setOpacity(0.3f);
	g.drawRect(previewArea.expanded(2), 2.0f);

    //[/UserPaint]
}

void PluginEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    BFmodeCB->setBounds (338, 466, 112, 24);
    cameraCB->setBounds (326, 522, 140, 24);
    aspectRatioCB->setBounds (745, 522, 58, 24);
    fovCB->setBounds (645, 522, 58, 24);
    mirrorLR_TB->setBounds (510, 522, 24, 24);
    mirrorUD_TB->setBounds (578, 522, 24, 24);
    azi_SL->setBounds (32, 488, 152, 32);
    elev_SL->setBounds (184, 464, 48, 88);
    auto_TB->setBounds (72, 528, 24, 24);
    bin_TB->setBounds (136, 528, 24, 24);
    PFmodeCB->setBounds (528, 466, 120, 24);
    lambda_SL->setBounds (720, 464, 87, 32);
    //[UserResized] Add your own custom resize handling here..

	if (cameraCB->getSelectedId() == 1)
		lastSnapshot.setBounds(0,0,0,0); /* hide */
	else
		lastSnapshot.setBounds(previewArea);

    if (overlayIncluded != nullptr){
        overlayIncluded->setAlwaysOnTop(true);
        overlayIncluded->setBounds(previewArea);
        overlayIncluded->resized();
    }
	repaint();
    //[/UserResized]
}

void PluginEditor::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == BFmodeCB)
    {
        //[UserComboBoxCode_BFmodeCB] -- add your combo box handling code here..
		sfcropaclib_setBFtype(hVst->hSfcropac, BFmodeCB->getSelectedId());
        //[/UserComboBoxCode_BFmodeCB]
    }
    else if (comboBoxThatHasChanged == cameraCB)
    {
        //[UserComboBoxCode_cameraCB] -- add your combo box handling code here..
		cameraDevice = nullptr;
		cameraPreviewComp = nullptr;

		if (cameraCB->getSelectedId() > 1) {
			cameraDevice = CameraDevice::openDevice(cameraCB->getSelectedId() - 2, 128, 64, 2048 * 2, 1536 * 2, false); // high quality mode?
			//cameraDevice = CameraDevice::openDevice(cameraCB->getSelectedId() - 2);
			cameraDevice->addListener(this);
			if (cameraDevice != nullptr) {
				cameraPreviewComp = cameraDevice->createViewerComponent();
			}
		}
		resized();
        //[/UserComboBoxCode_cameraCB]
    }
    else if (comboBoxThatHasChanged == aspectRatioCB)
    {
        //[UserComboBoxCode_aspectRatioCB] -- add your combo box handling code here..
        switch (aspectRatioCB->getSelectedId()){
            case 1: sfcropaclib_setAspectRatio(hVst->hSfcropac, 2.0f/1.0f);  break; /* 2:1 */
            case 2: sfcropaclib_setAspectRatio(hVst->hSfcropac, 16.0f/9.0f); break; /* 16:9 */
			case 3: sfcropaclib_setAspectRatio(hVst->hSfcropac, 4.0f / 3.0f); break; /* 4:3 */
			case 4: sfcropaclib_setAspectRatio(hVst->hSfcropac, 1.0f / 1.0f); break; /* 1:1 */
        }

        int OverlayWidth = OVERLAY_HEIGHT*sfcropaclib_getAspectRatio(hVst->hSfcropac);
        previewArea.setBounds((getWidth()-OverlayWidth)/2, 40, OverlayWidth,
                              OVERLAY_HEIGHT);
        resized();
        //[/UserComboBoxCode_aspectRatioCB]
    }
    else if (comboBoxThatHasChanged == fovCB)
    {
        //[UserComboBoxCode_fovCB] -- add your combo box handling code here..
        switch (fovCB->getSelectedId()){
            case 1: sfcropaclib_setFOV(hVst->hSfcropac, 360.0f);
				aspectRatioCB->setSelectedId(1);
				aspectRatioCB->setEnabled(false);
				break;
			case 2: sfcropaclib_setFOV(hVst->hSfcropac, 180.0f);
				aspectRatioCB->setSelectedId(4);
				aspectRatioCB->setEnabled(false);
				break;
            case 3: sfcropaclib_setFOV(hVst->hSfcropac, 90.0f);
				aspectRatioCB->setEnabled(true);
				break;
			case 4: sfcropaclib_setFOV(hVst->hSfcropac, 60.0f);
				aspectRatioCB->setEnabled(true);
				break;
        }
        //[/UserComboBoxCode_fovCB]
    }
    else if (comboBoxThatHasChanged == PFmodeCB)
    {
        //[UserComboBoxCode_PFmodeCB] -- add your combo box handling code here..
		sfcropaclib_setPFtype(hVst->hSfcropac, PFmodeCB->getSelectedId());
        //[/UserComboBoxCode_PFmodeCB]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void PluginEditor::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == mirrorLR_TB)
    {
        //[UserButtonCode_mirrorLR_TB] -- add your button handler code here..
        bMirrorImageLR = mirrorLR_TB->getToggleState();
        //[/UserButtonCode_mirrorLR_TB]
    }
    else if (buttonThatWasClicked == mirrorUD_TB)
    {
        //[UserButtonCode_mirrorUD_TB] -- add your button handler code here..
		bMirrorImageUD = mirrorUD_TB->getToggleState();
        //[/UserButtonCode_mirrorUD_TB]
    }
    else if (buttonThatWasClicked == auto_TB)
    {
        //[UserButtonCode_auto_TB] -- add your button handler code here..
		sfcropaclib_setAutoFLAG(hVst->hSfcropac, auto_TB->getToggleState());
        //[/UserButtonCode_auto_TB]
    }
    else if (buttonThatWasClicked == bin_TB)
    {
        //[UserButtonCode_bin_TB] -- add your button handler code here..
		sfcropaclib_setBinFLAG(hVst->hSfcropac, bin_TB->getToggleState());
        //[/UserButtonCode_bin_TB]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void PluginEditor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == azi_SL)
    {
        //[UserSliderCode_azi_SL] -- add your slider handling code here..
		sfcropaclib_setBeamAzi(hVst->hSfcropac, (float)azi_SL->getValue());
        //[/UserSliderCode_azi_SL]
    }
    else if (sliderThatWasMoved == elev_SL)
    {
        //[UserSliderCode_elev_SL] -- add your slider handling code here..
		sfcropaclib_setBeamElev(hVst->hSfcropac, (float)elev_SL->getValue());
        //[/UserSliderCode_elev_SL]
    }
    else if (sliderThatWasMoved == lambda_SL)
    {
        //[UserSliderCode_lambda_SL] -- add your slider handling code here..
		sfcropaclib_setLambda(hVst->hSfcropac, (float)lambda_SL->getValue());
        //[/UserSliderCode_lambda_SL]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void PluginEditor::timerCallback()
{
	if (cameraCB->getSelectedId() == 1){
	}
    if (incomingImage.isValid())
        triggerAsyncUpdate();

	if ((overlayIncluded != nullptr) && (hVst->isPlaying)) {
		overlayIncluded->repaint();
	}
}

void PluginEditor::updateCameraList()
{
	cameraCB->clear();
	cameraCB->addItem("No camera", 1);
	cameraCB->addSeparator();

	StringArray cameras = CameraDevice::getAvailableDevices();

	for (int i = 0; i < cameras.size(); ++i)
		cameraCB->addItem(cameras[i], i + 2);
}

void PluginEditor::imageReceived(const Image& image)
{
	Image mirrorImage = image;
	mirrorImage=mirrorImage.getClippedImage(mirrorImage.getBounds());
	Graphics g(mirrorImage);
	if (bMirrorImageLR && !bMirrorImageUD) {
		g.drawImageTransformed(mirrorImage, AffineTransform::scale(-1.0f, 1.0f).withAbsoluteTranslation(incomingImage.getWidth(), 0));
		incomingImage = mirrorImage;
	}
	else if (bMirrorImageUD && !bMirrorImageLR) {
		g.drawImageTransformed(mirrorImage, AffineTransform::scale(1.0f, -1.0f).withAbsoluteTranslation(0, incomingImage.getHeight()));
		//g.drawImageTransformed(mirrorImage, AffineTransform().rotated(M_PI).withAbsoluteTranslation(0, incomingImage.getHeight()));
		//g.drawImageTransformed(mirrorImage, AffineTransform::rotation(M_PI, 0, 0));
		//AffineTransform::rotation(const float rad)
		incomingImage = mirrorImage;
	}
	else if (bMirrorImageUD && bMirrorImageLR) {
		g.drawImageTransformed(mirrorImage, AffineTransform::scale(-1.0f, -1.0f).withAbsoluteTranslation(incomingImage.getWidth(), incomingImage.getHeight()));
		incomingImage = mirrorImage;
	}
	else {
		incomingImage = image;
	}
	// incomingImage.desaturate();				/* remove colour (grey-scale) */
}

void PluginEditor::handleAsyncUpdate()
{
    if (incomingImage.isValid() && (hVst->isPlaying) ) {
        lastSnapshot.setImage(incomingImage);
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
                 parentClasses="public AudioProcessorEditor, public Timer, private CameraDevice::Listener, public AsyncUpdater"
                 constructorParams="PluginProcessor* ownerFilter" variableInitialisers="AudioProcessorEditor(ownerFilter)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="840" initialHeight="575">
  <BACKGROUND backgroundColour="ffffffff">
    <RECT pos="0 30 840 545" fill=" radial: 432 256, 840 576, 0=ff839496, 1=ff073642"
          hasStroke="1" stroke="1.9, mitered, butt" strokeColour="solid: ffa3a4a5"/>
    <RECT pos="24 454 216 104" fill=" radial: 280 568, 104 496, 0=5b000000, 1=a000000"
          hasStroke="1" stroke="1.9, mitered, butt" strokeColour="solid: 86a3a4a5"/>
    <RECT pos="256 454 560 48" fill=" radial: 464 504, 696 504, 0=5b000000, 1=a000000"
          hasStroke="1" stroke="1.9, mitered, butt" strokeColour="solid: 86a3a4a5"/>
    <RECT pos="0 0 840 32" fill="solid: ff073642" hasStroke="1" stroke="2.7, mitered, butt"
          strokeColour="solid: dcbdbdbd"/>
    <TEXT pos="-19 0 190 32" fill="solid: ffffffff" hasStroke="0" text="sfCroPaC"
          fontname="Default font" fontsize="18.800000000000000711" kerning="0"
          bold="1" italic="0" justification="36" typefaceStyle="Bold"/>
    <RECT pos="256 510 560 48" fill=" radial: 464 504, 696 504, 0=5b000000, 1=a000000"
          hasStroke="1" stroke="1.9, mitered, butt" strokeColour="solid: 86a3a4a5"/>
    <TEXT pos="713 519 33 30" fill="solid: ffffffff" hasStroke="0" text="AR:"
          fontname="Default font" fontsize="15" kerning="0" bold="1" italic="0"
          justification="33" typefaceStyle="Bold"/>
    <TEXT pos="264 519 60 30" fill="solid: ffffffff" hasStroke="0" text="Camera:"
          fontname="Default font" fontsize="15" kerning="0" bold="1" italic="0"
          justification="33" typefaceStyle="Bold"/>
    <TEXT pos="608 519 35 30" fill="solid: ffffffff" hasStroke="0" text="FOV:"
          fontname="Default font" fontsize="15" kerning="0" bold="1" italic="0"
          justification="33" typefaceStyle="Bold"/>
    <TEXT pos="472 519 39 30" fill="solid: ffffffff" hasStroke="0" text="MLR:"
          fontname="Default font" fontsize="15" kerning="0" bold="1" italic="0"
          justification="33" typefaceStyle="Bold"/>
    <TEXT pos="540 519 41 30" fill="solid: ffffffff" hasStroke="0" text="MUD:"
          fontname="Default font" fontsize="15" kerning="0" bold="1" italic="0"
          justification="33" typefaceStyle="Bold"/>
    <TEXT pos="31 521 41 42" fill="solid: ffffffff" hasStroke="0" text="Auto:"
          fontname="Default font" fontsize="15" kerning="0" bold="1" italic="0"
          justification="33" typefaceStyle="Bold"/>
    <TEXT pos="104 521 48 42" fill="solid: ffffffff" hasStroke="0" text="Bin:"
          fontname="Default font" fontsize="15" kerning="0" bold="1" italic="0"
          justification="33" typefaceStyle="Bold"/>
    <TEXT pos="455 462 69 30" fill="solid: ffffffff" hasStroke="0" text="PF mode:"
          fontname="Default font" fontsize="15" kerning="0" bold="1" italic="0"
          justification="33" typefaceStyle="Bold"/>
    <TEXT pos="655 462 69 30" fill="solid: ffffffff" hasStroke="0" text="Lambda:"
          fontname="Default font" fontsize="15" kerning="0" bold="1" italic="0"
          justification="33" typefaceStyle="Bold"/>
    <TEXT pos="267 463 69 30" fill="solid: ffffffff" hasStroke="0" text="BF mode:"
          fontname="Default font" fontsize="15" kerning="0" bold="1" italic="0"
          justification="33" typefaceStyle="Bold"/>
    <TEXT pos="71 457 81 30" fill="solid: ffffffff" hasStroke="0" text="Beam Dir"
          fontname="Default font" fontsize="15" kerning="0" bold="1" italic="0"
          justification="33" typefaceStyle="Bold"/>
  </BACKGROUND>
  <COMBOBOX name="" id="787134d7259eea10" memberName="BFmodeCB" virtualName=""
            explicitFocusOrder="0" pos="338 466 112 24" editable="0" layout="33"
            items="Basic&#10;Dolph-Cheby&#10;MaxRE&#10;MVDR" textWhenNonSelected="Dolph-Cheby"
            textWhenNoItems=""/>
  <COMBOBOX name="" id="7860b9e7ca7beb04" memberName="cameraCB" virtualName=""
            explicitFocusOrder="0" pos="326 522 140 24" editable="0" layout="33"
            items="" textWhenNonSelected="" textWhenNoItems=""/>
  <COMBOBOX name="" id="14aa0334c6d58151" memberName="aspectRatioCB" virtualName=""
            explicitFocusOrder="0" pos="745 522 58 24" editable="0" layout="33"
            items="2:1&#10;16:9&#10;4:3&#10;1:1" textWhenNonSelected="16:9"
            textWhenNoItems=""/>
  <COMBOBOX name="" id="de9e750d5cefeadf" memberName="fovCB" virtualName=""
            explicitFocusOrder="0" pos="645 522 58 24" editable="0" layout="33"
            items="360&#176;&#10;180&#176;&#10;90&#176;&#10;60&#176;" textWhenNonSelected="360&#176;"
            textWhenNoItems=""/>
  <TOGGLEBUTTON name="new toggle button" id="8084b5eca1ef3987" memberName="mirrorLR_TB"
                virtualName="" explicitFocusOrder="0" pos="510 522 24 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="4dc3e20ba0c3efa7" memberName="mirrorUD_TB"
                virtualName="" explicitFocusOrder="0" pos="578 522 24 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <SLIDER name="new slider" id="beeddee6192cf45c" memberName="azi_SL" virtualName=""
          explicitFocusOrder="0" pos="32 488 152 32" textboxtext="ffffffff"
          textboxbkgd="ffffff" min="-180" max="180" int="0.10000000000000000555"
          style="LinearHorizontal" textBoxPos="TextBoxAbove" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <SLIDER name="new slider" id="e09980369d54d9b0" memberName="elev_SL"
          virtualName="" explicitFocusOrder="0" pos="184 464 48 88" textboxtext="ffffffff"
          textboxbkgd="ffffff" min="-90" max="90" int="0.10000000000000000555"
          style="LinearVertical" textBoxPos="TextBoxAbove" textBoxEditable="1"
          textBoxWidth="40" textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <TOGGLEBUTTON name="new toggle button" id="f8caf4a182c8ecb3" memberName="auto_TB"
                virtualName="" explicitFocusOrder="0" pos="72 528 24 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="d2315807f90224f7" memberName="bin_TB"
                virtualName="" explicitFocusOrder="0" pos="136 528 24 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <COMBOBOX name="" id="8176190f2be838a9" memberName="PFmodeCB" virtualName=""
            explicitFocusOrder="0" pos="528 466 120 24" editable="0" layout="33"
            items="Off&#10;CroPaC Legacy&#10;CroPaC LCMV" textWhenNonSelected="CroPaC Legacy"
            textWhenNoItems=""/>
  <SLIDER name="new slider" id="69786b79d5005bc5" memberName="lambda_SL"
          virtualName="" explicitFocusOrder="0" pos="720 464 87 32" textboxtext="ffffffff"
          textboxbkgd="ffffff" min="0" max="1" int="0.010000000000000000208"
          style="LinearHorizontal" textBoxPos="TextBoxAbove" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1" needsCallback="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
