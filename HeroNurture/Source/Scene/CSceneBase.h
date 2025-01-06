#pragma once
#include <Windows.h>
#include "Sprite3D\CSprite3D.h"
#include "Sprite2D\CSprite2D.h"
#include "UIObject\CUIObject.h"
#include <memory>

//=====================================
//シーン基底クラス
//制作者：石田櫂夢
//=====================================
class CSceneBase
{
	//フェードの最大時間
	static constexpr int	FADE_TIME = FPS;	//約1秒間
	static constexpr bool	DEBUG_FLG = false;	//デバッグフラグ
	static constexpr float  FADESPEED = 0.05f;	//フェードスピード

public:
	CSceneBase();
	virtual ~CSceneBase();

	//初期化関数
	virtual void Initialize();

	//更新関数
	virtual void Update();

	//描画関数
	virtual void Draw();

	//構築関数
	virtual void Create() {};

	//データ読み込み関数
	virtual void  LoadData() {};

	//破棄関数
	virtual void Releace();

protected:
    //フェードアウト
    bool FadeOut();
    //フェードイン
    bool FadeIn();
public:
	//白フェード関連の初期化
	void InitWhiteFade();
	//白フェード
	void PlayWhiteFade(int max, float speed, float alpha);


protected:
	//ライト情報
	LIGHT       m_Light;

	//----デバッグ用カメラ情報----
	//位置
	D3DXVECTOR3 m_CamPos;
	//注視点
	D3DXVECTOR3	m_CamLook;

	//----フラグ----
	//シーン遷移用
	bool        m_IsScene;  
    //シーン遷移フラグ
    bool        m_SceneTransitionFlg;
	//白フェードフラグ
	bool        m_WhiteFlag;

	//選択中番号
    int         m_SelectNo;

	//アニメーションカウント
	float       m_AnimCnt;		
private:
	//----フェード----
	//シーン遷移	
	std::unique_ptr<CUIObject> m_pFade;        //フェード用UI
	int			m_FadeTime;		                //シーン切り替え用のタイマー	
	float		m_FadeAlpha;	                //アルファ値	
    bool        m_FadeOutFlg;                   //フェードアウトフラグ(フェードアウト中にフェードインさせないため)
	//白フェード
	std::unique_ptr<CUIObject> m_pWhiteFade;	//白フェード用UI
	int			m_WhiteFadeTime;		        //シーン切り替え用のタイマー	
	bool		m_AlphaChange;					//フェード回数制御用フラグ
	int         m_WhiteFadeCnt;					//フェード回数のカウント
	float       m_WhiteFadeAlpha;				//フェード画像のα値
};

