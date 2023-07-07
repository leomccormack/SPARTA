/* 
Copyright © 2012 NaturalPoint Inc.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License. */

#ifndef _NATUTILS_H_
#define _NATUTILS_H_

// Euler angle support copyright Ken Shoemake, 1993

typedef struct {float x, y, z, w;} Quat; /* Quaternion */
enum QuatPart {X, Y, Z, W};
typedef Quat EulerAngles;    /* (x,y,z)=ang 1,2,3, w=order code  */


// note:
/* ogl matrix representation (column-vectors):

| 1 0 0 x |  
| 0 1 0 y |
| 0 0 1 z |
| 0 0 0 1 |

= 

| [0] [4] [8]  [12] |  
| [1] [5] [9]  [13] |
| [2] [6] [10] [14] |
| [3] [7] [11] [15] |
*/
typedef float HMatrix[4][4]; /* Right-handed, for column vectors */


/*** Order type constants, constructors, extractors ***/
/* There are 24 possible conventions, designated by:    */
/*	  o EulAxI = axis used initially		    */
/*	  o EulPar = parity of axis permutation		    */
/*	  o EulRep = repetition of initial axis as last	    */
/*	  o EulFrm = frame from which axes are taken	    */
/* Axes I,J,K will be a permutation of X,Y,Z.	    */
/* Axis H will be either I or K, depending on EulRep.   */
/* Frame S takes axes from initial static frame.	    */
/* If ord = (AxI=X, Par=Even, Rep=No, Frm=S), then	    */
/* {a,b,c,ord} means Rz(c)Ry(b)Rx(a), where Rz(c)v	    */
/* rotates v around Z by c radians.			    */
#define EulFrmS	     0
#define EulFrmR	     1
#define EulFrm(ord)  ((unsigned)(ord)&1)
#define EulRepNo     0
#define EulRepYes    1
#define EulRep(ord)  (((unsigned)(ord)>>1)&1)
#define EulParEven   0
#define EulParOdd    1
#define EulPar(ord)  (((unsigned)(ord)>>2)&1)
#define EulSafe	     "\000\001\002\000"
#define EulNext	     "\001\002\000\001"
#define EulAxI(ord)  ((int)(EulSafe[(((unsigned)(ord)>>3)&3)]))
#define EulAxJ(ord)  ((int)(EulNext[EulAxI(ord)+(EulPar(ord)==EulParOdd)]))
#define EulAxK(ord)  ((int)(EulNext[EulAxI(ord)+(EulPar(ord)!=EulParOdd)]))
#define EulAxH(ord)  ((EulRep(ord)==EulRepNo)?EulAxK(ord):EulAxI(ord))
/* EulGetOrd unpacks all useful information about order simultaneously. */
#define EulGetOrd(ord,i,j,k,h,n,s,f) {unsigned o=ord;f=o&1;o>>=1;s=o&1;o>>=1;\
    n=o&1;o>>=1;i=EulSafe[o&3];j=EulNext[i+n];k=EulNext[i+1-n];h=s?k:i;}
/* EulOrd creates an order value between 0 and 23 from 4-tuple choices. */
#define EulOrd(i,p,r,f)	   (((((((i)<<1)+(p))<<1)+(r))<<1)+(f))
/* Static axes */
#define EulOrdXYZs    EulOrd(X,EulParEven,EulRepNo,EulFrmS)
#define EulOrdXYXs    EulOrd(X,EulParEven,EulRepYes,EulFrmS)
#define EulOrdXZYs    EulOrd(X,EulParOdd,EulRepNo,EulFrmS)
#define EulOrdXZXs    EulOrd(X,EulParOdd,EulRepYes,EulFrmS)
#define EulOrdYZXs    EulOrd(Y,EulParEven,EulRepNo,EulFrmS)
#define EulOrdYZYs    EulOrd(Y,EulParEven,EulRepYes,EulFrmS)
#define EulOrdYXZs    EulOrd(Y,EulParOdd,EulRepNo,EulFrmS)
#define EulOrdYXYs    EulOrd(Y,EulParOdd,EulRepYes,EulFrmS)
#define EulOrdZXYs    EulOrd(Z,EulParEven,EulRepNo,EulFrmS)
#define EulOrdZXZs    EulOrd(Z,EulParEven,EulRepYes,EulFrmS)
#define EulOrdZYXs    EulOrd(Z,EulParOdd,EulRepNo,EulFrmS)
#define EulOrdZYZs    EulOrd(Z,EulParOdd,EulRepYes,EulFrmS)
/* Rotating axes */
#define EulOrdZYXr    EulOrd(X,EulParEven,EulRepNo,EulFrmR)
#define EulOrdXYXr    EulOrd(X,EulParEven,EulRepYes,EulFrmR)
#define EulOrdYZXr    EulOrd(X,EulParOdd,EulRepNo,EulFrmR)
#define EulOrdXZXr    EulOrd(X,EulParOdd,EulRepYes,EulFrmR)
#define EulOrdXZYr    EulOrd(Y,EulParEven,EulRepNo,EulFrmR)
#define EulOrdYZYr    EulOrd(Y,EulParEven,EulRepYes,EulFrmR)
#define EulOrdZXYr    EulOrd(Y,EulParOdd,EulRepNo,EulFrmR)
#define EulOrdYXYr    EulOrd(Y,EulParOdd,EulRepYes,EulFrmR)
#define EulOrdYXZr    EulOrd(Z,EulParEven,EulRepNo,EulFrmR)
#define EulOrdZXZr    EulOrd(Z,EulParEven,EulRepYes,EulFrmR)
#define EulOrdXYZr    EulOrd(Z,EulParOdd,EulRepNo,EulFrmR)
#define EulOrdZYZr    EulOrd(Z,EulParOdd,EulRepYes,EulFrmR)

// Global Functions for Euler angles.
EulerAngles Eul_(float ai, float aj, float ah, int order);
Quat Eul_ToQuat(EulerAngles ea);
void Eul_ToHMatrix(EulerAngles ea, HMatrix M);
EulerAngles Eul_FromHMatrix(HMatrix M, int order);
EulerAngles Eul_FromQuat(Quat q, int order);


// helper routines for NatNet clients
class NATUtils
{
public:

    // networking helpers
    static int GetLocalIPAddresses(unsigned long Addresses[], int nMax);
    static int GetLocalIPAddresses2(unsigned long Addresses[], int nMax);

    // math helpers

    //////////////////////////////////////////////////////////////////////////
    /// <summary>
    /// Converts a quaternion to a rotation matrix.
    /// </summary>
    /// <param name='q'>Quaternion stored in x, y, z, w order.</param>
    /// <param name='m'>Pointer to an array of length 9. Rotation matrix
    /// is placed into this array in column major order.</param>
    //////////////////////////////////////////////////////////////////////////
    template<typename T>
    static void QaternionToRotationMatrix(T *q, T*m);

    //////////////////////////////////////////////////////////////////////////
    /// <summary>
    /// Multiplies a vector with 3 components by a 3 x 3 matrix and overwrites
    /// the input vector with the result.
    /// </summary>
    /// <param name='v'>On input a vector with 3 components. On output the 
    /// result of the multiplication.</param>
    /// <param name='m'>3 x 3 matrix stored in column major order</param>
    //////////////////////////////////////////////////////////////////////////
    template<typename T>
    static void Vec3MatrixMult(T *v, T*m);

    //////////////////////////////////////////////////////////////////////////
    /// <summary>
    /// Converts radians to degrees.
    /// </summary>
    /// <param name='fRadians'>Radians.</param>
    /// <returns>Degrees.</returns>
    //////////////////////////////////////////////////////////////////////////
    static float RadiansToDegrees(float fRadians)
    {
      return fRadians * (180.0F / 3.14159265F);
    }

};


template<typename T>
void NATUtils::QaternionToRotationMatrix(T *q, T *m)
{
  m[0] = 1-2*q[Y]*q[Y]-2*q[Z]*q[Z]; m[3] = 2*q[X]*q[Y]-2*q[W]*q[Z];   m[6] = 2*q[X]*q[Z]+2*q[W]*q[Y];
  m[1] = 2*q[X]*q[Y]+2*q[W]*q[Z];   m[4] = 1-2*q[X]*q[X]-2*q[Z]*q[Z]; m[7] = 2*q[Y]*q[Z]-2*q[W]*q[X];
  m[2] = 2*q[X]*q[Z]-2*q[W]*q[Y];   m[5] = 2*q[Y]*q[Z]+2*q[W]*q[X];   m[8] = 1-2*q[X]*q[X]-2*q[Y]*q[Y];
}


template<typename T>
void NATUtils::Vec3MatrixMult(T *v, T *m)
{
  T x = v[0]*m[0]+v[1]*m[3]+v[2]*m[6];
  T y = v[0]*m[1]+v[1]*m[4]+v[2]*m[7];
  T z = v[0]*m[2]+v[1]*m[5]+v[2]*m[8];
  v[0] = x;
  v[1] = y;
  v[2] = z;
}

#endif // _NATUTILS_H_