#pragma once
#include "Scene\CSceneBase.h"
#include "Camera\CCamera.h"
#include "StaticMeshObject\Sky\CSky.h"
#include "WriteText\WriteText.h"
#include "StaticMeshObject\Ground\CGround.h"
#include "SkinMeshObject\Hero\CHeroBase.h"
#include "json.hpp"

//=====================================
// 前方宣言
//=====================================
//----各ヒーローのクラス
class CYui;
class CKaito;

// =======================
// 定数宣言 (_NS = トレーニング結果シーンで用いることを示す)
// =======================	
//----各ヒーローのカメラ配置・注視点----
static const D3DXVECTOR3 CAMPOS_NS  = { 0.0f, 5.2f, -2.8f };
static const D3DXVECTOR3 CAMLOOK_NS = { 0.0f, 6.2f,  3.0f };


class CNatureHeroSelectScene
	:public CSceneBase
{
public:
	CNatureHeroSelectScene();
	~CNatureHeroSelectScene();

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
	//アカウント名取得
	void SetUserName(std::wstring name) { m_UserName = name; }

private:

	//カメラマネージャ
	CCameraManager* m_pCamera;


    //=====================================
	// オブジェクトクラス
	//=====================================
	//----スタティックメッシュ-----
	//スカイボックス
	std::unique_ptr<CSky>    m_pSky;
	//地面
	std::unique_ptr<CGround> m_pGround;

	//----スキンメッシュ----
	//ユイ
	std::unique_ptr<CYui>	m_pYui;
	//カイト
	std::unique_ptr<CKaito> m_pKaito;


	//ユーザー名
	std::wstring m_UserName;


};