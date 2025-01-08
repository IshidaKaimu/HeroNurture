#pragma once
#pragma once
#include "SkinMeshObject\CSkinMeshObject.h"
#include "SkinMeshObject\Hero\CHeroBase.h"

//=====================================
//カイトクラス
//制作者：石田櫂夢
//=====================================

class CKaito
	:public CHeroBase
{
public:
	CKaito();
	virtual ~CKaito() override;


	//初期化関数
	void Initialize() override;

	//データ読み込み関数
	void LoadMeshData() override;

	//パラメータ情報読み込み
	void LoadParamData(const json& jsondata) override;

	//バトルパラメータ情報読み込み
	void LoadBattleParamData(const json& jsondata) override;

	//更新関数
	void Update() override;

	//描画関数
	void Draw() override;

	// =======================
	// 各シーンごとのアニメーション
	// =======================
	//育成ヒーロー選択シーン
	virtual void NatureHeroSelectAnimation() override;
	//バトルヒーロー選択シーン
	virtual void BattleHeroSelectAnimation() override;
	// 育成シーン		
	void NatureAnimation(int no) override;

	void SetAnimSpeed(double speed) { m_AnimSpeed = speed; }

	//場面切り替え
	bool SceneChange();

	//アニメーション切り替えフラグ立てる
	void AnimChange();

protected:
	D3DXVECTOR3    m_BonePos;			//カイト:ボーン座標
	bool           m_Run;				//走り出すフラグ
	bool           m_AnimChange;		//アニメーション切り替えフラグ
	float          m_EffPosZ;			//エフェクトのZ軸位置

};

