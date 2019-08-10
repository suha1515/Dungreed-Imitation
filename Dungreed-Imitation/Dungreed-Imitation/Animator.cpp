#include "stdafx.h"
#include "Animator.h"


Animator::Animator()
{
}


Animator::~Animator()
{
}

void Animator::Initialize()
{
	animStartX = 0;
	animStartY = 0;
	animEndX = 0;
	animEndY = 0;
	animTime = 0.0f;

	m_AnimSpeed = 0.0f;
	m_AnimType = ANIMATION_ONCE;
	m_ClipName = L"";
}
void Animator::Release()
{
}
void Animator::SetInfo(int heightCount, int widthCount)
{
	animEndX = widthCount;
	animEndY = heightCount;
	animXGap = 1.0f / widthCount;
	animYGap = 1.0f / heightCount;
}
void Animator::SetClip(const wstring & clipName, float speed, ANIMATION_TYPE type)
{
	Initialize();
	m_AnimSpeed = speed;
	m_AnimType = type;
	m_ClipName = clipName;
}
void Animator::SetClipName(const wstring & clipName)
{
	m_ClipName = clipName;
}
void Animator::SetSpeed(float speed)
{
	m_AnimSpeed = speed;
}
void Animator::SetType(ANIMATION_TYPE type)
{
	m_AnimType = type;
}
void Animator::MakeClip(const wstring&  imgName,int sizeX,int sizeY)
{
	auto iter_find = m_Clips.find(imgName);

	if (m_Clips.end() != iter_find)
		return;
	
	BitMap* clip = ImageManager::GetInstance()->GetBitMap(imgName);


	ANIM_INFO info;
	info.heightCount = clip->GetHeight()/sizeY;
	info.widthCount = clip->GetWidth()/sizeX;

	m_Clips.insert({ imgName,info});
}

bool Animator::PlayAnim(Renderer * render,Vertex* vertex)
{
	ANIM_INFO info = m_Clips.at(m_ClipName);
		//애니메이션 재생 구간
		switch (m_AnimType)
		{
		case ANIMATION_ONCE:
			SetInfo(info.heightCount,info.widthCount);
			vertex[0].tex = Vector2(0.0f,		 0.0f)	+ Vector2(animXGap*animStartX, animYGap*animStartY);
			vertex[1].tex = Vector2(0.0f,	 animYGap)	+ Vector2(animXGap*animStartX, animYGap*animStartY);
			vertex[2].tex = Vector2(animXGap,animYGap)	+ Vector2(animXGap*animStartX, animYGap*animStartY);
			vertex[3].tex = Vector2(animXGap,	 0.0f)	+ Vector2(animXGap*animStartX, animYGap*animStartY);

			if (animStartX > animEndX)
			{
				//한번만 재생하니 false 반환
				return false;
			}
			else
			{
				if (animTime >= m_AnimSpeed)
				{
					animStartX++;
					animTime -= animTime;
				}
				else
					animTime += DELTA_TIME*100.f;
			}
			render->SetTexture(ImageManager::GetInstance()->GetBitMap(m_ClipName));
			return true;
			break;
		case ANIMATION_LOOP:
			SetInfo(info.heightCount, info.widthCount);
			vertex[0].tex = Vector2(0.0f, 0.0f) + Vector2(animXGap*animStartX, animYGap*animStartY);
			vertex[1].tex = Vector2(0.0f, animYGap) + Vector2(animXGap*animStartX, animYGap*animStartY);
			vertex[2].tex = Vector2(animXGap, animYGap) + Vector2(animXGap*animStartX, animYGap*animStartY);
			vertex[3].tex = Vector2(animXGap, 0.0f) + Vector2(animXGap*animStartX, animYGap*animStartY);
			if (animStartX < animEndX)
			{
				if (animTime >= m_AnimSpeed)
				{
					animStartX++;
					animTime -= animTime;
				}
				else
					animTime += DELTA_TIME*100.f;
			}
			else
				animStartX = 0;
			render->SetTexture(ImageManager::GetInstance()->GetBitMap(m_ClipName));
			//루프이니 계속 반환
			return true; 
			break;
		case ANIMATION_END:
			break;
		default:
			break;
		}
}

