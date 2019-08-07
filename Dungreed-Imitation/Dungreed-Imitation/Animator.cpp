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
	animStart = 0;
	animEnd = 0;
	animTime = 0.0f;
}
void Animator::SetInfo(int heightCount, int widthCount)
{
	animEnd = widthCount;
	animXGap = 1.0f / widthCount;
	animYGap = 1.0f / heightCount;
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

void Animator::PlayAnim(Renderer * render, const wstring & clipName,Vertex* vertex, ANIMATION_TYPE type, float speed)
{
	ANIM_INFO info = m_Clips.at(clipName);
		//애니메이션 재생 구간
		switch (type)
		{
		case ANIMATION_ONCE:
			SetInfo(info.heightCount,info.widthCount);
			vertex[0].tex = Vector2(0.0f, 0.0f) + Vector2(0.2f*animStart, 0.f);
			vertex[1].tex = Vector2(0.0f, 1.0f) + Vector2(0.2f*animStart, 0.f);
			vertex[2].tex = Vector2(0.2f, 1.0f) + Vector2(0.2f*animStart, 0.f);
			vertex[3].tex = Vector2(0.2f, 0.0f) + Vector2(0.2f*animStart, 0.f);
			if (animStart < animEnd)
			{
				if (animTime >= speed)
				{
					animStart++;
					animTime -= animTime;
				}
				else
					animTime += DELTA_TIME*100.f;
			}
			render->SetTexture(ImageManager::GetInstance()->GetBitMap(clipName));

			break;
		case ANIMATION_LOOP:
			SetInfo(info.heightCount, info.widthCount);
			vertex[0].tex = Vector2(0.0f, 0.0f) + Vector2(0.2f*animStart, 0.f);
			vertex[1].tex = Vector2(0.0f, 1.0f) + Vector2(0.2f*animStart, 0.f);
			vertex[2].tex = Vector2(0.2f, 1.0f) + Vector2(0.2f*animStart, 0.f);
			vertex[3].tex = Vector2(0.2f, 0.0f) + Vector2(0.2f*animStart, 0.f);
			if (animStart < animEnd)
			{
				if (animTime >= speed)
				{
					animStart++;
					animTime -= animTime;
				}
				else
					animTime += DELTA_TIME*100.f;
			}
			else
				animStart = 0;
			render->SetTexture(ImageManager::GetInstance()->GetBitMap(clipName));
			break;
		case ANIMATION_END:
			break;
		default:
			break;
		}
}

