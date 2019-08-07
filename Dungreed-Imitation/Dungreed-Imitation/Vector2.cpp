#include "stdafx.h"
#include "Vector2.h"

Vector2 Vector2::zero = Vector2(0, 0);
Vector2 Vector2::one = Vector2(1, 1);
Vector2 Vector2::right = Vector2(1, 0);
Vector2 Vector2::up = Vector2(0, 1);

Vector2 Vector2::Lerp(const Vector2& begin, const Vector2& end, float ratio_)
{
	//__min과 __max는 전처리기 매크로이다 
	//__max에서 ratio와 0을 비교하여 큰숫자를 반환하고
	// __min에서 두숫자와 비교하여 작은값을 반환한다. ratio가 1을 벗어날 경우 1
	float ratio = __min(1, __max(0, ratio_));
	Vector2 temp;
	//ex begin (2,3) end( 4,4) ratio = 0.5f
	//temp.x  = 2 + (4-2) * 0.5f = 3
	//temp.y  = 3 + (4-3) * 0.5f = 3.5
	//0.5 면 정확히 반이니깐 둘을 더한 벡터는 6,7의 반은 3,3.5가 맞다
	temp.x = begin.x + (end.x - begin.x) * ratio;
	temp.y = begin.y + (end.y - begin.y) * ratio;
	return temp;
}