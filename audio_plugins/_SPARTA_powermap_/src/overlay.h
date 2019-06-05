/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.0.2

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
 
#include "PluginProcessor.h"
#include "powermap.h"
#ifndef MIN
  #define MIN(a,b) (( (a) < (b) ) ? (a) : (b))
#endif
#ifndef MAX
  #define MAX(a,b) (( (a) > (b) ) ? (a) : (b))
#endif

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class overlay  : public Component
{
public:
    //==============================================================================
    overlay (PluginProcessor* ownerFilter);
    ~overlay();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    
    void refreshPowerMap(float* _dirs_deg, float* _pmap, int _nDirs, int _pmapWidth, int _hfov, int _aspectRatio );
    bool getFinishedRefresh(){ return finishedRefresh; }
    void setEnableTransparency(bool newState){ enableTransparency = newState; }
    
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    float* dirs_deg, *pmap; 
    int nDirs, pmapWidth, hfov, aspectRatio;
    Rectangle<int> localBounds; 
    bool finishedRefresh;
    bool enableTransparency;
    //[/UserVariables]

    //==============================================================================


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (overlay)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
