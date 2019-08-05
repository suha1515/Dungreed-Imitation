#include "stdafx.h"
#include "Renderer.h"


Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}

void Renderer::DrawBitMap(int x0, int y0,CBitMap* bitmap)
{
	int height = bitmap->GetHeight();
	int width = bitmap->GetWidth();
	int padding = bitmap->GetPadding();

	//픽셀 데이터는 아래 위가 뒤집혀서 저장되므로 아래쪽부터 직행해야한다.
	for (int y = height - 1,y1=0; y >= 0; y--,y1++)
	{
		//가로 크기만큼 반복
		for (int x = 0; x < width; ++x)
		{
			//일렬로된 배열에 접근하기위해 인덱스계산
			//(x*픽셀크기) 는 픽셀의 가로 위치
			//(y*(세로크기*픽셀크기)) 는 픽셀이 몇 번째 줄인지 계산
			//남는공간 * y는 줄별로 누적된 남는 공간.

			//남는공간을 더해주는이유는 아래부터 접근하므로 아래로 픽셀데이터가 저장되면서 남는공간이 누적되므로
			//해당 남는공간을 무시하고 정확하게 원하는 데이터 접근을 위해서 남는공간을 더한다
			//위로올라갈수록 남는공간을 더해주는 값이 줄어들어 정확해진다.
			int index = (x*PIXEL_SIZE) + (y*(width*PIXEL_SIZE)) + (padding*y);
			uint32_t color = bitmap->ToUInt32(index);

			//원하지 않는 색은 그리지 않는다.
			if (color != colorMask)
			{
				m_Rasterizer->SetPixel(x + x0, y1 + y0,color );
			}	
		}
	}
}
void Renderer::DrawTriangleBarycentric(Vertex p1, Vertex p2, Vertex p3)
{
	//bounding box
	int maxX = __max(p1.pos.x, __max(p2.pos.x, p3.pos.x));
	int minX = __min(p1.pos.x, __min(p2.pos.x, p3.pos.x));
	int maxY = __max(p1.pos.y, __max(p2.pos.y, p3.pos.y));
	int minY = __min(p1.pos.y, __min(p2.pos.y, p3.pos.y));

	CVector2 _p1(p1.pos);
	CVector2 _p2(p2.pos);
	CVector2 _p3(p3.pos);

	float triArea = Cross2D(_p1, _p2, _p3);

	mRGB color;
	CVector2 _p;
	//float denom = Dot(normal, normal);
	for (_p.y = minY; _p.y <= maxY; ++_p.y)
	{
		for (_p.x = minX; _p.x <= maxX; ++_p.x)
		{
			float w0 = Cross2D(_p2, _p3, _p) / triArea;
			float w1 = Cross2D(_p3, _p1, _p) / triArea;
			float w2 = Cross2D(_p1, _p2, _p) / triArea;
			//Vector3 flatNormal = Normalize(normal);
			//float shade = Dot(lit, flatNormal);
			//shade = __max(0.0f, shade);
			if ((w0 >= 0 && w1 >= 0 && w2 >= 0))
			{
				color = p1.color*w0 + p2.color*w1 + p3.color*w2;

				color[0] = __min(1.0f, color[0]);
				color[1] = __min(1.0f, color[1]);
				color[2] = __min(1.0f, color[2]);



				m_Rasterizer->SetPixel(_p.x, _p.y, color);
			}
		}
	}
}

void Renderer::DrawTriangleBarycentric(Vertex p1, Vertex p2, Vertex p3,CBitMap *bitmap)
{
	//bounding box
	int maxX = __max(p1.pos.x, __max(p2.pos.x, p3.pos.x));
	int minX = __min(p1.pos.x, __min(p2.pos.x, p3.pos.x));
	int maxY = __max(p1.pos.y, __max(p2.pos.y, p3.pos.y));
	int minY = __min(p1.pos.y, __min(p2.pos.y, p3.pos.y));

	CVector2 _p1(p1.pos);
	CVector2 _p2(p2.pos);
	CVector2 _p3(p3.pos);

	float triArea = Cross2D(_p1, _p2, _p3);

	CVector2 _p;
	//float denom = Dot(normal, normal);
	for (_p.y = minY; _p.y <= maxY; ++_p.y)
	{
		for (_p.x = minX; _p.x <= maxX; ++_p.x)
		{
			float w0 = Cross2D(_p2, _p3, _p) / triArea;
			float w1 = Cross2D(_p3, _p1, _p) / triArea;
			float w2 = Cross2D(_p1, _p2, _p) / triArea;

			if ((w0 >= 0 && w1 >= 0 && w2 >= 0))
			{
				CVector2 texcoord = p1.tex*w0 + p2.tex*w1 + p3.tex*w2;
				int u= int((bitmap->GetWidth())*texcoord.x );
				int v= int((bitmap->GetHeight())*texcoord.y);
				//(x*PIXEL_SIZE) + (y*(width*PIXEL_SIZE)) + (padding*y);
				int index = (u*PIXEL_SIZE) + (v*(bitmap->GetWidth()*PIXEL_SIZE)) + (bitmap->GetPadding()*v);
				uint32_t color = bitmap->ToUInt32(index);
				if(color != colorMask)
				m_Rasterizer->SetPixel(_p.x, _p.y, color);
			}
		}
	}
}

void Renderer::DrawTriangleBarycentric(Vertex p1, Vertex p2, Vertex p3, Bitmap *bitmap)
{
	//bounding box
	int maxX = __max(p1.pos.x, __max(p2.pos.x, p3.pos.x));
	int minX = __min(p1.pos.x, __min(p2.pos.x, p3.pos.x));
	int maxY = __max(p1.pos.y, __max(p2.pos.y, p3.pos.y));
	int minY = __min(p1.pos.y, __min(p2.pos.y, p3.pos.y));

	CVector2 _p1(p1.pos);
	CVector2 _p2(p2.pos);
	CVector2 _p3(p3.pos);

	float triArea = Cross2D(_p1, _p2, _p3);

	CVector2 _p;
	//float denom = Dot(normal, normal);
	for (_p.y = minY; _p.y <= maxY; ++_p.y)
	{
		for (_p.x = minX; _p.x <= maxX; ++_p.x)
		{
			float w0 = Cross2D(_p2, _p3, _p) / triArea;
			float w1 = Cross2D(_p3, _p1, _p) / triArea;
			float w2 = Cross2D(_p1, _p2, _p) / triArea;

			if ((w0 >= 0 && w1 >= 0 && w2 >= 0))
			{
				CVector2 texcoord = p1.tex*w0 + p2.tex*w1 + p3.tex*w2;
				Color color;
				bitmap->GetPixel(texcoord.x*bitmap->GetWidth(), texcoord.y*bitmap->GetHeight(), &color);
				m_Rasterizer->SetPixel(_p.x, _p.y, color);
			}
		}
	}
}
void Renderer::SetRasterizer(CRasterizer * raster)
{
	m_Rasterizer = raster;
}
void Renderer::SetColorMask(mRGB color)
{
	colorMask = color.ToUInt32();
}
