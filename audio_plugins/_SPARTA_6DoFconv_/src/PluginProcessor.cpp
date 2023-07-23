/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PluginProcessor::PluginProcessor() :
    AudioProcessor(BusesProperties()
        .withInput("Input", AudioChannelSet::discreteChannels(64), true)
        .withOutput("Output", AudioChannelSet::discreteChannels(64), true))
{
    nSampleRate = 48000;
    nHostBlockSize = -1;
    tvconv_create(&hTVCnv);
    
    // (@todo) to be automated
    enable_rotation = true;
    
    rotator_create(&hRot);

    // (@todo) needs to be made adaptive 
    rotator_setOrder(hRot, 4);

    refreshWindow = true;

    /* specify here on which UDP port number to receive incoming OSC messages */
    osc_port_ID = DEFAULT_OSC_PORT;
    osc_connected = osc.connect(osc_port_ID);
    /* tell the component to listen for OSC messages */
    osc.addListener(this);

    if (osc_connected)
    {
        DBG("osc connected");
    }
    else
    {
        DBG("osc not connected");
    }

	// Parameter 1
    addParameter(receiver_coordinate_x = new juce::AudioParameterFloat("receiver_coordinate_x", // parameterID
        "receiver_coordinate_x", // parameter name
        0.0f,   // minimum value
        1.0f,   // maximum value
        0.5f)); // default value
	// Parameter 2
	addParameter(receiver_coordinate_y = new juce::AudioParameterFloat("receiver_coordinate_y", // parameterID
		"receiver_coordinate_y", // parameter name
		0.0f,   // minimum value
		1.0f,   // maximum value
		0.5f)); // default value
	// Parameter 3
	addParameter(receiver_coordinate_z = new juce::AudioParameterFloat("receiver_coordinate_z", // parameterID
		"receiver_coordinate_z", // parameter name
		0.0f,   // minimum value
		1.0f,   // maximum value
		0.5f)); // default value
	// Parameter 4
	addParameter(receiver_quaternion_w = new juce::AudioParameterFloat("receiver_quaternion_w", // parameterID
		"receiver_quaternion_w", // parameter name
		0.0f,   // minimum value
		1.0f,   // maximum value
		0.5f)); // default value
	// Parameter 5
	addParameter(receiver_quaternion_x = new juce::AudioParameterFloat("receiver_quaternion_x", // parameterID
		"receiver_quaternion_x", // parameter name
		0.0f,   // minimum value
		1.0f,   // maximum value
		0.5f)); // default value
	// Parameter 6
	addParameter(receiver_quaternion_y = new juce::AudioParameterFloat("receiver_quaternion_y", // parameterID
		"receiver_quaternion_y", // parameter name
		0.0f,   // minimum value
		1.0f,   // maximum value
		0.5f)); // default value
	// Parameter 7
	addParameter(receiver_quaternion_z = new juce::AudioParameterFloat("receiver_quaternion_z", // parameterID
		"receiver_quaternion_z", // parameter name
		0.0f,   // minimum value
		1.0f,   // maximum value
		0.5f)); // default value
	// Parameter 8
	addParameter(receiver_yaw = new juce::AudioParameterFloat("receiver_yaw", // parameterID
		"receiver_yaw", // parameter name
		0.0f,   // minimum value
		1.0f,   // maximum value
		0.5f)); // default value
	// Parameter 9
	addParameter(receiver_pitch = new juce::AudioParameterFloat("receiver_pitch", // parameterID
		"receiver_pitch", // parameter name
		0.0f,   // minimum value
		1.0f,   // maximum value
		0.5f)); // default value
	// Parameter 10
	addParameter(receiver_roll = new juce::AudioParameterFloat("receiver_roll", // parameterID
		"receiver_roll", // parameter name
		0.0f,   // minimum value
		1.0f,   // maximum value
		0.5f)); // default value
	// Parameter 11
	addParameter(room_size_x = new juce::AudioParameterFloat("room_size_x", // parameterID
		"room_size_x", // parameter name
		0.0f,   // minimum value
		1.0f,   // maximum value
		0.5f)); // default value
	// Parameter 12
	addParameter(room_size_y = new juce::AudioParameterFloat("room_size_y", // parameterID
		"room_size_y", // parameter name
		0.0f,   // minimum value
		1.0f,   // maximum value
		0.5f)); // default value
	// Parameter 13
	addParameter(room_size_z = new juce::AudioParameterFloat("room_size_z", // parameterID
		"room_size_z", // parameter name
		0.0f,   // minimum value
		1.0f,   // maximum value
		0.5f)); // default value

}

PluginProcessor::~PluginProcessor()
{
    osc.disconnect();
    osc.removeListener(this);
    tvconv_destroy(&hTVCnv);
}

//==============================================================================


void PluginProcessor::oscMessageReceived(const OSCMessage& message)
{
    if (message.size() == 3 && message.getAddressPattern().toString().compare("/xyz") == 0 ) {
        if (message[0].isFloat32())
            setParameterRaw(0, message[0].getFloat32());
        if (message[1].isFloat32())
            setParameterRaw(1, message[1].getFloat32());
        if (message[2].isFloat32())
            setParameterRaw(2, message[2].getFloat32());
        return;
    }
    
    else if (message.size() == 4 && message.getAddressPattern().toString().compare("/quat") == 0) {
        if (message[0].isFloat32())
            rotator_setQuaternionW(hRot, message[0].getFloat32());
        if (message[1].isFloat32())
            rotator_setQuaternionX(hRot, message[1].getFloat32());
        if (message[2].isFloat32())
            rotator_setQuaternionY(hRot, message[2].getFloat32());
        if (message[3].isFloat32())
            rotator_setQuaternionZ(hRot, message[3].getFloat32());
        return;
    }

    else if (message.size() == 7 && message.getAddressPattern().toString().compare("/xyzquat") == 0) {
        if (message[0].isFloat32())
            setParameterRaw(0, message[0].getFloat32());
        if (message[1].isFloat32())
            setParameterRaw(1, message[1].getFloat32());
        if (message[2].isFloat32())
            setParameterRaw(2, message[2].getFloat32());
        if (message[3].isFloat32())
            rotator_setQuaternionW(hRot, message[3].getFloat32());
        if (message[4].isFloat32())
            rotator_setQuaternionX(hRot, message[4].getFloat32());
        if (message[5].isFloat32())
            rotator_setQuaternionY(hRot, message[5].getFloat32());
        if (message[6].isFloat32())
            rotator_setQuaternionZ(hRot, message[6].getFloat32());
        return;
    }

    else if (message.size() == 3 && message.getAddressPattern().toString().compare("/ypr") == 0) {
        if (message[0].isFloat32())
            rotator_setYaw(hRot, message[0].getFloat32());
        if (message[1].isFloat32())
            rotator_setPitch(hRot, message[1].getFloat32());
        if (message[2].isFloat32())
            rotator_setRoll(hRot, message[2].getFloat32());
        return;
    }

    else if (message.size() == 6 && message.getAddressPattern().toString().compare("/xyzypr") == 0 ) {
        if (message[0].isFloat32())
            setParameterRaw(0, message[0].getFloat32());
        if (message[1].isFloat32())
            setParameterRaw(1, message[1].getFloat32());
        if (message[2].isFloat32())
            setParameterRaw(2, message[2].getFloat32());
        if (message[3].isFloat32())
            rotator_setYaw(hRot, message[3].getFloat32());
        if (message[4].isFloat32())
            rotator_setPitch(hRot, message[4].getFloat32());
        if (message[5].isFloat32())
            rotator_setRoll(hRot, message[5].getFloat32());
        return;
    }
}

const juce::String PluginProcessor::getName() const
{
    return JucePlugin_Name;
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

bool PluginProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double PluginProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PluginProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int PluginProcessor::getCurrentProgram()
{
    return 0;
}

void PluginProcessor::setCurrentProgram (int /*index*/)
{
}

const juce::String PluginProcessor::getProgramName (int /*index*/)
{
    return {};
}

void PluginProcessor::changeProgramName (int /*index*/, const juce::String& /*newName*/)
{
}

//==============================================================================
int PluginProcessor::getNumParameters()
{
    return k_NumOfParameters;
}

float PluginProcessor::getParameter(int index)
{
    if (index < 3) 
    {
        if (tvconv_getMaxDimension(hTVCnv, index) > tvconv_getMinDimension(hTVCnv, index))
        {
            return (tvconv_getTargetPosition(hTVCnv, index)-tvconv_getMinDimension(hTVCnv, index))/
                (tvconv_getMaxDimension(hTVCnv, index)-tvconv_getMinDimension(hTVCnv, index));
        }
    }
    if (index == k_room_size_x)
    {
        return (tvconv_getMaxDimension(hTVCnv, 0) - tvconv_getMinDimension(hTVCnv, 0));
    }
    if (index == k_room_size_y)
    {
        return (tvconv_getMaxDimension(hTVCnv, 1) - tvconv_getMinDimension(hTVCnv, 1));
    }
    if (index == k_room_size_z)
    {
        return (tvconv_getMaxDimension(hTVCnv, 2) - tvconv_getMinDimension(hTVCnv, 2));
    }

    // otherwise
    return 0.0f;
}

const String PluginProcessor::getParameterName (int index)
{
    switch (index) {
        //case k_receiverCoordX:	return "receiver_coordinate_x";
  //      case k_receiverCoordY:	return "receiver_coordinate_y";
  //      case k_receiverCoordZ:	return "receiver_coordinate_z";
		//case k_qw:				return "receiver_quaternion_w";
		//case k_qx:				return "receiver_quaternion_x";
		//case k_qy:				return "receiver_quaternion_y";
		//case k_qz:				return "receiver_quaternion_z";
		//case k_yaw:				return "receiver_yaw";
		//case k_pitch:			return "receiver_pitch";
		//case k_roll:			return "receiver_roll";
  //      case k_room_size_x:		return "room_size_x";
  //      case k_room_size_y:		return "room_size_y";
  //      case k_room_size_z:		return "room_size_z";
	
        default: return "NULL";
    }
	//return "NULL";
}

const String PluginProcessor::getParameterText(int index)
{
    if (index < 3) {
        return String(tvconv_getTargetPosition(hTVCnv, index));
    }
    else return "NULL";
}

void PluginProcessor::setParameter (int index, float newValue)
{
    DBG("param set");

	// VST parameters are in the range [0, 1]
    float newValueScaled;
    if (index < 3) {
        newValueScaled = newValue *
        (tvconv_getMaxDimension(hTVCnv, index) - tvconv_getMinDimension(hTVCnv, index)) +
        tvconv_getMinDimension(hTVCnv, index);
        if (newValueScaled != tvconv_getTargetPosition(hTVCnv, index)){
            tvconv_setTargetPosition(hTVCnv, newValueScaled, index);
            refreshWindow = true;
        }
    }
	if( index == k_qw )
	{
		newValueScaled = (newValue - 0.5) * 2.0f;
		rotator_setQuaternionW(hRot, newValueScaled);
	}
	if ( index == k_qx )
	{
		newValueScaled = (newValue - 0.5) * 2.0f;
		rotator_setQuaternionX(hRot, newValueScaled);
	}
	if ( index == k_qy )
	{
		newValueScaled = (newValue - 0.5) * 2.0f;
		rotator_setQuaternionY(hRot, newValueScaled);
	}
	if ( index == k_qz )
	{
		newValueScaled = (newValue - 0.5) * 2.0f;
		rotator_setQuaternionZ(hRot, newValueScaled);
	}
	if( index == k_yaw )
	{
		newValueScaled = ( newValue - 0.5 ) * 360.0f;
		rotator_setYaw( hRot, newValueScaled );
	}
	if( index == k_pitch )
	{	
		newValueScaled = ( newValue - 0.5 ) * 360.0f;
		rotator_setPitch( hRot, newValueScaled );
	}
	if( index == k_roll )
	{
		newValueScaled = ( newValue - 0.5 ) * 360.0f;
		rotator_setRoll( hRot, newValueScaled );
	}

	//refreshWindow = true;
}

void PluginProcessor::setParameterRaw(int index, float newValue)
{
    if (index < 3) {
        if (newValue != tvconv_getTargetPosition(hTVCnv, index)) {
            tvconv_setTargetPosition(hTVCnv, newValue, index);
            refreshWindow = true;
        }
    }
}

//==============================================================================
void PluginProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{

    nHostBlockSize = samplesPerBlock;
    nNumInputs =  getTotalNumInputChannels();
    nNumOutputs = getTotalNumOutputChannels();
    nSampleRate = (int)(sampleRate + 0.5);
    //isPlaying = false;

    tvconv_init(hTVCnv, nSampleRate, nHostBlockSize);

    int numConvolverOutputChannels = tvconv_getNumOutputChannels(hTVCnv);

    if (numConvolverOutputChannels) {
        
        int sh_order = sqrt(numConvolverOutputChannels) - 1;
        
        DBG("order");
        DBG(String(sh_order));
        rotator_setOrder(hRot, sh_order);
    }

    AudioProcessor::setLatencySamples(tvconv_getProcessingDelay(hTVCnv));
    rotator_init(hRot, (float)sampleRate);
}

void PluginProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool PluginProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void PluginProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& /*midiMessages*/)
{
    int nCurrentBlockSize = nHostBlockSize = buffer.getNumSamples();
    nNumInputs = jmin(getTotalNumInputChannels(), buffer.getNumChannels());
    nNumOutputs = jmin(getTotalNumOutputChannels(), buffer.getNumChannels());
    float** bufferData = buffer.getArrayOfWritePointers();

    tvconv_process(hTVCnv, bufferData, bufferData, nNumInputs, nNumOutputs, nCurrentBlockSize);

    if (enable_rotation) {
        float* pFrameData[MAX_NUM_CHANNELS];
        int frameSize = rotator_getFrameSize();

        if ((nCurrentBlockSize % frameSize == 0)) { /* divisible by frame size */
            for (int frame = 0; frame < nCurrentBlockSize / frameSize; frame++) {
                for (int ch = 0; ch < buffer.getNumChannels(); ch++)
                    pFrameData[ch] = &bufferData[ch][frame * frameSize];

                /* perform processing */
                rotator_process(hRot, pFrameData, pFrameData, nNumOutputs, nNumOutputs, frameSize);
            }
        }
        else
            buffer.clear();
    }

}

//==============================================================================
bool PluginProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* PluginProcessor::createEditor()
{
    return new PluginEditor (this);
}

//==============================================================================
void PluginProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    /* Create an outer XML element.. */
    XmlElement xml("TVCONVAUDIOPLUGINSETTINGS");
    xml.setAttribute("LastSofaFilePath", tvconv_getSofaFilePath(hTVCnv));
    xml.setAttribute("ReceiverX", tvconv_getTargetPosition(hTVCnv, 0));
    xml.setAttribute("ReceiverY", tvconv_getTargetPosition(hTVCnv, 1));
    xml.setAttribute("ReceiverZ", tvconv_getTargetPosition(hTVCnv, 2));

    xml.setAttribute("OSC_PORT", osc_port_ID);

    copyXmlToBinary(xml, destData);
}

void PluginProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    /* This getXmlFromBinary() function retrieves XML from the binary blob */
        std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

        if (xmlState != nullptr) {
            /* make sure that it's actually the correct XML object */
            if (xmlState->hasTagName("TVCONVAUDIOPLUGINSETTINGS")) {
     
                if(xmlState->hasAttribute("LastSofaFilePath")){
                    String directory = xmlState->getStringAttribute("LastSofaFilePath", "no_file");
                    const char* new_cstring = (const char*)directory.toUTF8();
                    tvconv_setSofaFilePath(hTVCnv, new_cstring);
                }
                if (xmlState->hasAttribute("ReceiverX")){
                    tvconv_setTargetPosition(hTVCnv,
                        (float)xmlState->getDoubleAttribute("ReceiverX"), 0);
                }
                if (xmlState->hasAttribute("ReceiverY")){
                    tvconv_setTargetPosition(hTVCnv,
                        (float)xmlState->getDoubleAttribute("ReceiverY"), 1);
                }
                if (xmlState->hasAttribute("ReceiverZ")){
                    tvconv_setTargetPosition(hTVCnv,
                        (float)xmlState->getDoubleAttribute("ReceiverZ"), 2);
                }

                if (xmlState->hasAttribute("OSC_PORT")) {
                    osc_port_ID = xmlState->getIntAttribute("OSC_PORT", DEFAULT_OSC_PORT);
                    osc.connect(osc_port_ID);
                }

                if (xmlState->hasAttribute("TBRotFlag")) {
                    DBG("flag set");
                }
                
                tvconv_refreshParams(hTVCnv);

				// Notify the host about the room size
                room_size_x->beginChangeGesture();
				room_size_x->setValueNotifyingHost( tvconv_getMaxDimension(hTVCnv, 0) - tvconv_getMinDimension(hTVCnv, 0) );
				room_size_x->endChangeGesture();
				room_size_y->beginChangeGesture();
				room_size_y->setValueNotifyingHost( tvconv_getMaxDimension(hTVCnv, 1) - tvconv_getMinDimension(hTVCnv, 1) );
				room_size_y->endChangeGesture();
				room_size_z->beginChangeGesture();
				room_size_z->setValueNotifyingHost( tvconv_getMaxDimension(hTVCnv, 2) - tvconv_getMinDimension(hTVCnv, 2) );
				room_size_z->endChangeGesture();
            }
        }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginProcessor();
}
