/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.1.2

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

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

    addAndMakeVisible (dummySlider = new Slider ("new slider"));
    dummySlider->setRange (0.01, 0.3, 0.001);
    dummySlider->setSliderStyle (Slider::LinearHorizontal);
    dummySlider->setTextBoxStyle (Slider::TextBoxRight, false, 70, 20);
    dummySlider->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (176, 400);


    //[Constructor] You can add your own custom stuff here..
    setSize (sensorEdit_width, sensorEdit_height*currentNCH); 
    hVst = ownerFilter;
    hAmbi = hVst->getFXHandle();
    maxNCH = _maxNCH ;
    currentNCH =_currentNCH;
    aziSliders =  new ScopedPointer<Slider>[maxNCH];
    elevSliders =  new ScopedPointer<Slider>[maxNCH];

    for( int i=0; i<maxNCH; i++){
        /* create and initialise azimuth sliders */
        addAndMakeVisible (aziSliders[i] = new Slider ("new slider"));
        aziSliders[i]->setRange (-360.0, 360.0, 0.001);
        aziSliders[i]->setValue(ambi_enc_getSourceAzi_deg(hAmbi, i));
        aziSliders[i]->setSliderStyle (Slider::LinearHorizontal);
        aziSliders[i]->setTextBoxStyle (Slider::TextBoxRight, false, 70, 20);
        aziSliders[i]->setBounds(-25, 8 + i*sensorEdit_height, 96, 16);
        aziSliders[i]->addListener (this);

        /* create and initialise elevation sliders */
        addAndMakeVisible (elevSliders[i] = new Slider ("new slider"));
        elevSliders[i]->setRange (-180.0, 180.0, 0.001);
        elevSliders[i]->setValue(ambi_enc_getSourceElev_deg(hAmbi, i));
        elevSliders[i]->setSliderStyle (Slider::LinearHorizontal);
        elevSliders[i]->setTextBoxStyle (Slider::TextBoxLeft, false, 70, 20);
        elevSliders[i]->setBounds(105, 8 + i*sensorEdit_height, 96, 16);
        elevSliders[i]->addListener (this);
    }

    sliderHasChanged = true;
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
    }
    delete [] aziSliders;
    delete [] elevSliders;
    //[/Destructor]
}

//==============================================================================
void inputCoordsView::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    {
        int x = 88, y = 0, width = 88, height = 2048;
        Colour fillColour1 = Colour (0x2affffff), fillColour2 = Colour (0x05252a25);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (ColourGradient (fillColour1,
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
        Colour fillColour1 = Colour (0x2affffff), fillColour2 = Colour (0x05252a25);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (ColourGradient (fillColour1,
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
        g.drawText (String(i+1), 72, 5+ i*sensorEdit_height, 33, 23,
                    Justification::centred, true);

        /* draw rectangle around sensor parameter */
        //Colour strokeColour = Colour (0x2370702b);
        //g.setColour (strokeColour);
        g.setColour(Colours::white);
        g.setOpacity(0.15f);
        g.drawRect (0, i*sensorEdit_height, sensorEdit_width, sensorEdit_height, 1);
    }


    //[/UserPaint]
}

void inputCoordsView::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    dummySlider->setBounds (-176, 144, 96, 16);
    //[UserResized] Add your own custom resize handling here..
    setSize (sensorEdit_width, sensorEdit_height*currentNCH);
    repaint();
    //[/UserResized]
}

void inputCoordsView::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    for(int i=0; i<maxNCH; i++){
        if (sliderThatWasMoved == aziSliders[i]) {
            ambi_enc_setSourceAzi_deg(hAmbi, i, (float)aziSliders[i]->getValue());
            break;
        }
        if (sliderThatWasMoved == elevSliders[i]) {
            ambi_enc_setSourceElev_deg(hAmbi, i, (float)elevSliders[i]->getValue());
            break;
        }
    }

    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == dummySlider)
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
        aziSliders[i]->setRange (-360.0, 360.0, 0.001);
        aziSliders[i]->setValue(ambi_enc_getSourceAzi_deg(hAmbi, i), dontSendNotification);
        elevSliders[i]->setRange (-180.0, 180.0, 0.001);
        elevSliders[i]->setValue(ambi_enc_getSourceElev_deg(hAmbi, i), dontSendNotification);
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
    <RECT pos="88 0 88 2048" fill="linear: 88 128, 176 128, 0=2affffff, 1=5252a25"
          hasStroke="0"/>
    <RECT pos="0 0 88 2048" fill="linear: 88 128, 0 128, 0=2affffff, 1=5252a25"
          hasStroke="0"/>
  </BACKGROUND>
  <SLIDER name="new slider" id="4689db34530ab7c7" memberName="dummySlider"
          virtualName="" explicitFocusOrder="0" pos="-176 144 96 16" min="0.010000000000000000208"
          max="0.2999999999999999889" int="0.0010000000000000000208" style="LinearHorizontal"
          textBoxPos="TextBoxRight" textBoxEditable="1" textBoxWidth="70"
          textBoxHeight="20" skewFactor="1" needsCallback="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
