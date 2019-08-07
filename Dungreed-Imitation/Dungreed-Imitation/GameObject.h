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
	void SetDead(bool IsDead);
	void SetBmpKey(const wstring& wstKey);
public:
	void SetPos(Vector2 pos);
	void SetRotation(float angle);
	void SetScale(float scale);


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
};

