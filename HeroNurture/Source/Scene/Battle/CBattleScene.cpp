#pragma once
#include "CBattleScene.h"
#include "SkinMeshObject\Hero\CHeroManager.h"
#include "ImGui\ImGuiManager\ImGuiManager.h"

CBattleScene::CBattleScene()
	: m_pHero( &CHeroManager::GetInstance() )
	, m_BattleTurn()
{
}

CBattleScene::~CBattleScene()
{
}

void CBattleScene::Create()
{
	//選択されたヒーローのインスタンス生成
	if (m_pHero->GetBattleHeroName() == "Yui")
	{
		m_pHero->SetHero(CHeroManager::Yui);
	}
	else if (m_pHero->GetBattleHeroName() == "Kaito")
	{
		m_pHero->SetHero(CHeroManager::Kaito);
	}
}

void CBattleScene::Releace()
{
}

void CBattleScene::LoadData()
{
	//選択されているヒーローのメッシュデータ設定
	m_pHero->LoadMeshData();
	//バトルに使用するデータの読み込み
	m_pHero->LoadBattleParamData();

}

void CBattleScene::Initialize()
{
}

void CBattleScene::Update()
{
	//フェードイン処理
	if (!FadeIn()) { return; }

	//デバッグ処理
	Debug();
}

void CBattleScene::Draw()
{
	//ヒーローマネージャー
	CHeroManager* HeroMng = &CHeroManager::GetInstance();
	HeroMng->Draw();
}

void CBattleScene::Debug()
{
	ImGui::Begin(JAPANESE("パラメータ"));
	ImGui::Text(JAPANESE("筋力:%f"), m_pHero->GetBattleParam().Power);
	ImGui::Text(JAPANESE("魔力:%f"), m_pHero->GetBattleParam().Magic);
	ImGui::Text(JAPANESE("素早さ:%f"), m_pHero->GetBattleParam().Speed);
	ImGui::Text(JAPANESE("体力:%f"), m_pHero->GetBattleParam().Hp);
	ImGui::End();
}

//バトルに使用するデータの読み込み
void CBattleScene::LoadBattleData()
{
	//読み込むファイルのパス
	//パラメータ情報更新時に読み込むファイルのパス
	std::string BattleDataFilePath = "Data\\Hero\\BattleData\\BattleData";

	//バトルに使用するデータの読み込み
	if (!m_pJson->Load(m_BattleData, BattleDataFilePath)) { return; }

}
