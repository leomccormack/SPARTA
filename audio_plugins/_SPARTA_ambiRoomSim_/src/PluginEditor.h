#pragma once

#include "JuceHeader.h"
#include "PluginProcessor.h"
#include "pannerView.h"
#include "pathTimelineView.h"
#include "RoomSettingsView.h"
#include "PathEditView.h"
#include "../../resources/SPARTALookAndFeel.h"

typedef enum _SPARTA_WARNINGS{
    k_warning_none,
    k_warning_NinputCH,
    k_warning_NoutputCH,
    k_warning_frameSize
}SPARTA_WARNINGS;

class PluginEditor  : public AudioProcessorEditor,
                       public Timer
{
public:
    PluginEditor (PluginProcessor& p);
    ~PluginEditor() override;

    void timerCallback() override;
    void paint (juce::Graphics& g) override;
    void resized() override;

private:
    PluginProcessor& processor;
    void* hAmbi;
#ifndef PLUGIN_EDITOR_DISABLE_OPENGL
    std::unique_ptr<OpenGLGraphicsContextCustomShader> shader;
    OpenGLContext openGLContext;
#endif
    SPARTALookAndFeel LAF;

    std::unique_ptr<RoomSettingsView> roomSettingsView;
    std::unique_ptr<PathEditView> pathEditView;
    std::unique_ptr<pannerView> panWindow;
    std::unique_ptr<pathTimelineView> pathTimeline;

    SPARTA_WARNINGS currentWarning;
    SharedResourcePointer<TooltipWindow> tipWindow;
    std::unique_ptr<juce::ComboBox> pluginDescription;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};
