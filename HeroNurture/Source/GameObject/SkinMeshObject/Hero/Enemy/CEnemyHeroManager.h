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
	void Initialize() override;

	//データ読み込み関数
	void LoadMeshData() override;

	//更新関数
	void Update() override;

	//描画関数
	void Draw() override;

	//デバッグ関数
	void Debug() override;

	//作成するヒーロークラスの設定
	void CreateEnemyHero(enHeroList list);

	//各ヒーロークラスの作成
	static std::unique_ptr<CHeroBase>Create(enHeroList list);

	// =======================
	// ゲッター・セッター関数
	// =======================	
	//バトルに使用するパラメータ情報の設定
	void SetBattleParamData(const json& jsondata) override;

private:
	CEnemyHeroManager();

private:
	//ヒーロー基底クラス
	std::unique_ptr<CHeroBase> m_pEnemyHero;
};
