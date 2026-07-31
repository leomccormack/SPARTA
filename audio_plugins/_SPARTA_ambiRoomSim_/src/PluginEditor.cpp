#include "PluginEditor.h"

PluginEditor::PluginEditor (PluginProcessor& p)
    : AudioProcessorEditor(p), processor(p)
{
    hAmbi = processor.getFXHandle();

#ifndef PLUGIN_EDITOR_DISABLE_OPENGL
    openGLContext.setMultisamplingEnabled(true);
    openGLContext.attachTo(*this);
#endif

    setLookAndFeel(&LAF);

    roomSettingsView = std::make_unique<RoomSettingsView>(p);
    addAndMakeVisible(roomSettingsView.get());

    panWindow.reset (new pannerView(p, 600, 600));
    addAndMakeVisible (panWindow.get());
    panWindow->setInteractionMode(InteractionMode::AddKeyframe);

    pathTimeline.reset (new pathTimelineView(p));
    addAndMakeVisible (pathTimeline.get());

    pathEditView = std::make_unique<PathEditView>(p);
    addAndMakeVisible (pathEditView.get());

    pluginDescription.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (pluginDescription.get());
    pluginDescription->setBounds (0, 0, 200, 32);
    pluginDescription->setAlpha(0.0f);
    pluginDescription->setEnabled(false);
    pluginDescription->setTooltip(TRANS("This is a shoebox room simulator based on the image source method."));

    setSize (1050, 560);
    startTimer(80);
    currentWarning = k_warning_none;
}

PluginEditor::~PluginEditor()
{
    stopTimer();
    setLookAndFeel(nullptr);
}

void PluginEditor::resized()
{
    int w = getWidth(), h = getHeight();
    int timelineH = 55;
    int mainH = h - timelineH;

    /* Room settings: left column */
    if (roomSettingsView)
        roomSettingsView->setBounds(0, 0, 480, mainH);

    /* Room view: center */
    if (panWindow)
        panWindow->setBounds(488, 52, 280, mainH - 52);

    /* Path controls: right column */
    if (pathEditView)
        pathEditView->setBounds(780, 52, 260, mainH - 52);

    /* Timeline strip: full width at bottom */
    if (pathTimeline)
        pathTimeline->setBounds(0, mainH, w, timelineH);
}

void PluginEditor::paint (juce::Graphics& g)
{
    using namespace ColoursUI;

    g.fillAll(bgDark1);

    int h = getHeight();
    int timelineY = h - 55;

    /* Draw the "Room View" label and panel */
    drawPanel(g, {488, 52, 280, (float)(timelineY - 52)}, panelFill, panelStroke);
    drawLabel(g, {580, 28, 163, 30}, "Room View", 15.f);

    /* Draw the "Path Controls" label and panel */
    drawPanel(g, {780, 52, 260, (float)(timelineY - 52)}, panelFill, panelStroke);
    drawLabel(g, {870, 28, 163, 30}, "Path Controls", 15.f);

    /* Draw the Timeline panel across the full bottom */
    drawPanel(g, {0, (float)timelineY, (float)getWidth(), 55}, panelFill, panelStroke);
    drawLabel(g, {200, timelineY + 2, 163, 30}, "Path Timeline", 15.f);

    /* Version */
    g.setColour(Colours::white);
    g.setFont(juce::FontOptions (11.00f, Font::plain));
    g.drawText(TRANS("Version ") + JucePlugin_VersionString + BUILD_VER_SUFFIX,
        16, getHeight() - 16, 200, 11,
        Justification::centredLeft, true);
}

void PluginEditor::timerCallback()
{
    if (roomSettingsView)
        roomSettingsView->refresh();

    if (pathEditView) {
        panWindow->setEditingObject(
            pathEditView->getSelectedSourceIndex(),
            pathEditView->getSelectedIsReceiver(),
            pathEditView->getSelectedPathIndex());
        double t = processor.getCurrentHostTime();
        panWindow->setScrubTime(t);
        pathTimeline->setScrubTime(t);
        pathEditView->refresh();
    }

    if (panWindow)
        panWindow->refreshPanView();

    if ((processor.getCurrentNumInputs() < ambi_roomsim_getNumSources(hAmbi))){
        currentWarning = k_warning_NinputCH;
        repaint(0,0,getWidth(),32);
    }
    else if ((processor.getCurrentNumOutputs() < ambi_roomsim_getNSHrequired(hAmbi))){
        currentWarning = k_warning_NoutputCH;
        repaint(0,0,getWidth(),32);
    }
    else if ((processor.getCurrentBlockSize() != ambi_roomsim_getFrameSize())){
        currentWarning = k_warning_frameSize;
        repaint(0,0,getWidth(),32);
    }
    else if(currentWarning){
        currentWarning = k_warning_none;
        repaint(0,0,getWidth(),32);
    }
}
