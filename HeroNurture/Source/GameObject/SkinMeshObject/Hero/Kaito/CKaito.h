#pragma once
#pragma once
#include "SkinMeshObject\CSkinMeshObject.h"
#include "SkinMeshObject\Hero\CHeroBase.h"


// =======================
// 定数宣言
// =======================
//バトルシーンでの初期情報
const D3DXVECTOR3 BATTLE_SCALE_KAITO  = { 0.3f,0.3f,0.3f };//拡縮

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

	// =======================
	// 各シーンごとの初期化
	// =======================
	//主に使用する初期化関数
	void Initialize() override;
	//バトルシーンで使用する初期化
	void BattleInitialize() override;
	//敵になった際の初期化関数
	void EnemyInit() override;

	//データ読み込み関数
	void LoadMeshData() override;

	//パラメータ情報読み込み
	void LoadParamData(const json& jsondata) override;

	//バトルパラメータ情報読み込み
	void SetBattleParamData(const json& jsondata) override;

	//更新関数
	void Update() override;

	//描画関数
	void Draw() override;

	//デバッグ関数
	void Debug() override;

	// =======================
	// 各シーンごとのアニメーション
	// =======================
	//育成ヒーロー選択シーン
	virtual void NatureHeroSelectAnimation() override;
	//バトルヒーロー選択シーン
	virtual void BattleHeroSelectAnimation() override;
	// 育成シーン		
	void NatureAnimation(int no) override;

	// =======================
	// 攻撃関数
	// =======================
	//攻撃1
	float PowerAttack() override;
	//攻撃2
	float MagicAttack() override;

	// =======================
	// 各バトルフェーズでのアニメーション
	// =======================
	// 行動選択中のアニメーション
	void MoveSelectAnim() override;
	//----攻撃フェーズ----
	//攻撃1中のアニメーション
	void PowerAttackAnim(float vector) override;
	//攻撃2中のアニメーション
	void MagicAttackAnim(float vector) override;
	//固有攻撃中のアニメーション
	void UniqueAttackAnim() override;
	//ダメージを受けた時のアニメーション
	void DamageAnim(float vector) override;

private:
	//----アニメーション関連----
	//アニメーションに関する初期化
	void AnimInit();
	//アニメーションスピードの設定
	void SetAnimSpeed(double speed) { m_AnimSpeed = speed; }
	//アニメーション切り替え関数
	void AnimChange(int animno) override;

protected:
	D3DXVECTOR3    m_BonePos;			//カイト:ボーン座標
	bool           m_Run;				//走り出すフラグ
	bool           m_AnimChange;		//アニメーション切り替えフラグ
	float          m_EffPosZ;			//エフェクトのZ軸位置

};

