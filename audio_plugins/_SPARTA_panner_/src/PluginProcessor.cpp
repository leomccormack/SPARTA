/*
 ==============================================================================
 
 This file is part of SPARTA; a suite of spatial audio plug-ins.
 Copyright (c) 2018 - Leo McCormack.
 
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
#include "PluginProcessor.h"
#include "PluginEditor.h"

PluginProcessor::PluginProcessor()
{
    ringBufferInputs = new float*[MAX_NUM_CHANNELS];
    for (int i = 0; i < MAX_NUM_CHANNELS; i++)
        ringBufferInputs[i] = new float[FRAME_SIZE];
    
    ringBufferOutputs = new float*[MAX_NUM_CHANNELS];
    for (int i = 0; i < MAX_NUM_CHANNELS; i++)
        ringBufferOutputs[i] = new float[FRAME_SIZE];
    
	panner_create(&hPan);
}

PluginProcessor::~PluginProcessor()
{
	panner_destroy(&hPan);
    
    for (int i = 0; i < MAX_NUM_CHANNELS; ++i) {
        delete[] ringBufferInputs[i];
    }
    delete[] ringBufferInputs;
    
    for (int i = 0; i < MAX_NUM_CHANNELS; ++i) {
        delete[] ringBufferOutputs[i];
    }
    delete[] ringBufferOutputs;
}

void PluginProcessor::setParameter (int index, float newValue)
{
	switch (index)
	{
        case k_nSources: panner_setNumSources(hPan, MAX((int)(newValue*MAX_NUM_CHANNELS+0.5f),1)); break;
        case k_srcAzi_0: panner_setSourceAzi_deg(hPan, 0, (newValue - 0.5f)*360.0f); break; case k_srcElev_0: panner_setSourceElev_deg(hPan, 0, (newValue - 0.5f)*180.0f); break;
        case k_srcAzi_1: panner_setSourceAzi_deg(hPan, 1, (newValue - 0.5f)*360.0f); break; case k_srcElev_1: panner_setSourceElev_deg(hPan, 1, (newValue - 0.5f)*180.0f); break;
        case k_srcAzi_2: panner_setSourceAzi_deg(hPan, 2, (newValue - 0.5f)*360.0f); break; case k_srcElev_2: panner_setSourceElev_deg(hPan, 2, (newValue - 0.5f)*180.0f); break;
        case k_srcAzi_3: panner_setSourceAzi_deg(hPan, 3, (newValue - 0.5f)*360.0f); break; case k_srcElev_3: panner_setSourceElev_deg(hPan, 3, (newValue - 0.5f)*180.0f); break;
        case k_srcAzi_4: panner_setSourceAzi_deg(hPan, 4, (newValue - 0.5f)*360.0f); break; case k_srcElev_4: panner_setSourceElev_deg(hPan, 4, (newValue - 0.5f)*180.0f); break;
        case k_srcAzi_5: panner_setSourceAzi_deg(hPan, 5, (newValue - 0.5f)*360.0f); break; case k_srcElev_5: panner_setSourceElev_deg(hPan, 5, (newValue - 0.5f)*180.0f); break;
        case k_srcAzi_6: panner_setSourceAzi_deg(hPan, 6, (newValue - 0.5f)*360.0f); break; case k_srcElev_6: panner_setSourceElev_deg(hPan, 6, (newValue - 0.5f)*180.0f); break;
        case k_srcAzi_7: panner_setSourceAzi_deg(hPan, 7, (newValue - 0.5f)*360.0f); break; case k_srcElev_7: panner_setSourceElev_deg(hPan, 7, (newValue - 0.5f)*180.0f); break;
        case k_srcAzi_8: panner_setSourceAzi_deg(hPan, 8, (newValue - 0.5f)*360.0f); break; case k_srcElev_8: panner_setSourceElev_deg(hPan, 8, (newValue - 0.5f)*180.0f); break;
        case k_srcAzi_9: panner_setSourceAzi_deg(hPan, 9, (newValue - 0.5f)*360.0f); break; case k_srcElev_9: panner_setSourceElev_deg(hPan, 9, (newValue - 0.5f)*180.0f); break;
        case k_srcAzi_10: panner_setSourceAzi_deg(hPan, 10, (newValue - 0.5f)*360.0f); break; case k_srcElev_10: panner_setSourceElev_deg(hPan, 10, (newValue - 0.5f)*180.0f); break;
        case k_srcAzi_11: panner_setSourceAzi_deg(hPan, 11, (newValue - 0.5f)*360.0f); break; case k_srcElev_11: panner_setSourceElev_deg(hPan, 11, (newValue - 0.5f)*180.0f); break;
        case k_srcAzi_12: panner_setSourceAzi_deg(hPan, 12, (newValue - 0.5f)*360.0f); break; case k_srcElev_12: panner_setSourceElev_deg(hPan, 12, (newValue - 0.5f)*180.0f); break;
        case k_srcAzi_13: panner_setSourceAzi_deg(hPan, 13, (newValue - 0.5f)*360.0f); break; case k_srcElev_13: panner_setSourceElev_deg(hPan, 13, (newValue - 0.5f)*180.0f); break;
        case k_srcAzi_14: panner_setSourceAzi_deg(hPan, 14, (newValue - 0.5f)*360.0f); break; case k_srcElev_14: panner_setSourceElev_deg(hPan, 14, (newValue - 0.5f)*180.0f); break;
        case k_srcAzi_15: panner_setSourceAzi_deg(hPan, 15, (newValue - 0.5f)*360.0f); break; case k_srcElev_15: panner_setSourceElev_deg(hPan, 15, (newValue - 0.5f)*180.0f); break;
        case k_srcAzi_16: panner_setSourceAzi_deg(hPan, 16, (newValue - 0.5f)*360.0f); break; case k_srcElev_16: panner_setSourceElev_deg(hPan, 16, (newValue - 0.5f)*180.0f); break;
        case k_srcAzi_17: panner_setSourceAzi_deg(hPan, 17, (newValue - 0.5f)*360.0f); break; case k_srcElev_17: panner_setSourceElev_deg(hPan, 17, (newValue - 0.5f)*180.0f); break;
        case k_srcAzi_18: panner_setSourceAzi_deg(hPan, 18, (newValue - 0.5f)*360.0f); break; case k_srcElev_18: panner_setSourceElev_deg(hPan, 18, (newValue - 0.5f)*180.0f); break;
        case k_srcAzi_19: panner_setSourceAzi_deg(hPan, 19, (newValue - 0.5f)*360.0f); break; case k_srcElev_19: panner_setSourceElev_deg(hPan, 19, (newValue - 0.5f)*180.0f); break;
        case k_srcAzi_20: panner_setSourceAzi_deg(hPan, 20, (newValue - 0.5f)*360.0f); break; case k_srcElev_20: panner_setSourceElev_deg(hPan, 20, (newValue - 0.5f)*180.0f); break;
        case k_srcAzi_21: panner_setSourceAzi_deg(hPan, 21, (newValue - 0.5f)*360.0f); break; case k_srcElev_21: panner_setSourceElev_deg(hPan, 21, (newValue - 0.5f)*180.0f); break;
        case k_srcAzi_22: panner_setSourceAzi_deg(hPan, 22, (newValue - 0.5f)*360.0f); break; case k_srcElev_22: panner_setSourceElev_deg(hPan, 22, (newValue - 0.5f)*180.0f); break;
        case k_srcAzi_23: panner_setSourceAzi_deg(hPan, 23, (newValue - 0.5f)*360.0f); break; case k_srcElev_23: panner_setSourceElev_deg(hPan, 23, (newValue - 0.5f)*180.0f); break;
        case k_srcAzi_24: panner_setSourceAzi_deg(hPan, 24, (newValue - 0.5f)*360.0f); break; case k_srcElev_24: panner_setSourceElev_deg(hPan, 24, (newValue - 0.5f)*180.0f); break;
        case k_srcAzi_25: panner_setSourceAzi_deg(hPan, 25, (newValue - 0.5f)*360.0f); break; case k_srcElev_25: panner_setSourceElev_deg(hPan, 25, (newValue - 0.5f)*180.0f); break;
        case k_srcAzi_26: panner_setSourceAzi_deg(hPan, 26, (newValue - 0.5f)*360.0f); break; case k_srcElev_26: panner_setSourceElev_deg(hPan, 26, (newValue - 0.5f)*180.0f); break;
        case k_srcAzi_27: panner_setSourceAzi_deg(hPan, 27, (newValue - 0.5f)*360.0f); break; case k_srcElev_27: panner_setSourceElev_deg(hPan, 27, (newValue - 0.5f)*180.0f); break;
        case k_srcAzi_28: panner_setSourceAzi_deg(hPan, 28, (newValue - 0.5f)*360.0f); break; case k_srcElev_28: panner_setSourceElev_deg(hPan, 28, (newValue - 0.5f)*180.0f); break;
        case k_srcAzi_29: panner_setSourceAzi_deg(hPan, 29, (newValue - 0.5f)*360.0f); break; case k_srcElev_29: panner_setSourceElev_deg(hPan, 29, (newValue - 0.5f)*180.0f); break;
        case k_srcAzi_30: panner_setSourceAzi_deg(hPan, 30, (newValue - 0.5f)*360.0f); break; case k_srcElev_30: panner_setSourceElev_deg(hPan, 30, (newValue - 0.5f)*180.0f); break;
        case k_srcAzi_31: panner_setSourceAzi_deg(hPan, 31, (newValue - 0.5f)*360.0f); break; case k_srcElev_31: panner_setSourceElev_deg(hPan, 31, (newValue - 0.5f)*180.0f); break;
        case k_srcAzi_32: panner_setSourceAzi_deg(hPan, 32, (newValue - 0.5f)*360.0f); break; case k_srcElev_32: panner_setSourceElev_deg(hPan, 32, (newValue - 0.5f)*180.0f); break;
		default: break;
	}
}

void PluginProcessor::setCurrentProgram (int index)
{
}

float PluginProcessor::getParameter (int index)
{
    switch (index)
	{
        case k_nSources: return MAX((float)panner_getNumSources(hPan)/(float)MAX_NUM_CHANNELS, 1.0f/(float)MAX_NUM_CHANNELS);
        case k_srcAzi_0: return (panner_getSourceAzi_deg(hPan, 0)/360.0f) + 0.5f; case k_srcElev_0: return (panner_getSourceElev_deg(hPan, 0)/180.0f) + 0.5f;
        case k_srcAzi_1: return (panner_getSourceAzi_deg(hPan, 1)/360.0f) + 0.5f; case k_srcElev_1: return (panner_getSourceElev_deg(hPan, 1)/180.0f) + 0.5f;
        case k_srcAzi_2: return (panner_getSourceAzi_deg(hPan, 2)/360.0f) + 0.5f; case k_srcElev_2: return (panner_getSourceElev_deg(hPan, 2)/180.0f) + 0.5f;
        case k_srcAzi_3: return (panner_getSourceAzi_deg(hPan, 3)/360.0f) + 0.5f; case k_srcElev_3: return (panner_getSourceElev_deg(hPan, 3)/180.0f) + 0.5f;
        case k_srcAzi_4: return (panner_getSourceAzi_deg(hPan, 4)/360.0f) + 0.5f; case k_srcElev_4: return (panner_getSourceElev_deg(hPan, 4)/180.0f) + 0.5f;
        case k_srcAzi_5: return (panner_getSourceAzi_deg(hPan, 5)/360.0f) + 0.5f; case k_srcElev_5: return (panner_getSourceElev_deg(hPan, 5)/180.0f) + 0.5f;
        case k_srcAzi_6: return (panner_getSourceAzi_deg(hPan, 6)/360.0f) + 0.5f; case k_srcElev_6: return (panner_getSourceElev_deg(hPan, 6)/180.0f) + 0.5f;
        case k_srcAzi_7: return (panner_getSourceAzi_deg(hPan, 7)/360.0f) + 0.5f; case k_srcElev_7: return (panner_getSourceElev_deg(hPan, 7)/180.0f) + 0.5f;
        case k_srcAzi_8: return (panner_getSourceAzi_deg(hPan, 8)/360.0f) + 0.5f; case k_srcElev_8: return (panner_getSourceElev_deg(hPan, 8)/180.0f) + 0.5f;
        case k_srcAzi_9: return (panner_getSourceAzi_deg(hPan, 9)/360.0f) + 0.5f; case k_srcElev_9: return (panner_getSourceElev_deg(hPan, 9)/180.0f) + 0.5f;
        case k_srcAzi_10: return (panner_getSourceAzi_deg(hPan, 10)/360.0f) + 0.5f; case k_srcElev_10: return (panner_getSourceElev_deg(hPan, 10)/180.0f) + 0.5f;
        case k_srcAzi_11: return (panner_getSourceAzi_deg(hPan, 11)/360.0f) + 0.5f; case k_srcElev_11: return (panner_getSourceElev_deg(hPan, 11)/180.0f) + 0.5f;
        case k_srcAzi_12: return (panner_getSourceAzi_deg(hPan, 12)/360.0f) + 0.5f; case k_srcElev_12: return (panner_getSourceElev_deg(hPan, 12)/180.0f) + 0.5f;
        case k_srcAzi_13: return (panner_getSourceAzi_deg(hPan, 13)/360.0f) + 0.5f; case k_srcElev_13: return (panner_getSourceElev_deg(hPan, 13)/180.0f) + 0.5f;
        case k_srcAzi_14: return (panner_getSourceAzi_deg(hPan, 14)/360.0f) + 0.5f; case k_srcElev_14: return (panner_getSourceElev_deg(hPan, 14)/180.0f) + 0.5f;
        case k_srcAzi_15: return (panner_getSourceAzi_deg(hPan, 15)/360.0f) + 0.5f; case k_srcElev_15: return (panner_getSourceElev_deg(hPan, 15)/180.0f) + 0.5f;
        case k_srcAzi_16: return (panner_getSourceAzi_deg(hPan, 16)/360.0f) + 0.5f; case k_srcElev_16: return (panner_getSourceElev_deg(hPan, 16)/180.0f) + 0.5f;
        case k_srcAzi_17: return (panner_getSourceAzi_deg(hPan, 17)/360.0f) + 0.5f; case k_srcElev_17: return (panner_getSourceElev_deg(hPan, 17)/180.0f) + 0.5f;
        case k_srcAzi_18: return (panner_getSourceAzi_deg(hPan, 18)/360.0f) + 0.5f; case k_srcElev_18: return (panner_getSourceElev_deg(hPan, 18)/180.0f) + 0.5f;
        case k_srcAzi_19: return (panner_getSourceAzi_deg(hPan, 19)/360.0f) + 0.5f; case k_srcElev_19: return (panner_getSourceElev_deg(hPan, 19)/180.0f) + 0.5f;
        case k_srcAzi_20: return (panner_getSourceAzi_deg(hPan, 20)/360.0f) + 0.5f; case k_srcElev_20: return (panner_getSourceElev_deg(hPan, 20)/180.0f) + 0.5f;
        case k_srcAzi_21: return (panner_getSourceAzi_deg(hPan, 21)/360.0f) + 0.5f; case k_srcElev_21: return (panner_getSourceElev_deg(hPan, 21)/180.0f) + 0.5f;
        case k_srcAzi_22: return (panner_getSourceAzi_deg(hPan, 22)/360.0f) + 0.5f; case k_srcElev_22: return (panner_getSourceElev_deg(hPan, 22)/180.0f) + 0.5f;
        case k_srcAzi_23: return (panner_getSourceAzi_deg(hPan, 23)/360.0f) + 0.5f; case k_srcElev_23: return (panner_getSourceElev_deg(hPan, 23)/180.0f) + 0.5f;
        case k_srcAzi_24: return (panner_getSourceAzi_deg(hPan, 24)/360.0f) + 0.5f; case k_srcElev_24: return (panner_getSourceElev_deg(hPan, 24)/180.0f) + 0.5f;
        case k_srcAzi_25: return (panner_getSourceAzi_deg(hPan, 25)/360.0f) + 0.5f; case k_srcElev_25: return (panner_getSourceElev_deg(hPan, 25)/180.0f) + 0.5f;
        case k_srcAzi_26: return (panner_getSourceAzi_deg(hPan, 26)/360.0f) + 0.5f; case k_srcElev_26: return (panner_getSourceElev_deg(hPan, 26)/180.0f) + 0.5f;
        case k_srcAzi_27: return (panner_getSourceAzi_deg(hPan, 27)/360.0f) + 0.5f; case k_srcElev_27: return (panner_getSourceElev_deg(hPan, 27)/180.0f) + 0.5f;
        case k_srcAzi_28: return (panner_getSourceAzi_deg(hPan, 28)/360.0f) + 0.5f; case k_srcElev_28: return (panner_getSourceElev_deg(hPan, 28)/180.0f) + 0.5f;
        case k_srcAzi_29: return (panner_getSourceAzi_deg(hPan, 29)/360.0f) + 0.5f; case k_srcElev_29: return (panner_getSourceElev_deg(hPan, 29)/180.0f) + 0.5f;
        case k_srcAzi_30: return (panner_getSourceAzi_deg(hPan, 30)/360.0f) + 0.5f; case k_srcElev_30: return (panner_getSourceElev_deg(hPan, 30)/180.0f) + 0.5f;
        case k_srcAzi_31: return (panner_getSourceAzi_deg(hPan, 31)/360.0f) + 0.5f; case k_srcElev_31: return (panner_getSourceElev_deg(hPan, 31)/180.0f) + 0.5f;
        case k_srcAzi_32: return (panner_getSourceAzi_deg(hPan, 32)/360.0f) + 0.5f; case k_srcElev_32: return (panner_getSourceElev_deg(hPan, 32)/180.0f) + 0.5f;
		default: return 0.0f;
	}
}

int PluginProcessor::getNumParameters()
{
	return k_NumOfParameters;
}

const String PluginProcessor::getName() const
{
    return JucePlugin_Name;
}

const String PluginProcessor::getParameterName (int index)
{
    switch (index)
	{
        case k_nSources: return "nSources";
        case k_srcAzi_0: return "srcAzi_0"; case k_srcElev_0: return "srcElev_0";
        case k_srcAzi_1: return "srcAzi_1"; case k_srcElev_1: return "srcElev_1";
        case k_srcAzi_2: return "srcAzi_2"; case k_srcElev_2: return "srcElev_2";
        case k_srcAzi_3: return "srcAzi_3"; case k_srcElev_3: return "srcElev_3";
        case k_srcAzi_4: return "srcAzi_4"; case k_srcElev_4: return "srcElev_4";
        case k_srcAzi_5: return "srcAzi_5"; case k_srcElev_5: return "srcElev_5";
        case k_srcAzi_6: return "srcAzi_6"; case k_srcElev_6: return "srcElev_6";
        case k_srcAzi_7: return "srcAzi_7"; case k_srcElev_7: return "srcElev_7";
        case k_srcAzi_8: return "srcAzi_8"; case k_srcElev_8: return "srcElev_8";
        case k_srcAzi_9: return "srcAzi_9"; case k_srcElev_9: return "srcElev_9";
        case k_srcAzi_10: return "srcAzi_10"; case k_srcElev_10: return "srcElev_10";
        case k_srcAzi_11: return "srcAzi_11"; case k_srcElev_11: return "srcElev_11";
        case k_srcAzi_12: return "srcAzi_12"; case k_srcElev_12: return "srcElev_12";
        case k_srcAzi_13: return "srcAzi_13"; case k_srcElev_13: return "srcElev_13";
        case k_srcAzi_14: return "srcAzi_14"; case k_srcElev_14: return "srcElev_14";
        case k_srcAzi_15: return "srcAzi_15"; case k_srcElev_15: return "srcElev_15";
        case k_srcAzi_16: return "srcAzi_16"; case k_srcElev_16: return "srcElev_16";
        case k_srcAzi_17: return "srcAzi_17"; case k_srcElev_17: return "srcElev_17";
        case k_srcAzi_18: return "srcAzi_18"; case k_srcElev_18: return "srcElev_18";
        case k_srcAzi_19: return "srcAzi_19"; case k_srcElev_19: return "srcElev_19";
        case k_srcAzi_20: return "srcAzi_20"; case k_srcElev_20: return "srcElev_20";
        case k_srcAzi_21: return "srcAzi_21"; case k_srcElev_21: return "srcElev_21";
        case k_srcAzi_22: return "srcAzi_22"; case k_srcElev_22: return "srcElev_22";
        case k_srcAzi_23: return "srcAzi_23"; case k_srcElev_23: return "srcElev_23";
        case k_srcAzi_24: return "srcAzi_24"; case k_srcElev_24: return "srcElev_24";
        case k_srcAzi_25: return "srcAzi_25"; case k_srcElev_25: return "srcElev_25";
        case k_srcAzi_26: return "srcAzi_26"; case k_srcElev_26: return "srcElev_26";
        case k_srcAzi_27: return "srcAzi_27"; case k_srcElev_27: return "srcElev_27";
        case k_srcAzi_28: return "srcAzi_28"; case k_srcElev_28: return "srcElev_28";
        case k_srcAzi_29: return "srcAzi_29"; case k_srcElev_29: return "srcElev_29";
        case k_srcAzi_30: return "srcAzi_30"; case k_srcElev_30: return "srcElev_30";
        case k_srcAzi_31: return "srcAzi_31"; case k_srcElev_31: return "srcElev_31";
        case k_srcAzi_32: return "srcAzi_32"; case k_srcElev_32: return "srcElev_32";
		default: return "NULL";
	}
}

const String PluginProcessor::getParameterText(int index)
{
	return String(getParameter(index), 1);    
}

const String PluginProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String PluginProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

double PluginProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PluginProcessor::getNumPrograms()
{
    return 0;
}

int PluginProcessor::getCurrentProgram()
{
    return 0;
}

const String PluginProcessor::getProgramName (int index)
{
    return String::empty;
}


bool PluginProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool PluginProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}


bool PluginProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool PluginProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool PluginProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

void PluginProcessor::changeProgramName (int index, const String& newName)
{
}

void PluginProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	nHostBlockSize = samplesPerBlock;
	nSampleRate = (int)(sampleRate + 0.5);
    
    nNumInputs = getTotalNumInputChannels();
    nNumOutputs = getTotalNumOutputChannels();
 
	setPlayConfigDetails(nNumInputs, nNumOutputs, (double)nSampleRate, nHostBlockSize);
	numChannelsChanged();
    isPlaying = false;

	panner_init(hPan, sampleRate);
    
    for (int i = 0; i < MAX_NUM_CHANNELS; ++i) {
        memset(ringBufferInputs[i], 0, FRAME_SIZE*sizeof(float));
    }
    for (int i = 0; i < MAX_NUM_CHANNELS; ++i) {
        memset(ringBufferOutputs[i], 0, FRAME_SIZE * sizeof(float));
    }
    wIdx = 1; rIdx = 1; /* read/write indices for ring buffers */
}

void PluginProcessor::releaseResources()
{
    isPlaying = false;
}

void PluginProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    int nCurrentBlockSize = buffer.getNumSamples();
    float** bufferData = buffer.getArrayOfWritePointers();
    float** outputs = new float*[nNumOutputs];
    for (int i = 0; i < nNumOutputs; i++) {
        outputs[i] = new float[FRAME_SIZE];
    }
    
    playHead = getPlayHead();
    bool PlayHeadAvailable = playHead->getCurrentPosition(currentPosition);
    if (PlayHeadAvailable == true)
        isPlaying = currentPosition.isPlaying;
    else
        isPlaying = false;
    
    if (nCurrentBlockSize % FRAME_SIZE == 0) { /* divisible by frame size */
        for (int frame = 0; frame < nCurrentBlockSize / FRAME_SIZE; frame++) {
            for (int ch = 0; ch < nNumInputs; ch++)
                for (int i = 0; i < FRAME_SIZE; i++)
                    ringBufferInputs[ch][i] = bufferData[ch][frame*FRAME_SIZE + i];
            
            /* determine if there is actually audio in the damn buffer */
            playHead = getPlayHead();
            bool PlayHeadAvailable = playHead->getCurrentPosition(currentPosition);
            if (PlayHeadAvailable == true)
                isPlaying = currentPosition.isPlaying;
            else
                isPlaying = false;
            
            /* perform processing */
            panner_process(hPan, ringBufferInputs, ringBufferOutputs, nNumInputs, nNumOutputs, FRAME_SIZE, isPlaying);
            
            /* replace buffer with new audio */
            buffer.clear(frame*FRAME_SIZE, FRAME_SIZE);
            for (int ch = 0; ch < nNumOutputs; ch++)
                for (int i = 0; i < FRAME_SIZE; i++)
                    bufferData[ch][frame*FRAME_SIZE + i] = ringBufferOutputs[ch][i];
        }
    }
    else
        buffer.clear();
    
    if (nHostBlockSize == (FRAME_SIZE/2)) {
        wIdx++; if (wIdx > 1) { wIdx = 0; }
        rIdx++; if (rIdx > 1) { rIdx = 0; }
    }
    
    for (int i = 0; i < nNumOutputs; ++i) {
        delete[] outputs[i];
    }
    delete[] outputs;
}

//==============================================================================
bool PluginProcessor::hasEditor() const
{
    return true; 
}

AudioProcessorEditor* PluginProcessor::createEditor()
{
    return new PluginEditor (this);
}

//==============================================================================
void PluginProcessor::getStateInformation (MemoryBlock& destData)
{
    XmlElement xml("PANNERPLUGINSETTINGS");
    for(int i=0; i<panner_getMaxNumSources(); i++){
        xml.setAttribute("SourceAziDeg" + String(i), panner_getSourceAzi_deg(hPan,i));
        xml.setAttribute("SourceElevDeg" + String(i), panner_getSourceElev_deg(hPan,i));
    }
    xml.setAttribute("nSources", panner_getNumSources(hPan));
    xml.setAttribute("DTT", panner_getDTT(hPan));
    
    for(int i=0; i<panner_getMaxNumLoudspeakers(); i++){
        xml.setAttribute("LoudspeakerAziDeg" + String(i), panner_getLoudspeakerAzi_deg(hPan,i));
        xml.setAttribute("LoudspeakerElevDeg" + String(i), panner_getLoudspeakerElev_deg(hPan,i));
    }
    xml.setAttribute("nLoudspeakers", panner_getNumLoudspeakers(hPan));

    copyXmlToBinary(xml, destData);
}

void PluginProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    ScopedPointer<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    
    if (xmlState != nullptr) {
        if (xmlState->hasTagName("PANNERPLUGINSETTINGS")) {
            for(int i=0; i<panner_getMaxNumSources(); i++){
                if(xmlState->hasAttribute("SourceAziDeg" + String(i)))
                    panner_setSourceAzi_deg(hPan, i, (float)xmlState->getDoubleAttribute("SourceAziDeg" + String(i), 0.0f));
                if(xmlState->hasAttribute("SourceElevDeg" + String(i)))
                    panner_setSourceElev_deg(hPan, i, (float)xmlState->getDoubleAttribute("SourceElevDeg" + String(i), 0.0f));
            }
            if(xmlState->hasAttribute("nSources"))
                panner_setNumSources(hPan, xmlState->getIntAttribute("nSources", 1));
            if(xmlState->hasAttribute("DTT"))
                panner_setDTT(hPan, (float)xmlState->getDoubleAttribute("DTT", 1));
            
            for(int i=0; i<panner_getMaxNumLoudspeakers(); i++){
                if(xmlState->hasAttribute("LoudspeakerAziDeg" + String(i)))
                    panner_setLoudspeakerAzi_deg(hPan, i, (float)xmlState->getDoubleAttribute("LoudspeakerAziDeg" + String(i),0.0f));
                if(xmlState->hasAttribute("LoudspeakerElevDeg" + String(i)))
                    panner_setLoudspeakerElev_deg(hPan, i, (float)xmlState->getDoubleAttribute("LoudspeakerElevDeg" + String(i), 0.0f));
            }
            if(xmlState->hasAttribute("nLoudspeakers"))
                panner_setNumLoudspeakers(hPan, xmlState->getIntAttribute("nLoudspeakers", 1));
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginProcessor();
}

