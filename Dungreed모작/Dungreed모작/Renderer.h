#pragma once
class Renderer
{
public:
	Renderer();
	~Renderer();
public:
	void DrawBitMap(int x0,int y0,CBitMap* bitmap);
	void DrawTriangleBarycentric(Vertex p1, Vertex p2, Vertex p3);
	void DrawTriangleBarycentric(Vertex p1, Vertex p2, Vertex p3,CBitMap* bitmap);
	void DrawTriangleBarycentric(Vertex p1, Vertex p2, Vertex p3,Bitmap* bitmap);
public:
	void SetRasterizer(CRasterizer* raster);
	void SetColorMask(mRGB color);

private:
	CRasterizer*		m_Rasterizer;
	
	uint32_t colorMask;				//제거할 컬러 마스크

};

