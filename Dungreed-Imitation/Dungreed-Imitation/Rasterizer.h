#pragma once
class Rasterizer
{
public:
	Rasterizer();
	~Rasterizer();
private:
	uint32_t* m_FrameBuffer;

private:
	HBITMAP			m_DibBitmap;
	BITMAPINFO		m_bitInfo;
	HDC				m_hDC;
	int				m_iWidth, m_iHeight;

public:
	void CreateDIB(HDC hdc, int width, int height);
	void ClearScreen();

public:
	void SetPixel(int x0, int y0, mRGB color);
	void SetPixel(int x0, int y0, uint32_t uint);
	void SetPixel(int x0, int y0, Color _color);

public:
	void Present(HDC* hdc);
};

