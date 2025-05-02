#pragma once
#include "SkinMeshObject\Hero\CHeroBase.h"
#include "SkinMeshObject\Hero\CHeroManager.h"
#include "Singleton\CSingleton.h"

class CEnemyHeroManager
	: public CHeroBase
	, public CSingleton<CEnemyHeroManager>
{ 
private:
	//フレンド宣言でアクセス権を与える.
	friend class CSingleton<CEnemyHeroManager>;
	~CEnemyHeroManager();

public:
	//初期化関数
	void Initialize()   { m_pEnemyHero->Initialize(); }

	//データ読み込み関数
	void LoadMeshData() { m_pEnemyHero->LoadMeshData(); };

	//更新関数
	void Update()		{ m_pEnemyHero->Update(); };

	//描画関数
	void Draw()			{ m_pEnemyHero->Draw(); };

	//デバッグ関数
	void Debug()		{ m_pEnemyHero->Debug(); };

	//作成するヒーロークラスの設定
	void CreateEnemyHero(enHeroList list);

	//各ヒーロークラスの作成
	static std::unique_ptr<CHeroBase>Create(enHeroList list);

	//死亡関数
	bool Death() { return m_pEnemyHero->GetHp() <= 0.0f; }

	//ダメージ関数
	void Damage(float damage) { m_pEnemyHero->Damage(damage); }

private:
	CEnemyHeroManager();

public:
	// =======================
	// 各ヒーローの攻撃関数
	// =======================
	//攻撃1(筋力による攻撃)
	float PowerAttack()  override {  return m_pEnemyHero->PowerAttack(); }
	//攻撃2(魔力による攻撃)
	float MagicAttack()  override {  return m_pEnemyHero->MagicAttack(); }
	//固有攻撃(各ヒーローの一番高いステータスを反映した攻撃)
	float UniqueAttack() override {  return m_pEnemyHero->UniqueAttack(); }

	//バトル開始時登場シーンのアニメーション
	void AppearanceAnimation() { m_pEnemyHero->AppearanceAnimation(); };

	// =======================
	// 各バトルフェーズでのアニメーション
	// =======================
	// 行動選択中のアニメーション
	void MoveSelectAnim()  override { m_pEnemyHero->MoveSelectAnim(); }
	//----攻撃フェーズ----
	//攻撃1中のアニメーション
	void PowerAttackAnim(float vector) override { m_pEnemyHero->PowerAttackAnim(vector); }
	//攻撃2中のアニメーション
	void MagicAttackAnim(float vector) override { m_pEnemyHero->MagicAttackAnim(vector); }
	//固有攻撃中のアニメーション
	void UniqueAttackAnim()override { m_pEnemyHero->UniqueAttackAnim(); }
	//ダメージを受けるときのアニメーション
	void DamageAnim(float vector)override { m_pEnemyHero->DamageAnim(vector); }

	//バトル中の位置の初期化
	void BattleInitPos() { m_pEnemyHero->SetPosition(ENEMYINIT_POS); }

	// =======================
	// ゲッター・セッター関数
	// =======================	
	//バトルに使用するパラメータ情報
	void SetBattleParamData(const json& jsondata) { m_pEnemyHero->SetBattleParamData(jsondata); };
	enParam GetBattleParamData() { return m_pEnemyHero->GetBattleParamData(); };
	//敵ヒーロー
	enHeroList GetSelectEnemyHero() { return m_SelectEnemyHero; }
	//敵ヒーローの名前の文字列
	std::string GetEnemyHeroName();
	//バトル中体力
	float GetHp() { return m_pEnemyHero->GetHp(); }
	void SetHp(float hp) { m_pEnemyHero->SetHp(hp); }
	//ダメージフラグ
	bool GetDamageFlag() { return m_pEnemyHero->GetDamageFlag(); }
	//アニメーション終了フラグ
	bool GetAnimEndFlag() { return m_pEnemyHero->GetAnimEndFlag(); }
	void SetAnimEndFlag(bool animend) { m_pEnemyHero->SetAnimEndFlag(animend); }
	//ダメージアニメーション終了フラグ
	bool GetDamageAnimEndFlag() { return m_pEnemyHero->GetDamageAnimEndFlag(); }
	void SetDamageAnimEndFlag(bool damageanimend) { m_pEnemyHero->SetDamageAnimEndFlag(damageanimend); }


private:
	//ヒーロー基底クラス
	std::unique_ptr<CHeroBase> m_pEnemyHero;
	//敵ヒーロー
	enHeroList m_SelectEnemyHero;
	//敵ヒーローの名前の文字列
	std::string m_EnemyHeroName;

};
