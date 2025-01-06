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
//シーン
class CSceneManager;
//ライト
class CLightManager;
//文字描画クラス
class WriteText;
//汎用クラス
class CUtility;

//Json使用に必要な名前空間の格納
using json = nlohmann::json;

// =======================
// 定数宣言
// =======================		
//----各ヒーローごとのカメラ位置/注視点---
//ユイ
const D3DXVECTOR3 CAMERAPOS_YUI  = { 0.0, 5.0, -4.0 };
const D3DXVECTOR3 CAMERALOOK_YUI = { 0.0, 5.0, 0.0 };
//カイト
const D3DXVECTOR3 CAMERAPOS_KAITO  =  { 0.0, 5.0, -4.5 };
const D3DXVECTOR3 CAMERALOOK_KAITO =  { 0.0, 5.0, 0.0 };

//----UI情報(_N = 育成シーンで用いることを示す)----
//パラメータ背景
constexpr float PARAMBACK_POSX_N     = 330.0f; //X座標
constexpr float PARAMBACK_POSY_N     = 410.0f; //Y座標
const D3DXVECTOR3 PARAMBACK_SCALE_N = { 0.8f,0.8f,0.8f }; //拡縮
//トレーニングUI
constexpr float TRANING_POSX_N     = 300.0f; //X座標
constexpr float TRANING_POSY_N     = 580.0f; //Y座標
constexpr float TRANING_INTERVAL_N = 180.0f; //配置間隔
const D3DXVECTOR3 TRANING_SCALE_N  = { 0.5f,0.5f,0.5f }; //拡縮
//数値
constexpr float PARAMVALUE_POSX_N = 425.0f; //X座標
constexpr float PARAMVALUE_POSY_N = 430.0f; //Y座標
constexpr float PARAMVALUE_INTERVAL_N = 150.0f; //配置間隔
//ランク
constexpr float RANK_POSX_N = 350.0f; //X座標
constexpr float RANK_POSY_N = 430.0f; //Y座標
constexpr float RANK_INTERVAL_N = 150.0f;//配置間隔
//位置の補正を入れる桁数
constexpr int   CORRECTION_DIGIT = 3;

//----スタミナゲージ----
//スタミナの最大値
constexpr float STAMINA_MAX = 100.0f;

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
class CNatureScene
	:public CSceneBase
{
public:
	CNatureScene();
	~CNatureScene();

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
	void CreateNatureUI(std::unique_ptr<CUIObject>& gage, std::unique_ptr<CUIObject>& back);
	//データのロード
	void LoadNatureUI(std::unique_ptr<CUIObject>& gage, std::unique_ptr<CUIObject>& back);
	//初期化
	void InitNatureUI(std::unique_ptr<CUIObject>& gage, std::unique_ptr<CUIObject>& back);
	//描画
	void DrawNatureUI(std::unique_ptr<CUIObject>& gage, std::unique_ptr<CUIObject>& back);

public:
	//各ヒーロー用ファイルの作成・読み込み
	void LoadHeroData(const std::string& heroname);

	//トレーニング選択処理
	void SelectTraning();

	//UIの初期設定
	void UIInit(std::unique_ptr<CUIObject>& traning,float x, float y, float interval, D3DXVECTOR3 scale, int no);

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
	void GageAnim();
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
	//地面クラス
	std::unique_ptr<CGround> m_pGround;
	//スカイボックスクラス
	std::unique_ptr<CSky>	 m_pSky;
	
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
	//スタミナゲージの幅
	float m_GageWidth;

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

