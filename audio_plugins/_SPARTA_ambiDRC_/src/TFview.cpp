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

#include "TFview.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...

#ifndef MIN
#define MIN(a,b) (( (a) < (b) ) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a,b) (( (a) > (b) ) ? (a) : (b))
#endif
//[/MiscUserDefs]

//==============================================================================
TFview::TFview (PluginProcessor* ownerFilter, int _width, int _height, float _min_freq, float _max_freq, float _min_dB, float _max_dB)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]


    //[UserPreSize]
    //[/UserPreSize]

    setSize (470, 220);


    //[Constructor] You can add your own custom stuff here..
    /* local pars */
	hVst = ownerFilter;
    hAmbi = hVst->getFXHandle();
    width = _width;
    height = _height;
    min_freq = _min_freq;
    max_freq = _max_freq;
    min_dB = _min_dB;
    max_dB = _max_dB;
    freqVector = NULL;

    /* component bounds */
    setSize(width, height);
    localBounds = getBounds();

    //[/Constructor]
}

TFview::~TFview()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void TFview::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..

    /* Background */
    int x = 0, y = 0;
    Colour fillColour2 = Colour (0xff4e4e4e), fillColour1 = Colour (0xff202020);
    //Colour fillColour1 = Colour (0xffcdf1ff), fillColour2 = Colour (0xff616161);
    Colour strokeColour = Colour (0x7dffffff);
    g.setGradientFill (ColourGradient (fillColour1,
                                       (float)width/2.0f + x,
                                       (float)width/2.0f + y,
                                       fillColour2,
                                       (float)width/2.0f + x,
                                       y,
                                       false));
    g.fillRect (x, y, width, height);
    g.setColour (strokeColour);
    g.drawRect (x, y, width, height, 1);

    if(freqVector!=NULL) {
        /* define TF tile bounds */
        float tileWidth = (float)(width) / (float)(NUM_DISPLAY_TIME_SLOTS);
        float c = log10f(min_freq);
        float m = (log10f(max_freq) - c)/(float)height;
        for (int band = 0; band < HYBRID_BANDS; band++) {
            float prev_Ypixel = band == 0 || band == 1 ? 0.0f : (log10f(freqVector[band-1]) - c)/m;
            float Ypixel = band == 0 ? 0.0f : (log10f(freqVector[band]) - c)/m;
            float tileHeight = Ypixel -prev_Ypixel;//SWAPPED!!!!
            for (int t = 0; t < NUM_DISPLAY_TIME_SLOTS; t++) {
                TFtiles[band][t].setBounds((float)t*tileWidth,
                                           (float)height- Ypixel, //SWAPPED!!! prev_Ypixel,
                                           tileWidth,
                                           tileHeight);
            }
        }

        /* Fill in TF tiles */ //MIN_DISPLAY_DB
        float**gainTF = ambi_drc_getGainTF(hAmbi);
        int wIdx = ambi_drc_getGainTFwIdx(hAmbi);
        int rIdx;
        float logScale = (log10f(1.0f) - log10f(SPECTRAL_FLOOR));
        g.setOpacity(1.0f);
        for (int band = 0; band < HYBRID_BANDS; band++) {
            for (int t = 0; t < READ_OFFSET; t++) {
                rIdx = 0>wIdx - READ_OFFSET + t ? 0 : wIdx - READ_OFFSET + t;
                float col_val = 1.0f - (log10f(gainTF[band][rIdx]) - log10f(SPECTRAL_FLOOR))/logScale;
                int col_idx = MAX(MIN((int)(col_val*(float)(mapColourTable_N)), mapColourTable_N-1), 0);
                g.setColour(mapColourTable[col_idx]);
                g.fillRect(TFtiles[band][(int)(rIdx)]);
            }
        }
    }

	/* Draw wIdx line */
	g.setColour(Colours::black);
	g.setOpacity(1.0f);
	g.drawLine(0.0f, height, width, height, 2.0f);

    /* draw frequency guide lines on top */
    g.setColour(Colours::white);
    g.setOpacity(0.35f);
    float freq;
    float c = log10f(min_freq);
    float m = (log10f(max_freq) - c)/(float)height;
    bool done = false;
    freq = min_freq;
    while(!done){
        float Ypixel = (log10f(freq) - c)/m;
        g.drawLine(0.0f, height-Ypixel, width, height-Ypixel, 1.0f);
        if (freq <= max_freq){
            if(freq<10.0f){ freq+=1.0f; } else if(freq<1e2){ freq+=10.0f; } else if (freq<1e3f){ freq+=100.0f; }
            else if (freq<1e4f){ freq+=1000.0f; } else if (freq<1e5f){ freq+=10000.0f; }
        }
        else
            done = true;
    }

    /* draw time guide lines on top */
    g.setColour(Colours::white);
    g.setOpacity(0.17f);
    for(int i=0; i<NUM_DISPLAY_SECONDS; i++){
        g.drawLine((float)i*(float)width/(float)NUM_DISPLAY_SECONDS, 0.0f,
                   (float)i*(float)width/(float)NUM_DISPLAY_SECONDS, (float)height, 1.0f);
    }

	/* Draw scroll line */
    int wIdx = ambi_drc_getGainTFwIdx(hAmbi);
	float linePos = (float)wIdx*(width / (float)NUM_DISPLAY_TIME_SLOTS);
	g.setColour(Colours::white);
	g.setOpacity(1.0f);
	g.drawLine(linePos, 0, linePos, height, 1);
	g.setColour(Colour(0x7dffffff));
	g.drawRect(0, 0, width, height, 1);

    //[/UserPaint]
}

void TFview::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="TFview" componentName=""
                 parentClasses="public Component" constructorParams="PluginProcessor* ownerFilter, int _width, int _height, float _min_freq, float _max_freq, float _min_dB, float _max_dB"
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="1" initialWidth="470" initialHeight="220">
  <BACKGROUND backgroundColour="ffffffff"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
