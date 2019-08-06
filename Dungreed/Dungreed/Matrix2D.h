#pragma once
class Matrix2D
{
public:
	static Matrix2D zero;
	static Matrix2D identity;
public:
	union
	{
		struct
		{
			float _11, _12;
			float _21, _22;
		};
		float m_fElement[2][2];
	};


public:
	Matrix2D(float t11 = 1.0f, float t12 = 0.0f, float t21 = 0.0f, float t22 = 1.0f)
		:_11(t11), _12(t12), _21(t21), _22(t22) {}
	~Matrix2D() {}
	void Set(float t11, float t12, float t21, float t22)
	{
		_11 = t11;
		_12 = t12;
		_21 = t21;
		_22 = t22;
	}
	//단위행렬 함수
	void SetIdentity()
	{
		_11 = 1.0f; _12 = 0.0f;
		_21 = 0.0f; _22 = 1.0f;
	}
	void SetZero()
	{
		_11 = 0.0f; _12 = 0.0f;
		_21 = 0.0f; _22 = 0.0f;
	}
	//회전행렬화
	void SetRotation(float theta)
	{
		_11 = cosf(theta); _12 = -sinf(theta);
		_21 = sinf(theta); _22 = cosf(theta);
	}
	//쉬어변환행렬화
	void SetShear(float shearX, float shearY)
	{
		_11 = 1.0f; _12 = shearX;
		_21 = shearY; _22 = 1.0f;
	}
	//기저반환
	bool GetBasis(CVector2& basis_, int basisIndex_)
	{
		if (basisIndex_ == 0)
		{
			basis_.x = _11;
			basis_.y = _21;
		}
		else if (basisIndex_ == 1)
		{
			basis_.x = _12;
			basis_.y = _22;
		}
		else
			return false;

		return true;
	}
	float& operator()(int iRow, int iCol)
	{
		return m_fElement[iRow][iCol];
	}
};


inline CVector2 operator*(const Matrix2D& m, const CVector2& v)
{
	CVector2 temp;
	temp.x = m._11*v.x + m._12*v.y;
	temp.y = m._21*v.x + m._22*v.y;
	return temp;
}

inline CVector2 operator*(const CVector2& v, const Matrix2D& m)
{
	CVector2 temp;
	temp.x = m._11*v.x + m._12*v.y;
	temp.y = m._21*v.x + m._22*v.y;
	return temp;
}
inline Matrix2D operator*(float scalar, const Matrix2D& m)
{
	Matrix2D temp;
	temp._11 = scalar*m._11;
	temp._12 = scalar*m._12;
	temp._21 = scalar*m._21;
	temp._22 = scalar*m._22;
	return temp;
}
//행렬곱 연산자 오버로딩
inline Matrix2D operator*(const Matrix2D& m0, const Matrix2D& m1)
{
	Matrix2D temp;
	temp._11 = m0._11*m1._11 + m0._12*m1._21;
	temp._12 = m0._11*m1._12 + m0._12*m1._22;
	temp._21 = m0._21*m1._11 + m0._22*m1._21;
	temp._22 = m0._21*m1._12 + m0._22*m1._22;
	return temp;
}

inline int Determinant2D(Matrix2D mat)
{
	return  (mat._11*mat._22 - mat._12*mat._21);
}