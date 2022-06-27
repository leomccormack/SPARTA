#include "MathUtils.h"
#include <cmath>

void ConvertRHSPosZupToYUp(float& x, float& y, float& z)
{
    /*
    [RHS, Y-Up]     [RHS, Z-Up]

                          Y
     Y                 Z /
     |__ X             |/__ X
     /
    Z

    Xyup  =  Xzup
    Yyup  =  Zzup
    Zyup  =  -Yzup
    */
    float yOriginal = y;
    y = z;
    z = -yOriginal;
}

void ConvertRHSRotZUpToYUp(float& qx, float& qy, float& qz, float& qw)
{
    // -90 deg rotation about +X
    float qRx, qRy, qRz, qRw;
    float angle = -90.0f * MATH_PI / 180.0f;
    qRx = sin(angle / 2.0f);
    qRy = 0.0f;
    qRz = 0.0f;
    qRw = cos(angle / 2.0f);

    // rotate quat using quat multiply
    float qxNew, qyNew, qzNew, qwNew;
    qxNew = qw * qRx + qx * qRw + qy * qRz - qz * qRy;
    qyNew = qw * qRy - qx * qRz + qy * qRw + qz * qRx;
    qzNew = qw * qRz + qx * qRy - qy * qRx + qz * qRw;
    qwNew = qw * qRw - qx * qRx - qy * qRy - qz * qRz;

    qx = qxNew;
    qy = qyNew;
    qz = qzNew;
    qw = qwNew;
}
