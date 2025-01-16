#pragma once
#include "SkinMeshObject\CSkinMeshObject.h"
#include "SkinMeshObject\Hero\CHeroBase.h"
#include "ImGui\ImGuiManager\ImGuiManager.h"
#include "Utility\CUtility.h"

// =======================
// 前方宣言
// =======================
class CSceneManager;              

// =======================
// 定数宣言
// =======================
//バトルシーンでの拡縮
const D3DXVECTOR3 BATTLE_SCALE_YUI = { 0.04f,0.04f,0.04f }; //拡縮

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
    void EnemyInit()  override;

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
	void NatureHeroSelectAnimation() override;
	//バトルヒーロー選択シーン
	void BattleHeroSelectAnimation() override;
	// 育成シーン		
	void NatureAnimation(int no) override;

	// =======================
	// 各バトルフェーズでのアニメーション
	// =======================
	// 行動選択中のアニメーション
	void MoveSelectAnim() override;
	//----攻撃フェーズ----
	//攻撃1中のアニメーション
	void PowerAttackAnim() override;
	//攻撃2中のアニメーション
	void MagicAttackAnim() override;
	//固有攻撃中のアニメーション
	void UniqueAttackAnim() override;


	// =======================
	// 攻撃関数
	// =======================
	//攻撃1
	float PowerAttack() override;
	//攻撃2
	float MagicAttack() override;
	//固有攻撃
	float UniqueAttack() override;

private:
	//アニメーションに関する初期化
	void AnimInit();

	//アニメーションスピードの設定
	void SetAnimSpeed(double speed) { m_AnimSpeed = speed; }

	//アニメーション切り替えフラグ立てる
	void AnimChange();

private:
	//変動する回転軸
	float m_MoveRotateY; //Y軸
	float m_MoveRotateZ; //Z軸

	//Y軸回転の速さ
	float m_RotateSpeedY;

	bool           m_AnimChange;		//アニメーション切り替えフラグ

};

