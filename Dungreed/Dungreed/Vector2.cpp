#include "stdafx.h"
#include "Vector2.h"

CVector2 CVector2::zero = CVector2(0, 0);
CVector2 CVector2::one = CVector2(1, 1);
CVector2 CVector2::right = CVector2(1, 0);
CVector2 CVector2::up = CVector2(0, 1);

CVector2 CVector2::Lerp(const CVector2& begin, const CVector2& end, float ratio_)
{
	//__min�� __max�� ��ó���� ��ũ���̴� 
	//__max���� ratio�� 0�� ���Ͽ� ū���ڸ� ��ȯ�ϰ�
	// __min���� �μ��ڿ� ���Ͽ� �������� ��ȯ�Ѵ�. ratio�� 1�� ��� ��� 1
	float ratio = __min(1, __max(0, ratio_));
	CVector2 temp;
	//ex begin (2,3) end( 4,4) ratio = 0.5f
	//temp.x  = 2 + (4-2) * 0.5f = 3
	//temp.y  = 3 + (4-3) * 0.5f = 3.5
	//0.5 �� ��Ȯ�� ���̴ϱ� ���� ���� ���ʹ� 6,7�� ���� 3,3.5�� �´�
	temp.x = begin.x + (end.x - begin.x) * ratio;
	temp.y = begin.y + (end.y - begin.y) * ratio;
	return temp;
}