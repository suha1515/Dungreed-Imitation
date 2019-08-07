#include "stdafx.h"
#include "ImageManager.h"

IMPLEMENT_SINGLETON(ImageManager);
ImageManager::ImageManager()
{
}


ImageManager::~ImageManager()
{
	Release();
}

BitMap * ImageManager::GetBitMap(const wstring & wstrkey)
{
	auto iter_find = m_mapBitMap.find(wstrkey);

	if (m_mapBitMap.end() == iter_find)
		return nullptr;

	return iter_find->second;
}

void ImageManager::LoadBitMap(const wstring & wstrFilePath, const wstring & wstrkey)
{
	auto iter_find = m_mapBitMap.find(wstrkey);

	if (m_mapBitMap.end() != iter_find)
		return;

	BitMap* pBitmap = new BitMap;
	pBitmap->ReadBitMap(wstrFilePath);
	m_mapBitMap.insert({ wstrkey,pBitmap });
	pBitmap = nullptr;
}

void ImageManager::Release()
{
	/*map<wstring, BitMap*>::iterator iter_begin = m_mapBitMap.begin();
	map<wstring, BitMap*>::iterator iter_end = m_mapBitMap.end();
	for (; iter_begin != iter_end;)
	{
		SafeDelete(iter_begin->second);
		iter_begin = m_mapBitMap.erase(iter_begin);
	}
*/
	for (auto& MyPair : m_mapBitMap)
		SafeDelete(MyPair.second);

	m_mapBitMap.clear();

}
