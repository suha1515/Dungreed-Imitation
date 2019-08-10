#include "stdafx.h"
#include "Vector2.h"

Vector2 Vector2::zero = Vector2(0, 0);
Vector2 Vector2::one = Vector2(1, 1);
Vector2 Vector2::right = Vector2(1, 0);
Vector2 Vector2::up = Vector2(0, 1);

Vector2 Vector2::Lerp(const Vector2& begin, const Vector2& end, float ratio_)
{
	//__min�� __max�� ��ó���� ��ũ���̴� 
	//__max���� ratio�� 0�� ���Ͽ� ū���ڸ� ��ȯ�ϰ�
	// __min���� �μ��ڿ� ���Ͽ� �������� ��ȯ�Ѵ�. ratio�� 1�� ��� ��� 1
	float ratio = __min(1, __max(0, ratio_));
	Vector2 temp;
	//ex begin (2,3) end( 4,4) ratio = 0.5f
	//temp.x  = 2 + (4-2) * 0.5f = 3
	//temp.y  = 3 + (4-3) * 0.5f = 3.5
	//0.5 �� ��Ȯ�� ���̴ϱ� ���� ���� ���ʹ� 6,7�� ���� 3,3.5�� �´�
	temp.x = begin.x + (end.x - begin.x) * ratio;
	temp.y = begin.y + (end.y - begin.y) * ratio;
	return temp;
}