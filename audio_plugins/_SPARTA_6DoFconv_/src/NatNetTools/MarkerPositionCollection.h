/* 
Copyright © 2014 NaturalPoint Inc.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License. */

#ifndef _MARKER_POSITION_COLLECTION_H_
#define _MARKER_POSITION_COLLECTION_H_

#include <tuple>

#include "NatNetTypes.h"

//////////////////////////////////////////////////////////////////////////
/// <summary>
/// Class for storing ordered marker positions which are then accessed 
/// by index. Labeled marker data can also be stored and accessed by 
/// index.
/// </summary>
//////////////////////////////////////////////////////////////////////////
class MarkerPositionCollection
{
public:
  // Limit ourselves to reasonable number of markers for example purposes.
  static const size_t MAX_MARKER_COUNT = 1000;

  //*************************************************************************
  // Constructors
  //

  //////////////////////////////////////////////////////////////////////////
  /// Default constructor. Resulting object contains no marker data.
  //////////////////////////////////////////////////////////////////////////
  MarkerPositionCollection();


  //*************************************************************************
  // Member Functions
  //

  //////////////////////////////////////////////////////////////////////////
  /// <summary>
  /// Gets the x, y, z coordinates of the ith marker. Const version.
  /// </summary>
  /// <param name='i'>Marker index. Valid value are 
  /// 0 to MarkerPositionCollection::MarkerPositionCount() - 1</param>
  /// <returns>A const ref to the (x, y, z) tuple of coordinates</returns>
  //////////////////////////////////////////////////////////////////////////
  const std::tuple<float,float,float>& GetMarkerPosition (size_t i) const { return mMarkerPositions[i]; }

  //////////////////////////////////////////////////////////////////////////
  /// <summary>
  /// Gets the x, y, z coordinates of the ith marker. Non-const version.
  /// </summary>
  /// <param name='i'>Marker index. Valid value are 
  /// 0 to MarkerPositionCollection::MarkerPositionCount() - 1</param>
  /// <returns>A ref to the (x, y, z) tuple of coordinates.</returns>
  //////////////////////////////////////////////////////////////////////////
  std::tuple<float,float,float>& GetMarkerPosition (size_t i) { return mMarkerPositions[i]; }

  //////////////////////////////////////////////////////////////////////////
  /// <summary>
  /// Gets the labeled marker data for the ith labeled marker. Const version.
  /// </summary>
  /// <param name='i'>Marker index. Valid value are 
  /// 0 to MarkerPositionCollection::LabeledMarkerPositionCount() - 1</param>
  /// <returns>Const ref to marker data structure.</returns>
  //////////////////////////////////////////////////////////////////////////
  const sMarker& GetLabeledMarker (size_t i) const { return mLabledMarkers[i]; }

  //////////////////////////////////////////////////////////////////////////
  /// <summary>
  /// Gets the labeled marker data for the ith labeled marker. Non-const version.
  /// </summary>
  /// <param name='i'>Marker index. Valid value are 
  /// 0 to MarkerPositionCollection::LabeledMarkerPositionCount() - 1</param>
  /// <returns>Ref to marker data structure.</returns>
  //////////////////////////////////////////////////////////////////////////
  sMarker& GetLabeledMarker (size_t i) { return mLabledMarkers[i]; }

  //////////////////////////////////////////////////////////////////////////
  /// <summary>
  /// Gets the number of marker positions.
  /// </summary>
  /// <returns>Number of marker positions.</returns>
  //////////////////////////////////////////////////////////////////////////
  size_t MarkerPositionCount() const { return mMarkerPositionCount; }

  //////////////////////////////////////////////////////////////////////////
  /// <summary>
  /// Gets the number of labeled markers.
  /// </summary>
  /// <returns>Number of labeled marker.</returns>
  //////////////////////////////////////////////////////////////////////////
  size_t LabeledMarkerPositionCount() const { return mLabledMarkerCount; }

  //////////////////////////////////////////////////////////////////////////
  /// <summary>Appends the given marker positions to any existing marker positions
  /// contained in self.
  /// </summary>
  /// <param name='markerData'>Array of marker x, y, z coordinates.<param>
  /// <param name='numRigidBodies'>Number of markers.</param>
  /// <remarks>The order of the marker positions is preserved.</remarks>
  //////////////////////////////////////////////////////////////////////////
  void AppendMarkerPositions(float markerData[][3], size_t numMarkers);
  
  //////////////////////////////////////////////////////////////////////////
  /// <summary>
  /// Sets marker position data. Any existing marker position data will be
  /// lost.
  /// </summar>
  /// <param name='markerData'>Array of (x, y, z) coordinates for the markers.
  /// </param>
  /// <param name='numMarkers'>Number of marker positions.<param>
  //////////////////////////////////////////////////////////////////////////
  void SetMarkerPositions(float markerData[][3], size_t numMarkers)
  {
    mMarkerPositionCount = 0;
    AppendMarkerPositions(markerData, numMarkers);
  }

  //////////////////////////////////////////////////////////////////////////
  /// <summary>
  /// Appends labeled marker data to any existing labeled marker data.
  /// </summary>
  /// <param name='markers'>Array of labeled marker data structures.</param>
  /// <param name='numMarkers'>Number of labeled markers.</param>
  //////////////////////////////////////////////////////////////////////////
  void AppendLabledMarkers(sMarker markers[], size_t numMarkers);

  //////////////////////////////////////////////////////////////////////////
  /// <summary>
  /// Sets labeled marker data. Any existing labeled marker data will be
  /// lost.
  /// </summar>
  /// <param name='markers'>Array of labeled marker data structures.</param>
  /// <param name='numMarkers'>Number of labeled markers.</param>
  //////////////////////////////////////////////////////////////////////////
  void SetLabledMarkers(sMarker markers[], size_t numMarkers) 
  { 
    mLabledMarkerCount = 0; 
    AppendLabledMarkers(markers, numMarkers);
  }

private:
  //*************************************************************************
  // Instance Variables
  //

  // Array of (x, y, z) marker positions.
  std::tuple<float,float,float> mMarkerPositions[MAX_MARKER_COUNT];
  // Number of marker positions.
  size_t mMarkerPositionCount;

  // Array of labeled marker structures.
  sMarker mLabledMarkers[MAX_MARKER_COUNT];
  // Number of labeled marker structures.
  size_t mLabledMarkerCount;
};

#endif // _MARKER_POSITION_COLLECTION_H_