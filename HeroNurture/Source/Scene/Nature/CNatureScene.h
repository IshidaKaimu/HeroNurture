#pragma once
#include "SkinMeshObject\Hero\CHeroManager.h"
#include "Scene\CSceneBase.h"
#include "StaticMeshObject\Sky\CSky.h"
#include "StaticMeshObject\Ground\CGround.h"
#include "json.hpp"
#include <memory>

//----前方宣言----
class WriteText;
class CJson;
class CSceneManager;

//Json使用に必要な名前空間の格納
using json = nlohmann::json;

// =======================
// 定数宣言
// =======================		
//----各ヒーローごとのカメラ位置/注視点---
//ユイ
const D3DXVECTOR3 CAMERAPOS_YUI  = { 0.0, 5.0, -6.0 };
const D3DXVECTOR3 CAMERALOOK_YUI = { 0.0, 5.0, 0.0 };
//カイト
const D3DXVECTOR3 CAMERAPOS_KAITO  =  { 0.0, 5.0, -4.5 };
const D3DXVECTOR3 CAMERALOOK_KAITO =  { 0.0, 5.0, 0.0 };

//----パラメータUI情報----
//アイコン・パラメータ名
constexpr float PARAM_POSX = 225.0f;
constexpr float PARAM_POSY = 450.0f;
//数値
constexpr float PARAMVALUE_POSX = 230.0f;

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


protected:
	// =======================
    // 育成関連のシーンで固定するUI関連の関数
    // =======================		
    //インスタンス生成
	void CreateNatureUI( std::unique_ptr<CUIObject>& gage );
	//データのロード
	void LoadNatureUI( std::unique_ptr<CUIObject>& gage );
	//初期化
	void InitNatureUI( std::unique_ptr<CUIObject>& gage );
	//描画
	virtual void DrawNatureUI( std::unique_ptr<CUIObject>& gage );

public:
	//各ヒーロー用ファイルの作成・読み込み
	void LoadHeroData( const std::string& heroname );

	//トレーニング選択処理
	void SelectTraning();

	// =======================
	// パラメータ関連関数
	// =======================		
	//ヒーローのごとのパラメータ情報の書き込み
	void SaveParam();
	//パラメータ情報の書き込み(SaveParam関数で使う)
	void WriteParam( const std::string& heroname );
	//パラメータUIの初期設定
	void ParamInit( std::unique_ptr<CUIObject>& param, int no );
	//パラメータの描画
	void DrawParam();

	//残りターン数の描画
	void DrawRemainingTurn();

	//ゲージアニメーション
	void GageAnim();

public:
	//カメラマネージャクラス
	CCameraManager* m_pCamera;

	//ヒーローマネージャクラス
	CHeroManager* m_pHero;

	//jsonクラス
	std::unique_ptr<CJson> m_pJson;

	//名前構造体
	HeroName m_Name;

	// =======================
	// オブジェクトクラス
	// =======================		
	//スタティックメッシュ
	//地面クラス
	std::unique_ptr<CGround> m_pGround;
	//スカイボックスクラス
	std::unique_ptr<CSky>	 m_pSky;
	
	//UI
	//----各パラメータ----
	//筋力
	std::unique_ptr<CUIObject> m_pPowerParam;
	//魔力
	std::unique_ptr<CUIObject> m_pMagicParam;
	//素早さ
	std::unique_ptr<CUIObject> m_pSpeedParam;
	//体力
	std::unique_ptr<CUIObject> m_pHpParam;
	//----スタミナゲージ----
	//ゲージ
	std::unique_ptr<CUIObject> m_pStaminaGage;

	// =======================
	// json関連
	// =======================		
	//パラメータ情報の書き込み用
	json m_ParamWriter;
	//パラメータデータ格納用
	json m_ParamData;

};

