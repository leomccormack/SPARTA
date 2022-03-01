/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 6.0.3

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...

//[/Headers]

#include "inputCoordsView.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
const int sensorEdit_width = 176;
const int sensorEdit_height = 32;
//[/MiscUserDefs]

//==============================================================================
inputCoordsView::inputCoordsView (PluginProcessor* ownerFilter, int _maxNCH, int _currentNCH )
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]
    // TODO: remove dummySlider?
    dummySlider.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (dummySlider.get());
    dummySlider->setRange (0.01, 0.3, 0.001);
    dummySlider->setSliderStyle (juce::Slider::LinearHorizontal);
    dummySlider->setTextBoxStyle (juce::Slider::TextBoxRight, false, 70, 20);
    dummySlider->addListener (this);
    dummySlider->setBounds (-176, 144, 96, 16);

    //[UserPreSize]
    //[/UserPreSize]

    //[Constructor] You can add your own custom stuff here..
    setSize (sensorEdit_width, sensorEdit_height*currentNCH);
    hVst = ownerFilter;
    hBin = hVst->getFXHandle();
    maxNCH = _maxNCH ;
    currentNCH =_currentNCH;
    aziSliders = new std::unique_ptr<Slider>[(unsigned long)maxNCH];
    elevSliders = new std::unique_ptr<Slider>[(unsigned long)maxNCH];
    distSliders = new std::unique_ptr<Slider>[(unsigned long)maxNCH];
    
    int left = 15, tbw = 45, tbh = 20, tbhpad = 6; // text box layout dimensions
    int tbvpad = (sensorEdit_height - tbh) / 2;
    for( int i=0; i<maxNCH; i++){
        /* create and initialise azimuth sliders */
        aziSliders[i].reset (new Slider ("new slider"));
        aziSliders[i]->setTooltip("Source azimuth: 0 degrees is forward, 90 degrees is left, -90 degrees right.");
        addAndMakeVisible (aziSliders[i].get());
        aziSliders[i]->setRange (-360.0, 360.0, 0.1); // overwritten by refreshCoords() below
        aziSliders[i]->setValue(binauraliser_getSourceAzi_deg(hBin, i));
        aziSliders[i]->setSliderStyle(Slider::SliderStyle::LinearBarVertical); // vertical drag slider as number box
        aziSliders[i]->setSliderSnapsToMousePosition(false);
        aziSliders[i]->setColour(Slider::trackColourId, Colours::transparentBlack);
        aziSliders[i]->setColour(Slider::rotarySliderFillColourId, Colours::transparentBlack); // hide slider value fill
        aziSliders[i]->setBounds(left+tbhpad, tbvpad + i*sensorEdit_height, tbw, tbh);
        aziSliders[i]->addListener (this);
        aziSliders[i]->setNumDecimalPlacesToDisplay (1);

        /* create and initialise elevation sliders */
        elevSliders[i].reset (new Slider ("new slider"));
        elevSliders[i]->setTooltip("Source elevation: 90 degrees is above, -90 degree is below.");
        addAndMakeVisible (elevSliders[i].get());
        elevSliders[i]->setRange (-180.0, 180.0, 0.1);
        elevSliders[i]->setNumDecimalPlacesToDisplay (1);
        elevSliders[i]->setValue(binauraliser_getSourceElev_deg(hBin, i));
        elevSliders[i]->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
        elevSliders[i]->setSliderSnapsToMousePosition(false);
        elevSliders[i]->setColour(Slider::trackColourId, Colours::transparentBlack);
        elevSliders[i]->setColour(Slider::rotarySliderFillColourId, Colours::transparentBlack);
        elevSliders[i]->setBounds(left+tbhpad+tbw+tbhpad, tbvpad + i*sensorEdit_height, tbw, tbh);
        elevSliders[i]->addListener (this);
        
        /* create and initialise distance sliders */
        distSliders[i].reset (new Slider ("new slider"));
        distSliders[i]->setTooltip("Distance from the center of the head (m). Filters disengage when maximally far (approx > 3 m).");
        addAndMakeVisible (distSliders[i].get());
        distSliders[i]->setRange (binauraliserNF_getNearfieldLimit_m(hBin), hVst->upperDistRange, 0.001);
        distSliders[i]->setNumDecimalPlacesToDisplay (2);
        distSliders[i]->setSkewFactor (0.5, false);
        distSliders[i]->setValue(binauraliserNF_getSourceDist_m(hBin, i));
        distSliders[i]->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
        distSliders[i]->setSliderSnapsToMousePosition(false);
        distSliders[i]->setColour(Slider::trackColourId, Colours::transparentBlack);
        distSliders[i]->setColour(Slider::rotarySliderFillColourId , Colours::transparentBlack);
        distSliders[i]->setBounds(left+tbhpad+tbw+tbhpad+tbw+tbhpad, tbvpad + i*sensorEdit_height, tbw, tbh);
        distSliders[i]->addListener (this);
    }

    sliderHasChanged = true;

	/* Get and display current settings */
	refreshCoords();
	resized();

    //[/Constructor]
}

inputCoordsView::~inputCoordsView()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    dummySlider = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    for( int i=0; i<maxNCH; i++){
        aziSliders[i] = nullptr;
        elevSliders[i] = nullptr;
        distSliders[i] = nullptr;
    }
    delete [] aziSliders;
    delete [] elevSliders;
    delete [] distSliders;
    //[/Destructor]
}

//==============================================================================
void inputCoordsView::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    {
        int x = 88, y = 0, width = 88, height = 2048;
        juce::Colour fillColour1 = juce::Colour (0x21ffffff), fillColour2 = juce::Colour (0x05252a25);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             88.0f - 88.0f + x,
                                             128.0f - 0.0f + y,
                                             fillColour2,
                                             176.0f - 88.0f + x,
                                             128.0f - 0.0f + y,
                                             false));
        g.fillRect (x, y, width, height);
    }

    {
        int x = 0, y = 0, width = 88, height = 2048;
        juce::Colour fillColour1 = juce::Colour (0x21ffffff), fillColour2 = juce::Colour (0x05252a25);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             88.0f - 0.0f + x,
                                             128.0f - 0.0f + y,
                                             fillColour2,
                                             0.0f - 0.0f + x,
                                             128.0f - 0.0f + y,
                                             false));
        g.fillRect (x, y, width, height);
    }

    //[UserPaint] Add your own custom painting code here..
    Colour fillColour = Colours::white;
    g.setColour (fillColour);
    g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));

    for( int i=0; i<maxNCH; i++){
        /* draw sensor IDs */
        g.setColour (fillColour);
        g.drawText (String(i+1), -6, 4 + i*sensorEdit_height, 33, 23,
                    Justification::centred, true);
        /* draw rectangle around sensor parameter */
        g.setOpacity(0.15f);
        g.drawRect (0, i*sensorEdit_height, sensorEdit_width, sensorEdit_height+1, 1);
    }


    //[/UserPaint]
}

void inputCoordsView::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    setSize (sensorEdit_width, sensorEdit_height*currentNCH);
    repaint();
    //[/UserResized]
}

void inputCoordsView::sliderValueChanged (juce::Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    for(int i=0; i<maxNCH; i++){
        if (sliderThatWasMoved == aziSliders[i].get()) {
            binauraliser_setSourceAzi_deg(hBin, i, (float)aziSliders[i]->getValue());
            break;
        }
        if (sliderThatWasMoved == elevSliders[i].get()) {
            binauraliser_setSourceElev_deg(hBin, i, (float)elevSliders[i]->getValue());
            break;
        }
        if (sliderThatWasMoved == distSliders[i].get()) {
            binauraliserNF_setSourceDist_m(hBin, i, (float)distSliders[i]->getValue());
            break;
        }
    }

    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == dummySlider.get())
    {
        //[UserSliderCode_dummySlider] -- add your slider handling code here..
        //[/UserSliderCode_dummySlider]
    }

    //[UsersliderValueChanged_Post]
    sliderHasChanged = true;
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void inputCoordsView::refreshCoords(){
    /* update slider values and limits */
    for( int i=0; i<maxNCH; i++){
        aziSliders[i]->setRange (-360.0, 360.0, 0.1); // TODO: this range doens't conform to binauraliser_setSourceAzi_deg, so UI bugs out beyond +/-180 when dragging (but value OK on mouseup)
        aziSliders[i]->setValue(binauraliser_getSourceAzi_deg(hBin, i), dontSendNotification);
        
        elevSliders[i]->setRange (-180.0, 180.0, 0.1);
        elevSliders[i]->setValue (binauraliser_getSourceElev_deg(hBin, i), dontSendNotification);
        
        distSliders[i]->setRange (binauraliserNF_getNearfieldLimit_m(hBin), hVst->upperDistRange, 0.01);
        distSliders[i]->setValue (binauraliserNF_getSourceDist_m(hBin, i), dontSendNotification);
    }
}


//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="inputCoordsView" componentName=""
                 parentClasses="public Component" constructorParams="PluginProcessor* ownerFilter, int _maxNCH, int _currentNCH "
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="1" initialWidth="176" initialHeight="400">
  <BACKGROUND backgroundColour="323e10">
    <RECT pos="88 0 88 2048" fill="linear: 88 128, 176 128, 0=21ffffff, 1=5252a25"
          hasStroke="0"/>
    <RECT pos="0 0 88 2048" fill="linear: 88 128, 0 128, 0=21ffffff, 1=5252a25"
          hasStroke="0"/>
  </BACKGROUND>
  <SLIDER name="new slider" id="4689db34530ab7c7" memberName="dummySlider"
          virtualName="" explicitFocusOrder="0" pos="-176 144 96 16" min="0.01"
          max="0.3" int="0.001" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="70" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

