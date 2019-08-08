#include "stdafx.h"
#include "Rasterizer.h"

HDC BackDC;
Rasterizer::Rasterizer()
{
}


Rasterizer::~Rasterizer()
{
}

//Create DIB
void Rasterizer::CreateDIB(HDC hdc, int width, int heigth)
{
	m_iWidth = width;
	m_iHeight = heigth;

	m_hDC = CreateCompatibleDC(hdc);
	BackDC = m_hDC;

	m_bitInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_bitInfo.bmiHeader.biWidth = m_iWidth;
	m_bitInfo.bmiHeader.biHeight = -m_iHeight;

	m_bitInfo.bmiHeader.biPlanes = 1;
	m_bitInfo.bmiHeader.biBitCount = 32;
	m_bitInfo.bmiHeader.biCompression = BI_RGB;

	m_DibBitmap = CreateDIBSection(hdc, &m_bitInfo, DIB_RGB_COLORS, (void**)&m_FrameBuffer, NULL, 0);
	SelectObject(m_hDC, m_DibBitmap);


}

void Rasterizer::ClearScreen()
{
	/*static __m256i zero = _mm256_setzero_si256();
	for (__m256i* i = reinterpret_cast<__m256i*>(m_FrameBuffer), *end = reinterpret_cast<__m256i*>(&m_FrameBuffer[m_iWidth*m_iHeight]); i <end; ++i)
	{
	_mm256_store_si256(i, zero);
	}*/
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);
}

void Rasterizer::SetPixel(int x0, int y0, mRGB color)
{
	if ((x0 >= 0 && x0 < m_iWidth) && (y0 >= 0 && y0 < m_iHeight))
	{
		m_FrameBuffer[y0*m_iWidth + x0] = color.ToUInt32();
	}
}
void Rasterizer::SetPixel(int x0, int y0, uint32_t uint)
{
	if ((x0 >= 0 && x0 < m_iWidth) && (y0 >= 0 && y0 < m_iHeight))
	{
		m_FrameBuffer[y0*m_iWidth + x0] = uint;
	}
}

void Rasterizer::SetPixel(int x0, int y0, Color _color)
{
	if ((x0 >= 0 && x0 < m_iWidth) && (y0 >= 0 && y0 < m_iHeight))
	{
		uint32_t color = 0;
		uint32_t a = 0;

		color = (a << 24) | ((uint32_t)_color.GetR() << 16) | ((uint32_t)_color.GetG() << 8) | (uint32_t)_color.GetB();
		m_FrameBuffer[y0*m_iWidth + x0] = color;
	}
}

void Rasterizer::Present(HDC * hdc)
{
	BitBlt(*hdc, 0, 0, m_iWidth, m_iHeight, m_hDC, 0, 0, SRCCOPY);
}
