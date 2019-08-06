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
		cout << "파일이 존재하지 않습니다." << endl;
		return;
	}
	
	//1보다 작을경우 헤더 읽기에 실패한것이므로 파일 포인터를 닫고 프로그램종료.
	if (fread(&fileHeader, sizeof(BITMAPFILEHEADER), 1, fpBmp) < 1)
	{
		cout << "파일 헤더 읽기에 실패했습니다" << endl;
		return;
	}

	//매직 넘버가 MB가 맞는지 확인(2바이트 크기의 BM을 리틀엔디언으로 읽으면 MB가 됨)
	//MB가 아닐경우 프로그램 종료 (매직넘버는 BMP 파일이 맞는지 확인하는 넘버이다)
	if (fileHeader.bfType != 'MB')
	{
		cout << "매직넘버가 BM이 아닙니다" << endl;
		fclose(fpBmp);
		return;
	}
	// 비트맵 정보 헤더 읽기. 읽기에 실패하면 파일 포인터를 닫고 프로그램 종료
	if (fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, fpBmp) < 1)
	{
		fclose(fpBmp);
		cout << "정보 헤더 읽기에 실패했습니다." << endl;
		return ;
	}


	//24비트 비트맵이 아니면 프로그램 종료
	if (infoHeader.biBitCount != 24)
	{
		cout << "bitCount: " << infoHeader.biBitCount << endl;
		cout << "24비트맵이 아닙니다" << endl;
		fclose(fpBmp);
		return;
	}

	size = infoHeader.biSizeImage;			//픽셀 데이터 크기
	width = infoHeader.biWidth;				//비트맵 이미지의 가로크기
	height = infoHeader.biHeight;			//비트맵 이미지의 세로크기

	//남는공간이 생기는이유는 비트맵 포맷은 가로 한줄을 저장할 때 4의 배수 크기로 저장한다.
	//만약 가로 한줄의 크기가 4의 배수가 아니라면 남는공간은 0 으로 채워져 저장한다.
	//따라서 픽셀 데이터를 읽기위해 남는 공간을 알고 있어야한다. 이런 방식을 사용하는 이유는 cpu가 데이터 처리시 4바이트 크기가 효율적이기 때문이다.


	//이미지의 가로 크기에 픽셀 크기를 곱하여 가로 한줄의 크기를 구하고 4로 나머지를 구함
	//4를 나머지 결과로 빼면 남는공간을 구할수 있음
	//만약 남는 공간이 0이라면 최종결과가 4가되므로 그럴경우를 대비하여 다시 4로 나머지를 구한다
	// etc) 125*3 = 375 % 4 = 3 , 4- 3 = 1 -> 1%4 = 1(남는공간)
	// etc2) 128*3 = 384 % 4 = 0 , 4-0 = 4 -> 4%4 = 0(남는공간) 이런식이다
	padding = (PIXEL_ALIGN - ((width*PIXEL_SIZE) % PIXEL_ALIGN)) % PIXEL_ALIGN;

	if (size == 0)	//픽셀 데이터 크기가 0이라면
	{
		//이미지 가로크기 x 픽셀크기에 남는공간을 더해주면 완전한 가로 한 줄 크기가 나오고
		//그 결과에 높이를 곱하면 픽셀데이터의 크기를 구할 수 있다.
		size = (width*PIXEL_SIZE + padding)*height;
	}

	image = (unsigned char*)malloc(size);		//이미지의 크기만큼 동적할당

	//파일 포인터를 픽셀 데이터의 시작 위치로 이동
	fseek(fpBmp, fileHeader.bfOffBits, SEEK_SET);

	//파일에서 픽셀 데이터 크기 만큼 읽음 . 읽기 실패시 파일 포인터를 닫고 프로그램 종료
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

	//윈도우화면은 픽셀에 argb 4바이트 데이터를 담고 있다.
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
