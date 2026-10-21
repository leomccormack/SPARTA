#include "PluginEditor.h"

/* Layout constants of the editor (see resized() and paint()). */
static constexpr int editorWidth  = 1050;
/* The height is dictated by the room settings panel on the left, which
   needs ~490 pixels, plus the timeline panel at the bottom. */
static constexpr int editorHeight = 640;
static constexpr int timelineHeight = 140;   /* bottom panel */
static constexpr int timelineHeaderHeight = 24;
static constexpr int roomX = 488, roomY = 52, roomW = 280;
static constexpr int frameH = 56, framePad = 8;
static constexpr int controlsX = 780, controlsW = 260;

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
    /* Clicking the timeline previews the path at that position. */
    pathTimeline->onPreviewRequested = [this] (double t) { setPreview(t, true); };

    /* Loaded reference track: shows the full-track waveform in the timeline
       strip, auto-restored from plugin state on initialization. */
    trackChooser.addListener(this);
    trackChooser.setTooltip("Load an audio file to display its full waveform in the timeline strip.");
    addAndMakeVisible(trackChooser);
    TrackWaveform savedTrack = processor.getTrackWaveformSnapshot();
    if (savedTrack.filePath.isNotEmpty())
        trackChooser.setCurrentFile(savedTrack.filePath, false);

    /* Preview toggle: switches the room view between the live positions and
       the position that is being previewed on the timeline. */
    TB_preview.reset (new juce::ToggleButton ("Preview"));
    addAndMakeVisible (TB_preview.get());
    TB_preview->setTooltip("Show the objects at the position they will have at the previewed time (click the timeline to preview).");
    TB_preview->addListener (this);
    TB_preview->setToggleState (false, juce::dontSendNotification);

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

    setSize (editorWidth, editorHeight);
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
    int mainH = h - timelineHeight;

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
        pathEditView->setBounds(controlsX, roomY, controlsW, mainH - roomY);

    /* Timeline panel: full width at bottom. The top strip of the panel
       holds the title, the preview switch and the reference-track chooser,
       so that none of them overlaps the time axis. */
    if (pathTimeline)
        pathTimeline->setBounds(0, mainH + timelineHeaderHeight, w, timelineHeight - timelineHeaderHeight);
    if (TB_preview)
        TB_preview->setBounds(w - 430, mainH + 3, 95, 18);
    trackChooser.setBounds(w - 325, mainH + 2, 315, 20);
}

void PluginEditor::paint (juce::Graphics& g)
{
    using namespace ColoursUI;

    g.fillAll(bgDark1);

    int h = getHeight();
    int timelineY = h - timelineHeight;
    int mainH = timelineY;

    /* Draw the "Room View" label and panel */
    drawPanel(g, {roomX, roomY, roomW, (float)(mainH - roomY)}, panelFill, panelStroke);
    drawLabel(g, {roomX + (roomW - 163) / 2, 28, 163, 30}, "Room View", 15.f);

    /* Interaction mode frame below the room */
    int panH = mainH - roomY - frameH - framePad;
    int frameY = roomY + panH + framePad;
    drawPanel(g, {roomX, (float)frameY, (float)roomW, (float)frameH}, panelFillLight, panelStrokeLight);
    drawLabel(g, {roomX + 8, frameY - 2, 180, 20}, "Interaction mode:", 12.f);

    /* Draw the "Path Controls" label and panel */
    drawPanel(g, {controlsX, roomY, controlsW, (float)(mainH - roomY)}, panelFill, panelStroke);
    drawLabel(g, {controlsX + (controlsW - 163) / 2, 28, 163, 30}, "Path Controls", 15.f);

    /* Draw the Timeline panel across the full bottom */
    drawPanel(g, {0, (float)timelineY, (float)getWidth(), timelineHeight}, panelFill, panelStroke);
    drawLabel(g, {12, timelineY + 1, 163, 24}, "Path Timeline", 15.f);

    /* Warning banner: the state is evaluated in timerCallback(). */
    if (currentWarning != k_warning_none)
    {
        juce::String msg;
        switch (currentWarning)
        {
            case k_warning_NinputCH:
                msg = "Not enough input channels for the current number of sources";
                break;
            case k_warning_NoutputCH:
                msg = "Not enough output channels for the selected Ambisonic order";
                break;
            case k_warning_frameSize:
                msg = "The host block size does not match the processing frame size";
                break;
            default: break;
        }
        g.setColour(juce::Colour(0xffffb74d));
        g.fillRoundedRectangle((float)roomX, 2.0f, (float)(getWidth() - roomX - 4), 22.0f, 4.0f);
        g.setColour(juce::Colours::black);
        g.setFont(juce::FontOptions (11.0f, Font::bold));
        g.drawText(msg, roomX + 8, 2, getWidth() - roomX - 20, 22,
                   Justification::centredLeft, true);
    }
}

void PluginEditor::setPreview (double t, bool active)
{
    previewTime = t;
    previewActive = active;
    if (panWindow)
        panWindow->setPreviewTime(previewTime, previewActive);
    if (pathTimeline)
        pathTimeline->setPreviewTime(previewTime, previewActive);
    updatePreviewButton();
}

void PluginEditor::updatePreviewButton()
{
    if (TB_preview)
        TB_preview->setToggleState(previewActive, juce::dontSendNotification);
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
        if (obj >= 0) {
            const juce::SpinLock::ScopedLockType sl(processor.getPathLock());
            enabled = isRec ? pb.getReceiverPath(obj).enabled
                             : pb.getSourcePath(obj).enabled;
        }
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
    /* Preview switch: back to the live positions. */
    if (buttonThatWasClicked == TB_preview.get()) {
        setPreview(previewTime, TB_preview->getToggleState());
        return;
    }

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
        {
            const juce::SpinLock::ScopedLockType sl(processor.getPathLock());
            if (obj >= 0) {
                PathData& path = isRec ? pb.getReceiverPath(obj) : pb.getSourcePath(obj);
                path.enabled = drawPath;
            }
        }
        processor.markPathDirty();
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
