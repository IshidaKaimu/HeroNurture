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
//バトルシーンでの初期情報
const D3DXVECTOR3 BATTLEINIT_POS_YUI = { -4.0f,0.0f,0.0f };		//座標
const D3DXVECTOR3 BATTLEINIT_SCALE_YUI = { 0.04f,0.04f,0.04f }; //拡縮
const D3DXVECTOR3 BATTLEINIT_ROTATE_YUI = { 0.04f,D3DXToRadian(-90.0f),0.04f }; //回転
//敵になった際の初期情報
const D3DXVECTOR3 ENEMYINIT_POS_YUI    = { 2.0f,0.0f,0.0f };
const D3DXVECTOR3 ENEMYINIT_ROTATE_YUI = { 0.0f,D3DXToRadian(90.0f),0.0f };

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

protected:
	bool           m_AnimChange;		//アニメーション切り替えフラグ

};

