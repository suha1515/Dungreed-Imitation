#pragma once

//typedef struct _BITMAPFILEHEADER //BMP 비트맵 파일 헤더 구조체
//{
//	unsigned short	bfType;					// BMP 파일 매직넘버
//	unsigned int	bfSize;					// 파일크기
//	unsigned short  bfReserved1;			// 예약 부분
//	unsigned short  bfReserved2;		    // 예약 부분
//	unsigned int	bfOffbits;				// 비트맵 데이터의 시작위치
//};
//
//typedef struct _BITMAPINFOHEADER  // BMP 비트맵 정보 헤더 구조체 (DIB 헤더)
//{
//	unsigned int	biSize;			//현재 구조체의 크기
//	int				biWidth;		//비트맵 이미지의 가로크기
//	int				biHeight;		//비트맵 이미지의 세로크기
//	unsigned short	biPlanes;		//사용하는 색상판의 수
//	unsigned short  biBitCount;		//픽셀 하나를 표현하는 비트수
//	unsigned int	biCompression;	//압축 방식
//	unsigned int	biSizeImage;	//비트맵 이미지의 픽셀
//	int				biXPelsPerMeter;//그림 가로 해상도(미터당 픽셀)
//	int				biYPelsPerMeter;//그림 세로 해상도(미터당 픽셀)
//	unsigned int	biClrUsed;		//색상 테이블에서 실제 사용되는 색상수
//	unsigned int	biClrImportant;	//비트맵을 표현하기 위해 필요한 색상 인덱스 수
//};