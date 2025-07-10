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
//育成モード
class CNurtureManager;
//サウンド
class CSoundManager;
//エフェクト
class CEffect;
//--------------------------

// =======================


// =======================
// 定数宣言
// =======================
namespace Constant_Yui 
{
	//----バトル開始時登場シーン----
	const D3DXVECTOR3 APPEALANCE_POS     = { 0.0f, 1.0f, -5.0f }; //初期座標
	const float       APPEALANCE_SPEED   =  0.05f;				  //移動速度
	const float       APPEALANCE_GOAL_Z  =  -13.0f;				  //最後に停止する座標のZ値
	//------------------------------
	
	//----バトルシーン----
	const D3DXVECTOR3 BATTLE_SCALE   = { 0.04f,0.04f,0.04f }; //拡縮
	//--------------------

	//----攻撃1-----
	//T字
	constexpr int CHANGE_TSHARP  = 60;	//アニメーションを再生するタイミング
	constexpr int PLAY_TSHARP_SE = 60;	//T字の際のSEを再生するタイミング
	//回転
	constexpr float ROTATE_ADDSPEED          = 0.05f;  //加速度
	constexpr float ROTATE_ADDSPEED_MAX      = 8.0f;   //最大速度
	constexpr int   ROTATE_ADDSPEED_INTERVAL = 30;  //加速する間隔
	//動きの変更タイミング
	constexpr int	MOVECHANGE_FASTTIME    = 80;   //1段階目
	constexpr int	MOVECHANGE_SECONDTIME  = 120;  //2段階目
	constexpr int	MOVECHANGE_THIRDTIME   = 150;  //3段階目
	constexpr int	MOVECHANGE_FOURTHTIME  = 240;  //4段階目
	//動く速度
	constexpr float MOVESPEED_BACK = 0.1f; //下がる時
	constexpr float MOVESPEED_RUSH = 0.2f; //突進する時
	//傾けるときの速度
	constexpr float TILT_BACK_SPEED    = 0.005f; //後ろ
	constexpr float TILT_FORWARD_SPEED = 0.01f;  //前
	//傾ける最大値
	constexpr float TILT_BACK_MAX      = 0.5f;   //後ろ
	constexpr float TILT_FORWARD_MAX   = 0.35f;  //前
	//-------------

	//----攻撃1----
	//アニメーション終了タイミング
	constexpr int FASTATTACK_ANIM_END = 300;
	//--------------
    
	//----攻撃2----
	//アニメーション終了タイミング
	constexpr int SECONDATTACK_ANIM_END = 200;
	//-------------
	
	//----エフェクト----
	//回転に使う竜巻エフェクト
	const D3DXVECTOR3 TORNADE_POS      = { 0.3f, 0.3f, 0.3f };  //座標
	const D3DXVECTOR3 TORNADE_SCALE    = { 0.3f, 0.3f, 0.3f };  //拡縮
	constexpr int     TORNADE_PLAY     = 60;					//再生タイミング
	///攻撃に使う竜巻エフェクト
	const D3DXVECTOR3 ATTACKTORNADE_SCALE    = { 0.5f, 0.5f, 0.5f }; //拡縮
	constexpr float   ATTACKTORNADE_ROTATE_Y = 90.0f;				 //役割によって変わるY軸の回転値
	constexpr int     ATTACKTORNADE_PLAY     = 60;					 //再生タイミング
	//------------------
}
// =======================

//=====================================
//　ユイクラス
//　制作者：石田櫂夢
//=====================================
class CYui
	:public CHeroBase
{
public:
	CYui();
    ~CYui();
private:

	//==================w
    //構造体
    //==================

	//アニメーション番号
	enum Anim_No 
	{
		Jump,	//ジャンプ
		Run,	//走る
		Walk,	//歩く
		Wait,	//待機
		TSharp  //T字
	};

public:

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

	// =======================


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
	
	//バトル開始時登場シーン
	void AppearanceAnimation() override;
	//育成シーン		
	void NurtureAnimation(int no) override;

	// =======================


	// =======================
	// 攻撃関数
	// =======================
	
	//攻撃1
	float PowerAttack() override { return CHeroBase::PowerAttack(); }
	//攻撃2
	float MagicAttack() override { return CHeroBase::MagicAttack(); };

	// =======================

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
	//--------------------

	//========================

private:
	//----アニメーション関連----
	//アニメーションに関する初期化
	void AnimInit();
	//アニメーションスピードの設定
	void SetAnimSpeed(double speed) { m_AnimSpeed = speed; }
	//アニメーション切り替え関数
	void AnimChange(int animno) override;
	//-------------------------

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

