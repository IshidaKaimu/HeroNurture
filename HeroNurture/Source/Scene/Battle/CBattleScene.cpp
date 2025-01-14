#pragma once
#include "CBattleScene.h"
#include "SkinMeshObject\Hero\CHeroManager.h"
#include "SkinMeshObject\Hero\Enemy\CEnemyHeroManager.h"
#include "ImGui\ImGuiManager\ImGuiManager.h"
#include "Camera\CameraManager\CCameraManager.h"
#include "Sprite2D\UIManager\CUIManager.h"
#include "KeyManager\CKeyManager.h"
#include "Scene\CSceneManager.h"

CBattleScene::CBattleScene()
	: m_pHero	  (&CHeroManager::GetInstance())
	, m_pEnemyHero(&CEnemyHeroManager::GetInstance())
	, m_pCamera   (&CCameraManager::GetInstance())
	, m_pGround   ()
	, m_pSky      ()
	, m_pHpGage   ()
	, m_pHpGageBack ()
	, m_pHpGageFrame()
	, m_pEnemyHpGage()
	, m_pEnemyHpGageFrame()
	, m_pJson()
	, m_BattleData()
	, m_EnemyHeroData()
	, m_HpWidth()
	, m_EnemyHpWidth()
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

	//----スタティックメッシュオブジェクト----
	//地面
	m_pGround = std::make_unique<CGround>();
	//空
	m_pSky = std::make_unique<CSky>();
	//----UIオブジェクト----
	//Hpゲージ
	m_pHpGage      = std::make_unique<CUIObject>();
	m_pHpGageBack  = std::make_unique<CUIObject>();
	m_pHpGageFrame = std::make_unique<CUIObject>();
	//敵のHpゲージ
	m_pEnemyHpGage      = std::make_unique<CUIObject>();
	m_pEnemyHpGageBack  = std::make_unique<CUIObject>();
	m_pEnemyHpGageFrame = std::make_unique<CUIObject>();
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
	LoadBattleData();
	//バトルに使用するデータをヒーローに渡す
	m_pHero->SetBattleParamData(m_BattleData);
	//敵のパラメータを敵のヒーローに渡す
	for (const auto& enemy : m_EnemyHeroData)
	{
		//敵になっているヒーローのもののみ渡す
		if (m_pEnemyHero->GetEnemyHeroName() == enemy["HeroName"])
		{
			m_pEnemyHero->SetBattleParam(enemy);
		}
	}

	//----スタティックメッシュオブジェクトのメッシュデータ設定----
	//地面
	m_pGround->LoadData();
	//空
	m_pSky->LoadData();

	//----UIオブジェクトのスプライト設定----
	//Hpゲージ
	m_pHpGage->AttachSprite(CUIManager::GetSprite(CUIManager::HpGage));
	m_pHpGageBack->AttachSprite(CUIManager::GetSprite(CUIManager::HpGageBack));
	m_pHpGageFrame->AttachSprite(CUIManager::GetSprite(CUIManager::GageFrame));
	//敵のHpゲージ
	m_pEnemyHpGage->AttachSprite(CUIManager::GetSprite(CUIManager::HpGage));
	m_pEnemyHpGageBack->AttachSprite(CUIManager::GetSprite(CUIManager::HpGageBack));
	m_pEnemyHpGageFrame->AttachSprite(CUIManager::GetSprite(CUIManager::GageFrame));
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

	//体力の初期化
	m_Hp = m_pHero->GetBattleParamData().Hp;
	m_EnemyHp = m_pEnemyHero->GetBattleParamData().Hp;

	//Hpゲージの表示幅以外の設定
	InitHpGage();
}

void CBattleScene::Update()
{
	//フェードイン処理
	if (!FadeIn()) { return; }

	//----クラスのインスタンスを変数に代入----
	//キーマネージャー
	CKeyManager* KeyMng = CKeyManager::GetInstance();

	KeyMng->Update();

	if (KeyMng->IsKeep('A'))
	{
		m_Hp -= 10.0f;
		m_EnemyHp -= 10.0f;
	}
	else if(KeyMng->IsKeep('S'))
	{
		m_Hp += 10.0f;
		m_EnemyHp += 10.0f;
	}

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

	CSceneManager::GetInstance()->GetDx11()->SetDepth(false);
	//各Hpゲージの描画
	DrawHpGage();
	CSceneManager::GetInstance()->GetDx11()->SetDepth(true);

}

void CBattleScene::Debug()
{
#if _DEBUG
	ImGui::Begin(JAPANESE("パラメータ"));
	ImGui::Text(JAPANESE("プレイヤー"));
	ImGui::Text(JAPANESE("筋力:%f"), m_pHero->GetBattleParamData().Power);
	ImGui::Text(JAPANESE("魔力:%f"), m_pHero->GetBattleParamData().Magic);
	ImGui::Text(JAPANESE("素早さ:%f"), m_pHero->GetBattleParamData().Speed);
	ImGui::Text(JAPANESE("体力:%f"), m_pHero->GetBattleParamData().Hp);
	ImGui::Text(JAPANESE("敵"));
	ImGui::Text(JAPANESE("筋力:%f"), m_pEnemyHero->GetBattleParamData().Power);
	ImGui::Text(JAPANESE("魔力:%f"), m_pEnemyHero->GetBattleParamData().Magic);
	ImGui::Text(JAPANESE("素早さ:%f"), m_pEnemyHero->GetBattleParamData().Speed);
	ImGui::Text(JAPANESE("体力:%f"), m_pEnemyHero->GetBattleParamData().Hp);
	ImGui::End();
#endif
#if DEBUG
	CCameraManager::GetInstance().CameraUpdate();

	m_pHero->Debug();
	m_pEnemyHero->Debug();

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
	std::string BattleParamFilePath = "Data\\Hero\\BattleData\\BattleParam";//バトルに使用するパラメータ
	std::string EnemyParamFilePath = "Data\\Hero\\BattleData\\EnemyParam";  //敵のパラメータ

	//バトルに使用するデータのファイルを読み込み
	if (!m_pJson->Load(m_BattleData, BattleParamFilePath)) { return; }

	//敵のパラメータが保存されているファイルの読み込み
	if (!m_pJson->Load(m_EnemyHeroData, EnemyParamFilePath)) { return; }
}

//それぞれの体力ゲージの描画
void CBattleScene::DrawHpGage()
{
	//----UIオブジェクトの描画----
    //自分のHpゲージ
	HpGageAnim(m_pHpGage, m_Hp, m_pHero->GetBattleParamData().Hp, m_HpWidth);
	m_pHpGageBack->Draw();
	m_pHpGage->Draw();
	m_pHpGageFrame->Draw();
	//敵のHpゲージ
	HpGageAnim(m_pEnemyHpGage, m_EnemyHp, m_pEnemyHero->GetBattleParamData().Hp, m_EnemyHpWidth);
	m_pEnemyHpGageBack->Draw();
	m_pEnemyHpGage->Draw();
	m_pEnemyHpGageFrame->Draw();
}

//体力ゲージの各種初期設定
void CBattleScene::InitHpGage()
{
	//----設定----
	//Hpゲージ
	m_pHpGage->SetPosition(HPGAGE_POS);
	m_pHpGage->SetScale(HPGAGE_SCALE);
	m_pHpGage->SetDisplay(HPGAGE_DISPLAY.x, HPGAGE_DISPLAY.y);
	//Hpゲージ背景
	m_pHpGageBack->SetPosition(HPGAGE_POS);
	m_pHpGageBack->SetScale(HPGAGE_SCALE);
	m_pHpGageBack->SetDisplay(HPGAGE_DISPLAY.x, HPGAGE_DISPLAY.y);
	//Hpゲージ枠
	m_pHpGageFrame->SetPosition(HPFRAME_POS);
	m_pHpGageFrame->SetScale(HPGAGE_SCALE);
	m_pHpGageFrame->SetDisplay(HPGAGE_DISPLAY.x, HPGAGE_DISPLAY.y);
	//敵のHpゲージ
	m_pEnemyHpGage->SetPosition(ENEMY_HPGAGE_POS);
	m_pEnemyHpGage->SetRotation(0.0f, 0.0f, 0.0f);
	m_pEnemyHpGage->SetScale(0.8f, 0.8f, 0.8f);
	m_pEnemyHpGage->SetDisplay(1.0f, 1.0f);
	//敵のHpゲージ背景
	m_pEnemyHpGageBack->SetPosition(ENEMY_HPGAGE_POS);
	m_pEnemyHpGageBack->SetScale(0.8f, 0.8f, 0.8f);
	m_pEnemyHpGageBack->SetDisplay(1.0f, 1.0f);
	//敵のHpゲージ枠
	m_pEnemyHpGageFrame->SetPosition(800.0f, 10.0f, 0.0f);
	m_pEnemyHpGageFrame->SetScale(0.8f, 0.8f, 0.8f);
	m_pEnemyHpGageFrame->SetDisplay(1.0f, 1.0f);
}

//体力ゲージのアニメーション
void CBattleScene::HpGageAnim(std::unique_ptr<CUIObject>& gage, float& hp, float maxhp, float& width)
{
	//ゲージ幅の確認
	float GageScale = 1.0f * hp / maxhp;

	//高ければ
	if (GageScale < width) { width -= 0.1f; }
	//低ければ
	if (GageScale > width) { width += 0.1f; }

	//ゲージ幅を設定
	gage->SetDisplay(width, 1.0f);
}
