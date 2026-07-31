#pragma once

#include "JuceHeader.h"
#include "PluginProcessor.h"
#include "../../resources/SPARTALookAndFeel.h"

class PathEditView  : public Component,
                       public juce::ComboBox::Listener,
                       public juce::Button::Listener,
                       public juce::Slider::Listener,
                       public juce::ListBoxModel
{
public:
    PathEditView(PluginProcessor& p);
    ~PathEditView() override;

    void refresh();
    void paint(juce::Graphics& g) override;
    void resized() override;

    int getSelectedSourceIndex() const { return selectedSourceIndex; }
    bool getSelectedIsReceiver() const { return selectedIsReceiver; }
    int getSelectedPathIndex() const { return selectedPathIndex; }

    void comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged) override;
    void buttonClicked(juce::Button* buttonThatWasClicked) override;
    void sliderValueChanged(juce::Slider* sliderThatWasMoved) override;

    int getNumRows() override;
    void paintListBoxItem(int rowNumber, juce::Graphics& g,
                          int width, int height, bool rowIsSelected) override;

private:
    void updateKeyframeTable();

    PluginProcessor& processor;
    void* hAmbi;

    int selectedSourceIndex = 0;
    bool selectedIsReceiver = false;
    int selectedPathIndex = 0;

    void resyncTimeFromSliders();

    std::unique_ptr<juce::ComboBox> sourceSelector;
    std::unique_ptr<juce::Label> LB_source;
    std::unique_ptr<juce::ComboBox> pathSelector;
    std::unique_ptr<juce::Label> LB_path;
    std::unique_ptr<juce::TextButton> BT_addPath;
    std::unique_ptr<juce::TextButton> BT_removePath;
    std::unique_ptr<juce::ToggleButton> TB_pathLoop;
    std::unique_ptr<juce::Label> LB_loop;
    std::unique_ptr<juce::Slider> SL_pathStartTime;
    std::unique_ptr<juce::Label> LB_startTime;
    std::unique_ptr<juce::Slider> SL_pathEndTime;
    std::unique_ptr<juce::Label> LB_endTime;
    std::unique_ptr<juce::Label> LB_durationVal;
    std::unique_ptr<juce::TextButton> BT_pathClear;
    std::unique_ptr<juce::TextButton> BT_deleteNode;
    std::unique_ptr<juce::Label> LB_kfHeader;
    std::unique_ptr<juce::ListBox> keyframeList;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PathEditView)
};
