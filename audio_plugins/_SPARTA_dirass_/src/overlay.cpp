/*
 ==============================================================================
 
 This file is part of SPARTA; a suite of spatial audio plug-ins.
 Copyright (c) 2019 - Leo McCormack.
 
 SPARTA is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 SPARTA is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with SPARTA.  If not, see <http://www.gnu.org/licenses/>.
 
 ==============================================================================
*/

#include "overlay.h"

/* look-up colour table for powermap */
const int mapColourTable_N = 114;
const Colour mapColourTable[114] = {
    /* RGB colour gradient from 3D00D1->0DD9CC */
    Colour::fromRGB(61, 0, 209), Colour::fromRGB(59, 7, 208), Colour::fromRGB(56, 22, 208), Colour::fromRGB(54, 29, 208),
    Colour::fromRGB(51, 44, 207), Colour::fromRGB(47, 58, 207), Colour::fromRGB(44, 73, 207), Colour::fromRGB(44, 75, 207),
    Colour::fromRGB(43, 80, 207), Colour::fromRGB(43, 82, 207), Colour::fromRGB(41, 88, 206), Colour::fromRGB(41, 90, 206),
    Colour::fromRGB(40, 91, 206), Colour::fromRGB(39, 95, 206), Colour::fromRGB(39, 97, 206), Colour::fromRGB(39, 99, 206),
    Colour::fromRGB(38, 102, 206), Colour::fromRGB(38, 104, 206), Colour::fromRGB(37, 106, 206), Colour::fromRGB(36, 110, 206),
    Colour::fromRGB(36, 112, 206), Colour::fromRGB(35, 114, 206), Colour::fromRGB(34, 117, 206), Colour::fromRGB(34, 119, 206),
    Colour::fromRGB(34, 121, 206), Colour::fromRGB(33, 125, 206), Colour::fromRGB(33, 127, 206), Colour::fromRGB(32, 127, 206),
    Colour::fromRGB(32, 128, 206), Colour::fromRGB(31, 132, 205), Colour::fromRGB(31, 134, 205), Colour::fromRGB(31, 135, 205),
    Colour::fromRGB(30, 136, 205), Colour::fromRGB(30, 138, 205), Colour::fromRGB(30, 139, 205), Colour::fromRGB(30, 141, 205),
    Colour::fromRGB(29, 143, 205), Colour::fromRGB(29, 145, 205), Colour::fromRGB(28, 147, 205), Colour::fromRGB(27, 150, 205),
    Colour::fromRGB(26, 154, 205), Colour::fromRGB(26, 156, 205), Colour::fromRGB(26, 158, 205), Colour::fromRGB(25, 161, 205),
    Colour::fromRGB(24, 165, 205), Colour::fromRGB(24, 167, 205), Colour::fromRGB(23, 169, 205), Colour::fromRGB(22, 172, 205),
    Colour::fromRGB(21, 176, 204), Colour::fromRGB(21, 180, 204), Colour::fromRGB(20, 183, 204), Colour::fromRGB(19, 187, 204),
    Colour::fromRGB(18, 191, 204), Colour::fromRGB(17, 194, 204), Colour::fromRGB(17, 198, 204), Colour::fromRGB(16, 202, 213),
    Colour::fromRGB(15, 205, 204), Colour::fromRGB(14, 209, 204), Colour::fromRGB(13, 213, 204), Colour::fromRGB(13, 217, 204),

    /* Inverse-HSV colour gradient from 0DD9CC->93E151 (skipping first) */
    Colour::fromRGB(16, 217, 189), Colour::fromRGB(19, 217, 176), Colour::fromRGB(23, 218, 162), Colour::fromRGB(26, 218, 150),
    Colour::fromRGB(30, 218, 137), Colour::fromRGB(33, 219, 125), Colour::fromRGB(37, 219, 114), Colour::fromRGB(41, 220, 103),
    Colour::fromRGB(44, 220, 93), Colour::fromRGB(48, 221, 83), Colour::fromRGB(51, 221, 73), Colour::fromRGB(55, 222, 64),
    Colour::fromRGB(61, 222, 59), Colour::fromRGB(77, 222, 62), Colour::fromRGB(106, 223, 69), Colour::fromRGB(120, 224, 73),
    Colour::fromRGB(133, 224, 77), Colour::fromRGB(147, 225, 81),

    /* RGB colour gradient from 93E151->FEB506 (skipping first)  */
    Colour::fromRGB(152, 222, 77), Colour::fromRGB(158, 220, 73), Colour::fromRGB(163, 218, 69), Colour::fromRGB(175, 213, 65),
    Colour::fromRGB(180, 211, 57), Colour::fromRGB(186, 208, 53), Colour::fromRGB(192, 206, 49), Colour::fromRGB(197, 204, 45),
    Colour::fromRGB(203, 201, 41), Colour::fromRGB(208, 199, 37), Colour::fromRGB(214, 197, 33), Colour::fromRGB(220, 194, 29),
    Colour::fromRGB(225, 192, 25), Colour::fromRGB(231, 190, 21), Colour::fromRGB(237, 187, 17), Colour::fromRGB(242, 185, 13),
    Colour::fromRGB(248, 183, 9), Colour::fromRGB(254, 181, 6),

    /* HSV colour gradient from FEB506->FEFF05 (skipping first)  */
    Colour::fromRGB(254, 184, 5), Colour::fromRGB(254, 188, 5), Colour::fromRGB(254, 192, 5), Colour::fromRGB(254, 196, 5),
    Colour::fromRGB(254, 200, 5), Colour::fromRGB(254, 204, 5), Colour::fromRGB(254, 208, 5), Colour::fromRGB(254, 212, 5),
    Colour::fromRGB(254, 216, 5), Colour::fromRGB(254, 220, 5), Colour::fromRGB(254, 224, 5), Colour::fromRGB(254, 228, 5),
    Colour::fromRGB(254, 236, 5), Colour::fromRGB(254, 240, 5), Colour::fromRGB(254, 244, 5), Colour::fromRGB(254, 248, 5),
    Colour::fromRGB(254, 252, 5), Colour::fromRGB(253, 255, 5)
};

overlay::overlay (PluginProcessor& /*p*/)
{
    setSize (600, 400);

    dirs_deg = NULL;
    pmap = NULL;
    finishedRefresh = true;
    enableTransparency = false;
}

overlay::~overlay()
{
}

void overlay::paint (Graphics& g)
{
    if ( (dirs_deg!=NULL) && (pmap!=NULL) && (finishedRefresh) ){ /* in order to stop it from tripping over itself */
        finishedRefresh = false;

        Rectangle<int> r(getLocalBounds());
        localBounds = r;

        /* Draw Powermap */
        int pmapHeight = (int)((float)pmapWidth/(float)aspectRatio +0.5f);
        float windowWidth = (float)localBounds.getWidth();
        float windowHeight = (float)localBounds.getHeight();
        float vfov = (float)hfov/aspectRatio;
        if(pmapHeight<1.0f || pmapWidth < 1.0f || pmapHeight > windowHeight || pmapWidth > windowWidth){
            finishedRefresh = true;
            return;
        }

        Colour col;
        Image myImage (Image::PixelFormat::ARGB, pmapWidth, pmapHeight, false);
        Image myImageScaled;
        for(int i=0; i<pmapWidth; i++){
            for(int j=0; j<pmapHeight; j++){
                float alpha = pmap[(pmapHeight-j-1)*pmapWidth+(pmapWidth-i-1)]; /* between 0..1 */
                alpha = log(alpha+1.0f)/log(2.0f);
                int colIdx = MAX(MIN(alpha*(float)mapColourTable_N, mapColourTable_N-1),0);
                if(enableTransparency){
                    col = Colour::fromRGBA(mapColourTable[colIdx].getRed(), mapColourTable[colIdx].getGreen(),
                                           mapColourTable[colIdx].getBlue(),(uint8)(255.0f*alpha));
                    myImage.setPixelAt(i, j, col);
                }
                else
                    myImage.setPixelAt(i, j, mapColourTable[colIdx]); //pmap[i*50+j]
            }
        }
        myImageScaled = myImage.rescaled(windowWidth, windowHeight, Graphics::ResamplingQuality::lowResamplingQuality);
        g.drawImageAt(myImageScaled, 0, 0);

        /* Draw grid */
        int numGridLinesX = hfov == 360.0f ? 8 : 4;
        int numGridLinesY = numGridLinesX / 2;
        g.setColour(Colours::white);
        g.setOpacity(0.75f);
        g.drawLine(0.0f, windowHeight / 2.0f, windowWidth, windowHeight / 2.0f, 1.0f);
        g.drawLine(windowWidth / 2.0f, 0, windowWidth / 2.0f, windowHeight, 1.0f);

        for (int i = 0; i <= numGridLinesX; i++) {
            g.setOpacity(0.1f);
            g.drawLine((float)i*windowWidth / (float)numGridLinesX, 0, (float)i*windowWidth / (float)numGridLinesX, windowHeight, 1.0f);
            g.setOpacity(0.75f);
            if (i <= numGridLinesX / 2)
                g.drawText(String((int)(hfov / 2 - i * (int)hfov / numGridLinesX)) + "\xc2\xb0",
                    (float)i*windowWidth / (float)numGridLinesX, windowHeight / 2, 40, 20, Justification::centred, true);
            else
                g.drawText(String((int)(hfov / 2 - i * (int)hfov / numGridLinesX)) + "\xc2\xb0",
                    (float)i*windowWidth / (float)numGridLinesX - 40, windowHeight / 2, 40, 20, Justification::centred, true);
        }

        for (int i = 0; i <= numGridLinesY; i++) {
            g.setOpacity(0.1f);
            g.drawLine(0, (float)i*windowHeight / (float)numGridLinesY, windowWidth, (float)i*windowHeight / (float)numGridLinesY, 1.0f);
            g.setOpacity(0.75f);
            if (i <= numGridLinesY / 2)
                g.drawText(String((int)(vfov / 2 - i * (int)vfov / numGridLinesY)) + "\xc2\xb0",
                    windowWidth / 2.0f, (float)i*windowHeight / (float)numGridLinesY, 40, 20, Justification::centred, true);
            else
                g.drawText(String((int)(vfov / 2 - i * (int)vfov / numGridLinesY)) + "\xc2\xb0",
                    windowWidth / 2.0f, (float)i*windowHeight / (float)numGridLinesY - 20, 40, 20, Justification::centred, true);
        }

        finishedRefresh = true;
    }
}

void overlay::resized()
{
}

void overlay::refreshPowerMap(float* _dirs_deg, float* _pmap, int _nDirs, int _pmapWidth, int _hfov, float _aspectRatio )
{
    if(finishedRefresh){
        dirs_deg = _dirs_deg;
        pmap = _pmap;
        nDirs = _nDirs;
        pmapWidth = _pmapWidth;
        hfov = _hfov;
        aspectRatio = _aspectRatio;
        repaint();
    }
}
