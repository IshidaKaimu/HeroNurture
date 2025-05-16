#pragma once
#include "SkinMeshObject\CSkinMeshObject.h"
#include "SkinMeshObject\Hero\CHeroBase.h"
#include "ImGui\ImGuiManager\ImGuiManager.h"
#include "Utility\CUtility.h"

// =======================
// 前方宣言
// =======================
//----マネージャークラス----
//シーン
class CSceneManager;              
//サウンド
class CSoundManager;
//エフェクト
class CEffect;

// =======================
// 定数宣言
// =======================
namespace Constant_Yui 
{
	//バトル開始時登場シーン
	const D3DXVECTOR3 APPEALANCE_POS = { 0.0f, 1.0f, -5.0f }; //初期座標
	const float APPEALANCE_SPEED	 =  0.05f;				  //移動速度
	//バトルシーン
	const D3DXVECTOR3 BATTLE_SCALE   = { 0.04f,0.04f,0.04f }; //拡縮
}

//=====================================
//ユイクラス
//制作者：石田櫂夢
//=====================================
class CYui
	:public CHeroBase
{
public:
	CYui();
    ~CYui();

	// =======================
	// 各シーンごとの初期化
	// =======================
	//主に使用する初期化
	void Initialize() override;
	//バトルシーンで使用する初期化
	void BattleInitialize() override;
	//敵になった際の初期化関数
    void EnemyInitialize()  override;
	//登場シーンの初期化
	void AppearanceInitialize() override;

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

public:
	// =======================
	// 各シーンごとのアニメーション
	// =======================
	//育成ヒーロー選択シーン 
	void NurtureHeroSelectAnimation() override;
	//バトルヒーロー選択シーン
	void BattleHeroSelectAnimation() override;
	//バトル開始時登場シーン
	void AppearanceAnimation() override;
	//育成シーン		
	void NurtureAnimation(int no) override;


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
	//ダメージ中のアニメーション
	void DamageAnim(float vector) override;

private:
	//----アニメーション関連----
	//アニメーションに関する初期化
	void AnimInit();
	//アニメーションスピードの設定
	void SetAnimSpeed(double speed) { m_AnimSpeed = speed; }
	//アニメーション切り替え関数
	void AnimChange(int animno) override;

private:
	//変動する回転軸
	float m_MoveRotateY; //Y軸
	float m_MoveRotateZ; //Z軸

	//Y軸回転の速さ
	float m_RotateSpeedY;

	//アニメーション切り替えフラグ
	bool  m_AnimChange;	 

	//ダメージSE調整用カウント
	int m_DamageSECnt;
};

