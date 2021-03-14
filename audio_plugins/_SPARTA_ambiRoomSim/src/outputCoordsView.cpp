/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 6.0.5

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...

//[/Headers]

#include "outputCoordsView.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
const int sensorEdit_width = 212;
const int sensorEdit_height = 32;
//[/MiscUserDefs]

//==============================================================================
outputCoordsView::outputCoordsView (PluginProcessor* ownerFilter, int _maxNCH, int _currentNCH )
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    dummySlider.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (dummySlider.get());
    dummySlider->setRange (0.01, 0.3, 0.001);
    dummySlider->setSliderStyle (juce::Slider::LinearHorizontal);
    dummySlider->setTextBoxStyle (juce::Slider::TextBoxRight, false, 70, 20);
    dummySlider->addListener (this);

    dummySlider->setBounds (-176, 144, 96, 16);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (176, 400);


    //[Constructor] You can add your own custom stuff here..
    setSize (sensorEdit_width, sensorEdit_height*currentNCH);
    hVst = ownerFilter;
    hAmbi = hVst->getFXHandle();
    maxNCH = _maxNCH ;
    currentNCH =_currentNCH;
    xSliders =  new std::unique_ptr<Slider>[maxNCH];
    ySliders =  new std::unique_ptr<Slider>[maxNCH];
    zSliders =  new std::unique_ptr<Slider>[maxNCH];

    for( int i=0; i<maxNCH; i++){
        /* create x sliders */
        xSliders[i].reset (new Slider ("new slider"));
        addAndMakeVisible (xSliders[i].get());
        xSliders[i]->setTextBoxStyle (Slider::TextBoxRight, false, 58, 20);
        xSliders[i]->setBounds(24, 8 + i*sensorEdit_height, 58, 16);
        xSliders[i]->addListener (this);
        xSliders[i]->setColour(Slider::trackColourId, Colours::transparentBlack);
        xSliders[i]->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
        xSliders[i]->setSliderSnapsToMousePosition(false);

        /* create y sliders */
        ySliders[i].reset (new Slider ("new slider"));
        addAndMakeVisible (ySliders[i].get());
        ySliders[i]->setTextBoxStyle (Slider::TextBoxRight, false, 58, 20);
        ySliders[i]->setBounds(86, 8 + i*sensorEdit_height, 58, 16);
        ySliders[i]->addListener (this);
        ySliders[i]->setColour(Slider::trackColourId, Colours::transparentBlack);
        ySliders[i]->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
        ySliders[i]->setSliderSnapsToMousePosition(false);

        /* create z sliders */
        zSliders[i].reset (new Slider ("new slider"));
        addAndMakeVisible (zSliders[i].get());
        zSliders[i]->setTextBoxStyle (Slider::TextBoxRight, false, 58, 20);
        zSliders[i]->setBounds(148, 8 + i*sensorEdit_height, 58, 16);
        zSliders[i]->addListener (this);
        zSliders[i]->setColour(Slider::trackColourId, Colours::transparentBlack);
        zSliders[i]->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
        zSliders[i]->setSliderSnapsToMousePosition(false);

        /* Initialise sliders */
        xSliders[i]->setRange (0.0f, ambi_roomsim_getRoomDimX(hAmbi), 0.001);
        xSliders[i]->setValue(ambi_roomsim_getReceiverX(hAmbi, i), dontSendNotification);
        ySliders[i]->setRange (0.0f, ambi_roomsim_getRoomDimY(hAmbi), 0.001);
        ySliders[i]->setValue(ambi_roomsim_getReceiverY(hAmbi, i), dontSendNotification);
        zSliders[i]->setRange (0.0f, ambi_roomsim_getRoomDimZ(hAmbi), 0.001);
        zSliders[i]->setValue(ambi_roomsim_getReceiverZ(hAmbi, i), dontSendNotification);
    }

    sliderHasChanged = true;
    refreshCoords();
    resized();

    //[/Constructor]
}

outputCoordsView::~outputCoordsView()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    dummySlider = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    for( int i=0; i<maxNCH; i++){
        xSliders[i] = nullptr;
        ySliders[i] = nullptr;
        zSliders[i] = nullptr;
    }
    delete [] xSliders;
    delete [] ySliders;
    delete [] zSliders;
    //[/Destructor]
}

//==============================================================================
void outputCoordsView::paint (juce::Graphics& g)
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
        g.drawText (String(i+1), -4, 5+ i*sensorEdit_height, 33, 23,
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

void outputCoordsView::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    setSize (sensorEdit_width, sensorEdit_height*currentNCH);
    repaint();
    //[/UserResized]
}

void outputCoordsView::sliderValueChanged (juce::Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    for(int i=0; i<maxNCH; i++){
        if (sliderThatWasMoved == xSliders[i].get()) {
            ambi_roomsim_setReceiverX(hAmbi, i, (float)xSliders[i]->getValue());
            break;
        }
        if (sliderThatWasMoved == ySliders[i].get()) {
            ambi_roomsim_setReceiverY(hAmbi, i, (float)ySliders[i]->getValue());
            break;
        }
        if (sliderThatWasMoved == zSliders[i].get()) {
            ambi_roomsim_setReceiverZ(hAmbi, i, (float)zSliders[i]->getValue());
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

void outputCoordsView::refreshCoords(){
    /* update slider values and limits */
    for( int i=0; i<maxNCH; i++){
        xSliders[i]->setRange (0.0f, ambi_roomsim_getRoomDimX(hAmbi), 0.001);
        xSliders[i]->setValue(ambi_roomsim_getReceiverX(hAmbi, i), dontSendNotification);
        ySliders[i]->setRange (0.0f, ambi_roomsim_getRoomDimY(hAmbi), 0.001);
        ySliders[i]->setValue(ambi_roomsim_getReceiverY(hAmbi, i), dontSendNotification);
        zSliders[i]->setRange (0.0f, ambi_roomsim_getRoomDimZ(hAmbi), 0.001);
        zSliders[i]->setValue(ambi_roomsim_getReceiverZ(hAmbi, i), dontSendNotification);
    }
}


//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="outputCoordsView" componentName=""
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

