#pragma once
template <typename T>
void SafeDelete(T& ptr)
{
	if (ptr)
	{
		delete ptr;
		ptr = nullptr;
	}
}

template <typename T>
void SafeDelete_Array(T& ptr)
{
	if (ptr)
	{
		delete[] ptr;
		ptr = nullptr;
	}
}

inline float GetAngle(const Vector2& pStart,const Vector2& pEnd)
{
	float dx = pEnd.x - pStart.x;
	float dy = pEnd.y - pStart.y;

	return RadianToDegree(atan2f(dy, dx));
}