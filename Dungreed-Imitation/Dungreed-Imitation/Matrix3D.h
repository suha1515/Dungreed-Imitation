#pragma once
class Matrix3D
{
public:
	static Matrix3D zero;
	static Matrix3D identity;

public:
	union
	{
		struct
		{
			float _11, _12, _13;
			float _21, _22, _23;
			float _31, _32, _33;
		};
		float m_fElements[3][3];
	};


public:
	float& operator()(int iRow, int iCol);

	Matrix3D(float t11 = 1.0f, float t12 = 0.0f, float t13 = 0.0f,
		float t21 = 0.0f, float t22 = 1.0f, float t23 = 0.0f,
		float t31 = 0.0f, float t32 = 0.0f, float t33 = 1.0f)
		:_11(t11), _12(t12), _13(t13), _21(t21), _22(t22), _23(t23), _31(t31), _32(t32), _33(t33) {}
	~Matrix3D() {}

	void Set(float t11, float t12, float t13,
		float t21, float t22, float t23,
		float t31, float t32, float t33)
	{
		_11 = t11; _12 = t12; _13 = t13;
		_21 = t21; _22 = t22; _23 = t23;
		_31 = t31; _32 = t32; _33 = t33;
	}

	void SetIdentity()
	{
		_11 = 1.0f; _12 = 0.0f; _13 = 0.0f;
		_21 = 0.0f; _22 = 1.0f; _23 = 0.0f;
		_31 = 0.0f; _32 = 0.0f; _33 = 1.0f;
	}
	void SetRotation(float theta)
	{
		theta = DegreeToRadian(theta);
		SetIdentity();
		_11 = cosf(theta); _12 = -sinf(theta);
		_21 = sinf(theta); _22 = cosf(theta);
	}
	void SetShear(float shearXParallelToY, float shearYParallelToX)
	{
		SetIdentity();
		_11 = 1.0f; _12 = shearYParallelToX;
		_21 = shearXParallelToY; _22 = 1.0f;
	}
	void SetScale(float uniformScale)
	{
		SetIdentity();
		_11 = uniformScale;
		_22 = uniformScale;
		_33 = uniformScale;
	}
	void SetTranslation(float tx, float ty)
	{
		SetIdentity();
		_13 = tx;
		_23 = ty;
	}
	bool GetBasis(Vector2& basis_, int basisIndexFrom0_)
	{
		if (basisIndexFrom0_ == 0) {
			basis_.x = _11;
			basis_.y = _21;
		}
		else if (basisIndexFrom0_ == 1)
		{
			basis_.x = _12;
			basis_.y = _22;
		}
		else
		{
			return false;
		}

		return true;
	}
};
//오른쪽에서 곱했을경우  
/*
이부분은 벡터가 행벡터로 표현됬을때 행렬곱을 지정한것이다
아래 왼쪽곱과 다른점은 동차나누기를 어떤 요소로 하고 이동행렬에 필요한 상수항의 위치가 다르다.
*/
inline Vector2 operator*(const Vector2& v, const Matrix3D& m)
{
	Vector2 temp;
	temp.x = v.x*m._11 + v.y*m._21 + v.w*m._31;
	temp.y = v.x*m._12 + v.y*m._22 + v.w*m._32;

	temp.w = v.x*m._13 + v.y*m._23 + v.w*m._33;
	//temp.x /= temp.w; // homogeneous divide
	//temp.y /= temp.w;
	//temp.w /= temp.w;
	return temp;
}

//왼쪽에서 곱했을경우
//이경우는 벡터가 열벡터로 표현됬을대 행렬곱
inline Vector2 operator*(const Matrix3D& m, const Vector2& v)
{
	Vector2 temp;
	temp.x = m._11*v.x + m._12*v.y + m._13 *v.w;
	temp.y = m._21*v.x + m._22*v.y + m._23 *v.w;
	//나중에 표현할것이지만 지금 Vector2는 온전히 x,y 성분만이 있다.
	//w 동차좌표가 없으므로 1이라고 가정한후 z를 계산한다. (바꿧다!) 이제 w값 가진다 
	temp.w = m._31*v.x + m._32*v.y + m._33*v.w;//여기서 1.0f가 Vector2에서 임의의 마지막성분 w 이다
											   //z 값에 1이아닌 값이 들어갈수 있어 동차나누기를 진행한다고는하는데.. (투영행렬에서는 Z 값이 w로 들어가 w값을 변경시킨다)
											   //이 경우는 좀더 봐야할것같다 단순 이동행렬만 할시 필요는없다. 실제로 지금 주석처리해도 아무런 연관이 없다.
	//temp.x /= temp.w; // homogeneous divide
	//temp.y /= temp.w;
	//temp.w /= temp.w;
	return temp;
}

inline Matrix3D operator*(float scalar, const Matrix3D& m)
{
	Matrix3D temp;
	temp._11 = scalar*m._11; temp._12 = scalar*m._12; temp._13 = scalar*m._13;
	temp._21 = scalar*m._21; temp._22 = scalar*m._22; temp._23 = scalar*m._23;
	temp._31 = scalar*m._31; temp._32 = scalar*m._32; temp._33 = scalar*m._33;
	return temp;
}

// composition: matrix-matrix multiplication
inline Matrix3D operator*(const Matrix3D& m0, const Matrix3D& m1)
{
	Matrix3D temp;
	temp._11 = m0._11*m1._11 + m0._12*m1._21 + m0._13*m1._31;
	temp._12 = m0._11*m1._12 + m0._12*m1._22 + m0._13*m1._32;
	temp._13 = m0._11*m1._13 + m0._12*m1._23 + m0._13*m1._33;
	temp._21 = m0._21*m1._11 + m0._22*m1._21 + m0._23*m1._31;
	temp._22 = m0._21*m1._12 + m0._22*m1._22 + m0._23*m1._32;
	temp._23 = m0._21*m1._13 + m0._22*m1._23 + m0._23*m1._33;
	temp._31 = m0._31*m1._11 + m0._32*m1._21 + m0._33*m1._31;
	temp._32 = m0._31*m1._12 + m0._32*m1._22 + m0._33*m1._32;
	temp._33 = m0._31*m1._13 + m0._32*m1._23 + m0._33*m1._33;
	return temp;
}

inline int Determinant3D(Matrix3D mat)
{
	int rowZeroCount = 0;	//row Zero Count
	int colZeroCount = 0;	//col Zero Count;

	int row = 0;
	int col = 0;

	//row
	for (int i = 0; i < 3; ++i)
	{
		int zeroCount = 0;
		for (int j = 0; j < 3; ++j)
		{
			if (mat(i, j) == 0.0f)
			{
				++zeroCount;
			}
		}
		if (rowZeroCount < zeroCount)
		{
			row = i;
			rowZeroCount = zeroCount;
		}
	}
	//column
	for (int i = 0; i < 3; ++i)
	{
		int zeroCount = 0;
		for (int j = 0; j < 3; ++j)
		{
			if (mat(j, i) == 0.0f)
			{
				++zeroCount;
			}
		}
		if (colZeroCount < zeroCount)
		{
			col = i;
			colZeroCount = zeroCount;
		}
	}

	int size = 0;
	if (rowZeroCount <= colZeroCount)
	{
		size = 3 - colZeroCount;
		if (size == 0)
			return 0;
		int determinant = 0;
		for (int i = 0; i < 3; ++i)
		{
			if (mat(i, col) != 0)
			{
				Matrix2D tmp;
				tmp.SetZero();
				for (int j = 0, h = 0; j < 3; ++j)
				{
					if (j == i)
						continue;

					for (int k = 0, l = 0; k < 3; ++k)
					{
						if (k == col)
							continue;
						tmp(h, l) = mat(j, k);
						++l;
					}
					++h;
				}
				int cofactor = 0;
				if (((i + 1) + (col + 1)) % 2 == 0)
					cofactor = 1;
				else
					cofactor = -1;

				determinant += mat(i, col)*cofactor*Determinant2D(tmp);
			}
		}
		return determinant;
	}
	else
	{
		size = 3 - rowZeroCount;
		if (size == 0)
			return 0;
		int determinant = 0;
		for (int i = 0; i < 3; ++i)
		{
			if (mat(row, i) != 0)
			{
				Matrix2D tmp;
				tmp.SetZero();
				for (int j = 0, h = 0; j < 3; ++j)
				{
					if (j == row)
						continue;

					for (int k = 0, l = 0; k < 3; ++k)
					{
						if (k == i)
							continue;

						tmp(h, l) = mat(j, k);
						++l;
					}
					++h;
				}
				int cofactor = 0;
				if (((i + 1) + (row + 1)) % 2 == 0)
					cofactor = 1;
				else
					cofactor = -1;
				determinant += mat(row, i)*cofactor*Determinant2D(tmp);
			}
		}
		return determinant;
	}

}
inline float Determinant3DFast(Matrix3D mat)
{
	float a0 = (mat._11*mat._22*mat._33) + (mat._12*mat._23*mat._31) + (mat._13*mat._21*mat._32);
	float a1 = (mat._31*mat._22*mat._13) + (mat._32*mat._23*mat._11) + (mat._33*mat._21*mat._12);

	return a0 - a1;
}