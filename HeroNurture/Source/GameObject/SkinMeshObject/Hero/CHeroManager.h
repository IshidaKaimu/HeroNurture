#pragma once
#include "SkinMeshObject\Hero\CHeroBase.h"
#include "Singleton\CSingleton.h"
#include <memory>

class CHeroManager
	: public CHeroBase
	, public CSingleton<CHeroManager>
{
public:
	~CHeroManager();

	//初期化関数
	void Initialize() override;

	//データ読み込み関数
	void LoadData() override;

	//更新関数
	void Update() override;

	//描画関数
	void Draw( LIGHT& light ) override;

	//アニメーション関数
	void Animation();

private:
	CHeroManager();

private:
	//ヒーローベースクラス
	std::unique_ptr<CHeroBase> m_Hero;
};

