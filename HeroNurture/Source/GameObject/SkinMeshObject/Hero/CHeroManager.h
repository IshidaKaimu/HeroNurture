#pragma once
#include "SkinMeshObject\Hero\CHeroBase.h"
#include "Singleton\CSingleton.h"
#include <memory>

//=====================================
// ヒーローマネージャークラス
// 制作者:石田櫂夢
//=====================================
class CHeroManager
	: public CHeroBase
	, public CSingleton<CHeroManager>
{

public:

	// =======================
	// 列挙型
	// =======================

	//トレーニングリスト
	enum enTraningList : char
	{
		PowerTraining,
		MagicTraining,
		SpeedTraining,
		HpTraining,
		Rest,
		Max_T,
	};

	// =======================

public:
	//フレンド宣言でアクセス権を与える.
	friend class CSingleton<CHeroManager>;
	~CHeroManager();

public:
	// =======================
	// 各シーンごとの初期化
	// =======================
	
	//主に使用する初期化
	void Initialize()					{ m_pHero->Initialize(); }
	
	//バトルシーンで使用する初期化
	void BattleInitialize()				{ m_pHero->BattleInitialize(); }
	
	//バトル開始時登場シーンでの初期化
	void AppearanceInitialize()			{ m_pHero->AppearanceInitialize(); };
	
	//=========================

	//データ読み込み関数
	void LoadMeshData()					{ m_pHero->LoadMeshData(); }

	//パラメータ情報の読み込み
	void LoadParamData(const json& jsondata) { m_pHero->LoadParamData(jsondata); }

	//更新関数
	void Update() { m_pHero->Update(); }

	//描画関数
	void Draw()   { m_pHero->Draw(); }

	//デバッグ関数
	void Debug()  { m_pHero->Debug(); }

	//作成するヒーローの設定
	void CreateHero(enHeroList list);

	//各ヒーロークラスの作成
	static std::unique_ptr<CHeroBase>Create(enHeroList list);

	// =======================

	// =======================
	// 各シーンごとのアニメーション
	// =======================

	//ヒーロー選択シーン 
	void NurtureHeroSelectAnimation() { m_pHero->NurtureHeroSelectAnimation(); } 
	//育成シーン
	void NurtureAnimation(int no)	  { m_pHero->NurtureAnimation(no); }
	//バトル開始時登場シーン
	void AppearanceAnimation()		  { m_pHero->AppearanceAnimation(); };

	// =======================

	// =======================
	// 各パラメータ上昇関数
	// =======================
	//筋力
	void PowerUp(float stamina) { m_pHero->PowerUp(stamina); }
	//魔力
	void MagicUp(float stamina) { m_pHero->MagicUp(stamina); }
	//素早さ
	void SpeedUp(float stamina) { m_pHero->SpeedUp(stamina); }
	//体力
	void HpUp(float stamina)    { m_pHero->HpUp(stamina); }

	// =======================
	// 各ヒーローの攻撃関数
	// =======================

	//攻撃1(筋力による攻撃)
	float PowerAttack()  override {  return m_pHero->PowerAttack(); }
	//攻撃2(魔力による攻撃)
	float MagicAttack()  override {  return m_pHero->MagicAttack(); }
	//固有攻撃(各ヒーローの一番高いステータスを反映した攻撃)
	float UniqueAttack() override {  return m_pHero->UniqueAttack(); }

	// =======================

	// =======================
	// 各バトルフェーズでのアニメーション
	// =======================
	
	// 行動選択フェーズ中のアニメーション
	void MoveSelectAnim()  override				{ m_pHero->MoveSelectAnim(); }
	//----攻撃フェーズ----
	//攻撃1中のアニメーション
	void PowerAttackAnim(float vector) override { m_pHero->PowerAttackAnim(vector); }
	//攻撃2中のアニメーション
	void MagicAttackAnim(float vector) override { m_pHero->MagicAttackAnim(vector); }
	//固有攻撃中のアニメーション
	void UniqueAttackAnim()override			    { m_pHero->UniqueAttackAnim(); }
	//ダメージを受けたときのアニメーション
	void DamageAnim(float vector) override		{ m_pHero->DamageAnim(vector); }

	//========================


	// =======================
	// スタミナゲージ関連関数
	// =======================	
	
	//スタミナの初期化
	void InitStamina();
	//スタミナの減少
	void ReduceStamina();
	//スタミナの回復
	void StaminaRecovery();

	//========================


	//ダメージ関数
	void Damage(float damage) { m_pHero->Damage(damage); }
	//死亡関数
	bool Death();

	//バトル中の位置の初期化
	void BattleInitPos();

	//選択しているヒーローを文字列で返す関数
	std::string GetSelectHeroName();

	//========================

	// =======================
	// ゲッター・セッター関数
	// =======================
	
	// 座標の取得
	D3DXVECTOR3 GetPosition() { return m_pHero->GetPosition(); }	
	//選択したヒーロー
	void SelectHero(enHeroList list) { m_SelectHero = list; }
	enHeroList GetSelectHero() { return m_SelectHero; }
	//バトルに使用するヒーローの名前
	std::string GetBattleHeroName() { return m_pHero->GetBattleHeroName(); }
	void SetBattleHeroName(std::string heroname) { return m_pHero->SetBattleHeroName(heroname); }
	//現在のパラメータ
	enParam GetParam() { return m_pHero->GetParam(); }	
	//バトルに使用するパラメータ情報
	enParam GetBattleParamData() { return m_pHero->GetBattleParamData(); }
	void SetBattleParamData(const json& jsondata) { m_pHero->SetBattleParamData(jsondata); }
	//キャラごとの適正率
	enAppropriate GetApp() { return m_pHero->GetApp(); }
	//更新前のパラメータ
	enParam GetBeforeParam() { return m_pHero->GetBeforeParam(); }
	void SetBeforeParam(enParam before) { m_pHero->SetBeforeParam(before); }
	//スタミナ
	float GetStamina() { return m_Stamina; }
	void  SetStamina(float stamina) { m_Stamina = stamina; }
	//変化前のスタミナ
	float GetBeforeStamina() { return m_BeforeStamina; }
	void SetBeforeStamina(float before) { m_BeforeStamina = before; }
	//変化後のスタミナ
	float GetAfterStamina() { return m_AfterStamina; }
	//トレーニング
	enTraningList GetTraining() { return m_Traning; }
	void SetTraning(enTraningList traning) { m_Traning = traning; }
	//失敗率
	float GettFailureRate(float stamina) { return m_pHero->FailureRate(stamina); }
	//トレーニングに失敗したかのフラグ
	bool GetFailureFlag() { return m_pHero->GetFailureFlag(); }
	//トレーニングに大成功したかのフラグ
	bool GetGreatSuccessFlag() { return m_pHero->GetGreatSuccessFlag(); }
	//バトル中体力
	float GetHp() { return m_pHero->GetHp(); }
	void SetHp( float hp ) { m_pHero->SetHp(hp); }
	//ダメージフラグ
	bool GetDamageFlag() { return m_pHero->GetDamageFlag(); }
	//アニメーション終了フラグ
	bool GetAttackAnimEndFlag() { return m_pHero->GetAttackAnimEndFlag(); }
	void SetAttackAnimEndFlag(bool animend) { m_pHero->SetAttackAnimEndFlag(animend); }
	//ダメージアニメーション終了フラグ
	bool GetDamageAnimEndFlag() { return m_pHero->GetDamageAnimEndFlag(); }
	void SetDamageAnimEndFlag(bool damageanimend) { m_pHero->SetDamageAnimEndFlag(damageanimend); }
	//登場アニメーション終了フラグ
	bool GetAppealanceAnimEndFlag() { return m_pHero->GetAppealanceAnimEndFlag(); }

	// =======================


private:
	//他からアクセスすることがないように
	CHeroManager();

protected:
	//ヒーローベースクラス
	std::unique_ptr<CHeroBase> m_pHero;

	//選択されているヒーロー
	enHeroList m_SelectHero;
	//選択されているバトルに使用するヒーロー
	enHeroList m_SelectBattleHero;

	//トレーニングリスト
	enTraningList m_Traning;

	//ヒーロー名
	std::string m_HeroName;

	//スタミナ
    //どのヒーローでも共通
	float m_Stamina;

	//変化前のスタミナ
	float m_BeforeStamina;
	//変化後のスタミナ
	float m_AfterStamina;
};

