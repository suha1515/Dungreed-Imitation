#include "stdafx.h"
#include "BitMap.h"


CBitMap::CBitMap()
{
}


CBitMap::~CBitMap()
{
	free(image);
}

void CBitMap::ReadBitMap(const wstring& path)
{
	fopen_s(&fpBmp, _bstr_t(path.c_str()), "rb");
	if (fpBmp == NULL)
	{
		cout << "������ �������� �ʽ��ϴ�." << endl;
		return;
	}
	
	//1���� ������� ��� �б⿡ �����Ѱ��̹Ƿ� ���� �����͸� �ݰ� ���α׷�����.
	if (fread(&fileHeader, sizeof(BITMAPFILEHEADER), 1, fpBmp) < 1)
	{
		cout << "���� ��� �б⿡ �����߽��ϴ�" << endl;
		return;
	}

	//���� �ѹ��� MB�� �´��� Ȯ��(2����Ʈ ũ���� BM�� ��Ʋ��������� ������ MB�� ��)
	//MB�� �ƴҰ�� ���α׷� ���� (�����ѹ��� BMP ������ �´��� Ȯ���ϴ� �ѹ��̴�)
	if (fileHeader.bfType != 'MB')
	{
		cout << "�����ѹ��� BM�� �ƴմϴ�" << endl;
		fclose(fpBmp);
		return;
	}
	// ��Ʈ�� ���� ��� �б�. �б⿡ �����ϸ� ���� �����͸� �ݰ� ���α׷� ����
	if (fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, fpBmp) < 1)
	{
		fclose(fpBmp);
		cout << "���� ��� �б⿡ �����߽��ϴ�." << endl;
		return ;
	}


	//24��Ʈ ��Ʈ���� �ƴϸ� ���α׷� ����
	if (infoHeader.biBitCount != 24)
	{
		cout << "bitCount: " << infoHeader.biBitCount << endl;
		cout << "24��Ʈ���� �ƴմϴ�" << endl;
		fclose(fpBmp);
		return;
	}

	size = infoHeader.biSizeImage;			//�ȼ� ������ ũ��
	width = infoHeader.biWidth;				//��Ʈ�� �̹����� ����ũ��
	height = infoHeader.biHeight;			//��Ʈ�� �̹����� ����ũ��

	//���°����� ����������� ��Ʈ�� ������ ���� ������ ������ �� 4�� ��� ũ��� �����Ѵ�.
	//���� ���� ������ ũ�Ⱑ 4�� ����� �ƴ϶�� ���°����� 0 ���� ä���� �����Ѵ�.
	//���� �ȼ� �����͸� �б����� ���� ������ �˰� �־���Ѵ�. �̷� ����� ����ϴ� ������ cpu�� ������ ó���� 4����Ʈ ũ�Ⱑ ȿ�����̱� �����̴�.


	//�̹����� ���� ũ�⿡ �ȼ� ũ�⸦ ���Ͽ� ���� ������ ũ�⸦ ���ϰ� 4�� �������� ����
	//4�� ������ ����� ���� ���°����� ���Ҽ� ����
	//���� ���� ������ 0�̶�� ��������� 4���ǹǷ� �׷���츦 ����Ͽ� �ٽ� 4�� �������� ���Ѵ�
	// etc) 125*3 = 375 % 4 = 3 , 4- 3 = 1 -> 1%4 = 1(���°���)
	// etc2) 128*3 = 384 % 4 = 0 , 4-0 = 4 -> 4%4 = 0(���°���) �̷����̴�
	padding = (PIXEL_ALIGN - ((width*PIXEL_SIZE) % PIXEL_ALIGN)) % PIXEL_ALIGN;

	if (size == 0)	//�ȼ� ������ ũ�Ⱑ 0�̶��
	{
		//�̹��� ����ũ�� x �ȼ�ũ�⿡ ���°����� �����ָ� ������ ���� �� �� ũ�Ⱑ ������
		//�� ����� ���̸� ���ϸ� �ȼ��������� ũ�⸦ ���� �� �ִ�.
		size = (width*PIXEL_SIZE + padding)*height;
	}

	image = (unsigned char*)malloc(size);		//�̹����� ũ�⸸ŭ �����Ҵ�

	//���� �����͸� �ȼ� �������� ���� ��ġ�� �̵�
	fseek(fpBmp, fileHeader.bfOffBits, SEEK_SET);

	//���Ͽ��� �ȼ� ������ ũ�� ��ŭ ���� . �б� ���н� ���� �����͸� �ݰ� ���α׷� ����
	if (fread(image, size, 1, fpBmp) < 1)
	{
		fclose(fpBmp);
		return;
	}

	fclose(fpBmp);	
}

uint32_t CBitMap::ToUInt32(int index) const
{
	
	uint32_t r =(uint32_t)image[index + 2];
	uint32_t g =(uint32_t)image[index + 1];
	uint32_t b =(uint32_t)image[index];
	uint32_t a = 0;

	//������ȭ���� �ȼ��� argb 4����Ʈ �����͸� ��� �ִ�.
	uint32_t result = (a << 24) | (r << 16) | (g << 8) | b;
		return result;
}

void CBitMap::SetColorMask(mRGB color)
{
	colorMask = color.ToUInt32();
}

int CBitMap::GetHeight()
{
	return height;
}

int CBitMap::GetWidth()
{
	return width;
}

int CBitMap::GetSize()
{
	return size;
}

int CBitMap::GetPadding()
{
	return padding;
}
