#pragma once
#include "CBattleScene.h"
#include "SkinMeshObject\Hero\CHeroManager.h"
#include "SkinMeshObject\Hero\Enemy\CEnemyHeroManager.h"
#include "ImGui\ImGuiManager\ImGuiManager.h"
#include "Camera\CameraManager\CCameraManager.h"

CBattleScene::CBattleScene()
	: m_pHero( &CHeroManager::GetInstance() )
	, m_pEnemyHero( &CEnemyHeroManager::GetInstance() )
	, m_pCamera( &CCameraManager::GetInstance() )
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
		m_pHero->CreateHero(CHeroManager::Yui);
		//選択されなかったヒーローを敵として生成
		m_pEnemyHero->CreateEnemyHero(CHeroManager::Kaito);
	}
	else if (m_pHero->GetBattleHeroName() == "Kaito")
	{
		m_pHero->CreateHero(CHeroManager::Kaito);
		//選択されなかったヒーローを敵として生成
		m_pEnemyHero->CreateEnemyHero(CHeroManager::Yui);
	}

	//----スタティックメッシュオブジェクトのインスタンス生成----
	//地面
	m_pGround = std::make_unique<CGround>();
	//空
	m_pSky = std::make_unique<CSky>();
}

void CBattleScene::Releace()
{
	m_pHero = nullptr;
}

void CBattleScene::LoadData()
{
	//選択されているヒーローのメッシュデータ設定
	m_pHero->LoadMeshData();
	//敵のヒーローのメッシュデータ設定
	m_pEnemyHero->LoadMeshData();

	//ファイルからバトルに使用するデータを読み込む
	std::string BattleDataPath = "Data\\Hero\\BattleData\\BattleData";
	m_pJson->Load(m_BattleData, BattleDataPath);

	//バトルに使用するデータをヒーローに渡す
	m_pHero->SetBattleParamData(m_BattleData);

	//----スタティックメッシュオブジェクトのメッシュデータ設定----
	//地面
	m_pGround->LoadData();
	//空
	m_pSky->LoadData();
}

void CBattleScene::Initialize()
{
	//選択したヒーローの初期化
	m_pHero->BattleInitialize();
	//敵のヒーローの初期化
	m_pEnemyHero->Initialize();
	//カメラ情報の初期化
	m_pCamera->SetPos(INIT_CAMPOS_B);
	m_pCamera->SetLook(INIT_CAMLOOK_B);
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

	//カメラの動作
	CCameraManager::GetInstance().CameraUpdate();

	//選択したヒーローの描画
	m_pHero->Draw();
	//敵のヒーローの描画
	m_pEnemyHero->Draw();

	//----スタティックメッシュオブジェクトの描画----
	//地面
	m_pGround->Draw();
	//空
	m_pSky->Draw();
}

void CBattleScene::Debug()
{

#if DEBUG
	ImGui::Begin(JAPANESE("パラメータ"));
	ImGui::Text(JAPANESE("筋力:%f"), m_pHero->GetBattleParam().Power);
	ImGui::Text(JAPANESE("魔力:%f"), m_pHero->GetBattleParam().Magic);
	ImGui::Text(JAPANESE("素早さ:%f"), m_pHero->GetBattleParam().Speed);
	ImGui::Text(JAPANESE("体力:%f"), m_pHero->GetBattleParam().Hp);
	ImGui::End();

	m_pHero->Debug();
	m_pEnemyHero->Debug();


	CCameraManager::GetInstance().CameraUpdate();

	ImGui::Begin(JAPANESE("カメラ位置"));
	ImGui::InputFloat3(JAPANESE("座標:%f"), m_CamPos);
	ImGui::InputFloat3(JAPANESE("注視点:%f"), m_CamLook);
	CCameraManager::GetInstance().SetPos(m_CamPos);
	CCameraManager::GetInstance().SetLook(m_CamLook);
	ImGui::End();
#endif

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
