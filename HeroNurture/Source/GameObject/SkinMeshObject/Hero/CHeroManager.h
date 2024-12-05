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

	//アニメーション関数
	void Animation();

	//各ヒーロークラスの構築
	static std::unique_ptr<CHeroBase>Create(enHeroList list);

	//----パラメータ関連関数----
	//パラメータ上昇
	//筋力
	void PowerUp() { m_Hero->PowerUp(); }
	//魔力
	void MagicUp() { m_Hero->MagicUp(); }
	//素早さ								   
	void SpeedUp() { m_Hero->SpeedUp(); }
	//体力
	void HpUp() { m_Hero->HpUp(); }

	//----ゲッター・セッター----
	//ヒーロー設定関数
	void SetHero(enHeroList list);
	//ヒーロー選択関数
	void SelectHero(enHeroList list) { m_HeroList = list; }
	//選択したヒーロー取得
	enHeroList GetSelectHero() { return m_HeroList; }
	//現在のパラメータ取得
	enParam GetParam() { return m_Hero->GetParam(); }	
	//キャラごとの適正率取得
	enAppropriate GetApp() { return m_Hero->GetApp(); }
	//更新前のパラメータ
	enParam GetBeforeParam() { return m_Hero->GetBeforeParam(); }
	void SetBeforeParam(enParam before) { m_Hero->SetBeforeParam(before); }
	//パラメータ上昇量取得
	//筋力
	float GetPowerUpValue() { return m_Hero->GetPowerUpValue(); }
	//魔力
	float GetMagicValue() { return m_Hero->GetMagicUpValue(); }
	//素早さ
	float GetSpeedUpValue() { return m_Hero->GetSpeedUpValue(); }
	//体力
	float GetHpUpValue() { return m_Hero->GetHpUpValue(); }
	//トレーニング
	enTraningList GetTraining() { return m_Traning; }
	void SetTraning(enTraningList traning) { m_Traning = traning; }


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

};

