
#pragma once

#include "JuceHeader.h"
#include "PluginProcessor.h"
#include "../../resources/SPARTALookAndFeel.h"
#include "sceneView.h"

typedef enum _SPARTA_WARNINGS{
    k_warning_none,
    k_warning_sampleRate_missmatch,
    k_warning_nInputs_more_than_64,
    k_warning_nOutputs_more_than_64

}SPARTA_WARNINGS;

class PluginEditor  : public AudioProcessorEditor,
                      public Timer,
                      private FilenameComponentListener,
                      public juce::Slider::Listener,
                      public juce::ComboBox::Listener,
                      public juce::Button::Listener
{
public:
    //==============================================================================
    PluginEditor (PluginProcessor* ownerFilter);
    ~PluginEditor() override;

    //==============================================================================
    /* Refresh coordinate limits based on loaded sofa files*/
    void refreshCoords();

    bool getRefreshSceneViewWindow();

    void setRefreshSceneViewWindow(bool val);

    void paint (juce::Graphics& g) override;
    void resized() override;
    void sliderValueChanged (juce::Slider* sliderThatWasMoved) override;
    void comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged) override;
    void buttonClicked (juce::Button* buttonThatWasClicked) override;

private:
    PluginProcessor* hVst;
    void* hTVC;
    void* hRot;
    void timerCallback() override;
    String originalConnectButtonText;

    /* Look and Feel */
    SPARTALookAndFeel LAF;

    /* sofa loading */
    std::unique_ptr<juce::FilenameComponent> fileComp;
    SAF_TVCONV_ERROR_CODES tvConvError;

    /* sofa file loading */
     void filenameComponentChanged (FilenameComponent*) override  {
         String directory = fileComp->getCurrentFile().getFullPathName();
         const char* new_cstring = (const char*)directory.toUTF8();
         tvconv_setSofaFilePath(hTVC, new_cstring);
         refreshCoords();

     }

    /* scene view window */
    std::unique_ptr<sceneView> sceneWindow;
    int refreshInterval             = 40; /*ms (40ms = 25 frames per second) if refreshDecimationFactor = 1 */
    bool refreshSceneViewWindow;
    int refreshDecimationCounter    = 1;
    int targetDecimatedRefreshRate  = 1;

    /* warnings */
    SPARTA_WARNINGS currentWarning;
    SharedResourcePointer<TooltipWindow> tipWindow;
    std::unique_ptr<juce::ComboBox> pluginDescription; /* Dummy combo box to provide plugin description tooltip */


    //==============================================================================
    std::unique_ptr<juce::Label> label_hostBlockSize;
    std::unique_ptr<juce::Label> label_filterLength;
    std::unique_ptr<juce::Label> label_hostfs;
    std::unique_ptr<juce::Label> label_filterfs;
    std::unique_ptr<juce::Label> label_NOutputs;
    std::unique_ptr<juce::Label> label_nIRpositions;
    std::unique_ptr<juce::Slider> SL_source_y;
    std::unique_ptr<juce::Slider> SL_source_z;
    std::unique_ptr<juce::Slider> SL_source_x;
    std::unique_ptr<juce::Slider> SL_receiver_x;
    std::unique_ptr<juce::Slider> SL_receiver_y;
    std::unique_ptr<juce::Slider> SL_receiver_z;
    std::unique_ptr<juce::Label> label_receiverIdx;
    std::unique_ptr<juce::TextEditor> te_oscport;
    std::unique_ptr<juce::ComboBox> CBviewMode;
    std::unique_ptr<juce::Slider> s_yaw;
    std::unique_ptr<juce::Slider> s_pitch;
    std::unique_ptr<juce::Slider> s_roll;
    std::unique_ptr<juce::ToggleButton> t_flipYaw;
    std::unique_ptr<juce::ToggleButton> t_flipPitch;
    std::unique_ptr<juce::ToggleButton> t_flipRoll;
    std::unique_ptr<juce::ToggleButton> TBenableRotation;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};

