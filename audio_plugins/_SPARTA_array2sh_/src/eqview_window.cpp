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

#include "eqview_window.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
const int mag_lines_interval = 10; /* dB per horizontal guide line */

static int round_nearest(int number, int multiple) {
    int result = number + multiple/2;
    result -= result % multiple;
    return result;
}

static void setCurveColour(Graphics& g, int n){
    switch(n){
        case 0: g.setColour(Colours::blue); break;
        case 1: g.setColour(Colours::red); break;
        case 2: g.setColour(Colours::yellow); break;
        case 3: g.setColour(Colours::purple); break;
        case 4: g.setColour(Colours::green); break;
        case 5: g.setColour(Colours::lightblue); break;
        case 6: g.setColour(Colours::darkred); break;
        case 7: g.setColour(Colours::darkblue); break;
    }
}
//[/MiscUserDefs]

//==============================================================================
eqview_window::eqview_window (int _width, int _height, float _min_freq, float _max_freq, float _min_dB, float _max_dB, float _fs)
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
    min_dB = _min_dB;
    max_dB = _max_dB;
    fs = _fs;

    freqVector = NULL;
    solidCurves = NULL;
    faintCurves = NULL;

    //[/Constructor]
}

eqview_window::~eqview_window()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void eqview_window::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..

    /* background */
    Colour fillColour1 = Colour (0x75707070), fillColour2 = Colour (0xa1202020);
    g.setGradientFill (ColourGradient (fillColour1, 0, 0,
                                       fillColour2, 0, localBounds.getHeight(),
                                       false));
    g.fillRect (localBounds);
    g.setColour(Colours::white);
    g.setOpacity(0.3f);
    g.drawRect (localBounds);

    /* draw frequency guide lines */
    g.setColour(Colours::white);
    g.setOpacity(0.13f);
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
    g.setOpacity(0.03f);
    float start_dB = round_nearest(min_dB<0 ? min_dB-mag_lines_interval : min_dB, mag_lines_interval);
    float end_dB= round_nearest(max_dB, mag_lines_interval);
    for (int i = start_dB; i<=end_dB; i+=mag_lines_interval){
        float Ypixel = ((float)i-min_dB)* ((float)localBounds.getHeight()/(max_dB-min_dB));
        if ((i>min_dB-1) && (i< max_dB+1)){
            g.drawLine(0,localBounds.getHeight()-Ypixel, localBounds.getWidth(), localBounds.getHeight()-Ypixel,1.0f);
        }
    }

    /* plot faint magnitude curves (if defined) */
    if ( (freqVector != NULL) && (faintCurves != NULL) ){
        for(int crv=0; crv<numCurves; crv++){
            for(int f=0; f<numFreqPoints-1; f++){
                float Xpixel = (log10f(freqVector[f]) - c)/m;
                float Ypixel = (faintCurves[f][crv]-min_dB)* ((float)localBounds.getHeight()/(max_dB-min_dB));
                float Xpixel_next = (log10f(freqVector[f+1]) - c)/m;
                float Ypixel_next = (faintCurves[f+1][crv]-min_dB)* ((float)localBounds.getHeight()/(max_dB-min_dB));
                /* background line */
                g.setColour(Colours::white);
                g.setOpacity(0.1f);
                g.drawLine(Xpixel, localBounds.getHeight()-Ypixel, Xpixel_next, localBounds.getHeight()-Ypixel_next, 2.0f);
                /* main */
                setCurveColour(g, crv);
                g.setOpacity(0.3f);
                g.drawLine(Xpixel, localBounds.getHeight()-Ypixel, Xpixel_next, localBounds.getHeight()-Ypixel_next, 1.0f);
            }
        }
    }

    /* plot solid magnitude curves (if defined) */
    if ( (freqVector != NULL) && (solidCurves != NULL) ){
        for(int crv=0; crv<numCurves; crv++){
            for(int f=0; f<numFreqPoints-1; f++){
                float Xpixel = (log10f(freqVector[f]) - c)/m;
                float Ypixel = (solidCurves[f][crv]-min_dB)* ((float)localBounds.getHeight()/(max_dB-min_dB));
                float Xpixel_next = (log10f(freqVector[f+1]) - c)/m;
                float Ypixel_next = (solidCurves[f+1][crv]-min_dB)* ((float)localBounds.getHeight()/(max_dB-min_dB));
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
    //[/UserPaint]
}

void eqview_window::resized()
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

<JUCER_COMPONENT documentType="Component" className="eqview_window" componentName=""
                 parentClasses="public Component" constructorParams="int _width, int _height, float _min_freq, float _max_freq, float _min_dB, float _max_dB, float _fs"
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="1" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffffff"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
