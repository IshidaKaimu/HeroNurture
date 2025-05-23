#pragma once
#pragma once
#include "SkinMeshObject\CSkinMeshObject.h"
#include "SkinMeshObject\Hero\CHeroBase.h"


// =======================
// 前方宣言
// =======================
//育成モード
class CNurtureManager;

// =======================
// 定数宣言
// =======================
namespace Constant_Kaito
{
	//バトル開始時登場シーン
	const D3DXVECTOR3 APPEALANCE_POS = { 0.0f, 2.0f, -5.0f }; //初期座標
	constexpr float AFTER_POS_Y  = 2.0f;                      //移動後座標
	const float APPEALANCE_SPEED = 0.05f;				      //移動速度
	//バトルシーン
	const D3DXVECTOR3 BATTLE_SCALE = { 0.3f,0.3f,0.3f }; //拡縮
	//----エフェクト----
	//斬撃
	const D3DXVECTOR3 SLASH_SCALE  = { 0.6f, 0.6f, 0.6f };				   //拡縮 
	const D3DXVECTOR3 SLASH_ROTATE = { D3DXToRadian(-80.0f), 0.0f, 90.0f };//回転 
	//光エフェクト
	const D3DXVECTOR3 LIGHTMAGIC_SCALE  = { 0.2f, 0.2f, 0.2f };//拡縮 
	//役割ごとのY軸の回転
	constexpr float HERO_LIGHTMAGIC_ROTATE_Y      = 0.0f;	 //自分
	constexpr float ENEMYHERO_LIGHTMAGIC_ROTATE_Y = -180.0f; //敵
	//------------------
	
}

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
private:

	//アニメーション番号
	enum Anim_No
	{
		Wait,		//待機
		Run,		//走る
		SlashRight, //斬る(右上から左下)
		SlashLeft,  //斬る(左下から右上)
		SwingDown,  //剣を振り下ろす
		Avoidance,  //回避
		HandForward,//手を突き出す
		Damage,		//ダメージ
		Die			//死亡
	};

public:

	// =======================
	// 各シーンごとの初期化
	// =======================
	//主に使用する初期化関数
	void Initialize() override;
	//バトルシーンで使用する初期化
	void BattleInitialize() override;
	//敵になった際の初期化関数
	void EnemyInitialize() override;
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

	// =======================
	// 各シーンごとのアニメーション
	// =======================
	//バトル開始時登場シーン
	void AppearanceAnimation() override;
	// 育成シーン		
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

