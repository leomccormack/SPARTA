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

#include "RigidBodyCollection.h"

//////////////////////////////////////////////////////////////////////////
// RigidBodyCollection implementation
//////////////////////////////////////////////////////////////////////////


RigidBodyCollection::RigidBodyCollection()
  :mNumRigidBodies(0)
{
  ;
}

void RigidBodyCollection::AppendRigidBodyData(sRigidBodyData const * const rigidBodyData, size_t numRigidBodies)
{
    for (size_t i = 0; i < numRigidBodies; ++i)
    {
      const sRigidBodyData& rb = rigidBodyData[i];
      mXYZCoord[i + mNumRigidBodies] = std::make_tuple(rb.x, rb.y, rb.z);

      mXYZWQuats[i + mNumRigidBodies] = std::make_tuple(rb.qx, rb.qy, rb.qz, rb.qw);
      mIds[i + mNumRigidBodies] = rb.ID;
    }
    mNumRigidBodies += numRigidBodies;
}
