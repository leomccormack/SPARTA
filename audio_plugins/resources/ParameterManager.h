/*
 ==============================================================================
 
 This file is part of SPARTA; a suite of spatial audio plug-ins.
 Copyright (c) 2025 - Janani Fernandez.
 
 SPARTA is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 SPARTA is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with SPARTA.  If not, see <http://www.gnu.org/licenses/>.
 
 ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class ParameterManager
{
public:
    ParameterManager(juce::AudioProcessor& processor, juce::AudioProcessorValueTreeState::ParameterLayout layout)
        : parameters(processor, nullptr, "Parameters", std::move(layout))
    {
        for(int i = 0; i < parameters.state.getNumChildren(); i++) {
            auto child = parameters.state.getChild(i);
            if(child.hasProperty("id"))
                parameterIDs.push_back(child.getProperty("id").toString());
        }
    }
    ~ParameterManager() {}
    
    void addParameterListeners(juce::AudioProcessorValueTreeState::Listener* listener) {
        if(!listener)
            return;
        for(auto& paramID : parameterIDs) {
            if(paramID.isEmpty())
                continue;
            if(auto* p = parameters.getParameter(paramID))
                if(dynamic_cast<juce::RangedAudioParameter*>(p) != nullptr)
                    parameters.addParameterListener(paramID, listener);
        }
    }

    void removeParameterListeners(juce::AudioProcessorValueTreeState::Listener* listener) {
        if(!listener)
            return;
        for(auto& paramID : parameterIDs) {
            if(paramID.isEmpty())
                continue;
            if(auto* p = parameters.getParameter(paramID))
                if(dynamic_cast<juce::RangedAudioParameter*>(p) != nullptr)
                    parameters.removeParameterListener(paramID, listener);
        }
    }
    
    // Sets
    void setParameterValue(const juce::String& parameterID, float newValue) {
        if(auto* param = parameters.getParameter(parameterID))
            param->setValueNotifyingHost(param->convertTo0to1(newValue));
    }

    void setParameterValue(const juce::String& parameterID, double newValue) {
        setParameterValue(parameterID, static_cast<float>(newValue));
    }

    void setParameterValue(const juce::String& parameterID, int newValue) {
        setParameterValue(parameterID, static_cast<float>(newValue));
    }

    void setParameterValue(const juce::String& parameterID, bool newValue) {
        setParameterValue(parameterID, newValue ? 1.0f : 0.0f);
    }

    // Gets
    float getParameterFloat(const juce::String& parameterID) const {
        if(auto* v = parameters.getRawParameterValue(parameterID))
            return *v;
        return 0.0f;
    }

    int getParameterInt(const juce::String& parameterID) const {
        return static_cast<int>(getParameterFloat(parameterID));
    }

    bool getParameterBool(const juce::String& parameterID) const {
        return getParameterFloat(parameterID) != 0.0f;
    }

    int getParameterChoice(const juce::String& parameterID) const {
        return static_cast<int>(getParameterFloat(parameterID));
    }

    juce::AudioProcessorValueTreeState parameters;
    
private:
    std::vector<juce::String> parameterIDs;
};

class SliderWithAttachment : public juce::Slider
{
public:
    SliderWithAttachment(juce::AudioProcessorValueTreeState& parameters, const juce::String& paramID)
        : attachment(parameters, paramID, *this) {
            auto* param = dynamic_cast<juce::AudioProcessorParameterWithID*>(parameters.getParameter(paramID));
            if(param != nullptr)
                setTextValueSuffix(param->getLabel());
        }
private:
    juce::AudioProcessorValueTreeState::SliderAttachment attachment;
};

class ComboBoxWithAttachment : public juce::ComboBox
{
public:
    ComboBoxWithAttachment(juce::AudioProcessorValueTreeState& parameters, const juce::String& paramID) {
        if(auto* param = dynamic_cast<juce::AudioParameterChoice*>(parameters.getParameter(paramID))) {
            const auto& choices = param->choices;
            for(int i = 0; i < choices.size(); i++)
                addItem(choices[i], i + 1);
            setSelectedId(param->getIndex() + 1, juce::dontSendNotification);
        }
        attachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(parameters, paramID, *this);
    }
private:
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> attachment;
};

class ToggleButtonWithAttachment : public juce::ToggleButton
{
public:
    ToggleButtonWithAttachment(juce::AudioProcessorValueTreeState& parameters, const juce::String& paramID)
        : attachment(parameters, paramID, *this) {}
private:
    juce::AudioProcessorValueTreeState::ButtonAttachment attachment;
};

inline void setSliderAsTextBoxOnly(juce::Slider& slider)
{
    slider.setSliderStyle(juce::Slider::LinearBarVertical);
    slider.setSliderSnapsToMousePosition(false);
}
