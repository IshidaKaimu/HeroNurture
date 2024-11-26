#pragma once
#include "Scene/CSceneBase.h"
#include "Camera/CCamera.h"
#include "StaticMeshObject/Sky/CSky.h"
#include "WriteText/WriteText.h"
#include "StaticMeshObject/Ground/CGround.h"
#include "SkinMeshObject/Hero/CHeroBase.h"
#include "json.hpp"

//前方宣言
//----各ヒーローのクラス
class CYui;
class CKaito;

//----各ヒーローのカメラ配置・注視点----
//ユイ
static const D3DXVECTOR3 CAMPOS_YUI  = { 0.0f, 5.2f, -2.8f };
static const D3DXVECTOR3 CAMLOOK_YUI = { 0.0f, 6.2f,  3.0f };
////カイト
//static const D3DXVECTOR3 CAMPOS_KAITO  = { 0.0f, 5.0f, -4.0f };
//static const D3DXVECTOR3 CAMLOOK_KAITO = { 0.0f, 5.0f,  3.0f };

//ヒーローセレクトシーン
class CHeroSelect
	:public CSceneBase
{
public:
	CHeroSelect();
	~CHeroSelect();

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

	//スカイボックス
	CSky* m_pSky;

	//地面
	CGround* m_pGround;

	//ユーザー名
	std::wstring m_UserName;

	//デバッグ用
	D3DXVECTOR3 CamPos;
	D3DXVECTOR3 CamLook;	

    //----各ヒーロークラス----
	//ユイ
	CYui*	m_pYui;
	//カイト
	CKaito* m_pKaito;


	//選択肢用番号
	int m_SelectNo;


};