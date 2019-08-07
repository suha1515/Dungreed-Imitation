#pragma once

inline bool approx_eq(float a, float b)
{
	//fabs << 실수 절대값
	//실수의 대소비교는 오차가 있으므로 10.E-8 이하일경우 같다고 한다.
	return fabs(a - b) < 1.0E-8;
}
class mRGB
{
	union
	{
		float rgba[4];
	};


public:
	mRGB() { rgba[0] = 0.0f; rgba[1] = 0.0f; rgba[2] = 0.0f; rgba[3] = 0.0f; }
	mRGB(float r, float g, float b, float a = 0.0f) { rgba[0] = r; rgba[1] = g; rgba[2] = b; rgba[3] = a; }
	mRGB(const mRGB& rhs) { *this = rhs; }
	mRGB(float* pValue) { rgba[0] = pValue[0]; rgba[1] = pValue[1]; rgba[2] = pValue[2]; rgba[3] = pValue[3]; }


	mRGB& operator=(const mRGB& rhs) { rgba[0] = rhs.rgba[0]; rgba[1] = rhs.rgba[1]; rgba[2] = rhs.rgba[2]; rgba[3] = rhs.rgba[3]; return *this; }

	bool operator==(const mRGB& rhs) { return approx_eq(rgba[0], rhs.rgba[0]) && approx_eq(rgba[1], rhs.rgba[1]) && approx_eq(rgba[2], rhs.rgba[2]) && approx_eq(rgba[3], rhs.rgba[3]); }
	bool operator!=(const mRGB& rhs) { return !this->operator==(rhs); }

	mRGB operator+(const mRGB& rhs) const
	{
		mRGB temp;
		temp.rgba[0] = rgba[0] + rhs.rgba[0];
		temp.rgba[1] = rgba[1] + rhs.rgba[1];
		temp.rgba[2] = rgba[2] + rhs.rgba[2];
		temp.rgba[3] = rgba[3] + rhs.rgba[3];
		return temp;
	}
	mRGB operator-(const mRGB& rhs) const
	{
		mRGB temp;
		temp.rgba[0] = rgba[0] - rhs.rgba[0];
		temp.rgba[1] = rgba[1] - rhs.rgba[1];
		temp.rgba[2] = rgba[2] - rhs.rgba[2];
		temp.rgba[3] = rgba[3] - rhs.rgba[3];
		return temp;
	}
	mRGB operator*(float scale) const
	{
		mRGB temp;
		temp.rgba[0] = rgba[0] * scale;
		temp.rgba[1] = rgba[1] * scale;
		temp.rgba[2] = rgba[2] * scale;
		temp.rgba[3] = rgba[3] * scale;
		return temp;
	}
	mRGB operator*(const mRGB& rhs) const
	{
		mRGB temp;
		temp.rgba[0] = rgba[0] * rhs.rgba[0];
		temp.rgba[1] = rgba[1] * rhs.rgba[1];
		temp.rgba[2] = rgba[2] * rhs.rgba[2];
		temp.rgba[3] = rgba[3] * rhs.rgba[3];

		return temp;
	}

	mRGB operator/(float scale) const
	{
		mRGB temp;
		temp.rgba[0] = rgba[0] / scale;
		temp.rgba[1] = rgba[1] / scale;
		temp.rgba[2] = rgba[2] / scale;
		temp.rgba[3] = rgba[3] / scale;
		return temp;
	}
	mRGB operator+=(const mRGB& rhs_)
	{
		rgba[0] += rhs_.rgba[0];
		rgba[1] += rhs_.rgba[1];
		rgba[2] += rhs_.rgba[2];
		rgba[3] += rhs_.rgba[3];
		return *this;
	}
	mRGB operator-=(const mRGB& rhs_)
	{
		rgba[0] -= rhs_.rgba[0];
		rgba[1] -= rhs_.rgba[1];
		rgba[2] -= rhs_.rgba[2];
		rgba[3] -= rhs_.rgba[3];
		return *this;
	}
	mRGB operator/=(float scale)
	{
		rgba[0] /= scale;
		rgba[1] /= scale;
		rgba[2] /= scale;
		rgba[3] /= scale;
		return *this;
	}

	mRGB operator*=(float scale)
	{
		rgba[0] *= scale;
		rgba[1] *= scale;
		rgba[2] *= scale;
		rgba[3] *= scale;
		return *this;
	}
	float& operator[](int index)
	{
		return rgba[index];
	}
	const float& operator[](int index) const
	{
		return rgba[index];
	}
	uint32_t ToUInt32() const
	{
		uint32_t r = (uint32_t)(rgba[0] * 255.0f);
		uint32_t g = (uint32_t)(rgba[1] * 255.0f);
		uint32_t b = (uint32_t)(rgba[2] * 255.0f);
		uint32_t a = (uint32_t)(rgba[3] * 255.0f);

		//std::cout << r << " , " << g << " , " << b << " , " << a << std::endl;
		//std::cout << R << " , " << G << " , " << B << " , " << A << std::endl;
		//std::cout << std::hex << r;
		return (a << 24) | (r << 16) | (g << 8) | b;
	}

	friend std::ostream& operator<<(std::ostream& os, mRGB const& P) { return os << "rgb=(" << P.rgba[0] << ", " << P.rgba[1] << ", " << P.rgba[2] << " , " << P.rgba[3] << ")"; }
};