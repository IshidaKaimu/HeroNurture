#pragma once
#include "Scene/CSceneBase.h"
#include "SkinMeshObject/Kaito/CKaito.h"
#include "Camera/CCamera.h"
#include "StaticMeshObject/Sky/CSky.h"
#include "WriteText/WriteText.h"
#include "StaticMeshObject/Ground/CGround.h"
#include "SkinMeshObject/Player/CPlayer.h"
#include "json.hpp"

//ゲームメインシーン
class CGameMain
	:public CSceneBase
{
public:
	CGameMain();
	~CGameMain();

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

	//プレイヤー
	CPlayer* m_pPlayer;

	//デバッグ用
	D3DXVECTOR3 CamPos;
	D3DXVECTOR3 CamLook;	
};