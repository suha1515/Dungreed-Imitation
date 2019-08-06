#pragma once
class ImageManager
{
	DECLARE_SINGLETON(ImageManager)
public:
	ImageManager();
	~ImageManager();

public:
	CBitMap* GetBitMap(const wstring& wstrkey);
	void LoadBitMap(const wstring& wstrFilePath, const wstring& wstrkey);
private:
	void Release();  
private:
	map<wstring, CBitMap*>	m_mapBitMap;
};

