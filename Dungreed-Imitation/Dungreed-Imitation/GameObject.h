#pragma once
class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

public:
	const INFO& GetInfo() const;
	const RECT& GetRect() const;

public:
	BitMap* GetImage();

public:
	void SetDead(bool IsDead);
	void SetBmpKey(const wstring& wstKey);
	void SetImage(BitMap* bitmap);
	void SetTexture(const Vector2* tex);
	void SetRatio(const float& fcx, const float& fcy);
public:
	void SetPos(Vector2 pos);
	void SetRotation(float angle);
	void SetScale(float scale);

public:
	void Flip();


public:
	virtual void Initialize() = 0;
	virtual int	 Update() = 0;
	virtual void Render(Renderer* render) = 0;

protected:
	virtual void Release() = 0;


protected:
	void UpdateTex();
	void UpdateCopy();

protected:
	INFO		m_tInfo;
	RECT		m_tRect;
	bool		m_bIsDead;

	wstring		m_BmpName;

	Matrix3D    m_Translation;
	Matrix3D	m_Rotation;
	Matrix3D	m_Scale;

	BitMap*		m_ObjectImg;
};

