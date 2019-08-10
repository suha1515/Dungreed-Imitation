#pragma once
//2���� ���͸� ��Ÿ���� Ŭ����
/*
���ͳ��� ������ ��Į��� ������ִ�.
*/

class Vector2
{
public:
	static Vector2 zero;
	static Vector2 one;
	static Vector2 right;
	static Vector2 up;

	//1,2������ ���� ������ �����Ѵ� 3��° �Ķ���Ͱ� 0 �̸� begin�� ���� 1�ΰ�� end�� ����
	static Vector2 Lerp(const Vector2& begin, const Vector2& end, float ratio_);

public:
	float x;
	float y;
	float w;

public:

	Vector2() = default;
	Vector2(float tx, float ty, float tw = 1.0f) :x(tx), y(ty), w(tw) {};
	Vector2(int tx, int ty, int tw = 1) :x((int)tx), y((int)ty), w((int)tw) {};
	//����ũ��
	float Length()const
	{
		return sqrt(x*x + y*y);
	}
	//����ȭ
	void Normalize()
	{
		const float length = Length();
		x = x / length;
		y = y / length;
	}

};
//2���� ������ ���� = 2x2��Ľ� = ����纯���� ���� -> ������2 -> �ﰢ���� ����
inline float Cross2D(const Vector2& v0, const Vector2& v1, const Vector2& v2)
{
	//��Ľ� ������ �Ʒ��Ͱ��� ����
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