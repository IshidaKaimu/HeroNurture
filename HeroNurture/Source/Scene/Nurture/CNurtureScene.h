#pragma once
#include "SkinMeshObject\Hero\CHeroManager.h"
#include "Scene\CSceneBase.h"
#include "StaticMeshObject\Sky\CSky.h"
#include "StaticMeshObject\Ground\CGround.h"
#include "json.hpp"
#include <memory>
#include "Json\CJson.h"

// =======================
// 前方宣言
// =======================		
//----マネージャークラス----
//ImGui
class ImGuiManager;
//シーン
class CSceneManager;
//育成モード
class CNurtureManager;
//ライト
class CLightManager;
//サウンド
class CSoundManager;
//文字描画クラス
class WriteText;
//汎用クラス
class CUtility;


//Json使用に必要な名前空間の格納
using json = nlohmann::json;

// =======================
// 定数宣言
// =======================	
namespace Constant_NurtureScene
{
	//----各ヒーローごとのカメラ位置/注視点---
	//ユイ
	const D3DXVECTOR3 CAMERAPOS_YUI  = { 0.0, 5.0, -4.0 }; //座標
	const D3DXVECTOR3 CAMERALOOK_YUI = { 0.0, 5.0, 0.0 };  //注視点
	//カイト
	const D3DXVECTOR3 CAMERAPOS_KAITO  = { 0.0, 5.0, -4.5 }; //座標
	const D3DXVECTOR3 CAMERALOOK_KAITO = { 0.0, 5.0, 0.0 };  //注視点

	//----UI情報----
	//パラメータ背景
	const D3DXVECTOR3 PARAMBACK_POS   = { 330.0f,410.0f,0.0f }; //座標
	const D3DXVECTOR3 PARAMBACK_SCALE = { 0.8f,0.8f,0.8f };   //拡縮
	//トレーニングUI
	const D3DXVECTOR3 TRANING_POS = { 200.0f,580.0f,0.0f };  //X座標
	constexpr float   TRANING_INTERVAL = 180.0f;	         //配置間隔
	const D3DXVECTOR3 TRANING_SCALE = { 0.5f,0.5f,0.5f };    //拡縮
	//数値
	const D3DXVECTOR2 PARAMVALUE_POS = { 425.0f,430.0f };    //座標
	constexpr float PARAMVALUE_INTERVAL = 150.0f;			 //配置間隔
	//ランク
	const D3DXVECTOR2 RANK_POS = { 350.0f,430.0f };     //座標
	constexpr float RANK_INTERVAL = 150.0f;				      //配置間隔
	//スタミナゲージ
	const D3DXVECTOR3 STAMINA_POS	   = { 670.0f, 7.0f, 0.0f }; //ゲージ・ゲージ背景座標
	const D3DXVECTOR3 STAMINAFRAME_POS = { 575.0f, 0.0f, 0.0f }; //ゲージ枠座標
	//ターン数背景
	const D3DXVECTOR3 TURNBACK_POS = { 0.0f, 0.0f, 0.0f };  //座標
	//ターン数
	const D3DXVECTOR2 TURN_POS = { 180.0f,-10.0f };
	//「残り」テキスト
	const D3DXVECTOR2 REMAININGTEXT_POS = { 10.0f,-20.0f };
	//「ターン」テキスト
	const D3DXVECTOR2 TURNTEXT_POS = { 240.0f, -20.0f };
	//共通
	const D3DXVECTOR3 BASIC_SCALE   = { 1.0f, 1.0f, 1.0f }; //拡縮
	const D3DXVECTOR2 BASIC_DISPLAY = { 1.0f,1.0f };	    //幅
	//位置の補正を入れる桁数
	constexpr int CORRECTION_DIGIT = 3;
	//失敗率背景
	const D3DXVECTOR3 FAILUREBACK_POS   = { 30.0f, 350.0f, 0.0f }; //座標
	const D3DXVECTOR3 FAILUREBACK_SCALE = { 0.7f, 0.7f, 0.7f };	   //拡縮
	const D3DXVECTOR2 FAILUREBACK_DISP  = { 1.0f, 1.0f };		   //幅
	constexpr float   FAILUREBACK_ALPHA = 1.0f;					   //α値
	//失敗率
	const D3DXVECTOR3 FAILURERATE_POS   = { 95.0f, 430.0f, 0.0f };//座標
	//「失敗率」テキスト
	const D3DXVECTOR3 FAILURETEXT_POS   = { 55.0f, 370.0f, 0.0f }; //座標


	//失敗率基準値
	constexpr int SAFE = 30;	//安全
	constexpr int ANXIETY = 70; //警告

	//----スタミナゲージ----
	//スタミナの最大値
	constexpr float STAMINA_MAX = 100.0f;
}
//ヒーロー名構造体
struct HeroName
{
	//ユイ
	std::string Yui = "Yui";
	//カイト
	std::string Kaito = "Kaito";
};

//=====================================
//育成シーンクラス
//制作者：石田櫂夢
//=====================================
class CNurtureScene
	:public CSceneBase
{
public:
	CNurtureScene();
	~CNurtureScene();

	//構築関数
	void Create()	  override;
	//破棄関数
	void Releace()	  override;
	//データ設定関数
	void LoadData()	  override;
	//初期化関数
	void Initialize() override;
	//更新関数
	void Update()     override;
	//描画関数
	void Draw()		  override;
	//デバッグ用関数
	void Debug();

protected:
	// =======================
    // 育成関連のシーンで固定するUI関連の関数
    // =======================		
    //インスタンス生成
	void CreateNurtureUI(
		std::unique_ptr<CUIObject>& gage, 
		std::unique_ptr<CUIObject>& back,
		std::unique_ptr<CUIObject>& frame,
		std::unique_ptr<CUIObject>& turnback);
	//データのロード
	void LoadNurtureUI(
		std::unique_ptr<CUIObject>& gage,
		std::unique_ptr<CUIObject>& back,
		std::unique_ptr<CUIObject>& frame,
		std::unique_ptr<CUIObject>& turnback);
	//初期化
	void InitNurtureUI(
		std::unique_ptr<CUIObject>& gage, 
		std::unique_ptr<CUIObject>& back, 
		std::unique_ptr<CUIObject>& frame,
		std::unique_ptr<CUIObject>& turnback);
	//描画
	void DrawNurtureUI(
		std::unique_ptr<CUIObject>& gage, 
		std::unique_ptr<CUIObject>& back, 
		std::unique_ptr<CUIObject>& frame,
		std::unique_ptr<CUIObject>& turnback);
	//=========================

public:
	//各ヒーロー用ファイルの作成・読み込み
	void LoadHeroData(const std::string& heroname);

	//トレーニング選択処理
	void SelectTraning();

	//各トレーニングUIの初期設定
	void UIInit(std::unique_ptr<CUIObject>& traning, D3DXVECTOR3 pos, float interval, D3DXVECTOR3 scale, int no);

	//各失敗率背景の初期設定
	void FailureRateBackInit(std::unique_ptr<CUIObject>& back, D3DXVECTOR3 pos);

	// =======================
	// パラメータ関連関数
	// =======================		
	//ヒーローのごとのパラメータ情報の書き込み
	void SaveParam();
	//パラメータの描画
	void DrawParam();

	//各トレーニングの描画
	void DrawTraning();

	//残りターン数の描画
	void DrawRemainingTurn();

	//ゲージアニメーション
	void StaminaGageAnim();
public:
	//カメラマネージャクラス
	CCameraManager* m_pCamera;

	//ヒーローマネージャクラス
	CHeroManager* m_pHero;

	//名前構造体
	HeroName m_Name;

	// =======================
	// オブジェクトクラス
	// =======================		
	//----スタティックメッシュ----
	//地面
	std::unique_ptr<CGround> m_pGround;
	//----------------------------

	//----UI----	
	//パラメータ背景
	std::unique_ptr<CUIObject>  m_pParamBack;
	//筋力トレーニングUI
	std::unique_ptr<CUIObject> m_pPowerTraning;
	//魔力トレーニングUI
	std::unique_ptr<CUIObject> m_pMagicTraning;
	//素早さトレーニングUI
	std::unique_ptr<CUIObject> m_pSpeedTraning;
	//体力トレーニングUI
	std::unique_ptr<CUIObject> m_pHpTraning;
	//休息UI
	std::unique_ptr<CUIObject> m_pRest;
	//スタミナゲージ
	std::unique_ptr<CUIObject> m_pStaminaGage;
	//スタミナゲージ背景
	std::unique_ptr<CUIObject> m_pStaminaBack;
	//スタミナゲージ枠
	std::unique_ptr<CUIObject> m_pStaminaFrame;
	//スタミナゲージの幅
	float m_GageWidth;
	//ターン数の背景
	std::unique_ptr<CUIObject> m_pTurnBack;
	//失敗率背景(30%以下)
	std::unique_ptr<CUIObject> m_pSafeBack;
	//失敗率背景(30%以上70%以下)
	std::unique_ptr<CUIObject> m_pAnxietyBack;
	//失敗率背景(70%以上)
	std::unique_ptr<CUIObject> m_pDangerBack;
	//----------

	//===================================

	// =======================
	// json関連
	// =======================	
	//jsonクラス
	std::unique_ptr<CJson> m_pJson;
	//パラメータ情報の書き込み用
	json m_ParamWriter;
	//パラメータデータ格納用
	json m_ParamData;
};

