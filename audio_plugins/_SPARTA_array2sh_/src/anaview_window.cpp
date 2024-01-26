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

#include "anaview_window.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...

static int round_nearest(int number, int multiple) {
    int result = number + multiple/2;
    result -= result % multiple;
    return result;
}

static void setCurveColour(Graphics& g, int n){
    switch(n){
        default: /* fall through */
        case 0: g.setColour(Colours::blue); break;
        case 1: g.setColour(Colours::red); break;
        case 2: g.setColour(Colours::yellow); break;
        case 3: g.setColour(Colours::purple); break;
        case 4: g.setColour(Colours::green); break;
        case 5: g.setColour(Colours::lightblue); break;
        case 6: g.setColour(Colours::darkred); break;
        case 7: g.setColour(Colours::darkblue); break;
        case 8: g.setColour(Colours::blue); break;
        case 9: g.setColour(Colours::red); break;
        case 10: g.setColour(Colours::yellow); break;
    }
}

//[/MiscUserDefs]

//==============================================================================
anaview_window::anaview_window (int _width, int _height, float _min_freq, float _max_freq, float _min_Y, float _max_Y, float _yaxislineStepSize, float _fs)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..

    setSize (_width, _height);
    localBounds = getBounds();

    width = _width;
    height =_height;
    min_freq = _min_freq;
    max_freq = _max_freq;
    min_Y = _min_Y;
    max_Y = _max_Y;
    yaxislineStepSize = _yaxislineStepSize;
    fs = _fs;

    freqVector = NULL;
    solidCurves = NULL;

    //[/Constructor]
}

anaview_window::~anaview_window()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void anaview_window::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..

    /* background */
    //Colour fillColour1 = Colour (0x75707070), fillColour2 = Colour (0xa1202020);
    Colour fillColour1 = Colour (0xff4e4e4e), fillColour2 = Colour (0xff202020);
    g.setGradientFill (ColourGradient (fillColour1, 0, 0,
                                       fillColour2, 0, localBounds.getHeight(),
                                       false));
    g.fillRect (localBounds);
    g.setColour(Colours::white);
    g.setOpacity(0.3f);
    g.drawRect (localBounds);

    /* draw frequency guide lines */
    g.setColour(Colours::white);
    g.setOpacity(0.22f);
    float freq;
    float c = log10f(min_freq);
    float m = (log10f(max_freq) - c)/(float)localBounds.getWidth();
    bool done = false;
    freq = min_freq;
    while(!done){
        float Xpixel = (log10f(freq) - c)/m;
        g.drawLine(Xpixel, 0.0f, Xpixel, localBounds.getHeight(), 1.0f);
        if (freq <= max_freq){
            if(freq<10.0f){ freq+=1.0f; } else if(freq<1e2){ freq+=10.0f; } else if (freq<1e3f){ freq+=100.0f; }
            else if (freq<1e4f){ freq+=1000.0f; } else if (freq<1e5f){ freq+=10000.0f; }
        }
        else{
            done = true;
        }
    }

    /* draw magnitude guide lines */
    g.setColour(Colours::white);
    g.setOpacity(0.08f);
    float start_dB = round_nearest(min_Y<0 ? min_Y-yaxislineStepSize : min_Y, yaxislineStepSize);
    float end_dB= round_nearest(max_Y, yaxislineStepSize);
    for (int i = start_dB; i<=end_dB; i+=yaxislineStepSize){
        float Ypixel = ((float)i-min_Y)* ((float)localBounds.getHeight()/(max_Y-min_Y));
        if ((i>min_Y-1) && (i< max_Y+1)){
            g.drawLine(0,localBounds.getHeight()-Ypixel, localBounds.getWidth(), localBounds.getHeight()-Ypixel,1.0f);
        }
    }

    /* plot solid curves (if defined) */
    if ( (freqVector != NULL) && (solidCurves != NULL) ){
        for(int crv=0; crv<numCurves; crv++){
            for(int f=0; f<numFreqPoints-1; f++){
                float Xpixel = (log10f(freqVector[f]) - c)/m;
                float Ypixel = (solidCurves[f*numCurves+crv]-min_Y)* ((float)localBounds.getHeight()/(max_Y-min_Y));
                float Xpixel_next = (log10f(freqVector[f+1]) - c)/m;
                float Ypixel_next = (solidCurves[(f+1)*numCurves+crv]-min_Y)* ((float)localBounds.getHeight()/(max_Y-min_Y));
                /* background line */
                g.setColour(Colours::white);
                g.setOpacity(0.1f);
                g.drawLine(Xpixel, localBounds.getHeight()-Ypixel, Xpixel_next, localBounds.getHeight()-Ypixel_next, 5.0f);
                /* main */
                setCurveColour(g, crv);
                g.setOpacity(1.0f);
                g.drawLine(Xpixel, localBounds.getHeight()-Ypixel, Xpixel_next, localBounds.getHeight()-Ypixel_next, 2.0f);
            }
        }
    }

    /* Plot legend */
    float leg_x = 460;
    float leg_y = 82;
    g.setColour(Colours::grey);
    g.setOpacity(1.0f);
    g.drawRect(leg_x, leg_y, 38.0f, 10.0f*(float)numCurves, 1.0f);
    g.setOpacity(0.25f);
    g.fillRect(leg_x, leg_y, 38.0f, 10.0f*(float)numCurves);
    g.setOpacity(1.0f);
    g.setFont(9.0f);
    String suffix;
    for(int crv=0; crv<numCurves; crv++){
        g.setColour(Colours::white);
        if(crv==1)
            suffix = "st";
        else if(crv==2)
            suffix = "nd";
        else if(crv==3)
            suffix = "rd";
        else
            suffix = "th";
        g.drawText(String(crv)+suffix, leg_x+2.0f, leg_y+(float)crv*10.0f, 30.0f, 8.0f, Justification::centredLeft);
        setCurveColour(g, crv);
        g.drawLine(leg_x+18.0f, leg_y+(float)crv*10.0f+4.0f, leg_x+34.0f, leg_y+(float)crv*10.0f+4.0f, 2.0f);
    }
    //[/UserPaint]
}

void anaview_window::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//void overlay::refreshPowerMap(){
//
//    repaint();
//
//}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="anaview_window" componentName=""
                 parentClasses="public Component" constructorParams="int _width, int _height, float _min_freq, float _max_freq, float _min_Y, float _max_Y, float _yaxislineStepSize, float _fs"
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="1" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffffff"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

