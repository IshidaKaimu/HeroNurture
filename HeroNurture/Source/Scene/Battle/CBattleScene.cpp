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
	, m_IsHeroTurn()
	, m_SelectAttack()
	, m_Attack()
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
	m_pHero->SetHp(m_pHero->GetBattleParamData().Hp * 10.0f);
	m_pEnemyHero->SetHp(m_pEnemyHero->GetBattleParamData().Hp * 10.0f);

	//Hpゲージの表示幅以外の設定
	InitHpGage();
}

void CBattleScene::Update()
{
	//フェードイン処理
	if (!FadeIn()) { return; }

	switch (m_BattlePhase)
	{
	case CBattleScene::MoveSelectPhase: 
		MoveSelect();	//攻撃の選択
		break;
	case CBattleScene::AttackPhase:
		Attack();		//お互いの攻撃
		break;
	case CBattleScene::SetUpPhase:
		SetUpToNextTurn(); //次のターンの準備
		break;
	}

	//デバッグ処理
	Debug();
}

void CBattleScene::Draw()
{
	//クラスのインスタンスを変数に代入
	//テキスト描画クラス
	WriteText* Text = WriteText::GetInstance();

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
	ImGui::Text(JAPANESE("HP%f"), m_pHero->GetHp());
	ImGui::Text(JAPANESE("敵HP%f"), m_pEnemyHero->GetHp());
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
	HpGageAnim(m_pHpGage,m_pHero->GetHp(), m_pHero->GetBattleParamData().Hp, m_HpWidth);
	m_pHpGageBack->Draw();
	m_pHpGage->Draw();
	m_pHpGageFrame->Draw();
	//敵のHpゲージ
	HpGageAnim(m_pEnemyHpGage, m_pEnemyHero->GetHp(), m_pEnemyHero->GetBattleParamData().Hp, m_EnemyHpWidth);
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
	m_pEnemyHpGage->SetScale(0.8f, 0.8f, 0.8f);
	m_pEnemyHpGage->SetDisplay(1.0f, 1.0f);
	//敵のHpゲージ背景
	m_pEnemyHpGageBack->SetPosition(ENEMY_HPGAGE_POS);
	m_pEnemyHpGageBack->SetScale(0.8f, 0.8f, 0.8f);
	m_pEnemyHpGageBack->SetDisplay(1.0f, 1.0f);
	//敵のHpゲージ枠
	m_pEnemyHpGageFrame->SetPosition(ENEMY_HPFRAME_POS);
	m_pEnemyHpGageFrame->SetScale(0.8f, 0.8f, 0.8f);
	m_pEnemyHpGageFrame->SetDisplay(1.0f, 1.0f);
}

//体力ゲージのアニメーション
void CBattleScene::HpGageAnim(std::unique_ptr<CUIObject>& gage, float hp, float maxhp, float& width)
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

//行動選択フェーズ中の処理
void CBattleScene::MoveSelect()
{
	//----クラスのインスタンスを変数に代入----
	//キーマネージャー
	CKeyManager* KeyMng = CKeyManager::GetInstance();
	KeyMng->Update();

		//カーソルの移動
	if (KeyMng->IsDown(VK_RIGHT))
		{
			//キー入力で選択を進める
			if (m_SelectNo < enAttackList::Max - 1) { m_SelectNo++; }
			else { m_SelectNo = 0; }
		}
		else if (KeyMng->IsDown(VK_LEFT))
		{
			if (m_SelectNo > 0) { m_SelectNo--; }
			else { m_SelectNo = enAttackList::Max - 1; }
		}

		if (KeyMng->IsDown(VK_RETURN))
		{
			switch (m_SelectNo)
			{
			case 0: m_Attack = enAttackList::PowerAttack; break;
			case 1: m_Attack = enAttackList::MagicAttack; break;
			case 2: m_Attack = enAttackList::UniqueAttack; break;
			}
			
			//攻撃フェーズへ遷移
			m_BattlePhase = enBattlePhase::AttackPhase;
		}
}

void CBattleScene::Attack()
{
	if (m_IsHeroTurn)
	{
		HeroTurn();
	}
	else
	{
		EnemyHeroTurn();
	}

	//準備フェーズへ移動
	m_BattlePhase = enBattlePhase::SetUpPhase;
}

//次のターンの準備中の処理
void CBattleScene::SetUpToNextTurn()
{
	//自分と敵のスピードを比較
	if (m_pHero->GetBattleParamData().Speed > m_pEnemyHero->GetBattleParamData().Speed)
	{
		//自分のスピードが高ければ自分のターン
		m_IsHeroTurn = true;
	}
	else
	{
		//低ければ敵のターン
		m_IsHeroTurn = false;
	}
}

//自分のターンに行う処理
void CBattleScene::HeroTurn()
{
	switch (m_Attack)
	{
	case CBattleScene::PowerAttack: m_pEnemyHero->Damage(m_pHero->PowerAttack()); break;
	case CBattleScene::MagicAttack: m_pEnemyHero->Damage(m_pHero->MagicAttack()); break;
	case CBattleScene::UniqueAttack: m_pEnemyHero->Damage(m_pHero->UniqueAttack());break;
	}

	//敵の攻撃に移す
	m_IsHeroTurn = false;
}

//敵のターンに行う処理
void CBattleScene::EnemyHeroTurn()
{
	m_IsHeroTurn = true;
}
