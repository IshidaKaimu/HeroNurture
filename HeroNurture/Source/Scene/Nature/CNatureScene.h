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
	void CreateHeroData( const std::string& heroname );

	//残りターン数の描画
	void DrawRemainingTurn();

public:
	//カメラマネージャクラス
	CCameraManager* m_pCamera;

	//ヒーローマネージャクラス
	CHeroManager* m_pHero;

	//jsonクラス
	std::unique_ptr<CJson> m_pJson;

	//jsonデータ保存用
	json m_JsonData;

	//名前構造体
	HeroName m_Name;

	//----オブジェクトクラス----
	//スタティックメッシュ
	//地面クラス
	CGround*		m_pGround;
	//スカイボックスクラス
	CSky*			m_pSky;


};

