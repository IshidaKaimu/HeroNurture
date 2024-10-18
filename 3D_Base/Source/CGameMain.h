#pragma once
#include "CSceneBase.h"
#include "CKaito.h"
#include "CCamera.h"
#include "CSky.h"
#include "WriteText.h"
#include "CGround.h"



//ゲームメインシーン
class CGameMain
	:public CSceneBase
{
public:

public:
	CGameMain();
	~CGameMain();


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
	//文字の動き
	float Easing(float x);

private:
	//スカイボックス
	CSky* m_pSky;

	//地面
	CGround* m_pGround;

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

