/*
 ==============================================================================
 This file is part of the IEM plug-in suite.
 Author: Daniel Rudrich
 Copyright (c) 2017 - Institute of Electronic Music and Acoustics (IEM)
 https://iem.at

 The IEM plug-in suite is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 The IEM plug-in suite is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this software.  If not, see <https://www.gnu.org/licenses/>.
 ==============================================================================
 */

#pragma once

#ifndef CONFIGURATIONHELPER_ENABLE_MATRIX_METHODS
    #define CONFIGURATIONHELPER_ENABLE_MATRIX_METHODS 0
#endif

#ifndef CONFIGURATIONHELPER_ENABLE_DECODER_METHODS
    #define CONFIGURATIONHELPER_ENABLE_DECODER_METHODS 0
#endif

#ifndef CONFIGURATIONHELPER_ENABLE_LOUDSPEAKERLAYOUT_METHODS
    #define CONFIGURATIONHELPER_ENABLE_LOUDSPEAKERLAYOUT_METHODS 0
#else
    #undef CONFIGURATIONHELPER_ENABLE_GENERICLAYOUT_METHODS
    #define CONFIGURATIONHELPER_ENABLE_GENERICLAYOUT_METHODS 1
#endif

#ifndef CONFIGURATIONHELPER_ENABLE_GENERICLAYOUT_METHODS
    #define CONFIGURATIONHELPER_ENABLE_GENERICLAYOUT_METHODS 0
#endif

#ifndef CONFIGURATIONHELPER_ENABLE_ALL_METHODS
    #define CONFIGURATIONHELPER_ENABLE_ALL_METHODS 0
#endif


#if CONFIGURATIONHELPER_ENABLE_DECODER_METHODS
    #undef CONFIGURATIONHELPER_ENABLE_MATRIX_METHODS
    #define CONFIGURATIONHELPER_ENABLE_MATRIX_METHODS 1
#endif

#if CONFIGURATIONHELPER_ENABLE_ALL_METHODS
    #undef CONFIGURATIONHELPER_ENABLE_MATRIX_METHODS
    #define CONFIGURATIONHELPER_ENABLE_MATRIX_METHODS 1

    #undef CONFIGURATIONHELPER_ENABLE_DECODER_METHODS
    #define CONFIGURATIONHELPER_ENABLE_DECODER_METHODS 1

    #undef CONFIGURATIONHELPER_ENABLE_LOUDSPEAKERLAYOUT_METHODS
    #define CONFIGURATIONHELPER_ENABLE_LOUDSPEAKERLAYOUT_METHODS 1
    
    #undef CONFIGURATIONHELPER_ENABLE_GENERICLAYOUT_METHODS
    #define CONFIGURATIONHELPER_ENABLE_GENERICLAYOUT_METHODS 1
#endif

#if CONFIGURATIONHELPER_ENABLE_MATRIX_METHODS
    #include "ReferenceCountedMatrix.h"
#endif

#if CONFIGURATIONHELPER_ENABLE_DECODER_METHODS
    #include "ReferenceCountedDecoder.h"
#endif
//==============================================================================
/**
 This class contains some helper-functions for loading / storing Decoders, Matrices and LoudspeakerLayouts from / as JSON configuration files.
 This file should be included into a JUCE project as it has JUCE dependencies.
 */

class ConfigurationHelper
{
public:

    // =============== IMPORT ======================================================
    /**
     Loads a JSON-file (fileToParse) and writes the parsed content to a var object (dest).
     */
    static Result parseFile (const File& fileToParse, var& dest)
    {
        if (!fileToParse.exists())
            return Result::fail ("File '" + fileToParse.getFullPathName() + "' does not exist!");

        String jsonString = fileToParse.loadFileAsString();
        Result result = JSON::parse (jsonString, dest);
        if (!result.wasOk())
            return Result::fail ("File '" + fileToParse.getFullPathName() + "' could not be parsed:\n" + result.getErrorMessage());

        return Result::ok();
    }

#if CONFIGURATIONHELPER_ENABLE_MATRIX_METHODS
    /**
     Loads a JSON-file (fileToParse) and tries to parse for a TransformationMatrix object. If successful, writes the matrix into the destination (dest).
     */
    static Result parseFileForTransformationMatrix (const File& fileToParse, ReferenceCountedMatrix::Ptr* dest)
    {
        jassert (dest != nullptr);

        // parsing configuration file
        var parsedJson;
        {
            Result result = parseFile (fileToParse, parsedJson);
            if (! result.wasOk())
                return Result::fail(result.getErrorMessage());
        }

        // looking for a 'TransformationMatrix' object
        var tmVar = parsedJson.getProperty("TransformationMatrix", parsedJson);
        Result result = convertTransformationMatrixVarToMatrix (tmVar, dest,
                                                         parsedJson.getProperty("Name", var("")), parsedJson.getProperty("Description", var("")));

        if (! result.wasOk())
            return Result::fail (result.getErrorMessage());

        return Result::ok();
    }

    /**
     Converts the Matrix object within a TransformationMatrix var object (tmVar) to a ReferenceCountedMatrix (matrix).
     */
    static Result convertTransformationMatrixVarToMatrix (var& tmVar, ReferenceCountedMatrix::Ptr* matrix, var nameFallback = var (""), var descriptionFallback = var (""))
    {
        jassert (matrix != nullptr);

        String name = tmVar.getProperty (Identifier ("Name"), nameFallback);
        String description = tmVar.getProperty (Identifier ("Description"), descriptionFallback);

        if (! tmVar.hasProperty ("Matrix"))
            return Result::fail ("There is no 'Matrix' array.");

        int rows, cols;
        var matrixData = tmVar.getProperty ("Matrix", var());
        Result result = getMatrixDataSize (matrixData, rows, cols);

        if (! result.wasOk())
            return Result::fail(result.getErrorMessage());

        ReferenceCountedMatrix::Ptr newMatrix = new ReferenceCountedMatrix (name, description, rows, cols);
        result = getMatrix(matrixData, rows, cols, newMatrix->getMatrix());

        if (! result.wasOk())
            return Result::fail (result.getErrorMessage());

        *matrix = newMatrix;
        return Result::ok();
    }

    /**
     Converts a 'Matrix' var object to a Matrix<float> object.
     */
    static Result getMatrix (var&  matrixData, const int rows, const int cols, Matrix<float>& dest)
    {
        for (int r = 0; r < rows; ++r)
        {
            var rowVar = matrixData.getArray()->getUnchecked(r);
            if (rowVar.size() != cols)
                return Result::fail("Matrix row " + String(r+1) + " has wrong length (should be " + String(cols) + ").");

            for (int c = 0; c < cols; ++c)
            {
                var colVar = rowVar.getArray()->getUnchecked(c);
                if (colVar.isDouble() || colVar.isInt())
                {
                    dest(r, c) = colVar;
                }
                else
                    return Result::fail("Datatype of matrix element (" + String(r+1) + "," + String(c+1) + ") could not be parsed.");
            }

        }
        return Result::ok();
    }

    /**
     Extracts the number of rows and columns out of a 'Matrix' var object.
     */
    static Result getMatrixDataSize (var& matrixData, int& rows, int& cols)
    {
        rows = matrixData.size();
        cols = matrixData.getArray()->getUnchecked(0).size();

        return Result::ok();
    }

    

#endif // #if CONFIGURATIONHELPER_ENABLE_MATRIX_METHODS

#if CONFIGURATIONHELPER_ENABLE_DECODER_METHODS
    /**
     Converts a Decoder var object (decoderVar) to a ReferenceCountedDecoder (decoder).
     */
    static Result DecoderVar (var& decoderVar, ReferenceCountedDecoder::Ptr* decoder, var nameFallback = var (""), var descriptionFallback = var (""))
    {
        jassert (decoder != nullptr);

        String name = decoderVar.getProperty (Identifier("Name"), nameFallback);
        String description = decoderVar.getProperty (Identifier ("Description"), descriptionFallback);

        if (! decoderVar.hasProperty ("Matrix"))
            return Result::fail ("There is no 'Matrix' array within the 'Decoder' object.");

        // get matrix size
        int rows, cols;
        var matrixData = decoderVar.getProperty ("Matrix", var());
        Result result = getMatrixDataSize (matrixData, rows, cols);
        if (! result.wasOk())
            return Result::fail (result.getErrorMessage());

        //check if cols is a valid number of Ambisonic channels
        const int decoderOrder = sqrt (cols) - 1;
        if (cols != square (decoderOrder + 1))
            return Result::fail ("Decoder matrix's number of columns is no valid Ambisonic channel count: nCh = (order+1)^2.");

        // create decoder and get matrix from 'Decoder' object
        ReferenceCountedDecoder::Ptr newDecoder = new ReferenceCountedDecoder (name, description, rows, cols);
        result = getMatrix (matrixData, rows, cols, newDecoder->getMatrix());
        if (! result.wasOk())
            return Result::fail (result.getErrorMessage());

        if (decoderVar.hasProperty ("Routing"))
        {
            var routingData = decoderVar.getProperty ("Routing", var());
            result = getRoutingArray (routingData, rows, newDecoder);
            if (! result.wasOk())
                return Result::fail (result.getErrorMessage());
        }


        // ============ SETTINGS =====================
        ReferenceCountedDecoder::Settings settings;
        // normalization
        if (! decoderVar.hasProperty ("ExpectedInputNormalization"))
            Result::fail ("Could not find 'ExpectedInputNormalization' attribute.");


        var expectedNormalization (decoderVar.getProperty ("ExpectedInputNormalization", var()));
        if (expectedNormalization.toString().equalsIgnoreCase ("sn3d"))
            settings.expectedNormalization = ReferenceCountedDecoder::Normalization::sn3d;
        else if (expectedNormalization.toString().equalsIgnoreCase ("n3d"))
            settings.expectedNormalization = ReferenceCountedDecoder::Normalization::n3d;
        else
            return Result::fail ("Could not parse 'ExpectedInputNormalization' attribute. Expected 'sn3d' or 'n3d' but got '" + expectedNormalization.toString() + "'.");


        // weights
        if (decoderVar.hasProperty("Weights"))
        {
            var weights (decoderVar.getProperty ("Weights", var()));
            if (weights.toString().equalsIgnoreCase ("maxrE"))
                settings.weights = ReferenceCountedDecoder::Weights::maxrE;
            else if (weights.toString().equalsIgnoreCase ("inPhase"))
                settings.weights = ReferenceCountedDecoder::Weights::inPhase;
            else if (weights.toString().equalsIgnoreCase ("none"))
                settings.weights = ReferenceCountedDecoder::Weights::none;
            else
                return Result::fail("Could not parse 'Weights' attribute. Expected 'maxrE', 'inPhase' or 'none' but got '" + weights.toString() + "'.");
        }

        // weights already applied
        if (decoderVar.hasProperty ("WeightsAlreadyApplied"))
        {
            var weightsAlreadyApplied (decoderVar.getProperty ("WeightsAlreadyApplied", var()));
            if (weightsAlreadyApplied.isBool())
                settings.weightsAlreadyApplied = weightsAlreadyApplied;
            else
                return Result::fail ("Could not parse 'WeightsAlreadyApplied' attribute. Expected bool but got '" + weightsAlreadyApplied.toString() + "'.");
        }
        if (decoderVar.hasProperty ("SubwooferChannel"))
        {
            var subwooferChannel (decoderVar.getProperty ("SubwooferChannel", var()));
            if (subwooferChannel.isInt())
            {
                if (static_cast<int>(subwooferChannel) < 1 || static_cast<int>(subwooferChannel) > 64)
                    return Result::fail ("'SubwooferChannel' attribute is not a valid channel number (1 <= subwooferChannel <= 64).");

                settings.subwooferChannel = subwooferChannel;
            }
            else
                return Result::fail("Could not parse 'SubwooferChannel' attribute. Expected channel number (int) but got '" + subwooferChannel.toString() + "'.");
        }

        newDecoder->setSettings(settings);

        *decoder = newDecoder;
        return Result::ok();
    }


    /**
     Extracts the routing array from a 'Routing' Var object and writes it to the ReferenceCountedMatrix object.
     */
    static Result getRoutingArray (var& routingData, const int rows, ReferenceCountedMatrix::Ptr dest)
    {
        if (routingData.size() != rows)
            return Result::fail("Length of 'Routing' attribute does not match number of matrix outputs (rows).");

        Array<int>& routingArray = dest->getRoutingArrayReference();
        for (int r = 0; r < rows; ++r)
        {
            var element = routingData.getArray()->getUnchecked(r);

            if (element.isInt())
            {
                routingArray.set(r, (int) element - 1);
            }
            else
                return Result::fail("Datatype of 'Routing' element at position " + String(r+1) + " could not be interpreted (expected integer).");
        }
        return Result::ok();
    }

    /**
     Loads a JSON-file (fileToParse) and tries to parse for a 'Decoder' object. If successful, writes the decoder into the destination (decoder).
     */
    static Result parseFileForDecoder (const File& fileToParse, ReferenceCountedDecoder::Ptr* decoder)
    {
        jassert (decoder != nullptr);

        // parsing configuration file
        var parsedJson;
        Result result = parseFile (fileToParse, parsedJson);
        if (! result.wasOk())
            return Result::fail (result.getErrorMessage());

        // looking for a 'Decoder' object
        if (! parsedJson.hasProperty ("Decoder"))
            return Result::fail ("No 'Decoder' object found in the configuration file.");

        var decoderObject = parsedJson.getProperty ("Decoder", parsedJson);
        result = DecoderVar (decoderObject, decoder,
                                         parsedJson.getProperty ("Name", var("")), parsedJson.getProperty ("Description", var("")));

        if (! result.wasOk())
            return Result::fail (result.getErrorMessage());

        return Result::ok();
    }

#endif //#if CONFIGURATIONHELPER_ENABLE_DECODER_METHODS

#if CONFIGURATIONHELPER_ENABLE_LOUDSPEAKERLAYOUT_METHODS
    /**
     Loads a JSON-file (fileToParse) and tries to parse for a 'LoudspeakerLayout' object. If successful, writes the loudspeakers (named 'elements') into a ValeTree object (loudspeakers). Set 'undoManager' to nullptr in case you don't want to use a undoManager.
     */
    static Result parseFileForLoudspeakerLayout (const File& fileToParse, ValueTree& loudspeakers, UndoManager* undoManager)
    {
        return parseFileForGenericLayout(fileToParse, loudspeakers, undoManager);
    }

#endif // #if CONFIGURATIONHELPER_ENABLE_LOUDSPEAKERLAYOUT_METHODS
    
#if CONFIGURATIONHELPER_ENABLE_GENERICLAYOUT_METHODS
    /**
     Loads a JSON-file (fileToParse) and tries to parse for a 'LoudspeakerLayout' or 'GenericLayout' object. If successful, writes the generic object into a ValueTree object (elements). Set 'undoManager' to nullptr in case you don't want to use a undoManager.
     */
    static Result parseFileForGenericLayout (const File& fileToParse, ValueTree& elements, UndoManager* undoManager)
    {
        // parse configuration file
        var parsedJson;
        Result result = parseFile (fileToParse, parsedJson);
        if (! result.wasOk())
            return Result::fail (result.getErrorMessage());
        
        // looks for a 'GenericLayout' or 'LoudspeakerLayout' object
        var genericLayout;
        if (parsedJson.hasProperty ("GenericLayout"))
            genericLayout = parsedJson.getProperty ("GenericLayout", var());
        else if (parsedJson.hasProperty ("LoudspeakerLayout"))
            genericLayout = parsedJson.getProperty ("LoudspeakerLayout", var());
        else
            return Result::fail ("No 'GenericLayout' or 'LoudspeakerLayout' object found in the configuration file.");
        
        // looks for a 'GenericLayout' or 'LoudspeakerLayout' object
        var elementArray;
        if (genericLayout.hasProperty ("Elements"))
            elementArray = genericLayout.getProperty ("Elements", var());
        else if (genericLayout.hasProperty ("Loudspeakers"))
            elementArray = genericLayout.getProperty ("Loudspeakers", var());
        else
            return Result::fail ("No 'Elements' or 'Loudspeakers' attribute found within the 'GenericLayout' or 'LoudspeakerLayout' object.");
        
        result = addElementsToValueTree (elementArray, elements, undoManager);
        
        if (! result.wasOk())
            return Result::fail (result.getErrorMessage());
        
        return Result::ok();
    }
    
    /**
     Appends all elements within the GenericLayout to the elements ValueTree.
     */
    static Result addElementsToValueTree (var& elementArray, ValueTree& elements, UndoManager* undoManager)
    {
        if (! elementArray.isArray())
            return Result::fail ("'elementArray' is not an array.");
        
        const int nElements = elementArray.size();
        
        for (int i = 0; i < nElements; ++i)
        {
            var& element = elementArray[i];
            float azimuth, elevation, distance, gain;
            int channel;
            bool isImaginary;
            
            if (! element.hasProperty ("Azimuth"))
                return Result::fail ("No 'Azimuth' attribute for element #" + String (i+1) + ".");
            var azi = element.getProperty ("Azimuth", var());
            if (azi.isDouble() || azi.isInt())
                azimuth = azi;
            else
                return Result::fail ("Wrong datatype for attribute 'Azimuth' for element #" + String (i+1) + ".");
            
            if (! element.hasProperty ("Elevation"))
                return Result::fail ("No 'Elevation' attribute for element #" + String (i+1) + ".");
            var ele = element.getProperty ("Elevation", var());
            if (ele.isDouble() || ele.isInt())
                elevation = ele;
            else
                return Result::fail ("Wrong datatype for attribute 'Elevation' for element #" + String (i+1) + ".");
            
            if (! element.hasProperty ("Distance"))
                return Result::fail ("No 'Distance' attribute for element #" + String (i+1) + ".");
            var dist = element.getProperty ("Distance", var());
            if (dist.isDouble() || dist.isInt())
                distance = dist;
            else
                return Result::fail("Wrong datatype for attribute 'Distance' for element #" + String (i+1) + ".");
            
            if (! element.hasProperty ("Gain"))
                return Result::fail ("No 'Gain' attribute for element #" + String (i+1) + ".");
            var g = element.getProperty ("Gain", var());
            if (g.isDouble() || g.isInt())
                gain = g;
            else
                return Result::fail ("Wrong datatype for attribute 'Gain' for element #" + String (i+1) + ".");
            
            if (! element.hasProperty ("Channel"))
                return Result::fail ("No 'Channel' attribute for element #" + String (i+1) + ".");
            var ch = element.getProperty ("Channel", var());
            if (ch.isInt())
                channel = ch;
            else
                return Result::fail ("Wrong datatype for attribute 'Channel' for element #" + String (i+1) + ".");
            
            if (! element.hasProperty ("IsImaginary"))
                return Result::fail ("No 'IsImaginary' attribute for element #" + String(i+1) + ".");
            var im = element.getProperty ("IsImaginary", var());
            if (im.isBool())
                isImaginary = im;
            else
                return Result::fail ("Wrong datatype for attribute 'IsImaginary' for element #" + String (i+1) + ".");

            elements.appendChild (createElement(azimuth, elevation, distance, channel, isImaginary, gain), undoManager);
        }
        
        return Result::ok();
    }
    
    /**
     Creates a single element ValueTree, which can be appended to another ValueTree holding several elements.
     */
    static ValueTree createElement (const float azimuth, const float elevation, const float distance, const int channel, const bool isImaginary, const float gain)
    {
        ValueTree newElement ("Element");
        
        newElement.setProperty ("Azimuth", azimuth, nullptr);
        newElement.setProperty ("Elevation", elevation, nullptr);
        newElement.setProperty ("Distance", distance, nullptr);
        newElement.setProperty ("Channel", channel, nullptr);
        newElement.setProperty ("Imaginary", isImaginary, nullptr);
        newElement.setProperty ("Gain", gain, nullptr);
        
        return newElement;
    }
    
#endif // #if CONFIGURATIONHELPER_ENABLE_GENERICLAYOUT_METHODS

#if CONFIGURATIONHELPER_ENABLE_DECODER_METHODS
    // =============== EXPORT ======================================================
    /**
     Converts a ReferenceCountedDecoder object to a var object. Useful for writing the Decoder to a configuration file.
     */
    static var convertDecoderToVar (ReferenceCountedDecoder::Ptr& decoder)
    {
        if (decoder == nullptr)
            return var();

        DynamicObject* obj = new DynamicObject();
        obj->setProperty ("Name", decoder->getName());
        obj->setProperty ("Description", decoder->getDescription());

        ReferenceCountedDecoder::Settings settings = decoder->getSettings();

        obj->setProperty ("ExpectedInputNormalization", settings.expectedNormalization == ReferenceCountedDecoder::n3d ? "n3d" : "sn3d");

        obj->setProperty ("Weights", settings.weights == ReferenceCountedDecoder::maxrE ? "maxrE" : settings.weights == ReferenceCountedDecoder::inPhase ? "inPhase" : "none");
        obj->setProperty ("WeightsAlreadyApplied", var(settings.weightsAlreadyApplied));

        const int subwooferChannel = settings.subwooferChannel;
        if (subwooferChannel > 0)
          obj->setProperty ("SubwooferCHannel", subwooferChannel);

        // decoder matrix
        var decoderMatrix = convertMatrixToVar (decoder->getMatrix());
        obj->setProperty ("Matrix", decoderMatrix);

        // routing array
        var routing;
        Array<int>& routingArray = decoder->getRoutingArrayReference();
        for (int i = 0; i < routingArray.size(); ++i)
            routing.append(routingArray[i] + 1); // one count
        
        obj->setProperty ("Routing", routing);

        return var(obj);
    }

#endif // #if CONFIGURATIONHELPER_ENABLE_DECODER_METHODS

#if CONFIGURATIONHELPER_ENABLE_MATRIX_METHODS
    /**
     Converts a Matrix<float> object to a var object.
     */
    static var convertMatrixToVar (Matrix<float>& mat)
    {
        var matrixVar;
        for (int m = 0; m < mat.getSize()[0]; ++m)
        {
            var row;
            for (int n = 0; n < mat.getSize()[1]; ++n)
            {
                row.append(mat(m,n));
            }
            matrixVar.append(row);
        }
        return matrixVar;
    }

    /**
     Converts a ReferenceCountedMatrix object to a var object. Useful for writing the Matrix to a configuration file.
     */
    static var convertTransformationMatrixToVar (ReferenceCountedMatrix::Ptr& matrix)
    {
        if (matrix == nullptr)
            return var();

        DynamicObject* obj = new DynamicObject();
        obj->setProperty ("Name", matrix->getName());
        obj->setProperty ("Description", matrix->getDescription());

        var transformationMatrix = convertMatrixToVar (matrix->getMatrix());

        obj->setProperty ("Matrix", transformationMatrix);
        return var(obj);
    }

#endif // #if CONFIGURATIONHELPER_ENABLE_MATRIX_METHODS

#if CONFIGURATIONHELPER_ENABLE_LOUDSPEAKERLAYOUT_METHODS
    /**
     Converts a loudspeakers ValueTree object to a var object. Useful for writing the loudspeakers to a configuration file ('LoudspeakerLayout'). Make sure the ValueTree contains valid loudspeakers.
     */
    static var convertLoudspeakersToVar (ValueTree& loudspeakers, String name = "", String description = "")
    {
        DynamicObject* obj = new DynamicObject(); // loudspeaker layout object
        if (! name.isEmpty())
            obj->setProperty("Name", name);
        if (! description.isEmpty())
            obj->setProperty("Description", description);

        var loudspeakerArray;

        for (ValueTree::Iterator it = loudspeakers.begin() ; it != loudspeakers.end(); ++it)
        {
            DynamicObject* loudspeaker = new DynamicObject(); // loudspeaker which get's added to the loudspeakerArray var

            loudspeaker->setProperty ("Azimuth", (*it).getProperty ("Azimuth"));
            loudspeaker->setProperty ("Elevation", (*it).getProperty ("Elevation"));
            loudspeaker->setProperty ("Distance", (*it).getProperty ("Distance"));
            loudspeaker->setProperty ("IsImaginary", (*it).getProperty("Imaginary"));
            loudspeaker->setProperty ("Channel", (*it).getProperty("Channel"));
            loudspeaker->setProperty ("Gain", (*it).getProperty("Gain"));

            loudspeakerArray.append(var(loudspeaker));
        }

        obj->setProperty("Loudspeakers", loudspeakerArray);
        return var(obj);
    }

#endif //#if CONFIGURATIONHELPER_ENABLE_LOUDSPEAKERLAYOUT_METHODS
    
#if CONFIGURATIONHELPER_ENABLE_GENERICLAYOUT_METHODS
    /**
     Converts a elements ValueTree object to a var object. Useful for writing the sources to a configuration file ('GenericLayout'). Make sure the ValueTree contains valid elements.
     */
    static var convertElementsToVar (ValueTree& elements, String name = "", String description = "")
    {
        DynamicObject* obj = new DynamicObject();  
        if (! name.isEmpty())
            obj->setProperty("Name", name);
        if (! description.isEmpty())
            obj->setProperty("Description", description);
        
        var elementArray;
        
        for (ValueTree::Iterator it = elements.begin() ; it != elements.end(); ++it)
        {
            DynamicObject* element = new DynamicObject();
            
            element->setProperty ("Azimuth", (*it).getProperty ("Azimuth"));
            element->setProperty ("Elevation", (*it).getProperty ("Elevation"));
            element->setProperty ("Distance", (*it).getProperty ("Distance"));
            element->setProperty ("IsImaginary", (*it).getProperty("Imaginary"));
            element->setProperty ("Channel", (*it).getProperty("Channel"));
            element->setProperty ("Gain", (*it).getProperty("Gain"));
            
            elementArray.append(var(element));
        }
        
        obj->setProperty("Elements", elementArray);
        return var(obj);
    }
    
#endif //#if CONFIGURATIONHELPER_ENABLE_GENERICLAYOUT_METHODS
    
    /**
     Writes a configuration var to a JSON file.
     Example use-case:
        DynamicObject* configuration = new DynamicObject();
        configuration->setProperty("Name", var("Configuration Name"));
        configuration->setProperty("Description", var("Description"));
        configuration->setProperty ("Decoder", ConfigurationHelper::convertDecoderToVar (referenceCountedDecoder));
        configuration->setProperty ("LoudspeakerLayout", ConfigurationHelper::convertLoudspeakersToVar (loudspeakersValueTree));
        ConfigurationHelper::writeConfigurationToFile (fileName, var (configuration));
     */
    static Result writeConfigurationToFile (File& fileToWrite, var configuration)
    {
        String jsonString = JSON::toString (configuration);
        if (fileToWrite.replaceWithText (jsonString))
            return Result::ok();
        else
            return Result::fail ("Writing configuration failed.");
    }
};
