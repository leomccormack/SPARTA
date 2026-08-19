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
    /* Start in Move mode: matches the "Move S/R" radio checked below. */
    panWindow->setInteractionMode(InteractionMode::Move);

    pathTimeline.reset (new pathTimelineView(p));
    addAndMakeVisible (pathTimeline.get());

    /* Loaded reference track: shows the full-track waveform in the timeline
       strip, auto-restored from plugin state on initialization. */
    trackChooser.addListener(this);
    trackChooser.setTooltip("Load an audio file to display its full waveform in the timeline strip.");
    addAndMakeVisible(trackChooser);
    TrackWaveform savedTrack = processor.getTrackWaveformSnapshot();
    if (savedTrack.filePath.isNotEmpty())
        trackChooser.setCurrentFile(savedTrack.filePath, false);

    pathEditView = std::make_unique<PathEditView>(p);
    addAndMakeVisible (pathEditView.get());

    /* Interaction mode: Move S/R (path disabled) or Draw Path (enabled) */
    RB_moveSR.reset (new juce::ToggleButton ("Move S/R"));
    addAndMakeVisible (RB_moveSR.get());
    RB_moveSR->setRadioGroupId (1001);
    RB_moveSR->setToggleState (true, juce::dontSendNotification);
    RB_moveSR->setTooltip ("Move sources/receivers in the room. Path automation is disabled.");
    RB_moveSR->addListener (this);

    RB_drawPath.reset (new juce::ToggleButton ("Draw Path"));
    addAndMakeVisible (RB_drawPath.get());
    RB_drawPath->setRadioGroupId (1001);
    RB_drawPath->setTooltip ("Draw/edit the motion path for the selected source/receiver. Clicking in the room adds keyframes.");
    RB_drawPath->addListener (this);

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
    int timelineH = 120;
    int mainH = h - timelineH;

    const int roomX = 488, roomY = 52, roomW = 280;
    const int frameH = 56, framePad = 8;

    /* Room settings: left column */
    if (roomSettingsView)
        roomSettingsView->setBounds(0, 0, 480, mainH);

    /* Room view: center, with room below it for the interaction mode */
    int panH = mainH - roomY - frameH - framePad;
    if (panWindow)
        panWindow->setBounds(roomX, roomY, roomW, panH);
    int frameY = roomY + panH + framePad;
    if (RB_moveSR)
        RB_moveSR->setBounds(roomX + 14, frameY + 20, roomW - 20, 18);
    if (RB_drawPath)
        RB_drawPath->setBounds(roomX + 14, frameY + 38, roomW - 20, 18);

    /* Path controls: right column */
    if (pathEditView)
        pathEditView->setBounds(780, 52, 260, mainH - 52);

    /* Timeline strip: full width at bottom */
    if (pathTimeline)
        pathTimeline->setBounds(0, mainH, w, timelineH);

    /* Reference-track chooser in the top-right of the timeline panel. */
    trackChooser.setBounds(w - 400, mainH + 3, 390, 20);
}

void PluginEditor::paint (juce::Graphics& g)
{
    using namespace ColoursUI;

    g.fillAll(bgDark1);

    int h = getHeight();
    int timelineY = h - 120;
    int mainH = timelineY;

    const int roomX = 488, roomY = 52, roomW = 280;
    const int frameH = 56, framePad = 8;

    /* Draw the "Room View" label and panel */
    drawPanel(g, {488, 52, 280, (float)(timelineY - 52)}, panelFill, panelStroke);
    drawLabel(g, {580, 28, 163, 30}, "Room View", 15.f);

    /* Interaction mode frame below the room */
    int panH = mainH - roomY - frameH - framePad;
    int frameY = roomY + panH + framePad;
    drawPanel(g, {roomX, (float)frameY, (float)roomW, (float)frameH}, panelFillLight, panelStrokeLight);
    drawLabel(g, {roomX + 8, frameY - 2, 180, 20}, "Interaction mode:", 12.f);

    /* Draw the "Path Controls" label and panel */
    drawPanel(g, {780, 52, 260, (float)(timelineY - 52)}, panelFill, panelStroke);
    drawLabel(g, {870, 28, 163, 30}, "Path Controls", 15.f);

    /* Draw the Timeline panel across the full bottom */
    drawPanel(g, {0, (float)timelineY, (float)getWidth(), 120}, panelFill, panelStroke);
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
            pathEditView->getSelectedIsReceiver());
        double t = processor.getCurrentHostTime();
        panWindow->setScrubTime(t);
        pathTimeline->setScrubTime(t);
        pathEditView->refresh();
    }

    /* Sync the interaction-mode radios from the selected path's state */
    if (RB_moveSR && RB_drawPath && pathEditView) {
        PathBank& pb = processor.getPathBank();
        int obj = pathEditView->getSelectedSourceIndex();
        bool isRec = pathEditView->getSelectedIsReceiver();
        bool enabled = false;
        if (obj >= 0)
            enabled = isRec ? pb.getReceiverPath(obj).enabled
                            : pb.getSourcePath(obj).enabled;
        RB_drawPath->setToggleState(enabled, juce::dontSendNotification);
        RB_moveSR->setToggleState(!enabled, juce::dontSendNotification);
        /* Keep the room view's interaction mode in lockstep with the radios
           (selection changes can enable/disable a path without a click). */
        if (panWindow)
            panWindow->setInteractionMode(enabled ? InteractionMode::AddKeyframe
                                                  : InteractionMode::Move);
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

void PluginEditor::buttonClicked (juce::Button* buttonThatWasClicked)
{
    /* Interaction mode: "Draw Path" enables the selected path and switches
       the room view to path editing; "Move S/R" disables it and returns to
       icon dragging. */
    if (buttonThatWasClicked == RB_drawPath.get()
        || buttonThatWasClicked == RB_moveSR.get()) {
        bool drawPath = RB_drawPath->getToggleState();
        panWindow->setInteractionMode(drawPath ? InteractionMode::AddKeyframe
                                               : InteractionMode::Move);
        PathBank& pb = processor.getPathBank();
        int obj = pathEditView->getSelectedSourceIndex();
        bool isRec = pathEditView->getSelectedIsReceiver();
        juce::SpinLock::ScopedLockType sl(processor.getPathLock());
        if (obj >= 0) {
            PathData& path = isRec ? pb.getReceiverPath(obj) : pb.getSourcePath(obj);
            path.enabled = drawPath;
            processor.markPathDirty();
        }
    }
}

void PluginEditor::filenameComponentChanged (juce::FilenameComponent* /*fc*/)
{
    juce::File file = trackChooser.getCurrentFile();
    if (file.getFullPathName().isEmpty())
        processor.clearTrackFile();
    else
        processor.loadTrackFile(file);
}
