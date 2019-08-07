#pragma once

#define PIXEL_ALIGN 4	//픽셀 데이터 가로 한줄을 4의 배수 크기로 저장
#define PIXEL_SIZE 3	//픽셀 한개의 크기 3바이트(24비트)

class BitMap
{
public:
	BitMap();
	~BitMap();

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

public:
	void Release();
private:
	FILE				*fpBmp;		//비트맵 파일 포인터
	BITMAPFILEHEADER	fileHeader;	//비트맵 파일 헤더 구조체 변수
	BITMAPINFOHEADER	infoHeader; //비트맵 정보 헤더 구조체 변수

	unsigned char *image;			//픽셀 데이터 포인터
	int size;					    //픽셀 데이터 크기
	int width, height;				//비트맵 이미지의 가로 세로크기
	int padding;					//픽셀 데이터의 가로 크기가 4의 배수가 아닐때 남는공간의 크기.

	uint32_t colorMask;				//제거할 컬러 마스크

	string	filePath;				//파일 경로

};

