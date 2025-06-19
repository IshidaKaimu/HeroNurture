#pragma once
#include "SkinMeshObject\CSkinMeshObject.h"
#include "json.hpp"
#include "Json\CJson.h"
#include "Utility\CUtility.h"

//Json使用に必要な名前空間の格納
using json = nlohmann::json;

// =======================
// 定数宣言
// =======================
//----トレーニング関連----		
constexpr float INCREASE_VALUE		     = 20.0f; //基本上昇値
constexpr float MIN_FAILURE			     = 0.0f;  //失敗率の最低
constexpr float MAX_FAILURE			     = 99.0f; //失敗率の最高
constexpr float GREAT_SUCCESS_RATE       = 0.2f;  //大成功の確率	
constexpr float GREAT_SUCCESS_MULTIPLIER = 2.0f;  //大成功の倍率	
//------------------------

//----スタミナゲージ関連----
constexpr float MAX_STAMINA	     = 100.0f; //最大値
constexpr float REDUSE_STAMINA   = 25.0f;  //減少量
constexpr float RECOVERY_STAMINA = 25.0f;  //回復量
//--------------------------

//----バトルシーン----
const D3DXVECTOR3 BATTLEINIT_POS = { -5.5f,0.0f,0.0f }; //初期座標(自分)
const D3DXVECTOR3 ENEMYINIT_POS  = { 2.5f,0.0f,0.0f };	//初期座標(敵)
const D3DXVECTOR3 BATTLE_ROTATE  = { 0.0f,D3DXToRadian(-90.0f),0.0f };//回転(自分)
const D3DXVECTOR3 ENEMY_ROTATE   = { 0.0f,D3DXToRadian(90.0f),0.0f }; //回転(敵)
//--------------------

//=====================================
// ヒーロー基底クラス
// 制作者:石田櫂夢
//=====================================
class CHeroBase
	: public CSkinMeshObject
{
public :

	//===============
	// 列挙型
	//===============

	//ヒーロー名リスト
	enum enHeroList :char
	{
		Yui,
		Kaito,
		Max,
	};
	
	//===============


	//===============
	// 構造体
	//===============

	//パラメータ構造体
	struct enParam
	{
		//筋力
		float Power;
		//魔力
		float Magic;
		//素早さ
		float Speed;
		//体力
		float Hp;
	};

	//適正率構造体
	struct enAppropriate
	{
		//筋力
		float PowerApp;
		//魔力
		float MagicApp;
		//素早さ
		float SpeedApp;
		//体力
		float HpApp;
	};
	
	//===============


public:
	CHeroBase();
	virtual ~CHeroBase() override;

	// =======================
	// 各シーンごとの初期化
	// =======================
	
	//主に使用する初期化関数
	virtual void Initialize() {};
	//バトルシーンで使用する初期化
	virtual void BattleInitialize() {};
	//敵になった際の初期化関数
	virtual void EnemyInitialize() {};
	//バトル開始時登場シーンでの初期化
	virtual void AppearanceInitialize() {};

	// =======================


	//データ読み込み関数
	virtual void LoadMeshData() {};

	//パラメータ情報読み込み
	virtual void LoadParamData(const json& jsondata) {};

	//バトルパラメータ情報読み込み
	virtual void SetBattleParamData(const json& jsondata) {};

	//更新関数
	virtual void Update();

	//描画関数
	virtual void Draw();

	//デバッグ関数
	virtual void Debug() {};
	// =======================


public:
	
	//トレーニングの失敗率を返す関数
	float FailureRate(float stamina);

	// =======================
	// シーンごとのアニメーション関数
	// =======================		
	//育成ヒーロー選択シーン
	virtual void NurtureHeroSelectAnimation() {};
	//バトルヒーロー選択シーン
	virtual void BattleHeroSelectAnimation() {};
	//バトル開始時登場シーン
	virtual void AppearanceAnimation() {};
	//育成シーン
	virtual void NurtureAnimation(int no) {};
	// =======================
	
	// =======================
	// 攻撃関数
	// =======================
	//攻撃1(筋力による攻撃)
	virtual float PowerAttack();
	//攻撃1(魔力による攻撃)
	virtual float MagicAttack();
	//固有攻撃(各ヒーローの一番高いステータスを反映した攻撃)
	virtual float UniqueAttack() { return 0; }
	// =======================

	// =======================
	// 各バトルフェーズでのアニメーション
	// =======================
	// 行動選択中のアニメーション
	virtual void MoveSelectAnim() {};
	//----攻撃フェーズ----
	//攻撃1中のアニメーション
	virtual void PowerAttackAnim(float vector) {};
	//攻撃2中のアニメーション
	virtual void MagicAttackAnim(float vector) {};
	//固有攻撃中のアニメーション
	virtual void UniqueAttackAnim() {};
	//ダメージアニメーション
	virtual void DamageAnim(float vector) {};
	// =======================


	// =======================
	// ステータス上昇関数
	// =======================		
	//----トレーニングによる上昇----
	//筋力
	void PowerUp( float stamina );
	//魔力
	void MagicUp( float stamina );
	//素早さ
	void SpeedUp( float stamina );
	//体力
	void HpUp( float stamina );
	// =======================


	//ダメージ関数
	void Damage(float damage);

	// =======================
	// ゲッター・セッター関数
	// =======================
	// 座標の取得
	D3DXVECTOR3 GetPosition() { return m_vPosition; }
	//育成中のパラメータ
	enParam GetParam()       { return  m_Param; }
	//バトルに使用するパラメータ
	enParam GetBattleParamData() { return m_BattleParam; }
	//バトルに使用するヒーローの名前
	std::string GetBattleHeroName() { return m_BattleHeroName; }
	void SetBattleHeroName(std::string heroname) { m_BattleHeroName = heroname; }
	//キャラごとの適正率
	enAppropriate GetApp()  { return  m_App; }
	//更新前のパラメータ
	enParam GetBeforeParam() { return m_BeforeParam; }
	void SetBeforeParam(enParam before) { m_BeforeParam = before; }
	//トレーニング失敗フラグ
	bool GetFailureFlag() { return m_Failure; }
	void SetFailureFlag(bool failure) { m_Failure = failure; }
	//トレーニング大成功フラグ
	bool GetGreatSuccessFlag() { return m_GreatSuccess; }
	//バトルに使用するパラメータ情報の設定
	void SetBattleParam(const json& jsondata);
	//バトル中のHP
	float GetHp() { return m_Hp; }
	void SetHp(float hp) { m_Hp = hp; }
	//ダメージフラグ
	bool GetDamageFlag() { return m_Damage; }
	void SetDamageFlag(bool damage) { m_Damage = damage; }
	//攻撃アニメーション終了フラグ
	bool GetAttackAnimEndFlag()             { return m_AttackAnimEnd; }
	void SetAttackAnimEndFlag(bool animend) { m_AttackAnimEnd = animend; }
	//ダメージアニメーション終了フラグ
	bool GetDamageAnimEndFlag() { return m_DamageAnimEnd; }
	void SetDamageAnimEndFlag(bool damageanimend) { m_DamageAnimEnd = damageanimend; }
	//登場アニメーション終了フラグ
	bool GetAppealanceAnimEndFlag() { return m_AppealanceAnimEnd; }
	// =======================

	//アニメーション切り替え関数
	virtual void AnimChange(int animno);

protected :	
	// =======================
	// jsonファイル関連関数
	// =======================		
	//各ヒーローの初期パラメータ取得
	void LoadParam(const json& jsondata , const std::string& heroname);
	//各ヒーローのパラメータ更新
	void UpdateParam(const json& jsondata, const std::string& heroname);
	//========================

private:
	//残りスタミナ量による補正関数
	void CorrectionByStamina(float stamina);
	//トレーニング結果関数
	void TraningResult(float stamina, float app, float& param);

protected:
	//育成中のパラメータ
	enParam m_Param;
	//バトルのパラメータ
	enParam m_BattleParam;

	//バトルするヒーローの名前
	std::string m_BattleHeroName;

	//ヒーローの適正率構造体
	enAppropriate m_App;

	//jsonクラス
	std::unique_ptr<CJson> m_pJson;

	//ユーザーネーム
	std::string m_UserName;

	//現在の体力
	float m_Hp;

	//アニメーション用カウント
	int m_AnimCnt;
	//エフェクト用カウント
	int m_EffCnt;

	//イベントシーン用の変動させる変数
	float m_MoveX; //X座標
	float m_MoveY; //Y座標
	float m_MoveZ; //Z座標

	//----フラグ----
	//ダメージを受けたとき立てる
	bool m_Damage;
	//攻撃アニメーションが終了したら立てる
	bool m_AttackAnimEnd;
	//ダメージのアニメーションが終了したら立てる
	bool m_DamageAnimEnd;
	//登場アニメーションが終了したら立てる
	bool m_AppealanceAnimEnd;
	//--------------

private:
	//パラメータ更新前のパラメータ情報
	enParam m_BeforeParam;

	//残りスタミナによる補正
	float m_Correction;

	//----フラグ----
	//トレーニングが失敗したら立てる
	bool m_Failure;

	//トレーニングが大成功したら立てる
	bool m_GreatSuccess;

	//--------------

};