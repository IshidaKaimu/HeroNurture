#pragma once
#include <Windows.h>
#include "CSprite3D.h"
#include "CSprite2D.h"
#include "CUIObject.h"

//CPU列挙型
enum class enCPUList
{
    Kicker = 0, //キッカー
    Keeper,     //キーパー
    none = -1,
};

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

	//初期化処理

	virtual void Initialize();

	virtual void Update() {};
	virtual void Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera);

	virtual void Create() {};

	virtual void  LoadData() {};

	//シーン読み込み関数
	virtual void LoadScene(){};


protected:
    //フェードアウト
    bool FadeOut();
    //フェードイン
    bool FadeIn();

protected:
	//カメラ情報.
	CAMERA		m_Camera;	
	//行列.
	D3DXMATRIX	m_mView;	//ビュー(カメラ)行列.
	D3DXMATRIX	m_mProj;	//射影（プロジェクション）行列.

	//シーン遷移用
	bool        m_IsScene;  
    //シーン遷移フラグ
    bool        m_SceneTransitionFlg;
    //選択中番号
    int         m_SelectNo;

	float       m_AnimCnt;				//アニメーションカウント


    //CPU
    enCPUList   m_CPU;

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

