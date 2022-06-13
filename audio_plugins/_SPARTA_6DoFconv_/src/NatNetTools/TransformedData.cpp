#include "TransformedData.h"
#include "MathUtils.h"
#include "NATUtils.h"

TransformedData::TransformedData() {
	this->x = 0.0;
	this->y = 0.0;
	this->z = 0.0;
	this->yaw = 0.0;
	this->pitch = 0.0;
	this->roll = 0.0;
}

void TransformedData::setFromBodyData(
	std::tuple<float, float, float> coords,
	std::tuple<float, float, float, float> quat,
	int upAxis
) {
	std::tie(this->x, this->y, this->z) = coords;
	Quat q{};
	std::tie(q.x, q.y, q.z, q.w) = quat;

	// If Motive is streaming Z-up, convert to this renderer's Y-up coordinate system
	if (upAxis == 2) {
		// convert position
		// ConvertRHSPosZupToYUp(this->x, this->y, this->z);

		// convert orientation
		ConvertRHSRotZUpToYUp(q.x, q.y, q.z, q.w);
	}

	// Convert Motive quaternion output to Euler angles
	// Motive coordinate conventions : X(Pitch), Y(Yaw), Z(Roll), Relative, RHS

	//der = EulOrdXYZr; / was not correct
	int order = EulOrdZYXr;

	EulerAngles ea = Eul_FromQuat(q, order);

	ea.x = NATUtils::RadiansToDegrees(ea.x);
	ea.y = NATUtils::RadiansToDegrees(ea.y);
	ea.z = NATUtils::RadiansToDegrees(ea.z);

	this->yaw = ea.x;
	this->pitch = ea.y;
	this->roll = ea.z;
}

