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
	void DrawBitMap(int x0,int y0,CBitMap* bitmap);
	void DrawTriangleBarycentric(Vertex p1, Vertex p2, Vertex p3);
	void DrawTriangleBarycentric(Vertex p1, Vertex p2, Vertex p3,CBitMap* bitmap);
	void DrawTriangleBarycentric(Vertex p1, Vertex p2, Vertex p3,Bitmap* bitmap);

	void DrawOnCanvas();
public:
	void SetRasterizer(HDC hdc, int width, int heigth);
	void SetColorMask(mRGB color);
	void SetVertexBuffer(Vertex* pVertex);
	void SetTexture(CBitMap* bitmap);

public:
	ScreenCoordinate	m_ScreenCoord;	//��ũ�� ��ǥ�� (�߽�)
private:
	CRasterizer		    m_Rasterizer;

	Vertex*				m_VertexBuffer;	//����
	CBitMap*			m_Texture;		//�ؽ�ó��
	uint32_t colorMask;				//������ �÷� ����ũ
	

};

