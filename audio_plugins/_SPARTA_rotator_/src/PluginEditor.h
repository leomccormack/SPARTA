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

#pragma once

//[Headers]     -- You can add your own extra header files here --

#include "JuceHeader.h"
#include "PluginProcessor.h"


//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class PluginEditor  : public AudioProcessorEditor,
                      public Timer,
                      private OSCReceiver,
                      private OSCReceiver::Listener<OSCReceiver::RealtimeCallback>,
                      public Slider::Listener,
                      public Button::Listener,
                      public ComboBox::Listener
{
public:
    //==============================================================================
    PluginEditor (PluginProcessor* ownerFilter);
    ~PluginEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    PluginProcessor* hVst;
    void timerCallback() override;

	void oscMessageReceived(const OSCMessage& message) override {
		if (message.size() == 3 ) {
			//message[0]

			//message.getAddressPattern == "/yaw"
			if (message[0].isFloat32()) {
                rotator_setYaw(hVst->hRot, message[0].getFloat32());
				s_yaw->setValue(jlimit(-180.0f, 180.0f, message[0].getFloat32()), dontSendNotification);
			}
			if (message[1].isFloat32()) {
                rotator_setPitch(hVst->hRot, message[1].getFloat32());
				s_pitch->setValue(jlimit(-90.0f, 90.0f, message[1].getFloat32()), dontSendNotification);
			}

			if (message[2].isFloat32()) {
                rotator_setRoll(hVst->hRot, message[2].getFloat32());
				s_roll->setValue(jlimit(-90.0f, 90.0f, message[2].getFloat32()), dontSendNotification);
			}
		}
	}


    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;
    void buttonClicked (Button* buttonThatWasClicked) override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    bool showingFrameSizeWarning;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Slider> s_yaw;
    ScopedPointer<Slider> s_pitch;
    ScopedPointer<Slider> s_roll;
    ScopedPointer<ToggleButton> t_flipYaw;
    ScopedPointer<ToggleButton> t_flipPitch;
    ScopedPointer<ToggleButton> t_flipRoll;
    ScopedPointer<TextEditor> te_oscport;
    ScopedPointer<ComboBox> CBoutputFormat;
    ScopedPointer<ComboBox> CBnorm;
    ScopedPointer<ComboBox> CBorder;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
