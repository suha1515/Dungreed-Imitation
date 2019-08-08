#pragma once
inline float RadianToDegree(const float& rad)
{
	return rad*180.f / M_PI;
}
inline float DegreeToRadian(const float& degree)
{
	return degree*M_PI / 180.f;
}