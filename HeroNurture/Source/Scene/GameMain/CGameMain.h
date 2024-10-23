#pragma once
#include "Scene/CSceneBase.h"
#include "SkinMeshObject/Kaito/CKaito.h"
#include "Camera/CCamera.h"
#include "StaticMeshObject/Sky/CSky.h"
#include "WriteText/WriteText.h"
#include "StaticMeshObject/Ground/CGround.h"
#include "SkinMeshObject/Player/CPlayer.h"


//ゲームメインシーン
class CGameMain
	:public CSceneBase
{
public:

public:
	CGameMain();
	~CGameMain();

	//初期化関数
	void Initialize() override;
	//構築関数
	void Create() override;
	//データ設定関数
	void LoadData() override;
	//破棄関数
	void Releace() override;
	//更新関数
	void Update() override;
	//描画関数
	void Draw() override;

private:
	//スカイボックス
	CSky* m_pSky;

	//地面
	CGround* m_pGround;

	//プレイヤー
	CPlayer* m_pPlayer;

	D3DXMATRIX	m_mView;	//ビュー(カメラ)行列.
	D3DXMATRIX	m_mProj;	//射影（プロジェクション）行列.


	//オープニングに移らせるフラグ
	bool m_Opening;
	//ボス出現シーンに移らせるフラグ
	bool m_BossApp;
	//ボス進化シーンに移らせるフラグ
	bool m_BossEvo;
	//必殺技シーンに移らせるフラグ
	bool m_Special;
	//ボス撃破シーンに移らせるフラグ
	bool m_BossDeath;

	//時間経過でかわるX
	float m_Time;


};

