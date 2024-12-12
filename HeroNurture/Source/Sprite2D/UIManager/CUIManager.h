#pragma once
#include "Sprite2D/CSprite2D.h"
#include "CDirectX11.h"
#include "SkinMeshObject/Hero/CHeroBase.h"

class CUIManager
{
public:
	//UIリスト
	enum UIList
	{
		Fade,		 //シーン遷移時に使うフェード用の画像
		WhiteFade,	 //白フェード用画像
		PowerParam,  //筋力パラメータ表示用画像
		SpeedParam,  //素早さパラメータ表示用画像
		MagicParam,  //魔力パラメータ表示用画像
		HpParam,     //体力パラメータ表示用画像
		StaminaGage, //スタミナゲージ表示用画像

		Max,
	};

	//シングルトン化
	static CUIManager* GetInstance() {
		static CUIManager s_Instance;
		return &s_Instance;
	}

public:
	~CUIManager();

	HRESULT Load(CDirectX11* Dx11);

	void SetDx11(CDirectX11& Dx11) { m_pDx11 = &Dx11; }

	static CSprite2D& GetSprite(UIList list) { return *GetInstance()->m_pSprite2D[list]; }

private:
	//シングルトン化
	CUIManager();
	CUIManager(const CUIManager& rhs) = delete;
	CUIManager& operator = (const CUIManager& rhs) = delete;

private:
	CDirectX11* m_pDx11;

	CSprite2D* m_pSprite2D[UIList::Max];

	CHeroBase* m_pHero;
};

