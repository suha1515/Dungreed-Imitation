
#include "stdafx.h"
#include "Matrix3D.h"

static Matrix3D zero = Matrix3D(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
static Matrix3D identity = Matrix3D(1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);

float& Matrix3D::operator()(int iRow, int iCol)
{
	return m_fElements[iRow][iCol];
}//Mat