#pragma once

//typedef struct _BITMAPFILEHEADER //BMP ��Ʈ�� ���� ��� ����ü
//{
//	unsigned short	bfType;					// BMP ���� �����ѹ�
//	unsigned int	bfSize;					// ����ũ��
//	unsigned short  bfReserved1;			// ���� �κ�
//	unsigned short  bfReserved2;		    // ���� �κ�
//	unsigned int	bfOffbits;				// ��Ʈ�� �������� ������ġ
//};
//
//typedef struct _BITMAPINFOHEADER  // BMP ��Ʈ�� ���� ��� ����ü (DIB ���)
//{
//	unsigned int	biSize;			//���� ����ü�� ũ��
//	int				biWidth;		//��Ʈ�� �̹����� ����ũ��
//	int				biHeight;		//��Ʈ�� �̹����� ����ũ��
//	unsigned short	biPlanes;		//����ϴ� �������� ��
//	unsigned short  biBitCount;		//�ȼ� �ϳ��� ǥ���ϴ� ��Ʈ��
//	unsigned int	biCompression;	//���� ���
//	unsigned int	biSizeImage;	//��Ʈ�� �̹����� �ȼ�
//	int				biXPelsPerMeter;//�׸� ���� �ػ�(���ʹ� �ȼ�)
//	int				biYPelsPerMeter;//�׸� ���� �ػ�(���ʹ� �ȼ�)
//	unsigned int	biClrUsed;		//���� ���̺��� ���� ���Ǵ� �����
//	unsigned int	biClrImportant;	//��Ʈ���� ǥ���ϱ� ���� �ʿ��� ���� �ε��� ��
//};