#pragma once
#define WINCX 800
#define WINCY 600

#define DELTA_TIME g_fDeltaTime

#define NO_EVENT 0
#define DEAD_OBJ 1

#define NULL_CHECK(ptr)	\
if(nullptr == (ptr)) return;

//ΩÃ±€≈Ê ∏≈≈©∑Œ
#define DECLARE_SINGLETON(ClassName)	\
public:									\
static ClassName* GetInstance();		\
void DestroyInstance();					\
private:								\
	static ClassName* m_pInstance;

#define IMPLEMENT_SINGLETON(ClassName)			\
ClassName* ClassName::m_pInstance = nullptr;	\
ClassName* ClassName::GetInstance()		\
{											\
	if (nullptr == m_pInstance)				\
		m_pInstance = new ClassName;		\
	return m_pInstance;						\
}											\
void ClassName::DestroyInstance()			\
{											\
	if (m_pInstance)						\
	{										\
		delete m_pInstance;					\
		m_pInstance = nullptr;				\
	}										\
}