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

public:
	//フレンド宣言でアクセス権を与える.
	friend class CSingleton<CHeroManager>;
	~CHeroManager();

	//初期化関数
	void Initialize() override;

	//データ読み込み関数
	void LoadData(const json& jsondata) override;

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
	void PowerUp(int power) { m_Hero->PowerUp(power); }
	//魔力
	void MagicUp(int magic) { m_Hero->MagicUp(magic); }
	//素早さ
	void SpeedUp(int speed) { m_Hero->SpeedUp(speed); }
	//体力
	void HpUp(int hp) { m_Hero->HpUp(hp); }

	//----ゲッター・セッター----
	//ヒーロー設定関数
	void SetHero(enHeroList list);
	//ヒーロー選択関数
	void SelectHero(enHeroList list) { m_HeroList = list; }
	//選択したヒーロー取得
	enHeroList GetSelectHero() { return m_HeroList; }
	//現在のパラメータ取得
	enStatus GetParam() { return m_Hero->GetParam(); }	
	//パラメータ上昇量取得
	//筋力
	int GetPowerUpValue() { return m_Hero->GetPowerUpValue(); }
	//魔力
	int GetMagicValue() { return m_Hero->GetMagicUpValue(); }
	//素早さ
	int GetSpeedUpValue() { return m_Hero->GetSpeedUpValue(); }
	//体力
	int GetHpUpValue() { return m_Hero->GetHpUpValue(); }

private:
	//他からアクセスすることがないように
	CHeroManager();

private:
	//ヒーローベースクラス
	std::unique_ptr<CHeroBase> m_Hero;

	//ヒーローリスト
	enHeroList m_HeroList;

};

