#include "PathEditView.h"

PathEditView::PathEditView(PluginProcessor& p)
    : processor(p)
{
    hAmbi = processor.getFXHandle();

    /* Source selector */
    LB_source.reset(new juce::Label("lbSrc", "Source:"));
    addAndMakeVisible(LB_source.get());
    LB_source->setColour(juce::Label::textColourId, juce::Colours::white);
    LB_source->setFont(juce::FontOptions(12.0f));

    sourceSelector.reset(new juce::ComboBox("sourceSel"));
    addAndMakeVisible(sourceSelector.get());
    sourceSelector->setEditableText(false);
    sourceSelector->setJustificationType(juce::Justification::centredLeft);
    sourceSelector->addListener(this);

    /* Path selector */
    LB_path.reset(new juce::Label("lbPath", "Path:"));
    addAndMakeVisible(LB_path.get());
    LB_path->setColour(juce::Label::textColourId, juce::Colours::white);
    LB_path->setFont(juce::FontOptions(12.0f));

    pathSelector.reset(new juce::ComboBox("pathSel"));
    addAndMakeVisible(pathSelector.get());
    pathSelector->setEditableText(false);
    pathSelector->setJustificationType(juce::Justification::centredLeft);
    pathSelector->addListener(this);

    BT_addPath.reset(new juce::TextButton("+"));
    addAndMakeVisible(BT_addPath.get());
    BT_addPath->addListener(this);

    BT_removePath.reset(new juce::TextButton("-"));
    addAndMakeVisible(BT_removePath.get());
    BT_removePath->addListener(this);

    /* Path controls with labels */
    addAndMakeVisible(LB_loop.get());
    LB_loop->setColour(juce::Label::textColourId, juce::Colours::white);
    LB_loop->setFont(juce::FontOptions(12.0f));
    TB_pathLoop.reset(new juce::ToggleButton("loop"));
    addAndMakeVisible(TB_pathLoop.get());
    TB_pathLoop->setButtonText(juce::String());
    TB_pathLoop->addListener(this);

    /* Start Time */
    LB_startTime.reset(new juce::Label("stLabel", "Start:"));
    addAndMakeVisible(LB_startTime.get());
    LB_startTime->setColour(juce::Label::textColourId, juce::Colours::white);
    LB_startTime->setFont(juce::FontOptions(12.0f));

    SL_pathStartTime.reset(new juce::Slider("startTime"));
    addAndMakeVisible(SL_pathStartTime.get());
    SL_pathStartTime->setSliderStyle(juce::Slider::LinearHorizontal);
    SL_pathStartTime->setTextBoxStyle(juce::Slider::TextBoxRight, false, 50, 20);
    SL_pathStartTime->setRange(0.0, 300.0, 0.1);
    SL_pathStartTime->setValue(0.0);
    SL_pathStartTime->addListener(this);
    SL_pathStartTime->setColour(juce::Slider::textBoxTextColourId, juce::Colours::white);

    /* End Time */
    LB_endTime.reset(new juce::Label("etLabel", "End:"));
    addAndMakeVisible(LB_endTime.get());
    LB_endTime->setColour(juce::Label::textColourId, juce::Colours::white);
    LB_endTime->setFont(juce::FontOptions(12.0f));

    SL_pathEndTime.reset(new juce::Slider("endTime"));
    addAndMakeVisible(SL_pathEndTime.get());
    SL_pathEndTime->setSliderStyle(juce::Slider::LinearHorizontal);
    SL_pathEndTime->setTextBoxStyle(juce::Slider::TextBoxRight, false, 50, 20);
    SL_pathEndTime->setRange(0.1, 300.0, 0.1);
    SL_pathEndTime->setValue(10.0);
    SL_pathEndTime->addListener(this);
    SL_pathEndTime->setColour(juce::Slider::textBoxTextColourId, juce::Colours::white);

    /* Duration info */
    LB_durationVal.reset(new juce::Label("durVal", "Duration: 10.0s"));
    addAndMakeVisible(LB_durationVal.get());
    LB_durationVal->setColour(juce::Label::textColourId, juce::Colour(0xffaaaaaa));
    LB_durationVal->setFont(juce::FontOptions(11.0f));

    BT_pathClear.reset(new juce::TextButton("Clear Path"));
    addAndMakeVisible(BT_pathClear.get());
    BT_pathClear->addListener(this);

    BT_deleteNode.reset(new juce::TextButton("Delete Node"));
    addAndMakeVisible(BT_deleteNode.get());
    BT_deleteNode->addListener(this);

    /* Keyframe list header */
    LB_kfHeader.reset(new juce::Label("kfHeader", "#  Time    X      Y      Z"));
    addAndMakeVisible(LB_kfHeader.get());
    LB_kfHeader->setColour(juce::Label::textColourId, juce::Colour(0xffaaaaaa));
    LB_kfHeader->setFont(juce::FontOptions(11.0f));

    /* Keyframe list (selectable) */
    keyframeList.reset(new juce::ListBox("keyframes", this));
    addAndMakeVisible(keyframeList.get());
    keyframeList->setRowHeight(18);

    /* Tooltips */
    sourceSelector->setTooltip("Select the source or receiver whose path to edit");
    pathSelector->setTooltip("Select which path to edit for this source/receiver");
    RB_moveSR->setTooltip("Move sources/receivers in the room. Path automation is disabled.");
    RB_drawPath->setTooltip("Draw/edit the motion path for this source/receiver. Clicking in the room adds keyframes.");
    TB_pathLoop->setTooltip("When ON, this path loops back to the start time.");
    SL_pathStartTime->setTooltip("Timeline position where this path begins.");
    SL_pathEndTime->setTooltip("Timeline position where this path ends.");
}

PathEditView::~PathEditView() {}

void PathEditView::resized()
{
    auto r = getLocalBounds().reduced(6, 8);
    int y = r.getY();
    int lblW = 44, ctrlW = r.getWidth() - lblW;

    /* Source selector */
    LB_source->setBounds(r.getX(), y, lblW, 22);
    sourceSelector->setBounds(r.getX() + lblW, y, ctrlW, 22);
    y += 24;

    /* Path selector + add/remove buttons */
    LB_path->setBounds(r.getX(), y, lblW, 22);
    int btnW = 22;
    pathSelector->setBounds(r.getX() + lblW, y, ctrlW - btnW * 2 - 4, 22);
    BT_addPath->setBounds(r.getX() + lblW + ctrlW - btnW * 2 - 4, y, btnW, 22);
    BT_removePath->setBounds(r.getX() + lblW + ctrlW - btnW, y, btnW, 22);
    y += 26;

    /* Interaction mode frame: title + two stacked radio buttons */
    int frameH = 56;
    RB_moveSR->setBounds(r.getX() + 12, y + 20, ctrlW - 12, 18);
    RB_drawPath->setBounds(r.getX() + 12, y + 38, ctrlW - 12, 18);
    y += frameH + 2;

    /* Loop */
    LB_loop->setBounds(r.getX(), y, lblW, 20);
    TB_pathLoop->setBounds(r.getX() + lblW, y, ctrlW, 20);
    y += 24;

    /* Start time */
    LB_startTime->setBounds(r.getX(), y, lblW, 22);
    SL_pathStartTime->setBounds(r.getX() + lblW, y, ctrlW, 22);
    y += 26;

    /* End time */
    LB_endTime->setBounds(r.getX(), y, lblW, 22);
    SL_pathEndTime->setBounds(r.getX() + lblW, y, ctrlW, 22);
    y += 22;

    /* Duration info */
    LB_durationVal->setBounds(r.getX() + lblW, y, ctrlW, 18);
    y += 22;

    /* Button row: Clear + Delete side by side */
    float btnW2 = r.getWidth() * 0.5f - 2;
    BT_pathClear->setBounds(r.getX(), y, (int)btnW2, 24);
    BT_deleteNode->setBounds(r.getX() + (int)(btnW2 + 4), y, (int)btnW2, 24);
    y += 30;

    /* Keyframe list */
    LB_kfHeader->setBounds(r.getX(), y, r.getWidth(), 16);
    y += 18;
    keyframeList->setBounds(r.getX(), y, r.getWidth(), r.getHeight() - (y - r.getY()));
}

static PathData& currentPath(PluginProcessor& proc, bool isReceiver, int srcIdx, int pathIdx)
{
    PathBank& pb = proc.getPathBank();
    if (isReceiver)
        return pb.getReceiverPath(srcIdx, pathIdx);
    return pb.getSourcePath(srcIdx, pathIdx);
}

void PathEditView::refresh()
{
    PathBank& pb = processor.getPathBank();
    int nSrc = ambi_roomsim_getNumSources(hAmbi);
    int nRec = ambi_roomsim_getNumReceivers(hAmbi);

    /* Populate source selector */
    sourceSelector->clear(juce::dontSendNotification);
    for (int i = 0; i < nSrc; ++i)
        sourceSelector->addItem("S" + juce::String(i + 1), i + 1);
    for (int i = 0; i < nRec; ++i)
        sourceSelector->addItem("R" + juce::String(i + 1), nSrc + i + 1);
    int selId = selectedIsReceiver ? nSrc + selectedSourceIndex + 1 : selectedSourceIndex + 1;
    if (selId >= 1 && selId <= nSrc + nRec)
        sourceSelector->setSelectedId(selId, juce::dontSendNotification);

    /* Populate path selector */
    int nPaths = selectedIsReceiver ? pb.getNumReceiverPaths(selectedSourceIndex)
                                    : pb.getNumSourcePaths(selectedSourceIndex);
    pathSelector->clear(juce::dontSendNotification);
    for (int p = 0; p < nPaths; ++p) {
        auto& path = selectedIsReceiver ? pb.getReceiverPath(selectedSourceIndex, p)
                                        : pb.getSourcePath(selectedSourceIndex, p);
        juce::String name = path.name.empty() ? ("Path " + juce::String(p + 1))
                                               : juce::String(path.name);
        pathSelector->addItem(name, p + 1);
    }
    if (selectedPathIndex >= 0 && selectedPathIndex < nPaths)
        pathSelector->setSelectedId(selectedPathIndex + 1, juce::dontSendNotification);

    /* Sync sliders and toggles from the current path data */
    if (nPaths > 0) {
        auto& path = currentPath(processor, selectedIsReceiver, selectedSourceIndex, selectedPathIndex);
        SL_pathStartTime->setValue(path.startTime, juce::dontSendNotification);
        SL_pathEndTime->setValue(path.endTime, juce::dontSendNotification);
        TB_pathLoop->setToggleState(path.loop, juce::dontSendNotification);
        RB_drawPath->setToggleState(path.enabled, juce::dontSendNotification);
        RB_moveSR->setToggleState(!path.enabled, juce::dontSendNotification);
    }

    updateKeyframeTable();
}

void PathEditView::comboBoxChanged(juce::ComboBox* combo)
{
    if (combo == sourceSelector.get()) {
        int id = sourceSelector->getSelectedId();
        int nSrc = ambi_roomsim_getNumSources(hAmbi);
        if (id >= 1 && id <= nSrc) {
            selectedSourceIndex = id - 1;
            selectedIsReceiver = false;
        } else if (id > nSrc) {
            selectedSourceIndex = id - nSrc - 1;
            selectedIsReceiver = true;
        }
        selectedPathIndex = 0;
    } else if (combo == pathSelector.get()) {
        selectedPathIndex = pathSelector->getSelectedId() - 1;
        if (selectedPathIndex < 0) selectedPathIndex = 0;
    }
    updateKeyframeTable();
}

void PathEditView::resyncTimeFromSliders()
{
    double start = SL_pathStartTime->getValue();
    double end = SL_pathEndTime->getValue();
    if (end <= start) {
        end = start + 0.1;
        SL_pathEndTime->setValue(end, juce::dontSendNotification);
    }
    PathBank& pb = processor.getPathBank();
    int nPaths = selectedIsReceiver ? pb.getNumReceiverPaths(selectedSourceIndex)
                                    : pb.getNumSourcePaths(selectedSourceIndex);
    if (selectedPathIndex >= nPaths) selectedPathIndex = nPaths - 1;
    if (selectedPathIndex >= 0) {
        PathData& path = currentPath(processor, selectedIsReceiver, selectedSourceIndex, selectedPathIndex);
        path.startTime = start;
        path.endTime = end;
        if (path.keyframes.size() >= 2) {
            double dur = end - start;
            PathData::redistributeTimes(path, dur);
        }
        LB_durationVal->setText("Duration: " + juce::String(end - start, 1) + "s",
                                 juce::dontSendNotification);
        processor.markPathDirty();
    }
    updateKeyframeTable();
}

void PathEditView::buttonClicked(juce::Button* button)
{
    PathBank& pb = processor.getPathBank();

    if (button == BT_addPath.get()) {
        int newIdx = selectedIsReceiver ? pb.addReceiverPath(selectedSourceIndex)
                                        : pb.addSourcePath(selectedSourceIndex);
        selectedPathIndex = newIdx;
        processor.markPathDirty();
        refresh();
        return;
    }

    if (button == BT_removePath.get()) {
        int nPaths = selectedIsReceiver ? pb.getNumReceiverPaths(selectedSourceIndex)
                                        : pb.getNumSourcePaths(selectedSourceIndex);
        if (nPaths <= 1) return;
        if (selectedIsReceiver)
            pb.removeReceiverPath(selectedSourceIndex, selectedPathIndex);
        else
            pb.removeSourcePath(selectedSourceIndex, selectedPathIndex);
        selectedPathIndex = juce::jmax(0, selectedPathIndex - 1);
        processor.markPathDirty();
        refresh();
        return;
    }

    if (button == BT_pathClear.get()) {
        PathData& path = currentPath(processor, selectedIsReceiver, selectedSourceIndex, selectedPathIndex);
        path.keyframes.clear();
        path.enabled = false;
        processor.markPathDirty();
        updateKeyframeTable();
        return;
    }

    if (button == RB_drawPath.get() || button == RB_moveSR.get()) {
        PathData& path = currentPath(processor, selectedIsReceiver, selectedSourceIndex, selectedPathIndex);
        path.enabled = RB_drawPath->getToggleState();
        processor.markPathDirty();
        return;
    }

    if (button == TB_pathLoop.get()) {
        PathData& path = currentPath(processor, selectedIsReceiver, selectedSourceIndex, selectedPathIndex);
        path.loop = TB_pathLoop->getToggleState();
        processor.markPathDirty();
        return;
    }

    if (button == BT_deleteNode.get()) {
        int sel = keyframeList->getSelectedRow();
        if (sel < 0) return;
        PathData& path = currentPath(processor, selectedIsReceiver, selectedSourceIndex, selectedPathIndex);
        if ((size_t)sel >= path.keyframes.size()) return;
        path.keyframes.erase(path.keyframes.begin() + sel);
        if (path.keyframes.size() >= 2) {
            double dur = path.endTime - path.startTime;
            PathData::redistributeTimes(path, dur);
        } else if (path.keyframes.empty()) {
            path.enabled = false;
        }
        processor.markPathDirty();
        updateKeyframeTable();
        return;
    }
}

void PathEditView::sliderValueChanged(juce::Slider* slider)
{
    if (slider == SL_pathStartTime.get() || slider == SL_pathEndTime.get())
        resyncTimeFromSliders();
}

int PathEditView::getNumRows()
{
    PathData& path = currentPath(processor, selectedIsReceiver, selectedSourceIndex, selectedPathIndex);
    return (int)path.keyframes.size();
}

void PathEditView::paintListBoxItem(int rowNumber, juce::Graphics& g,
                                     int width, int height, bool rowIsSelected)
{
    PathData& path = currentPath(processor, selectedIsReceiver, selectedSourceIndex, selectedPathIndex);
    if (rowIsSelected)
        g.fillAll(juce::Colour(0xff3a5a8c));
    else if (rowNumber % 2 == 0)
        g.fillAll(juce::Colour(0xff1e1e1e));
    else
        g.fillAll(juce::Colour(0xff252525));

    if ((size_t)rowNumber < path.keyframes.size()) {
        auto& kf = path.keyframes[rowNumber];
        juce::String text = juce::String(rowNumber + 1).paddedRight(' ', 2)
                + juce::String(kf.timeSeconds, 1).paddedRight(' ', 6)
                + juce::String(kf.x, 1).paddedRight(' ', 6)
                + juce::String(kf.y, 1).paddedRight(' ', 6)
                + juce::String(kf.z, 1).paddedRight(' ', 6);
        g.setColour(juce::Colours::white);
        g.setFont(juce::FontOptions(11.0f));
        g.drawText(text, 4, 0, width - 4, height, juce::Justification::centredLeft, true);
    }
}

void PathEditView::updateKeyframeTable()
{
    PathData& path = currentPath(processor, selectedIsReceiver, selectedSourceIndex, selectedPathIndex);
    LB_durationVal->setText("Duration: " + juce::String(path.endTime - path.startTime, 1) + "s",
                             juce::dontSendNotification);

    keyframeList->updateContent();
    keyframeList->repaint();
}

void PathEditView::paint(juce::Graphics& g)
{
    using namespace ColoursUI;

    /* Frame around the interaction-mode radio buttons (placed below the
       source/path selector rows, matching the layout in resized()). */
    auto r = getLocalBounds().reduced(6, 8);
    int frameY = r.getY() + 50;
    drawPanel(g, {(float)r.getX(), (float)frameY, (float)r.getWidth(), 56.0f},
              panelFill, panelStroke);
    drawLabel(g, {r.getX() + 8, frameY - 2, 150, 20}, "Interaction mode:", 12.f);
}
