#pragma once

#include "JuceHeader.h"
#include "PluginProcessor.h"
#include "../../resources/SPARTALookAndFeel.h"

/* Column IDs for the editable keyframe table. */
enum PathEditColumnId {
    colIndex = 1,
    colTime,
    colX,
    colY,
    colZ,
    colStop
};

class PathEditView  : public Component,
                       public juce::ComboBox::Listener,
                       public juce::Button::Listener,
                       public juce::Slider::Listener,
                       public juce::TableListBoxModel
{
public:
    PathEditView(PluginProcessor& p);
    ~PathEditView() override;

    void refresh();
    void paint(juce::Graphics& g) override;
    void resized() override;

    int getSelectedSourceIndex() const { return selectedSourceIndex; }
    bool getSelectedIsReceiver() const { return selectedIsReceiver; }

    void comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged) override;
    void buttonClicked(juce::Button* buttonThatWasClicked) override;
    void sliderValueChanged(juce::Slider* sliderThatWasMoved) override;

    /* TableListBoxModel */
    int getNumRows() override;
    void paintRowBackground(juce::Graphics& g, int rowNumber, int width,
                            int height, bool rowIsSelected) override;
    void paintCell(juce::Graphics& g, int rowNumber, int columnId,
                   int width, int height, bool rowIsSelected) override;
    juce::Component* refreshComponentForCell(int rowNumber, int columnId,
                                             bool isRowSelected,
                                             juce::Component* existingComponentToUpdate) override;

    /* Called by the inline cell editors when the user commits an edit. */
    void cellEdited(int columnId, int row, const juce::String& text);

    /* Called by the inline cell editors while a cell editor is open; the
       ~80ms timer refresh skips the table while editing so the TextEditor
       is never disturbed. */
    void setCellEditing(bool isEditing) { isCellEditing = isEditing; }

private:
    bool isCellEditing = false;
    juce::String getCellText(int row, int columnId) const;
    void updateKeyframeTable();

    PluginProcessor& processor;
    void* hAmbi;

    int selectedSourceIndex = 0;
    bool selectedIsReceiver = false;

    void resyncTimeFromSliders();

    std::unique_ptr<juce::ComboBox> sourceSelector;
    std::unique_ptr<juce::Label> LB_source;
    std::unique_ptr<juce::ToggleButton> TB_pathLoop;
    std::unique_ptr<juce::Label> LB_loop;
    std::unique_ptr<juce::Slider> SL_pathStartTime;
    std::unique_ptr<juce::Label> LB_startTime;
    std::unique_ptr<juce::Slider> SL_pathEndTime;
    std::unique_ptr<juce::Label> LB_endTime;
    std::unique_ptr<juce::Label> LB_durationVal;
    std::unique_ptr<juce::TextButton> BT_pathClear;
    std::unique_ptr<juce::TextButton> BT_deleteNode;
    std::unique_ptr<juce::TableListBox> keyframeList;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PathEditView)
};
