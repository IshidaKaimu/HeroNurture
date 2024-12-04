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

//Json使用に必要な名前空間の格納
using json = nlohmann::json;

//----定数宣言----
//各ヒーローごとのカメラ位置/注視点
//ユイ
const D3DXVECTOR3 CAMERAPOS_YUI  = { 0.0, 5.0, -6.0 };
const D3DXVECTOR3 CAMERALOOK_YUI = { 0.0, 5.0, 0.0 };
//カイト
const D3DXVECTOR3 CAMERAPOS_KAITO  =  { 0.0, 5.0, -4.5 };
const D3DXVECTOR3 CAMERALOOK_KAITO =  { 0.0, 5.0, 0.0 };

//パラメータUI情報
//アイコン・パラメータ名
constexpr float PARAM_POSX = 225.0f;
constexpr float PARAM_POSY = 450.0f;
//数値
constexpr float PARAMVALUE_POSX = 230.0f;

//ヒーロー名構造体
struct HeroName
{
	//ユイ
	std::string Yui = "Yui";
	//カイト
	std::string Kaito = "Kaito";
};

//----------------
//育成シーンクラス
//----------------
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

public:
	//各ヒーロー用ファイルの作成・読み込み
	void LoadHeroData( const std::string& heroname );

	//パラメータ情報の書き込み
	void WriteParam( const std::string& heroname );

	//パラメータUIの設定
	void ParamInit(CUIObject* param, int no);

	//パラメータの描画
	void DrawParam();

	//残りターン数の描画
	void DrawRemainingTurn();

public:
	//カメラマネージャクラス
	CCameraManager* m_pCamera;

	//ヒーローマネージャクラス
	CHeroManager* m_pHero;

	//jsonクラス
	std::unique_ptr<CJson> m_pJson;

	//名前構造体
	HeroName m_Name;

	//----オブジェクトクラス----
	//スタティックメッシュ
	//地面クラス
	std::unique_ptr<CGround> m_pGround;
	//スカイボックスクラス
	std::unique_ptr<CSky>	 m_pSky;
	
	//UI
	//各パラメータ表示
	//筋力
	CUIObject* m_pPowerParam;
	//魔力
	CUIObject* m_pMagicParam;
	//素早さ
	CUIObject* m_pSpeedParam;
	//体力
	CUIObject* m_pHpParam;

	//----json関連----
    //パラメータ情報の書き込み用
	json m_ParamWriter;
	//パラメータデータ格納用
	json m_ParamData;

};

