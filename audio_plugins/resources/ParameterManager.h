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

#include <JuceHeader.h>

class ParameterManager : public juce::AudioProcessorValueTreeState::Listener
{
public:
    ParameterManager(juce::AudioProcessor& processor, juce::AudioProcessorValueTreeState::ParameterLayout layout)
        : parameters(processor, nullptr, "Parameters", std::move(layout))
    {
        for(int i = 0; i < parameters.state.getNumChildren(); i++) {
            auto paramID = parameters.state.getChild(i).getProperty("id").toString();
            parameters.addParameterListener(paramID, this);
        }
    }
    ~ParameterManager(){
        for(int i = 0; i < parameters.state.getNumChildren(); i++) {
            auto paramID = parameters.state.getChild(i).getProperty("id").toString();
            parameters.removeParameterListener(paramID, this);
        }
    }
    
    // Sets
    void setParameterValue(const juce::String& parameterID, float newValue){
        auto* param = parameters.getParameter(parameterID);
        param->setValueNotifyingHost(param->convertTo0to1(newValue));
    }
    void setParameterValue(const juce::String& parameterID, double newValue){
        auto* param = parameters.getParameter(parameterID);
        param->setValueNotifyingHost(param->convertTo0to1(static_cast<float>(newValue)));
    }
    void setParameterValue(const juce::String& parameterID, int newValue){
        auto* param = parameters.getParameter(parameterID);
        param->setValueNotifyingHost(param->convertTo0to1(static_cast<float>(newValue)));
    }
    void setParameterValue(const juce::String& parameterID, bool newValue){
        auto* param = parameters.getParameter(parameterID);
        param->setValueNotifyingHost(param->convertTo0to1(static_cast<float>(newValue)));
    }

    // Gets
    float getParameterFloat(const juce::String& parameterID) const {
        return *parameters.getRawParameterValue(parameterID);
    }
    int getParameterInt(const juce::String& parameterID) const {
        return static_cast<int>(*parameters.getRawParameterValue(parameterID));
    }
    int getParameterChoice(const juce::String& parameterID) const {
        return static_cast<int>(*parameters.getRawParameterValue(parameterID));
    }

    juce::AudioProcessorValueTreeState parameters;
};


class SliderWithAttachment : public juce::Slider
{
public:
    SliderWithAttachment(juce::AudioProcessorValueTreeState& parameters, const juce::String& paramID)
        : attachment(parameters, paramID, *this) {}
private:
    juce::AudioProcessorValueTreeState::SliderAttachment attachment;
};

class ComboBoxWithAttachment : public juce::ComboBox
{
public:
    ComboBoxWithAttachment(juce::AudioProcessorValueTreeState& parameters, const juce::String& paramID) {
        if (auto* param = dynamic_cast<juce::AudioParameterChoice*>(parameters.getParameter(paramID))) {
            const auto& choices = param->choices;
            for (int i = 0; i < choices.size(); i++)
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
