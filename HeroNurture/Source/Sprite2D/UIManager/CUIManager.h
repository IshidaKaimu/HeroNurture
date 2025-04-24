#pragma once
#include "Sprite2D\CSprite2D.h"
#include "CDirectX11.h"
#include "Singleton\CSingleton.h"

class CUIManager
	:public CSingleton<CUIManager>
{
private:
	friend class CSingleton<CUIManager>;
	~CUIManager();
public:
	//UIリスト
	enum UIList
	{
		Fade,		        //シーン遷移時に使うフェード用の画像
		WhiteFade,	        //白フェード用画像
		TitleBack,          //タイトル背景
		TitleInfoBack,      //タイトル指示テキスト背景
		ModeSelectLeft,     //モード選択シーン背景左
		ModeSelectRight,	//モード選択シーン背景右
		ModeSelectCover,    //モード選択シーン背景かぶせる画像
		ControlBar,			//操作方法指示バー
		ParamList,          //育成中のパラメータ表
		ResultParamList,    //育成結果表示時のパラメータ表
		PowerTraning,       //筋力トレーニング
		MagicTraning,       //魔力トレーニング
		SpeedTraning,       //素早さトレーニング
		HpTraning,          //体力トレーニング
		Rest,               //休息		
		PowerBack,		    //筋力トレーニング背景
		MagicBack,		    //魔力トレーニング背景
		SpeedBack,		    //素早さトレーニング背景
		HpBack,		        //体力トレーニング背景
		RestBack,		    //休息背景
		TextBox,		    //テキストボックス
		StaminaGage,        //スタミナゲージ
		StaminaBack,        //スタミナゲージ背景
		StaminaFrame,       //スタミナゲージ背景
		HpGage,			    //体力ゲージ
		HpGageBack,         //体力ゲージ背景
		GageFrame,          //ゲージ枠
		TurnBack,			//ターン数背景
		PowerAttack,	    //筋力攻撃アイコン
		MagicAttack,		//魔法攻撃アイコン
		AttackCover,        //攻撃アイコンに被せる画像
		UniqueGage,		    //ユニークゲージ
		Arrow,              //矢印
		SelectArrow,		//選択肢矢印
		NameSpace,			//名前入力スペース
		Safe,				//失敗率アイコン(30%以下)
		Anxiety,			//失敗率アイコン(30%以上70%以下)
		Danger,				//失敗率アイコン(70%以上)
		Max,
	};

private:
	//他からアクセスされることがないように
	CUIManager();

public:
	HRESULT Load(CDirectX11* Dx11);

	void SetDx11(CDirectX11& Dx11) { m_pDx11 = &Dx11; }

	static CSprite2D& GetSprite(UIList list) { return *GetInstance().m_pSprite2D[list]; }
private:
	CDirectX11* m_pDx11;

	CSprite2D* m_pSprite2D[UIList::Max];
};

