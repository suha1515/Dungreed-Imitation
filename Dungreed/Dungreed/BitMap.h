#pragma once

#define PIXEL_ALIGN 4	//�ȼ� ������ ���� ������ 4�� ��� ũ��� ����
#define PIXEL_SIZE 3	//�ȼ� �Ѱ��� ũ�� 3����Ʈ(24��Ʈ)

class CBitMap
{
public:
	CBitMap();
	~CBitMap();

public:
	void ReadBitMap(const wstring& path);
	uint32_t ToUInt32(int index) const;

public:
	void SetColorMask(mRGB color);
	
public:
	int GetHeight();
	int GetWidth();
	int GetSize();
	int GetPadding();
private:
	FILE				*fpBmp;		//��Ʈ�� ���� ������
	BITMAPFILEHEADER	fileHeader;	//��Ʈ�� ���� ��� ����ü ����
	BITMAPINFOHEADER	infoHeader; //��Ʈ�� ���� ��� ����ü ����

	unsigned char *image;			//�ȼ� ������ ������
	int size;					    //�ȼ� ������ ũ��
	int width, height;				//��Ʈ�� �̹����� ���� ����ũ��
	int padding;					//�ȼ� �������� ���� ũ�Ⱑ 4�� ����� �ƴҶ� ���°����� ũ��.

	uint32_t colorMask;				//������ �÷� ����ũ

	string	filePath;				//���� ���

};

