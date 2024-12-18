#pragma once
#include "SkinMeshObject\Hero\CHeroBase.h"
#include "Singleton\CSingleton.h"
#include <memory>
class CHeroManager
	: public CHeroBase
	, public CSingleton<CHeroManager>
{
public:
	//ヒーローリスト列挙型
	enum enHeroList :char
	{
		Yui,
		Kaito,
        Max,
	};

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

	//初期化関数
	void Initialize() override;

	//データ読み込み関数
	void LoadMeshData() override;

	//パラメータ情報の読み込み
	void LoadParamData(const json& jsondata) override;

	//更新関数
	void Update() override;

	//描画関数
	void Draw() override;

	// =======================
	// 各シーンごとのアニメーション
	// =======================
    //ヒーロー選択シーン 
	void SelectAnimation() override;
	//育成シーン
	void NatureAnimation(int no) override;

	//各ヒーロークラスの構築
	static std::unique_ptr<CHeroBase>Create(enHeroList list);

	// =======================
	// 各パラメータ上昇関数
	// =======================
	//筋力
	void PowerUp(float stamina) { m_Hero->PowerUp(stamina); }
	//魔力
	void MagicUp(float stamina) { m_Hero->MagicUp(stamina); }
	//素早さ
	void SpeedUp(float stamina) { m_Hero->SpeedUp(stamina); }
	//体力
	void HpUp(float stamina) { m_Hero->HpUp(stamina); }

	// =======================
	// スタミナゲージ関連関数
	// =======================	
	//スタミナの初期化
	void InitStamina() { m_Stamina = MAX_STAMINA; }
	//スタミナの減少
	void ReduceStamina();
	//スタミナの回復
	void StaminaRecovery();

	// =======================
	// ゲッター・セッター関数
	// =======================
	//ヒーロー設定関数
	void SetHero(enHeroList list);
	//ヒーロー選択関数
	void SelectHero(enHeroList list) { m_HeroList = list; }
	//選択したヒーロー
	enHeroList GetSelectHero() { return m_HeroList; }
	//現在のパラメータ
	enParam GetParam() { return m_Hero->GetParam(); }	
	//キャラごとの適正率
	enAppropriate GetApp() { return m_Hero->GetApp(); }
	//更新前のパラメータ
	enParam GetBeforeParam() { return m_Hero->GetBeforeParam(); }
	void SetBeforeParam(enParam before) { m_Hero->SetBeforeParam(before); }
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
	bool GetFailure() { return m_Hero->GetFailure(); }

private:
	//他からアクセスすることがないように
	CHeroManager();

private:
	//ヒーローベースクラス
	std::unique_ptr<CHeroBase> m_Hero;

	//ヒーローリスト
	enHeroList m_HeroList;

	//トレーニングリスト
	enTraningList m_Traning;

	//スタミナ
    //どのヒーローでも共通
	float m_Stamina;

	//変化前のスタミナ
	float m_BeforeStamina;
	//変化後のスタミナ
	float m_AfterStamina;


};

