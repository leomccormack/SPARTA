#pragma once

#include "JuceHeader.h"
#include "PluginProcessor.h"
#include "inputCoordsView.h"
#include "outputCoordsView.h"
#include "../../resources/SPARTALookAndFeel.h"

class RoomSettingsView  : public Component,
                           public juce::Slider::Listener,
                           public juce::ComboBox::Listener
{
public:
    RoomSettingsView(PluginProcessor& p);
    ~RoomSettingsView() override;

    void refresh();
    void paint(juce::Graphics& g) override;
    void resized() override;
    void sliderValueChanged(juce::Slider* sliderThatWasMoved) override;
    void comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged) override;

private:
    PluginProcessor& processor;
    void* hAmbi;

    /* source coordinates viewport */
    std::unique_ptr<Viewport> sourceCoordsVP;
    inputCoordsView* sourceCoordsView_handle;

    /* receiver coordinates viewport */
    std::unique_ptr<Viewport> receiverCoordsVP;
    outputCoordsView* receiverCoordsView_handle;

    bool refreshPanViewWindow;

    std::unique_ptr<SliderWithAttachment> SL_num_sources;
    std::unique_ptr<ComboBoxWithAttachment> CBoutputFormat;
    std::unique_ptr<ComboBoxWithAttachment> CBnormalisation;
    std::unique_ptr<ComboBoxWithAttachment> CBorder;
    std::unique_ptr<SliderWithAttachment> SL_num_receivers;
    std::unique_ptr<SliderWithAttachment> SL_max_reflection_order;
    std::unique_ptr<SliderWithAttachment> s_attenCoeff_pX;
    std::unique_ptr<SliderWithAttachment> s_attenCoeff_nX;
    std::unique_ptr<SliderWithAttachment> s_attenCoeff_nY;
    std::unique_ptr<SliderWithAttachment> s_attenCoeff_nZ;
    std::unique_ptr<SliderWithAttachment> s_attenCoeff_pZ;
    std::unique_ptr<SliderWithAttachment> s_attenCoeff_pY;
    std::unique_ptr<SliderWithAttachment> s_roomLenZ;
    std::unique_ptr<SliderWithAttachment> s_roomLenY;
    std::unique_ptr<SliderWithAttachment> s_roomLenX;
    std::unique_ptr<ToggleButtonWithAttachment> TB_enableIMS;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RoomSettingsView)
};
