#pragma once
#include "Scene\CSceneBase.h"

//=====================================
// 前方宣言
//=====================================
//ヒーローマネージャー
class CHeroManager;
//敵のヒーローマネージャー
class CEnemyHeroManager;
//カメラマネージャー
class CCameraManager;

//=====================================
// 定数宣言(_U = 固有攻撃シーンで用いることを示す)
//=====================================
//----カメラ情報----
//ユイの固有攻撃シーン
const D3DXVECTOR3 YUI_CAMPOS  = { -1.0f,2.0f,-7.0f }; //初期座標
const D3DXVECTOR3 YUI_CAMLOOK = { -1.0f,2.0f,0.0f };  //初期注視点
//カイトの固有攻撃シーン
const D3DXVECTOR3 KAITO_CAMPOS  = { -1.0f,2.0f,-7.0f }; //初期座標
const D3DXVECTOR3 KAITO_CAMLOOK = { -1.0f,2.0f,0.0f };  //初期注視点


class CUniqueAttack
	: public CSceneBase
{
public:
	CUniqueAttack();
	~CUniqueAttack();

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

private:
	//それぞれのヒーローの固有攻撃アニメーションに用いるカメラワーク
	void YuiCameraWork();  //ユイ
	void KaitoCameraWork();//カイト


private:
	//ヒーローマネージャー
	CHeroManager* m_pHero;
	//敵のヒーローマネージャー
	CEnemyHeroManager* m_pEnemyHero;
	//カメラマネージャー
	CCameraManager* m_pCamera;
};
