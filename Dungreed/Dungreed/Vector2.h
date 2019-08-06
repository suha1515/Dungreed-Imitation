#pragma once
//2���� ���͸� ��Ÿ���� Ŭ����
/*
���ͳ��� ������ ��Į��� ������ִ�.
*/

class CVector2
{
public:
	static CVector2 zero;
	static CVector2 one;
	static CVector2 right;
	static CVector2 up;

	//1,2������ ���� ������ �����Ѵ� 3��° �Ķ���Ͱ� 0 �̸� begin�� ���� 1�ΰ�� end�� ����
	static CVector2 Lerp(const CVector2& begin, const CVector2& end, float ratio_);

public:
	float x;
	float y;
	float w;

public:

	CVector2() = default;
	CVector2(float tx, float ty, float tw = 1.0f) :x(tx), y(ty), w(tw) {};
	CVector2(int tx, int ty, int tw = 1) :x((int)tx), y((int)ty), w((int)tw) {};
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
inline float Cross2D(const CVector2& v0, const CVector2& v1, const CVector2& v2)
{
	//��Ľ� ������ �Ʒ��Ͱ��� ����
	return (v1.x - v0.x)*(v2.y - v0.y) - (v1.y - v0.y)*(v2.x - v0.x);
}

inline CVector2 operator+(const CVector2& lhs, const CVector2& rhs)
{
	CVector2 temp(lhs.x + rhs.x, lhs.y + rhs.y);
	return temp;
}

inline CVector2 operator*(float scalar, const CVector2& rhs)
{
	CVector2 temp(scalar*rhs.x, scalar*rhs.y);
	return temp;
}

inline CVector2 operator*(const CVector2& lhs, float scalar)
{
	CVector2 temp(scalar*lhs.x, scalar*lhs.y);
	return temp;
}