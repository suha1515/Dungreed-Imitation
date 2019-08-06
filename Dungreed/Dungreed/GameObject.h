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
	void SetPos(CVector2 pos);
	void SetDead(bool IsDead);
	void SetBmpKey(const wstring& wstKey);


public :
	virtual void Initialize() = 0;
	virtual int	 Update() = 0;
	virtual void Render(Renderer* render) = 0;

protected:
	virtual void Release() = 0;

	
protected:
	void UpdateTex();

protected:
	INFO		m_tInfo;
	RECT		m_tRect;
	bool		m_bIsDead;
	
	wstring		m_BmpName;
};

