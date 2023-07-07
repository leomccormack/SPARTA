#pragma once
#include <tuple>
class TransformedData
{
public:
	TransformedData();

	float x;
	float y;
	float z;
	float yaw;
	float pitch;
	float roll;

	void setFromBodyData(
		std::tuple<float, float, float> coords,
		std::tuple<float, float, float, float> quat,
		int upAxis
	);
};

