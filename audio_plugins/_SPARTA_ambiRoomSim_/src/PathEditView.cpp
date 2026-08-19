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

    /* Path controls with labels */
    LB_loop.reset(new juce::Label("lbLoop", "Loop:"));
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

    /* Keyframe table with editable Time / X / Y / Z / Stop cells. */
    keyframeList.reset(new juce::TableListBox("keyframes", this));
    addAndMakeVisible(keyframeList.get());
    keyframeList->setRowHeight(18);
    keyframeList->setHeaderHeight(16);
    keyframeList->getHeader().addColumn("#", colIndex, 28);
    keyframeList->getHeader().addColumn("Time [s]", colTime, 62);
    keyframeList->getHeader().addColumn("X", colX, 46);
    keyframeList->getHeader().addColumn("Y", colY, 46);
    keyframeList->getHeader().addColumn("Z", colZ, 46);
    keyframeList->getHeader().addColumn("Stop [s]", colStop, 50);
    keyframeList->getHeader().setStretchToFitActive(true);
    keyframeList->setClickingTogglesRowSelection(true);

    /* Tooltips */
    sourceSelector->setTooltip("Select the source or receiver whose path to edit");
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
    y += 26;

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

    /* Keyframe table (its own column header is drawn by the TableListBox) */
    keyframeList->setBounds(r.getX(), y, r.getWidth(), r.getHeight() - (y - r.getY()));
}

static PathData& currentPath(PluginProcessor& proc, bool isReceiver, int srcIdx)
{
    PathBank& pb = proc.getPathBank();
    if (isReceiver)
        return pb.getReceiverPath(srcIdx);
    return pb.getSourcePath(srcIdx);
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

    /* Sync sliders and toggles from the current path data */
    auto& path = currentPath(processor, selectedIsReceiver, selectedSourceIndex);

    /* Keep both sliders able to reach the track end (the ranges grow with
       the track length instead of being capped at the initial 300 s). */
    double trackEnd = processor.getTrackEndTime();
    double endMax = juce::jmax(300.0, path.endTime, trackEnd);
    if (endMax > SL_pathEndTime->getMaximum())
        SL_pathEndTime->setRange(0.1, endMax, 0.1);
    double startMax = juce::jmax(300.0, path.startTime, trackEnd);
    if (startMax > SL_pathStartTime->getMaximum())
        SL_pathStartTime->setRange(0.0, startMax, 0.1);

    SL_pathStartTime->setValue(path.startTime, juce::dontSendNotification);
    SL_pathEndTime->setValue(path.endTime, juce::dontSendNotification);
    TB_pathLoop->setToggleState(path.loop, juce::dontSendNotification);

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
    }
    updateKeyframeTable();
}

void PathEditView::resyncTimeFromSliders()
{
    double start = SL_pathStartTime->getValue();
    double end = SL_pathEndTime->getValue();
    if (end <= start) {
        /* Keep end strictly above start. Grow the End slider range first so
           the stored value matches the thumb (otherwise setValue clamps the
           thumb to the old max while path.endTime keeps the larger value,
           and the two disagree for the rest of the session). */
        end = start + 0.1;
        if (end > SL_pathEndTime->getMaximum())
            SL_pathEndTime->setRange(0.1, end, 0.1);
        SL_pathEndTime->setValue(end, juce::dontSendNotification);
    }
    {
        const juce::SpinLock::ScopedLockType sl(processor.getPathLock());
        PathData& path = currentPath(processor, selectedIsReceiver, selectedSourceIndex);
        path.startTime = start;
        path.endTime = end;
        if (path.keyframes.size() >= 2) {
            double dur = end - start;
            PathData::redistributeTimes(path, dur);
        }
    }
    LB_durationVal->setText("Duration: " + juce::String(end - start, 1) + "s",
                             juce::dontSendNotification);
    processor.markPathDirty();
    updateKeyframeTable();
}

void PathEditView::buttonClicked(juce::Button* button)
{
    PathBank& pb = processor.getPathBank();

    if (button == BT_pathClear.get()) {
        {
            const juce::SpinLock::ScopedLockType sl(processor.getPathLock());
            PathData& path = currentPath(processor, selectedIsReceiver, selectedSourceIndex);
            path.keyframes.clear();
            path.enabled = false;
        }
        processor.markPathDirty();
        updateKeyframeTable();
        return;
    }

    if (button == TB_pathLoop.get()) {
        {
            const juce::SpinLock::ScopedLockType sl(processor.getPathLock());
            PathData& path = currentPath(processor, selectedIsReceiver, selectedSourceIndex);
            path.loop = TB_pathLoop->getToggleState();
        }
        processor.markPathDirty();
        return;
    }

    if (button == BT_deleteNode.get()) {
        int sel = keyframeList->getSelectedRow();
        if (sel < 0) return;
        {
            const juce::SpinLock::ScopedLockType sl(processor.getPathLock());
            PathData& path = currentPath(processor, selectedIsReceiver, selectedSourceIndex);
            if ((size_t)sel >= path.keyframes.size()) return;
            path.keyframes.erase(path.keyframes.begin() + sel);
            if (path.keyframes.size() >= 2) {
                double dur = path.endTime - path.startTime;
                PathData::redistributeTimes(path, dur);
            } else if (path.keyframes.empty()) {
                path.enabled = false;
            }
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
    PathData& path = currentPath(processor, selectedIsReceiver, selectedSourceIndex);
    return (int)path.keyframes.size();
}

void PathEditView::paintRowBackground(juce::Graphics& g, int rowNumber,
                                      int width, int height, bool rowIsSelected)
{
    if (rowIsSelected)
        g.fillAll(juce::Colour(0xff3a5a8c));
    else if (rowNumber % 2 == 0)
        g.fillAll(juce::Colour(0xff1e1e1e));
    else
        g.fillAll(juce::Colour(0xff252525));
}

void PathEditView::paintCell(juce::Graphics& g, int rowNumber, int columnId,
                             int width, int height, bool rowIsSelected)
{
    /* Only the row-number column is painted here; the value columns use
       inline editor labels created in refreshComponentForCell(). */
    if (columnId == colIndex) {
        g.setColour(juce::Colours::white);
        g.setFont(juce::FontOptions(11.0f));
        g.drawText(juce::String(rowNumber + 1), 4, 0, width - 8, height,
                   juce::Justification::centredLeft, true);
    }
}

juce::String PathEditView::getCellText(int row, int columnId) const
{
    PathData& path = currentPath(processor, selectedIsReceiver, selectedSourceIndex);
    if ((size_t)row >= path.keyframes.size()) return "";
    const auto& kf = path.keyframes[row];
    switch (columnId) {
        case colTime: return juce::String(kf.timeSeconds, 2);
        case colX:    return juce::String(kf.x, 2);
        case colY:    return juce::String(kf.y, 2);
        case colZ:    return juce::String(kf.z, 2);
        case colStop: return juce::String(kf.stopTime, 2);
        default:      return "";
    }
}

namespace
{
/* Inline editable cell: a Label that commits its text back to the table. */
class KeyframeCellEditor  : public juce::Label
{
public:
    KeyframeCellEditor(PathEditView& owner, int columnId)
        : owner(owner), columnId(columnId)
    {
        setEditable(true, false, false);
        setJustificationType(juce::Justification::centredLeft);
        setFont(juce::FontOptions(11.0f));
        setBorderSize(juce::BorderSize<int>(0));
        setColour(juce::Label::textColourId, juce::Colours::white);
    }

    void setRow(int row) { currentRow = row; }

    void editorShown(juce::TextEditor*) override
    {
        owner.setCellEditing(true);
    }

    void editorAboutToBeHidden(juce::TextEditor*) override
    {
        owner.setCellEditing(false);
    }

    /* Fired on Enter and on focus loss (clicking away), i.e. when the user
       "leaves" the cell: commit the typed value. */
    void textWasEdited() override
    {
        owner.cellEdited(columnId, currentRow, getText(true));
    }

private:
    PathEditView& owner;
    int columnId;
    int currentRow = -1;
};
}

juce::Component* PathEditView::refreshComponentForCell(int rowNumber, int columnId,
                                                       bool /*isRowSelected*/,
                                                       juce::Component* existingComponentToUpdate)
{
    if (columnId == colIndex) {
        delete existingComponentToUpdate;
        return nullptr;
    }

    auto* editor = dynamic_cast<KeyframeCellEditor*>(existingComponentToUpdate);
    if (editor == nullptr)
        editor = new KeyframeCellEditor(*this, columnId);
    /* The list reuses cell components across rows, so the row must be
       updated on every refresh. */
    editor->setRow(rowNumber);
    /* Do NOT reset the text while the user is typing in this cell:
       Label::setText() hides the editor, and the plugin's ~80ms timer
       refresh would otherwise kill the edit the moment it opens. */
    if (editor->getCurrentTextEditor() == nullptr)
        editor->setText(getCellText(rowNumber, columnId), juce::dontSendNotification);
    return editor;
}

void PathEditView::cellEdited(int columnId, int row, const juce::String& text)
{
    if (row < 0) return;
    PathData& path = currentPath(processor, selectedIsReceiver, selectedSourceIndex);
    if ((size_t)row >= path.keyframes.size()) return;

    double v = text.getDoubleValue();
    {
        const juce::SpinLock::ScopedLockType sl(processor.getPathLock());
        auto& kf = path.keyframes[row];
        switch (columnId) {
            case colTime: kf.timeSeconds = v; break;
            case colX:    kf.x = (float)v; break;
            case colY:    kf.y = (float)v; break;
            case colZ:    kf.z = (float)v; break;
            case colStop: {
                /* The pause is baked into the timeline: changing a node's
                   stop time shifts the arrival time of every later node (and
                   the path end time) by the same delta, so the path still
                   ends where the user left it and following nodes stay
                   consistent with their displayed times. */
                double oldStop = kf.stopTime;
                double newStop = juce::jmax(0.0, v);
                double delta = newStop - oldStop;
                kf.stopTime = (float)newStop;
                if (delta != 0.0) {
                    for (int j = row + 1; j < (int)path.keyframes.size(); ++j)
                        path.keyframes[j].timeSeconds += delta;
                    path.endTime += delta;
                }
                break;
            }
            default: break;
        }
    }
    processor.markPathDirty();
    updateKeyframeTable();
}

void PathEditView::updateKeyframeTable()
{
    PathData& path = currentPath(processor, selectedIsReceiver, selectedSourceIndex);
    LB_durationVal->setText("Duration: " + juce::String(path.endTime - path.startTime, 1) + "s",
                             juce::dontSendNotification);

    /* While the user is typing in a cell, do not touch the table: an
       updateContent() would re-lay-out the cells and can steal focus from
       the TextEditor, closing the edit before the user has finished. The
       value is committed by the cell editor itself when the user leaves. */
    if (isCellEditing)
        return;

    keyframeList->updateContent();
    keyframeList->repaint();
}

void PathEditView::paint(juce::Graphics& /*g*/) {}
