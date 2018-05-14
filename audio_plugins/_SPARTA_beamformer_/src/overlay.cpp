/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 4.2.3

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "overlay.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
static Point<int> convertAzElToPoint(float az, float el, Rectangle<int> localBounds, float hfov, float vfov)
{
    Point<int> AzElPos;
    Point<int> centre = localBounds.getCentre();
    float width  = (float)localBounds.getWidth();
    float height = (float)localBounds.getHeight();

    AzElPos.setX( (int)((float)centre.getX() + (az/ (hfov/2.0f)) * (width/2.0f)) );
    AzElPos.setY( (int)((float)centre.getY() - (el/ (vfov/2.0f)) * (height/2.0f)) );

    return AzElPos;
}

static void convertPointToAzEl(Point<int> AzElPos, Rectangle<int> localBounds, float hfov, float vfov, float* az, float* el)
{
    Point<int> centre = localBounds.getCentre();
    float width  = (float)localBounds.getWidth();
    float height = (float)localBounds.getHeight();
    float x = (float)AzElPos.getX();
    float y = (float)AzElPos.getY();

    (*az) = (  (x - (float)centre.getX()) / (width/2.0f)  ) * (hfov/2.0f);
    (*el) = ( -(y - (float)centre.getY()) / (height/2.0f) ) * (vfov/2.0f);
}

static void setColourGradient(Graphics& g, float val)
{
	if (val >= 0.9f)
		g.setColour(Colour::fromFloatRGBA(0.5f, 0.0f, 0.0f, 0.85f));
	else if (val >= 0.8f)
		g.setColour(Colour::fromFloatRGBA(1.0f, 0.2f, 0.0f, 0.85f));
	else if (val >= 0.7f)
		g.setColour(Colour::fromFloatRGBA(1.0f, 0.39f, 0.0f, 0.75f));
	else if (val >= 0.6f)
		g.setColour(Colour::fromFloatRGBA(1.0f, 0.78f, 0.0f, 0.65f));
	else if (val >= 0.5f)
		g.setColour(Colour::fromFloatRGBA(0.39f, 1.0f, 0.2f, 0.55f));
	else if (val >= 0.4f)
		g.setColour(Colour::fromFloatRGBA(0.39f, 1.0f, 1.0f, 0.45f));
	else if (val >= 0.3f)
		g.setColour(Colour::fromFloatRGBA(0.39f, 0.58f, 1.0f, 0.35f));
	else if (val >= 0.2f)
		g.setColour(Colour::fromFloatRGBA(0.0f, 0.39f, 1.0f, 0.25f));
	else if (val >= 0.1f)
		g.setColour(Colour::fromFloatRGBA(0.39f, 0.58f, 1.0f, 0.05f));
	else
		g.setColour(Colour::fromFloatRGBA(0.0f, 0.2f, 1.0f, 0.0f));
}

//[/MiscUserDefs]

//==============================================================================
overlay::overlay (PluginProcessor* ownerFilter)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    hVst = ownerFilter;
    hasFinishedDrawing = true;
    //[/Constructor]
}

overlay::~overlay()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void overlay::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
	if (hasFinishedDrawing) { /* in order to stop it from tripping over itself */
        hasFinishedDrawing = false;

        Rectangle<int> r(getLocalBounds());
        localBounds = r;

		

        /* CONFIGURE POWER MAP */
		float size = 8.0f;
		float lsize = 10.0f;
		float doa_x, doa_y;
        int nBands, nSecs;  
        float width = (float)localBounds.getWidth();
        float height = (float)localBounds.getHeight();
		sfcropaclib_getDOA(hVst->hSfcropac, DOA_sph, scaleAlpha, scaleColour, &nBands, &nSecs );
		float hfov = sfcropaclib_getFOV(hVst->hSfcropac);
		float vfov = hfov/ sfcropaclib_getAspectRatio(hVst->hSfcropac);

		if (DOA_sph!=NULL){
            /* DRAW DOA MAP */
            for (int i = 0; i < nBands; i++) {
                for (int j = 0; j < nSecs; j++) { 
					if (scaleColour[i][j] > 0.666f) {
						g.setColour(Colour::fromFloatRGBA(1.0f, 3.0f*(1.0f - scaleColour[i][j]), 0.0f, 1.0f));
					}
					else if (scaleColour[i][j] > 0.333f) {
						g.setColour(Colour::fromFloatRGBA(0.0f, 0.333f + (1.0f-scaleColour[i][j]), 0.0f, 1.0f));
					}
					else {
						g.setColour(Colour::fromFloatRGBA(0.0f, 1.0f*(scaleColour[i][j]), 1.0f, 1.0f));
					} 
                    g.setOpacity(powf(20.0f,scaleAlpha[i][j])/20.0f - 0.1f);
					doa_x = width * ((-DOA_sph[i][j][0] * 180.0f / M_PI + hfov / 2.0f) / hfov);
					doa_y = height * ((-DOA_sph[i][j][1] * 180.0f / M_PI + vfov / 2.0f) / vfov);

					g.fillEllipse(
						doa_x - (size) / 2.0f,  
						doa_y - (size) / 2.0f,
						size,
						size );
					g.drawLine(doa_x + lsize*0.8f, doa_y, doa_x - lsize*0.8f, doa_y, 2.0f);
					g.drawLine(doa_x, doa_y + lsize*0.8f, doa_x, doa_y - lsize*0.8f, 2.0f);
					g.drawLine(doa_x + lsize*0.666f, doa_y + lsize*0.333f, doa_x - lsize*0.666f, doa_y - lsize*0.333f, 2.0f);
					g.drawLine(doa_x + lsize*0.333f, doa_y + lsize*0.666f, doa_x - lsize*0.333f, doa_y - lsize*0.666f, 2.0f);
					g.drawLine(doa_x + lsize*0.666f, doa_y - lsize*0.333f, doa_x - lsize*0.666f, doa_y + lsize*0.333f, 2.0f);
					g.drawLine(doa_x + lsize*0.333f, doa_y - lsize*0.666f, doa_x - lsize*0.333f, doa_y + lsize*0.666f, 2.0f);
                }
            }
		}

		/* DRAW THE GRID ON TOP */
		int numGridLinesX = hfov == 360.0f ? 8 : 4;
		int numGridLinesY = numGridLinesX / 2;
		g.setColour(Colours::white);
		g.setOpacity(0.75f);

		g.drawLine(0.0f, height / 2.0f, width, height / 2.0f, 1.0f);
		g.drawLine(width / 2.0f, 0, width / 2.0f, height, 1.0f);

		for (int i = 0; i <= numGridLinesX; i++) {
			g.setOpacity(0.1f);
			g.drawLine((float)i*width / (float)numGridLinesX, 0, (float)i*width / (float)numGridLinesX, height, 1.0f);
			g.setOpacity(0.75f);
			if (i <= numGridLinesX / 2) {
				g.drawText(String((int)(hfov / 2 - i * (int)hfov / numGridLinesX)) + "\xc2\xb0",
					(float)i*width / (float)numGridLinesX, height / 2, 40, 20, Justification::centred, true);
			}
			else {
				g.drawText(String((int)(hfov / 2 - i * (int)hfov / numGridLinesX)) + "\xc2\xb0",
					(float)i*width / (float)numGridLinesX - 40, height / 2, 40, 20, Justification::centred, true);
			}
		}

		for (int i = 0; i <= numGridLinesY; i++) {
			g.setOpacity(0.1f);
			g.drawLine(0, (float)i*height / (float)numGridLinesY, width, (float)i*height / (float)numGridLinesY, 1.0f);
			g.setOpacity(0.75f);
			if (i <= numGridLinesY / 2) {
				g.drawText(String((int)(vfov / 2 - i * (int)vfov / numGridLinesY)) + "\xc2\xb0",
					width / 2.0f, (float)i*height / (float)numGridLinesY, 40, 20, Justification::centred, true);
			}
			else {
				g.drawText(String((int)(vfov / 2 - i * (int)vfov / numGridLinesY)) + "\xc2\xb0",
					width / 2.0f, (float)i*height / (float)numGridLinesY - 20, 40, 20, Justification::centred, true);
			}
		}

		/* BEAM POS MARKERS */
		Point<int> AzElPos = convertAzElToPoint(sfcropaclib_getBeamAzi(hVst->hSfcropac) ,
			sfcropaclib_getBeamElev(hVst->hSfcropac) ,
			localBounds, hfov, vfov); 
		BeamPos.setBounds(AzElPos.getX() - 5,
			AzElPos.getY() - 5,
			10,
			10);

		Line<float> lx, lx2;
		lx.setStart(BeamPos.getTopLeft());
		lx.setEnd(BeamPos.getBottomRight());
		lx2.setStart(BeamPos.getTopRight());
		lx2.setEnd(BeamPos.getBottomLeft());

		g.setColour(Colours::black);
		g.fillRect(BeamPos);
		g.setColour(Colours::white);
		g.drawLine(lx, 2);
		g.drawLine(lx2, 2);

        hasFinishedDrawing = true;
    }
    //[/UserPaint]
}

void overlay::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void overlay::mouseDown (const MouseEvent& e)
{
    //[UserCode_mouseDown] -- Add your code here...
	Point<int> downPos = e.getMouseDownPosition(); /* can only return as int... ridiculous. */
	Point<float> fdownPos;
	fdownPos.setXY((float)downPos.getX(), (float)downPos.getY());

	float az, el, hfov, vfov, ar;
	hfov = sfcropaclib_getFOV(hVst->hSfcropac); 
	ar = sfcropaclib_getAspectRatio(hVst->hSfcropac);
	vfov = hfov / ar;

	Point<int> currentPos = e.getPosition();
	convertPointToAzEl(currentPos, localBounds, hfov, hfov / ar, &az, &el);

	sfcropaclib_setBeamAzi(hVst->hSfcropac, MIN(MAX(az, -hfov / 2.0f), hfov / 2.0f));
	sfcropaclib_setBeamElev(hVst->hSfcropac, MIN(MAX(el, -vfov / 2.0f), vfov / 2.0f));
    //[/UserCode_mouseDown]
}

void overlay::mouseDrag (const MouseEvent& e)
{
    //[UserCode_mouseDrag] -- Add your code here...
	Point<int> downPos = e.getMouseDownPosition(); /* can only return as int... ridiculous. */
	Point<float> fdownPos;
	fdownPos.setXY((float)downPos.getX(), (float)downPos.getY());

	float az, el, hfov, vfov, ar;
	hfov = sfcropaclib_getFOV(hVst->hSfcropac);
	ar = sfcropaclib_getAspectRatio(hVst->hSfcropac);
	vfov = hfov / ar;

	Point<int> currentPos = e.getPosition();
	convertPointToAzEl(currentPos, localBounds, hfov, hfov / ar, &az, &el);

	sfcropaclib_setBeamAzi(hVst->hSfcropac, MIN(MAX(az, -hfov/2.0f), hfov/2.0f));
	sfcropaclib_setBeamElev(hVst->hSfcropac, MIN(MAX(el, -vfov / 2.0f), vfov / 2.0f));
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

<JUCER_COMPONENT documentType="Component" className="overlay" componentName=""
                 parentClasses="public Component" constructorParams="PluginProcessor* ownerFilter"
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="1" initialWidth="600" initialHeight="400">
  <METHODS>
    <METHOD name="mouseDown (const MouseEvent&amp; e)"/>
    <METHOD name="mouseDrag (const MouseEvent&amp; e)"/>
  </METHODS>
  <BACKGROUND backgroundColour="ffffff"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
