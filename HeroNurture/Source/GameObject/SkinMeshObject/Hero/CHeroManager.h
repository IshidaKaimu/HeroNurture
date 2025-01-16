#pragma once
#include "SkinMeshObject\Hero\CHeroBase.h"
#include "Singleton\CSingleton.h"
#include <memory>
class CHeroManager
	: public CHeroBase
	, public CSingleton<CHeroManager>
{

public:
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

public:
	//フレンド宣言でアクセス権を与える.
	friend class CSingleton<CHeroManager>;
	~CHeroManager();

public:
	// =======================
	// 各シーンごとの初期化
	// =======================
	//主に使用する初期化
	void Initialize() override;
	//バトルシーンで使用する初期化
	void BattleInitialize() override;

	//データ読み込み関数
	void LoadMeshData() override;

	//パラメータ情報の読み込み
	void LoadParamData(const json& jsondata) override;

	//更新関数
	void Update() override;

	//描画関数
	void Draw() override;

	//デバッグ関数
	void Debug() override;

	//作成するヒーローの設定
	void CreateHero(enHeroList list);

	//各ヒーロークラスの作成
	static std::unique_ptr<CHeroBase>Create(enHeroList list);

	// =======================
	// 各シーンごとのアニメーション
	// =======================
    //ヒーロー選択シーン 
	void NatureHeroSelectAnimation() override;
	//育成シーン
	void NatureAnimation(int no) override;

	// =======================
	// 各バトルフェーズでのアニメーション
	// =======================
	// 行動選択中のアニメーション
	void MoveSelectAnim()  override { m_pHero->MoveSelectAnim(); }
	//----攻撃フェーズ----
	//攻撃1中のアニメーション
	void PowerAttackAnim() override { m_pHero->PowerAttackAnim(); }
	//攻撃2中のアニメーション
	void MagicAttackAnim() override { m_pHero->MagicAttackAnim(); }
	//固有攻撃中のアニメーション
	void UniqueAttackAnim()override { m_pHero->UniqueAttackAnim(); }


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
	// スタミナゲージ関連関数
	// =======================	
	//スタミナの初期化
	void InitStamina() { m_Stamina = MAX_STAMINA; }
	//スタミナの減少
	void ReduceStamina();
	//スタミナの回復
	void StaminaRecovery();

	//ダメージ関数
	void Damage(float damage) { m_pHero->Damage(damage); }

	//選択しているヒーローを文字列で返す関数
	std::string GetHeroName();

	// =======================
	// ゲッター・セッター関数
	// =======================
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
	//トレーニングに失敗したかのフラグ
	bool GetFailure() { return m_pHero->GetFailure(); }
	//バトル中体力
	float GetHp() { return m_pHero->GetHp(); }
	void SetHp( float hp ) { m_pHero->SetHp(hp); }
	//固有攻撃ゲージ
	int GetUniqueGage() { return m_pHero->GetUniqueGage(); }

private:
	//他からアクセスすることがないように
	CHeroManager();

protected:
	//ヒーローベースクラス
	std::unique_ptr<CHeroBase> m_pHero;

	//選択されているヒーロー
	enHeroList m_SelectHero;

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

