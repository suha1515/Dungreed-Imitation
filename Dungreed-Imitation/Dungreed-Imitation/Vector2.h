#pragma once
//2차원 벡터를 나타내는 클래스
/*
벡터끼리 덧셈과 스칼라곱 기능이있다.
*/

class Vector2
{
public:
	static Vector2 zero;
	static Vector2 one;
	static Vector2 right;
	static Vector2 up;

	//1,2번값을 선형 보간을 수행한다 3번째 파라메터가 0 이면 begin을 리턴 1인경우 end를 리턴
	static Vector2 Lerp(const Vector2& begin, const Vector2& end, float ratio_);

public:
	float x;
	float y;
	float w;

public:

	Vector2() = default;
	Vector2(float tx, float ty, float tw = 1.0f) :x(tx), y(ty), w(tw) {};
	Vector2(int tx, int ty, int tw = 1) :x((int)tx), y((int)ty), w((int)tw) {};
	//벡터크기
	float Length()const
	{
		return sqrt(x*x + y*y);
	}
	//정규화
	void Normalize()
	{
		const float length = Length();
		x = x / length;
		y = y / length;
	}

};
//2차원 벡터의 외적 = 2x2행렬식 = 평행사변형의 넓이 -> 나누기2 -> 삼각형의 넓이
inline float Cross2D(const Vector2& v0, const Vector2& v1, const Vector2& v2)
{
	//행렬식 정리시 아래와같은 수식
	return (v1.x - v0.x)*(v2.y - v0.y) - (v1.y - v0.y)*(v2.x - v0.x);
}

inline Vector2 operator+(const Vector2& lhs, const Vector2& rhs)
{
	Vector2 temp(lhs.x + rhs.x, lhs.y + rhs.y);
	return temp;
}

inline Vector2 operator*(float scalar, const Vector2& rhs)
{
	Vector2 temp(scalar*rhs.x, scalar*rhs.y);
	return temp;
}

inline Vector2 operator*(const Vector2& lhs, float scalar)
{
	Vector2 temp(scalar*lhs.x, scalar*lhs.y);
	return temp;
}
inline bool operator == (const Vector2& lhs, const Vector2& rhs)
{
	if ((lhs.x == rhs.x&&lhs.y == rhs.y))
		return true;
		return false;
}