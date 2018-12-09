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

#include "log2dSlider.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
float round_float(float in, int nDecimalPoints)
{
    float out;
    int n = (int)pow(10, nDecimalPoints);
    out = in*(float)n;
    out = (out > (floor(out)+0.5f)) ? ceil(out) : floor(out);
    out = out/(float)n;
    return out;
}


//[/MiscUserDefs]

//==============================================================================
log2dSlider::log2dSlider (int _width, int _height, float _min_X_value, float _max_X_value, float _min_Y_value, float _max_Y_value, int _nDecimalPoints)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]


    //[UserPreSize]
    //[/UserPreSize]

    setSize (320, 50);


    //[Constructor] You can add your own custom stuff here..
    setSize (_width, _height);
    localBounds = getBounds();

    width = _width;
    height =_height;
    min_X_value = _min_X_value;
    max_X_value = _max_X_value;
    min_Y_value = _min_Y_value;
    max_Y_value = _max_Y_value;
    nDecimalPoints = _nDecimalPoints;

    X_vector = NULL;
    Y_values = NULL;
    Y_values_int = NULL;
    refreshValues = true;
    //[/Constructor]
}

log2dSlider::~log2dSlider()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void log2dSlider::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..

    /* background */
    int x = 0, y = 0;
    Colour fillColour1 = Colour (0x11ffffff), fillColour2 = Colour (0x425b5b5b);
    Colour strokeColour = Colour (0xe1999999);
    g.setGradientFill (ColourGradient (fillColour1,
                                       0.0f,
                                       0.0f,
                                       fillColour2,
                                       0.0f,
                                       (float)height,
                                       false));
    g.fillRect (x, y, width, height);
    g.setColour (strokeColour);
    g.drawRect (x, y, width, height, 1);


    /* draw logarithmic X-axis guide lines */
    g.setColour(Colours::white);
    g.setOpacity(0.15f);
    float xlog;
    float c = log10f(min_X_value);
    float m = (log10f(max_X_value) - c)/(float)localBounds.getWidth();
    bool done = false;
    xlog = min_X_value;
    while(!done){
        float Xpixel = (log10f(xlog) - c)/m;
        g.drawLine(Xpixel, 0.0f, Xpixel, localBounds.getHeight(), 1.0f);
        if (xlog <= max_X_value){
            if(xlog<10.0f){ xlog+=1.0f; } else if(xlog<1e2){ xlog+=10.0f; } else if (xlog<1e3f){ xlog+=100.0f; }
            else if (xlog<1e4f){ xlog+=1000.0f; } else if (xlog<1e5f){ xlog+=10000.0f; }
        }
        else
            done = true;
    }

    /* draw Y-axis guide lines */
    g.setColour(Colours::white);
    g.setOpacity(0.03f);
    g.drawLine(0.0f, (float)height/2.0f, (float)width, (float)height/2.0f, 1.0f);
    g.drawLine(0.0f, (float)height/4.0f, (float)width, (float)height/4.0f, 1.0f);
    g.drawLine(0.0f, 3.0f*(float)height/4.0f, (float)width,  3.0f*(float)height/4.0f, 1.0f);

    /* draw data */
    
    if( (X_vector!=NULL) && (useIntValues ? (Y_values_int!=NULL) : (Y_values!=NULL)) ){
        float y_range = max_Y_value - min_Y_value;
        for(int xIdx = 0; xIdx<num_X_points-1; xIdx++){
            float Xpixel_1 = MAX(0,(log10f(X_vector[xIdx]+2.23e-13f) - c)/m);
            float Xpixel_2 = MAX(0,(log10f(X_vector[xIdx+1]+2.23e-13f) - c)/m)+1;
            float Yval;
            if(useIntValues)
                Yval = (float)Y_values_int[xIdx]-min_Y_value;
            else
                Yval = Y_values[xIdx]-min_Y_value;
            Yval = round_float(Yval, nDecimalPoints);
            float Ylength;
            if(max_Y_value==min_Y_value)
                Ylength = height/2.0f;
            else
                Ylength = (Yval/y_range)*(float)height;

            g.setColour(Colours::deepskyblue);
            g.setOpacity(0.2f);
            g.fillRect(Xpixel_1, (float)height- Ylength, Xpixel_2-Xpixel_1, Ylength);
            g.setColour(Colours::white);
            g.setOpacity(0.3f);
            g.drawRect(Xpixel_1, (float)height- Ylength, Xpixel_2-Xpixel_1, Ylength ,1.0f);
        }
    }

    //refreshValues = false;
    //[/UserPaint]
}

void log2dSlider::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void log2dSlider::mouseDown (const MouseEvent& e)
{
    //[UserCode_mouseDown] -- Add your code here...
    float c = log10f(min_X_value);
    float m = (log10f(max_X_value) - c)/(float)localBounds.getWidth();
    bool shouldContinue = true;

    if( (X_vector!=NULL) && (useIntValues ? (Y_values_int!=NULL) : (Y_values!=NULL)) ){
        float y_range = max_Y_value - min_Y_value;
        for(int xIdx = 0; (xIdx<num_X_points-1) && shouldContinue; xIdx++){
            float Xpixel_1 = MAX(0,(log10f(X_vector[xIdx]+2.23e-13f) - c)/m);
            float Xpixel_2 = MAX(0,(log10f(X_vector[xIdx+1]+2.23e-13f) - c)/m);
            float Yval = 1.0f-(float)e.getPosition().y/(float)height;
            /* if down click is between two X-axis indices */
            if((e.getPosition().x>Xpixel_1) && (e.getPosition().x<=Xpixel_2)){
                Yval = round_float(Yval*y_range, nDecimalPoints);
                if(useIntValues)
                    Y_values_int[xIdx] = (int)(jlimit(min_Y_value, max_Y_value, Yval+min_Y_value)+0.5f);
                else
                    Y_values[xIdx] = jlimit(min_Y_value, max_Y_value, Yval+min_Y_value);
                refreshValues = true;
                shouldContinue = false;
            }
        }
    }
    //[/UserCode_mouseDown]
}

void log2dSlider::mouseDrag (const MouseEvent& e)
{
    //[UserCode_mouseDrag] -- Add your code here...
    float c = log10f(min_X_value);
    float m = (log10f(max_X_value) - c)/(float)localBounds.getWidth();
    bool shouldContinue = true;

    if( (X_vector!=NULL) && (useIntValues ? (Y_values_int!=NULL) : (Y_values!=NULL)) ){
        float y_range = max_Y_value - min_Y_value;
        for(int xIdx = 0; (xIdx<num_X_points-1) && shouldContinue; xIdx++){
            float Xpixel_1 = MAX(0,(log10f(X_vector[xIdx]+2.23e-13f) - c)/m)-6.0f;
            float Xpixel_2 = MAX(0,(log10f(X_vector[xIdx+1]+2.23e-13f) - c)/m)+6.0f;
            float Yval = 1.0f-(float)e.getPosition().y/(float)height;
            /* if down click is between two X-axis indices */
            if((e.getPosition().x>=Xpixel_1) && (e.getPosition().x<=Xpixel_2)){
                Yval = round_float(Yval*y_range, nDecimalPoints);
                if(useIntValues)
                    Y_values_int[xIdx] = (int)(jlimit(min_Y_value, max_Y_value, Yval+min_Y_value)+0.5f);
                else
                    Y_values[xIdx] = jlimit(min_Y_value, max_Y_value, Yval+min_Y_value);
                refreshValues = true;
            }
        }
    }
    //[/UserCode_mouseDrag]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="log2dSlider" componentName=""
                 parentClasses="public Component" constructorParams="int _width, int _height, float _min_X_value, float _max_X_value, float _min_Y_value, float _max_Y_value, int _nDecimalPoints"
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="1" initialWidth="320" initialHeight="50">
  <METHODS>
    <METHOD name="mouseDown (const MouseEvent&amp; e)"/>
    <METHOD name="mouseDrag (const MouseEvent&amp; e)"/>
  </METHODS>
  <BACKGROUND backgroundColour="b9b9b9"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
