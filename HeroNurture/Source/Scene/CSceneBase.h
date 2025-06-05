#pragma once
#include <Windows.h>
#include "UIObject\CUIObject.h"
#include "SpriteObject\CSpriteObject.h"
#include "Effect\CEffect.h"
#include <memory>

//=====================================
// 前方宣言
//=====================================
//----マネージャークラス----
class CSprite3DManager;
class CStaticMeshManager;
class CUIManager;
class CEffect;
class WriteText;
//--------------------------

//----オブジェクトクラス----
class CSky;
//--------------------------

//=====================================
// 定数宣言
//=====================================
//ライト情報
const D3DXVECTOR3 LIGHT_POS = { 0.0f, 1.0f, 0.0f };
const D3DXVECTOR3 LIGHT_DIR = { 0.0f, 1.0f, 0.0f };

//----UI----
//矢印
//左
const D3DXVECTOR3 ARROW_LEFT_POS_NS    = { 300.0f, 490.0f, 0.0f };        //育成ヒーロー選択時座標
const D3DXVECTOR3 ARROW_LEFT_POS_BS    = { 200.0f, 490.0f, 0.0f };        //座標
const D3DXVECTOR3 ARROW_LEFT_ROTATE = { 0.0f, 0.0f, D3DXToRadian(180.0f)};//回転
//右
const D3DXVECTOR3 ARROW_RIGHT_POS_NS = { 1000.0f, 400.0f, 0.0f };//育成ヒーロー選択時座標
const D3DXVECTOR3 ARROW_RIGHT_POS_BS = { 1100.0f, 400.0f, 0.0f };//バトルヒーロー選択時座標
//矢印共通
const D3DXVECTOR3 ARROW_SCALE = { 1.0f, 1.0f, 1.0f };//拡縮
const D3DXVECTOR2 ARROW_DISP  = { 1.0f, 1.0f };		 //幅
constexpr float   ARROW_ALPHA = 1.0f;			     //α値
//操作方法指示バー
const D3DXVECTOR3 CONTROLBAR_POS   = { 0.0f, 690.0f, 0.0f }; //座標
const D3DXVECTOR3 CONTROLBAR_SCALE = { 1.0f, 1.0f, 1.0f };   //拡縮
const D3DXVECTOR2 CONTROLBAR_DISP  = { 1.0f, 0.6f };		 //幅
constexpr float   CONTROLBAR_ALPHA = 1.0f;					 //α値
//「Enter 決定」テキスト
const D3DXVECTOR2 ENTERTEXT_POS  = { 970.0f, 675.0f }; //座標
//「Esc 戻る」テキスト
const D3DXVECTOR2 ESCAPETEXT_POS = { 1150.0f, 675.0f }; //座標
//-------

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
	//汎用背景の描画
	void DrawBasicBackGround();
	//操作方法指示バーテンプレートの描画
	void DrawControlBar( bool basictext);
	//空の描画
	void DrawSky();
public:
	//白フェード関連の初期化
	void InitWhiteFade();
	//白フェード
	void PlayWhiteFade(int max, float speed, float alpha);
	//白フェード中かの取得
	bool GetWhiteFadeNow() { return m_WhiteFadeNow; }

protected:
	//ライト情報
	LIGHT       m_Light;

	//----カメラを移動させる値----
	D3DXVECTOR3 m_MoveCamPos; //座標
	D3DXVECTOR3 m_MoveCamLook;//注視点
	//----------------------------

	//----デバッグ用情報----
	//オブジェクト位置
	D3DXVECTOR3 m_DebugPos;
	//オブジェクト回転
	D3DXVECTOR3 m_DebugRotate;
	//UI位置
	D3DXVECTOR2 m_DebugUiPos;
	//カメラ位置
	D3DXVECTOR3 m_DebugCamPos;
	//カメラ注視点
	D3DXVECTOR3	m_DebugCamLook;
	//-----------------------

	//----フラグ----
	//シーン遷移用
	bool        m_IsScene;  
    //シーン遷移フラグ
    bool        m_SceneTransitionFlg;
	//--------------

	//----イベントシーン----
	//イベント中アニメーションのカット番号
	int m_Scene;
	//アニメーションカウント
	float       m_AnimCnt;
	//----------------------

	//選択中番号
	int         m_SelectNo;

private:
	//----フェード----
	//シーン遷移	
	std::unique_ptr<CUIObject> m_pFade;         //フェード用画像
	int			m_FadeTime;		                //シーン切り替え用のタイマー	
	float		m_FadeAlpha;	                //アルファ値	
    bool        m_FadeOutFlg;                   //フェードアウトフラグ(フェードアウト中にフェードインさせないため)
	//白フェード
	std::unique_ptr<CUIObject> m_pWhiteFade;	//白フェード用画像
	int			m_WhiteFadeTime;		        //シーン切り替え用のタイマー	
	bool		m_AlphaChange;					//フェード回数制御用フラグ
	int         m_WhiteFadeCnt;					//フェード回数のカウント
	float       m_WhiteFadeAlpha;				//フェード画像のα値
	bool        m_WhiteFadeNow;				    //白フェード中であるか
	//----------------

	//----UI-----
	std::unique_ptr<CUIObject> m_pBasicBackGround; 	//汎用背景
	std::unique_ptr <CUIObject> m_pControlBar;      //操作方法指示バー画像
	//-----------

	//----スタティックメッシュ----
	std::unique_ptr<CSky> m_pSky; //空
	//----------------------------
};

