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
		Fade,		    //シーン遷移時に使うフェード用の画像
		WhiteFade,	    //白フェード用画像
		ParamList,      //育成中のパラメータ表
		ResultParamList,//育成結果表示時のパラメータ表
		PowerTraning,   //筋力トレーニング
		MagicTraning,   //魔力トレーニング
		SpeedTraning,   //素早さトレーニング
		HpTraning,      //体力トレーニング
		Rest,           //休息		
		PowerBack,		//筋力トレーニング背景
		MagicBack,		//魔力トレーニング背景
		SpeedBack,		//素早さトレーニング背景
		HpBack,		    //体力トレーニング背景
		RestBack,		//休息背景
		TextBox,		//テキストボックス
		StaminaGage,    //スタミナゲージ
		StaminaBack,    //スタミナゲージ背景
		HpGage,			//体力ゲージ
		HpGageBack,     //体力ゲージ背景
		GageFrame,      //ゲージ枠
		UniqueGage,		//ユニークゲージ
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

