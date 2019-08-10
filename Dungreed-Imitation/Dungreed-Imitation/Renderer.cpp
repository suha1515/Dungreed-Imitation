#include "stdafx.h"
#include "Renderer.h"


Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}

void Renderer::ClearScreen()
{
	m_Rasterizer.ClearScreen();
}

void Renderer::Present(HDC * hdc)
{
	m_Rasterizer.Present(hdc);
}

void Renderer::DrawBitMap(int x0, int y0, BitMap* bitmap)
{
	int height = bitmap->GetHeight();
	int width = bitmap->GetWidth();
	int padding = bitmap->GetPadding();

	//�ȼ� �����ʹ� �Ʒ� ���� �������� ����ǹǷ� �Ʒ��ʺ��� �����ؾ��Ѵ�.
	for (int y = height - 1, y1 = 0; y >= 0; y--, y1++)
	{
		//���� ũ�⸸ŭ �ݺ�
		for (int x = 0; x < width; ++x)
		{
			//�Ϸķε� �迭�� �����ϱ����� �ε������
			//(x*�ȼ�ũ��) �� �ȼ��� ���� ��ġ
			//(y*(����ũ��*�ȼ�ũ��)) �� �ȼ��� �� ��° ������ ���
			//���°��� * y�� �ٺ��� ������ ���� ����.

			//���°����� �����ִ������� �Ʒ����� �����ϹǷ� �Ʒ��� �ȼ������Ͱ� ����Ǹ鼭 ���°����� �����ǹǷ�
			//�ش� ���°����� �����ϰ� ��Ȯ�ϰ� ���ϴ� ������ ������ ���ؼ� ���°����� ���Ѵ�
			//���οö󰥼��� ���°����� �����ִ� ���� �پ��� ��Ȯ������.
			int index = (x*PIXEL_SIZE) + (y*(width*PIXEL_SIZE)) + (padding*y);
			uint32_t color = bitmap->ToUInt32(index);

			//������ �ʴ� ���� �׸��� �ʴ´�.
			if (color != colorMask)
			{
				m_Rasterizer.SetPixel(x + x0, y1 + y0, color);
			}
		}
	}
}
void Renderer::DrawTriangleBarycentric(Vertex p1, Vertex p2, Vertex p3)
{
	//bounding box
	int maxX = (int)__max(p1.pos.x, __max(p2.pos.x, p3.pos.x));
	int minX = (int)__min(p1.pos.x, __min(p2.pos.x, p3.pos.x));
	int maxY = (int)__max(p1.pos.y, __max(p2.pos.y, p3.pos.y));
	int minY = (int)__min(p1.pos.y, __min(p2.pos.y, p3.pos.y));

	Vector2 _p1(p1.pos);
	Vector2 _p2(p2.pos);
	Vector2 _p3(p3.pos);

	float triArea = Cross2D(_p1, _p2, _p3);

	mRGB color;
	Vector2 _p;
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

				m_Rasterizer.SetPixel((int)_p.x, (int)_p.y, color);
			}
		}
	}
}

void Renderer::DrawTriangleBarycentric(Vertex p1, Vertex p2, Vertex p3, BitMap *bitmap)
{
	//bounding box
	int maxX = (int)__max(p1.pos.x, __max(p2.pos.x, p3.pos.x));
	int minX = (int)__min(p1.pos.x, __min(p2.pos.x, p3.pos.x));
	int maxY = (int)__max(p1.pos.y, __max(p2.pos.y, p3.pos.y));
	int minY = (int)__min(p1.pos.y, __min(p2.pos.y, p3.pos.y));

	//���θ� 8���� ��������.
	int width = maxX - minX;		//60- 30 = 30
	int height = maxY - minY;		//30 -0  = 30

	int perThread = width / 8;		//30/8	=	3
	int restSize = width - perThread * 8;	// 30 - 3*8 = 6 << 8�� ������� �������� �κ��� ������ ���
	int restStart = width - restSize;		// 30 -6 =24  , 24���� 29���� �ȼ� ����

	vector<thread> threads;
	for (int i = 0; i < 8; ++i)
	{
		int startX = minX + perThread*i;
		int endX   = minX + perThread*(i+1);
		
		threads.push_back(thread(&Renderer::DrawMulti,startX,endX, minY, maxY,
											p1, p2, p3, bitmap, colorMask,
											&m_Rasterizer,&m_ScreenCoord));
	}

	for (int i = 0; i < 8; ++i)
	{
		threads[i].join();
	}

	if (restSize != 0)
	{
		Vector2 _p1(p1.pos);
		Vector2 _p2(p2.pos);
		Vector2 _p3(p3.pos);

		float triArea = Cross2D(_p1, _p2, _p3);

		Vector2 _p;
		//float denom = Dot(normal, normal);
		for (_p.y = minY; _p.y <= maxY; ++_p.y)
		{
			for (_p.x = restStart; _p.x <= maxX; ++_p.x)
			{
				float w0 = Cross2D(_p2, _p3, _p) / triArea;
				float w1 = Cross2D(_p3, _p1, _p) / triArea;
				float w2 = Cross2D(_p1, _p2, _p) / triArea;

				if ((w0 >= 0 && w1 >= 0 && w2 >= 0))
				{
					Vector2 texcoord = p1.tex*w0 + p2.tex*w1 + p3.tex*w2;
					//�ϴ�.. int�� float ������ ���궧���� barycentric �� �����߽ɰ��� �Ҽ��̹Ƿ�..
					// �е����� �Ҽ��� ���꿡���� �� ������ �ȵȴ�. �׷��� �糡������ ����� �ȵǴ� ���� �߰�.. �׷��� 0.1f ���� ����..
					int u = (bitmap->GetWidth() - 0.01f)*texcoord.x;
					int v = (bitmap->GetHeight() - 0.01f) - (bitmap->GetHeight() - 0.01f)*texcoord.y;

					int index = (u*PIXEL_SIZE) + (v*(bitmap->GetWidth()*PIXEL_SIZE)) + (bitmap->GetPadding()*v);
					uint32_t color = bitmap->ToUInt32(index);

					if (color != colorMask)
					{
						//��ũ�� ��ǥ���
						Vector2 pixel = _p;
						pixel.x = pixel.x*m_ScreenCoord._axsis0.x + pixel.y*m_ScreenCoord._axsis1.x;
						pixel.y = pixel.y*m_ScreenCoord._axsis1.y + pixel.x*m_ScreenCoord._axsis0.y;
						pixel.x = pixel.x + m_ScreenCoord._origin.x;
						pixel.y = pixel.y + m_ScreenCoord._origin.y;
						m_Rasterizer.SetPixel((int)pixel.x, (int)pixel.y, color);
					}

				}
			}
		}
	}


	//Vector2 _p1(p1.pos);
	//Vector2 _p2(p2.pos);
	//Vector2 _p3(p3.pos);

	//float triArea = Cross2D(_p1, _p2, _p3);

	//Vector2 _p;
	////float denom = Dot(normal, normal);
	//for (_p.y = minY; _p.y <= maxY; ++_p.y)
	//{
	//	for (_p.x = minX; _p.x <= maxX; ++_p.x)
	//	{
	//		float w0 = Cross2D(_p2, _p3, _p) / triArea;
	//		float w1 = Cross2D(_p3, _p1, _p) / triArea;
	//		float w2 = Cross2D(_p1, _p2, _p) / triArea;

	//		if ((w0 >= 0 && w1 >= 0 && w2 >= 0))
	//		{
	//			Vector2 texcoord = p1.tex*w0 + p2.tex*w1 + p3.tex*w2;
	//			//�ϴ�.. int�� float ������ ���궧���� barycentric �� �����߽ɰ��� �Ҽ��̹Ƿ�..
	//			// �е����� �Ҽ��� ���꿡���� �� ������ �ȵȴ�. �׷��� �糡������ ����� �ȵǴ� ���� �߰�.. �׷��� 0.1f ���� ����..
	//			int u = (bitmap->GetWidth()-0.01f)*texcoord.x;
	//			int v = (bitmap->GetHeight()-0.01f)-(bitmap->GetHeight()-0.01f)*texcoord.y;
	//			
	//			int index = (u*PIXEL_SIZE) + (v*(bitmap->GetWidth()*PIXEL_SIZE))+ (bitmap->GetPadding()*v);
	//			uint32_t color = bitmap->ToUInt32(index);

	//			if (color != colorMask)
	//			{
	//				//��ũ�� ��ǥ���
	//				Vector2 pixel = _p;
	//				pixel.x = pixel.x*m_ScreenCoord._axsis0.x + pixel.y*m_ScreenCoord._axsis1.x;
	//				pixel.y = pixel.y*m_ScreenCoord._axsis1.y + pixel.x*m_ScreenCoord._axsis0.y;
	//				pixel.x = pixel.x + m_ScreenCoord._origin.x;
	//				pixel.y = pixel.y + m_ScreenCoord._origin.y;
	//				m_Rasterizer.SetPixel((int)pixel.x, (int)pixel.y, color);
	//			}

	//		}
	//	}
	//}
}

void Renderer::DrawTriangleBarycentric(Vertex p1, Vertex p2, Vertex p3, Bitmap *bitmap)
{
	//bounding box
	int maxX = (int)__max(p1.pos.x, __max(p2.pos.x, p3.pos.x));
	int minX = (int)__min(p1.pos.x, __min(p2.pos.x, p3.pos.x));
	int maxY = (int)__max(p1.pos.y, __max(p2.pos.y, p3.pos.y));
	int minY = (int)__min(p1.pos.y, __min(p2.pos.y, p3.pos.y));

	
	//Vector2 _p1(p1.pos);
	//Vector2 _p2(p2.pos);
	//Vector2 _p3(p3.pos);

	//float triArea = Cross2D(_p1, _p2, _p3);

	//Vector2 _p;
	////float denom = Dot(normal, normal);
	//for (_p.y = minY; _p.y <= maxY; ++_p.y)
	//{
	//	for (_p.x = minX; _p.x <= maxX; ++_p.x)
	//	{
	//		float w0 = Cross2D(_p2, _p3, _p) / triArea;
	//		float w1 = Cross2D(_p3, _p1, _p) / triArea;
	//		float w2 = Cross2D(_p1, _p2, _p) / triArea;

	//		if ((w0 >= 0 && w1 >= 0 && w2 >= 0))
	//		{
	//			Vector2 texcoord = p1.tex*w0 + p2.tex*w1 + p3.tex*w2;
	//			Color color;
	//			bitmap->GetPixel((int)(texcoord.x*bitmap->GetWidth()), (int)(texcoord.y*bitmap->GetHeight()), &color);
	//			if (color.GetValue() != Gdiplus::Color::Magenta)
	//			{
	//				m_Rasterizer.SetPixel(_p.x, _p.y, color);
	//			}

	//		}
	//	}
	//}
}
void Renderer::DrawOnCanvas()
{
	DrawTriangleBarycentric(m_VertexBuffer[0], m_VertexBuffer[1], m_VertexBuffer[2], m_Texture);
	DrawTriangleBarycentric(m_VertexBuffer[2], m_VertexBuffer[3], m_VertexBuffer[0], m_Texture);

}
void Renderer::DrawMulti(int startX, int endX, int startY, int endY, 
								Vertex p1, Vertex p2, Vertex p3, BitMap 
								*bitmap,uint32_t colorMask
								,Rasterizer* rasterizer,ScreenCoordinate* ScreenCoord)
{
	Vector2 _p;
	Vector2 _p1(p1.pos);
	Vector2 _p2(p2.pos);
	Vector2 _p3(p3.pos);
	float triArea = Cross2D(_p1, _p2, _p3);

	for (_p.y = startY; _p.y <= endY; ++_p.y)
	{
		for (_p.x = startX; _p.x <= endX; ++_p.x)
		{
			float w0 = Cross2D(_p2, _p3, _p) / triArea;
			float w1 = Cross2D(_p3, _p1, _p) / triArea;
			float w2 = Cross2D(_p1, _p2, _p) / triArea;

			if ((w0 >= 0 && w1 >= 0 && w2 >= 0))
			{
				Vector2 texcoord = p1.tex*w0 + p2.tex*w1 + p3.tex*w2;
				//�ϴ�.. int�� float ������ ���궧���� barycentric �� �����߽ɰ��� �Ҽ��̹Ƿ�..
				// �е����� �Ҽ��� ���꿡���� �� ������ �ȵȴ�. �׷��� �糡������ ����� �ȵǴ� ���� �߰�.. �׷��� 0.1f ���� ����..
				int u = (bitmap->GetWidth() - 0.01f)*texcoord.x;
				int v = (bitmap->GetHeight() - 0.01f) - (bitmap->GetHeight() - 0.01f)*texcoord.y;

				int index = (u*PIXEL_SIZE) + (v*(bitmap->GetWidth()*PIXEL_SIZE)) + (bitmap->GetPadding()*v);
				uint32_t color = bitmap->ToUInt32(index);

				if (color != colorMask)
				{
					//��ũ�� ��ǥ���
					Vector2 pixel = _p;
					pixel.x = pixel.x*ScreenCoord->_axsis0.x + pixel.y*ScreenCoord->_axsis1.x;
					pixel.y = pixel.y*ScreenCoord->_axsis1.y + pixel.x*ScreenCoord->_axsis0.y;
					pixel.x = pixel.x + ScreenCoord->_origin.x;
					pixel.y = pixel.y + ScreenCoord->_origin.y;
					rasterizer->SetPixel((int)pixel.x, (int)pixel.y, color);

				}
			}
		}
	}
	//thread::id this_id = this_thread::get_id();
	//printf("������ %x �� %d ���� %d���� �����\n", this_id, startX, endX);
}
void Renderer::SetRasterizer(HDC hdc, int width, int heigth)
{
	m_Rasterizer.CreateDIB(hdc, width, heigth);
}
void Renderer::SetColorMask(mRGB color)
{
	colorMask = color.ToUInt32();
}

void Renderer::SetVertexBuffer(Vertex * pVertex)
{
	m_VertexBuffer = pVertex;
}

void Renderer::SetTexture(BitMap * bitmap)
{
	m_Texture = bitmap;
}
