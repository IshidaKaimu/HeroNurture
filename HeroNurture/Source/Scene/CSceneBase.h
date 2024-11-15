#pragma once
#include <Windows.h>
#include "Sprite3D/CSprite3D.h"
#include "Sprite2D/CSprite2D.h"
#include "UIObject/CUIObject.h"

//==============================//
//		シーンベースクラス		//
//==============================//

class CSceneBase
{
public:
	//フェードの最大時間
	static constexpr int	FADE_TIME = FPS;	//約1秒間
	static constexpr bool	DEBUG_FLG = false;	//デバッグフラグ
public:
	CSceneBase();
	virtual ~CSceneBase();

	//初期化関数
	virtual void Initialize();

	//更新関数
	virtual void Update() {};

	//描画関数
	virtual void Draw();

	//構築関数
	virtual void Create() {};

	//データ読み込み関数
	virtual void  LoadData() {};

	//シーン読み込み関数
	virtual void LoadScene(){};

	//破棄関数
	virtual void Releace();


protected:
    //フェードアウト
    bool FadeOut();
    //フェードイン
    bool FadeIn();

protected:
	//ライト情報
	LIGHT       m_Light;

	//シーン遷移用
	bool        m_IsScene;  
    //シーン遷移フラグ
    bool        m_SceneTransitionFlg;
    //選択中番号
    int         m_SelectNo;

	float       m_AnimCnt;				//アニメーションカウント

    //UI
    CUIObject* m_pLogo;         //ロゴ
    CUIObject* m_pBlueFrame;    //選択中青枠

private:
	//フェード	
    static constexpr float FADESPEED = 0.05f;	//フェードスピード
	CUIObject*	m_pFade;
	int			m_FadeTime;		        //シーン切り替え用のタイマー	
	float		m_FadeAlpha;	        //アルファ値	
    bool        m_FadeOutFlg;           //フェードアウトフラグ(フェードアウト中にフェードインさせないため)

};

