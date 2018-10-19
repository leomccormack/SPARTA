/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.3.2

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...

//[/Headers]

#include "anaview.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...


const int border_pixels_top = 10;
const int border_pixels_bottom = 35;
const int border_pixels_left = 45;
const int border_pixels_right = 10;
const String xlabel = String("Frequency (Hz)");

static int round_nearest(int number, int multiple) {
    if(multiple==0)
        return 0;
    int result = number + multiple/2;
    result -= result % multiple;
    return result;
}

//[/MiscUserDefs]

//==============================================================================
anaview::anaview (int _width, int _height, float _min_freq, float _max_freq, float _min_Y, float _max_Y, String _ylabel, float _yaxislineStepSize, float _fs)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    setSize (_width, _height);

    addAndMakeVisible (anaview_windowIncluded = new anaview_window(_width-(border_pixels_left+border_pixels_right),
                                                                 _height-(border_pixels_top+border_pixels_bottom),
                                                                 _min_freq, _max_freq,
                                                                 _min_Y, _max_Y, _yaxislineStepSize, _fs));
    anaview_windowIncluded->setAlwaysOnTop(true);
    anaview_windowIncluded->setTopLeftPosition(border_pixels_left, border_pixels_top );

    width = _width;
    height =_height;
    min_freq = _min_freq;
    max_freq = _max_freq;
    min_Y = _min_Y;
    max_Y = _max_Y;
    ylabel = _ylabel;
    yaxislineStepSize = _yaxislineStepSize;
    fs = _fs;

    //[/Constructor]
}

anaview::~anaview()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void anaview::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..

    localBounds = getBounds();
    int pow10;
    int min_pow10, max_pow10;
    float val, freq;
    float c = log10f(min_freq);
    float m = (log10f(max_freq) - c)/(float)anaview_windowIncluded->getWidth();

    /* round specified frequency limits to 10^x for labels */
    for (pow10 = 0; pow10<7; pow10++){
        val =  powf(10.0f, (float)pow10);
        if ( ((min_freq/ val) <= val +0.001f) && (min_freq >=val-0.001f) ){
            min_pow10 = pow10;
        }
        if ( ((max_freq/ val) <= val) && (max_freq >=val) ){
            max_pow10 = pow10;
        }
    }

    /* draw frequency labels for each 10^x Hz */
    int textWidth = 60;
    int textHeight = 25;
    g.setColour(Colours::white);
    for (pow10 = min_pow10; pow10<=max_pow10; pow10++){
        freq = powf(10.0f, (float)pow10);
        float Xpixel = (log10f(freq) - c)/m;
        if (freq > 999.0f){
            g.drawText(String((int)((freq/1000.0f)+0.05f)) + String("k"), border_pixels_left+Xpixel-textWidth/2,
                       border_pixels_top + anaview_windowIncluded->getHeight(), textWidth, textHeight, Justification::centred);
        }
        else {
        g.drawText(String((int)freq), border_pixels_left+Xpixel-textWidth/2,
                   border_pixels_top + anaview_windowIncluded->getHeight(), textWidth, textHeight, Justification::centred);
        }
    }

    /* draw Magnitude labels */
    textWidth = 60;
    textHeight = 25;
    float start_dB= round_nearest(min_Y<0 ? min_Y-yaxislineStepSize : min_Y, yaxislineStepSize);
    float end_dB= round_nearest(max_Y, yaxislineStepSize);
    for (int i = start_dB; i<=end_dB; i+=yaxislineStepSize){
        float Ypixel = ((float)i-min_Y)* ((float)anaview_windowIncluded->getHeight()/(max_Y-min_Y));

        if ((i>min_Y-1) && (i< max_Y+1)){
            g.drawText(String(i), (int)(3.0f*(float)border_pixels_left/4.0f) - textWidth/2,
                       border_pixels_top + (anaview_windowIncluded->getHeight()-Ypixel) - textHeight/2,
                       textWidth, textHeight, Justification::centred);
        }
    }

    /* Axis labels */
    textWidth = 110;
    textHeight = 50;
    g.drawText(xlabel, (anaview_windowIncluded->getWidth())/2+border_pixels_left - textWidth/2,
               anaview_windowIncluded->getHeight() + border_pixels_top,
               textWidth, textHeight, Justification::centred);

    // Guessed this one...
    g.addTransform(AffineTransform::rotation(-M_PI/2).followedBy(AffineTransform::translation(-(localBounds.getHeight()/2 - border_pixels_top - (int)((float)textWidth/2.5f)),
                                                                                                localBounds.getHeight()- border_pixels_top - textWidth/2)));
    g.drawText(ylabel, 0,
               localBounds.getHeight()/2 - border_pixels_top - textWidth/2,
               textWidth, 50, Justification::centred);
    g.addTransform(AffineTransform());

    /* draw curves */
    //anaview_windowIncluded->repaint();/* No need to call, as eqview will repaint any children too */

    //[/UserPaint]
}

void anaview::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//void overlay::refreshView(){

    //repaint();

//}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="anaview" componentName=""
                 parentClasses="public Component" constructorParams="int _width, int _height, float _min_freq, float _max_freq, float _min_Y, float _max_Y, String _ylabel, float _yaxislineStepSize, float _fs"
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="1" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="222222"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
