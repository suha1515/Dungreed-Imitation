#pragma once
class Renderer
{
public:
	Renderer();
	~Renderer();
public:
	void ClearScreen();
	void Present(HDC * hdc);
public:
	void DrawBitMap(int x0, int y0, BitMap* bitmap);
	void DrawTriangleBarycentric(Vertex p1, Vertex p2, Vertex p3);
	void DrawTriangleBarycentric(Vertex p1, Vertex p2, Vertex p3, BitMap* bitmap);
	void DrawTriangleBarycentric(Vertex p1, Vertex p2, Vertex p3, Bitmap* bitmap);

	void DrawOnCanvas();
public:
	void SetRasterizer(HDC hdc, int width, int heigth);
	void SetColorMask(mRGB color);
	void SetVertexBuffer(Vertex* pVertex);
	void SetTexture(BitMap* bitmap);

public:
	ScreenCoordinate	m_ScreenCoord;	//스크린 좌표계 (중심)
private:
	Rasterizer		    m_Rasterizer;

	Vertex*				m_VertexBuffer;	//정점
	BitMap*			m_Texture;		//텍스처들
	uint32_t colorMask;				//제거할 컬러 마스크


};

