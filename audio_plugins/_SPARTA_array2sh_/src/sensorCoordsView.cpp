/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.3.0

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...

//[/Headers]

#include "sensorCoordsView.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
const int sensorEdit_width = 176;
const int sensorEdit_height = 32;
//[/MiscUserDefs]

//==============================================================================
sensorCoordsView::sensorCoordsView (PluginProcessor* ownerFilter, int _maxQ, int _currentQ, bool _useDegreesInstead)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (dummySlider = new Slider ("new slider"));
    dummySlider->setRange (0.01, 0.3, 0.001);
    dummySlider->setSliderStyle (Slider::LinearHorizontal);
    dummySlider->setTextBoxStyle (Slider::TextBoxRight, false, 70, 20);
    dummySlider->addListener (this);

    dummySlider->setBounds (-176, 144, 96, 16);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (176, 400);


    //[Constructor] You can add your own custom stuff here..
    setSize (sensorEdit_width, sensorEdit_height*_currentQ);

    hVst = ownerFilter;
    maxQ = _maxQ;
    currentQ =_currentQ;
    useDegreesInstead =  _useDegreesInstead;
    aziSliders =  new ScopedPointer<Slider>[maxQ];
    elevSliders =  new ScopedPointer<Slider>[maxQ];

    for( int i=0; i<maxQ; i++){
        /* create and initialise azimuth sliders */
        addAndMakeVisible (aziSliders[i] = new Slider ("new slider"));
        if(useDegreesInstead){
            aziSliders[i]->setRange (-360.0, 360.0, 0.001);
            aziSliders[i]->setValue(array2sh_getSensorAzi_deg(hVst->hA2sh, i));
        }
        else{
            aziSliders[i]->setRange (-2.0*M_PI, 2.0*M_PI, 0.00001);
            aziSliders[i]->setValue(array2sh_getSensorAzi_rad(hVst->hA2sh, i));
        }
        aziSliders[i]->setSliderStyle (Slider::LinearHorizontal);
        aziSliders[i]->setTextBoxStyle (Slider::TextBoxRight, false, 70, 20);
        aziSliders[i]->setBounds(-25, 8 + i*sensorEdit_height, 96, 16);
        aziSliders[i]->addListener (this);

        /* create and initialise elevation sliders */
        addAndMakeVisible (elevSliders[i] = new Slider ("new slider"));
        if(useDegreesInstead){
            elevSliders[i]->setRange (-180.0, 180.0, 0.001);
            elevSliders[i]->setValue(array2sh_getSensorElev_deg(hVst->hA2sh, i));
        }
        else {
            elevSliders[i]->setRange (-M_PI, M_PI, 0.00001);
            elevSliders[i]->setValue(array2sh_getSensorElev_rad(hVst->hA2sh, i));
        }
        elevSliders[i]->setSliderStyle (Slider::LinearHorizontal);
        elevSliders[i]->setTextBoxStyle (Slider::TextBoxLeft, false, 70, 20);
        elevSliders[i]->setBounds(105, 8 + i*sensorEdit_height, 96, 16);
        elevSliders[i]->addListener (this);
    }
    
    refreshCoords();
    resized();

    //[/Constructor]
}

sensorCoordsView::~sensorCoordsView()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    dummySlider = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    for( int i=0; i<maxQ; i++){
        aziSliders[i] = nullptr;
        elevSliders[i] = nullptr;
    }
    delete [] aziSliders;
    delete [] elevSliders;
    //[/Destructor]
}

//==============================================================================
void sensorCoordsView::paint (Graphics& g)
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

    for( int i=0; i<maxQ; i++){
        /* draw sensor IDs */
        g.setColour (fillColour);
        g.drawText (String(i+1), 72, 5+ i*sensorEdit_height, 33, 23,
                    Justification::centred, true);

        /* draw rectangle around sensor parameter */
        //Colour strokeColour = Colour (0x2370702b);
        //g.setColour (strokeColour);
        g.setColour(Colours::white);
        g.setOpacity(0.15f);
        g.drawRect (0, i*sensorEdit_height, sensorEdit_width, sensorEdit_height+1, 1);
    }


    //[/UserPaint]
}

void sensorCoordsView::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    setSize (sensorEdit_width, sensorEdit_height*currentQ+1);
    repaint();
    //[/UserResized]
}

void sensorCoordsView::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    for(int i=0; i<maxQ; i++){
        if (sliderThatWasMoved == aziSliders[i]) {
            if(useDegreesInstead)
                array2sh_setSensorAzi_deg(hVst->hA2sh, i, (float)aziSliders[i]->getValue());
            else
                array2sh_setSensorAzi_rad(hVst->hA2sh, i, (float)aziSliders[i]->getValue());
            break;
        }
        if (sliderThatWasMoved == elevSliders[i]) {
            if(useDegreesInstead)
                array2sh_setSensorElev_deg(hVst->hA2sh, i, (float)elevSliders[i]->getValue());
            else
                array2sh_setSensorElev_rad(hVst->hA2sh, i, (float)elevSliders[i]->getValue());
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
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void sensorCoordsView::refreshCoords(){
    /* update slider values and limits */
    for( int i=0; i<maxQ; i++){
        if(useDegreesInstead){
            aziSliders[i]->setRange (-360.0, 360.0, 0.001);
            aziSliders[i]->setValue(array2sh_getSensorAzi_deg(hVst->hA2sh, i), dontSendNotification);
            elevSliders[i]->setRange (-180.0, 180.0, 0.001);
            elevSliders[i]->setValue(array2sh_getSensorElev_deg(hVst->hA2sh, i), dontSendNotification);
        }
        else{
            aziSliders[i]->setRange (-2.0*M_PI, 2.0*M_PI, 0.00001);
            aziSliders[i]->setValue(array2sh_getSensorAzi_rad(hVst->hA2sh, i), dontSendNotification);
            elevSliders[i]->setRange (-M_PI, M_PI, 0.00001);
            elevSliders[i]->setValue(array2sh_getSensorElev_rad(hVst->hA2sh, i), dontSendNotification);
        }
    }
}


void sensorCoordsView::setUseDegreesInstead(bool newState)
{
    useDegreesInstead = newState;
    refreshCoords();
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="sensorCoordsView" componentName=""
                 parentClasses="public Component" constructorParams="PluginProcessor* ownerFilter, int _maxQ, int _currentQ, bool _useDegreesInstead"
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="1" initialWidth="176" initialHeight="400">
  <BACKGROUND backgroundColour="323e10">
    <RECT pos="88 0 88 2048" fill="linear: 88 128, 176 128, 0=2affffff, 1=5252a25"
          hasStroke="0"/>
    <RECT pos="0 0 88 2048" fill="linear: 88 128, 0 128, 0=2affffff, 1=5252a25"
          hasStroke="0"/>
  </BACKGROUND>
  <SLIDER name="new slider" id="4689db34530ab7c7" memberName="dummySlider"
          virtualName="" explicitFocusOrder="0" pos="-176 144 96 16" min="0.01000000000000000021"
          max="0.29999999999999998890" int="0.00100000000000000002" style="LinearHorizontal"
          textBoxPos="TextBoxRight" textBoxEditable="1" textBoxWidth="70"
          textBoxHeight="20" skewFactor="1.00000000000000000000" needsCallback="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
