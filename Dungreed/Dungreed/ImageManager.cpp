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

CBitMap * ImageManager::GetBitMap(const wstring & wstrkey)
{
	auto iter_find = m_mapBitMap.find(wstrkey);

	if (m_mapBitMap.end() == iter_find)
		return nullptr;

	return iter_find->second;
}

void ImageManager::LoadBitMap(const wstring & wstrFilePath, const wstring & wstrkey)
{
	auto iter_find = m_mapBitMap.find(wstrkey);

	if (m_mapBitMap.end()!= iter_find)
		return;

	CBitMap* pBitmap = new CBitMap;
	pBitmap->ReadBitMap(wstrFilePath);

	m_mapBitMap.insert({ wstrkey,pBitmap });
}

void ImageManager::Release()
{
	map<wstring, CBitMap*>::iterator iter_begin = m_mapBitMap.begin();
	map<wstring, CBitMap*>::iterator iter_end = m_mapBitMap.end();

	for (; iter_begin != iter_end;)
	{
		SafeDelete(iter_begin->second);
		m_mapBitMap.erase(iter_begin->first);
		iter_begin++;
	}
}
