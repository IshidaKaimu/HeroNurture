#pragma once
#include "CBattleScene.h"
#include "Scene\CSceneManager.h"
#include "ModeManager\Battle\CBattleManager.h"
#include "SkinMeshObject\Hero\CHeroManager.h"
#include "SkinMeshObject\Hero\Enemy\CEnemyHeroManager.h"
#include "ImGui\ImGuiManager\ImGuiManager.h"
#include "Camera\CameraManager\CCameraManager.h"
#include "Sprite2D\UIManager\CUIManager.h"
#include "KeyManager\CKeyManager.h"
#include "Effect\CEffect.h"
#include "Sound\CSoundManager.h"

//定数の名前空間
using namespace Constant_BattleScene;

CBattleScene::CBattleScene()
	: m_pCamera			  (&CCameraManager::GetInstance())
	, m_pGround			  ()
	, m_pHpGage			  ()
	, m_pHpGageBack       ()
	, m_pHpGageFrame      ()
	, m_pEnemyHpGage      ()
	, m_pEnemyHpGageBack  ()
	, m_pEnemyHpGageFrame ()
	, m_pPowerAttack	  ()
	, m_pMagicAttack	  ()
	, m_pAttackCover	  ()
	, m_pJson			  ()
	, m_BattleData		  ()
	, m_EnemyHeroData     ()
	, m_HpWidth			  (1.0f)
	, m_EnemyHpWidth      (1.0f)
	, m_BattleTurn        ()
	, m_MoveSelectCut	  ()
	, m_IsHeroTurn        ()
	, m_CurrentTurn		  ()
	, m_SelectAttack      ()
	, m_Attack            ()
	, m_EnemyAttack		  ()
	, m_EnemyAttackNo     ()
	, m_BattlePhase		  ()
{
}

CBattleScene::~CBattleScene()
{
}

void CBattleScene::Create()
{
	CHeroManager*      HeroMng      = &CHeroManager::GetInstance();
	CEnemyHeroManager* EnemyHeroMng = &CEnemyHeroManager::GetInstance();

	//選択されたヒーローのインスタンス生成
	if (HeroMng->GetBattleHeroName() == "Yui")
	{
		HeroMng->CreateHero(CHeroManager::Yui);
		//選択されなかったヒーローを敵として生成
		EnemyHeroMng->CreateEnemyHero(CHeroManager::Kaito);
	}
	else if (HeroMng->GetBattleHeroName() == "Kaito")
	{
		HeroMng->CreateHero(CHeroManager::Kaito);
		//選択されなかったヒーローを敵として生成
		EnemyHeroMng->CreateEnemyHero(CHeroManager::Yui);
	}

	//----スタティックメッシュオブジェクト----
	//地面
	m_pGround = std::make_unique<CGround>();
	//----UIオブジェクト----
	//Hpゲージ
	m_pHpGage      = std::make_unique<CUIObject>();
	m_pHpGageBack  = std::make_unique<CUIObject>();
	m_pHpGageFrame = std::make_unique<CUIObject>();
	//敵のHpゲージ
	m_pEnemyHpGage      = std::make_unique<CUIObject>();
	m_pEnemyHpGageBack  = std::make_unique<CUIObject>();
	m_pEnemyHpGageFrame = std::make_unique<CUIObject>();
	//攻撃アイコン
	m_pPowerAttack = std::make_unique<CUIObject>(); //筋力
	m_pMagicAttack = std::make_unique<CUIObject>(); //魔力
	m_pAttackCover = std::make_unique<CUIObject>(); //被せる画像
}

void CBattleScene::Releace()
{
}

void CBattleScene::LoadData()
{
	CHeroManager*      HeroMng      = &CHeroManager::GetInstance();
	CEnemyHeroManager* EnemyHeroMng = &CEnemyHeroManager::GetInstance();

	//選択されているヒーローのメッシュデータ設定
	HeroMng->LoadMeshData();
	//敵のヒーローのメッシュデータ設定
	EnemyHeroMng->LoadMeshData();

	//ファイルからバトルに使用するデータを読み込む
	LoadBattleData();
	//バトルに使用するデータをヒーローに渡す
	HeroMng->SetBattleParamData(m_BattleData);
	//敵のパラメータを敵のヒーローに渡す
	for (const auto& enemy : m_EnemyHeroData)
	{
		//敵になっているヒーローのもののみ渡す
		if (EnemyHeroMng->GetEnemyHeroName() == enemy["HeroName"].get<std::string>())
		{
			EnemyHeroMng->SetBattleParamData(enemy);
		}
	}

	//----スタティックメッシュオブジェクトのメッシュデータ設定----
	//地面
	m_pGround->LoadData();

	//----UIオブジェクトのスプライト設定----
	//Hpゲージ
	m_pHpGage->AttachSprite(CUIManager::GetSprite(CUIManager::HpGage));
	m_pHpGageBack->AttachSprite(CUIManager::GetSprite(CUIManager::HpGageBack));
	m_pHpGageFrame->AttachSprite(CUIManager::GetSprite(CUIManager::GageFrame));
	//敵のHpゲージ
	m_pEnemyHpGage->AttachSprite(CUIManager::GetSprite(CUIManager::EnemyHpGage));
	m_pEnemyHpGageBack->AttachSprite(CUIManager::GetSprite(CUIManager::HpGageBack));
	m_pEnemyHpGageFrame->AttachSprite(CUIManager::GetSprite(CUIManager::GageFrame));
	//攻撃アイコン
	m_pPowerAttack->AttachSprite(CUIManager::GetSprite(CUIManager::PowerAttack)); //筋力
	m_pMagicAttack->AttachSprite(CUIManager::GetSprite(CUIManager::MagicAttack)); //魔力
	m_pAttackCover->AttachSprite(CUIManager::GetSprite(CUIManager::AttackCover)); //被せる画像

}

void CBattleScene::Initialize()
{
	CHeroManager* HeroMng = &CHeroManager::GetInstance();
	CEnemyHeroManager* EnemyHeroMng = &CEnemyHeroManager::GetInstance();


	//選択したヒーローの初期化
	HeroMng->BattleInitialize();
	//敵のヒーローの初期化
	EnemyHeroMng->Initialize();
	//カメラ情報の初期化
	m_pCamera->SetPos(INIT_CAMPOS);
	m_pCamera->SetLook(INIT_CAMLOOK);

	//行動が選択済みであるかのフラグの初期化
	m_SelectAttack = false;
	
	//体力の初期化
	HeroMng->SetHp(HeroMng->GetBattleParamData().Hp * 10.0f);
	EnemyHeroMng->SetHp(EnemyHeroMng->GetBattleParamData().Hp * 10.0f);

	//Hpゲージの表示幅以外の設定
	InitHpGage();

	//行動選択時カメラを移動させる値の初期化
	m_MoveCamPos  = INIT_MOVE_CAMPOS;
	m_MoveCamLook = INIT_MOVE_CAMLOOK;

}

void CBattleScene::Update()
{
	CSceneManager*       SceneMng     = &CSceneManager::GetInstance();
	CBattleManager*      BattleMng    = &CBattleManager::GetInstance();
	CHeroManager*        HeroMng      = &CHeroManager::GetInstance();
	CEnemyHeroManager*   EnemyHeroMng = &CEnemyHeroManager::GetInstance();

	//バトルヒーロー選択BGMを停止
	CSoundManager::GetInstance()->Stop(CSoundManager::BGM_BattleHeroSelect);

	//バトルBGMの再生
	CSoundManager::GetInstance()->PlayLoop(CSoundManager::BGM_Battle);
	CSoundManager::GetInstance()->Volume(CSoundManager::BGM_Battle, 40);

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
	case CBattleScene::Max:
		break;
	}

	//死亡時処理
    //自分
	if (HeroMng->Death())
	{
		//勝敗の設定
		BattleMng->SetBattleResult(BattleMng->Lose);

		m_SceneTransitionFlg = true;
	}
	//敵
	if (EnemyHeroMng->Death())
	{
		//勝敗の設定
		BattleMng->SetBattleResult(BattleMng->Win);

		m_SceneTransitionFlg = true;
	}

	//フェードアウト処理
	if (m_SceneTransitionFlg && FadeOut())
	{
		SceneMng->LoadCreate(CSceneManager::BattleResult);
	}


	//デバッグ処理
	Debug();
}

void CBattleScene::Draw()
{
	WriteText*         Text         = WriteText::GetInstance();
	CSceneManager*     SceneMng     = &CSceneManager::GetInstance();
	CUtility*          Utility      = &CUtility::GetInstance();
	CHeroManager*      HeroMng      = &CHeroManager::GetInstance();
	CEnemyHeroManager* EnemyHeroMng = &CEnemyHeroManager::GetInstance();

	//カメラの動作
	CCameraManager::GetInstance().CameraUpdate();

	//選択したヒーローの描画
	HeroMng->Draw();
	//敵のヒーローの描画
	EnemyHeroMng->Draw();

	//地面の描画
	m_pGround->Draw();
	//空の描画
	DrawSky();

	SceneMng->GetDx11()->SetDepth(false);
	
	//各Hpゲージの描画
	DrawHpGage();

	std::string debug = HeroMng->GetBattleHeroName();

	//自分、敵それぞれのヒーロー名
	Text->Draw_Text(Utility->StringToWstring(HeroMng->GetBattleHeroName()), WriteText::Hero, HERO_TEXT_POS);			    //自分
	Text->Draw_Text(Utility->StringToWstring(EnemyHeroMng->GetBattleHeroName()), WriteText::EnemyHero, ENEMYHERO_TEXT_POS); //敵

	//自分、敵それぞれのターンの描画処理
	if (m_SelectAttack)
	{
		//敵のターンでなければ
		if (!m_CurrentTurn) { DrawHeroTurn(); }
		else { DrawEnemyHeroTurn(); }
	}

	//攻撃アイコンの描画
	DrawAttack(m_pPowerAttack, POWER_ATTACK_POS, ATTACK_ALPHA); //筋力攻撃
	DrawAttack(m_pMagicAttack, MAGIC_ATTACK_POS, ATTACK_ALPHA); //魔力攻撃
	//選択によって位置を変えるための変数
	D3DXVECTOR3 CoverPos;
	if (m_SelectNo == 0) { CoverPos = MAGIC_ATTACK_POS; }

	else{ CoverPos = POWER_ATTACK_POS; }
	DrawAttack(m_pAttackCover, CoverPos, ATTACK_COVER_ALPHA);   //アイコンにかぶせる画像

	SceneMng->GetDx11()->SetDepth(true);
}

void CBattleScene::Debug()
{
#if DEBUG
	ImGui::Begin(JAPANESE("パラメータ"));
	ImGui::Text(JAPANESE("プレイヤー"));
	ImGui::Text(JAPANESE("筋力:%f"), HeroMng->GetBattleParamData().Power);
	ImGui::Text(JAPANESE("魔力:%f"), HeroMng->GetBattleParamData().Magic);
	ImGui::Text(JAPANESE("素早さ:%f"), HeroMng->GetBattleParamData().Speed);
	ImGui::Text(JAPANESE("体力:%f"), HeroMng->GetBattleParamData().Hp);
	ImGui::Text(JAPANESE("敵"));
	ImGui::Text(JAPANESE("筋力:%f"), EnemyHeroMng->GetBattleParamData().Power);
	ImGui::Text(JAPANESE("魔力:%f"), EnemyHeroMng->GetBattleParamData().Magic);
	ImGui::Text(JAPANESE("素早さ:%f"), EnemyHeroMng->GetBattleParamData().Speed);
	ImGui::Text(JAPANESE("体力:%f"), EnemyHeroMng->GetBattleParamData().Hp);
	ImGui::Text(JAPANESE("HP%f"), HeroMng->GetHp());
	ImGui::Text(JAPANESE("敵HP%f"), EnemyHeroMng->GetHp());
	ImGui::End();

	ImGui::Begin(JAPANESE("カメラ"));
	ImGui::Text(JAPANESE("カメラ注視点X:%f"), m_pCamera->GetLook().x);
	ImGui::End();

	ImGui::Begin(JAPANESE("トレーニング選択状況"));
	if (m_SelectNo == 0) { ImGui::Text(JAPANESE("物理")); }
	if (m_SelectNo == 1) { ImGui::Text(JAPANESE("魔法")); }
	if (m_SelectNo == 2) { ImGui::Text(JAPANESE("固有")); }
	ImGui::End();

#endif
#if DEBUG
	CCameraManager::GetInstance().CameraUpdate();
	ImGui::Begin(JAPANESE("カメラ位置"));
	ImGui::InputFloat3(JAPANESE("座標:%f"), m_CamPos);
	ImGui::InputFloat3(JAPANESE("注視点:%f"), m_CamLook);
	CCameraManager::GetInstance().SetPos(ATTACK_CAMPOS);
	CCameraManager::GetInstance().SetLook(ATTACK_CAMLOOK);
	ImGui::End();
#endif
#if DEBUG
	HeroMng->Debug();
	EnemyHeroMng->Debug();
#endif


}

//バトルに使用するデータの読み込み
void CBattleScene::LoadBattleData()
{
	CSceneManager* SceneMng = &CSceneManager::GetInstance();

	//設定されているユーザー名の取得
	std::string UserName = SceneMng->GetStringName();

	//読み込むファイルのパス
	std::string BattleParamFilePath = "Data\\Acount\\"+ UserName +"\\BattleData\\BattleParam";   //バトルに使用するパラメータ
	std::string EnemyParamFilePath  = "Data\\Acount\\" + UserName + "\\BattleData\\EnemyParam";  //敵のパラメータ

	//バトルに使用するデータのファイルを読み込み
	if (!m_pJson->Load(m_BattleData, BattleParamFilePath)) { return; }

	//敵のパラメータが保存されているファイルの読み込み
	if (!m_pJson->Load(m_EnemyHeroData, EnemyParamFilePath)) { return; }
}

//攻撃アイコンの描画
void CBattleScene::DrawAttack(std::unique_ptr<CUIObject>& icon, D3DXVECTOR3 pos, float alpha)
{
	icon->SetPosition(pos);
	icon->SetScale(ATTACK_SCALE);
	icon->SetDisplay(ATTACK_DISP.x,ATTACK_DISP.y);
	icon->SetAlpha(alpha);

	if (!m_SelectAttack) 
	{
		icon->Draw();
	}
}

//それぞれの体力ゲージの描画
void CBattleScene::DrawHpGage()
{
	CHeroManager*      HeroMng      = &CHeroManager::GetInstance();
	CEnemyHeroManager* EnemyHeroMng = &CEnemyHeroManager::GetInstance();

	//----UIオブジェクトの描画----
    //自分のHpゲージ
	HpGageAnim(m_pHpGage, HeroMng->GetHp(), HeroMng->GetBattleParamData().Hp * 10.0f, m_HpWidth);
	m_pHpGageBack->Draw();
	m_pHpGage->Draw();
	m_pHpGageFrame->Draw();
	//敵のHpゲージ
	HpGageAnim(m_pEnemyHpGage, EnemyHeroMng->GetHp(), EnemyHeroMng->GetBattleParamData().Hp * 10.0f, m_EnemyHpWidth);
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
	m_pEnemyHpGage->SetScale(HPGAGE_SCALE);
	m_pEnemyHpGage->SetDisplay(HPGAGE_DISPLAY.x, HPGAGE_DISPLAY.y);
	//敵のHpゲージ背景
	m_pEnemyHpGageBack->SetPosition(ENEMY_HPGAGE_POS);
	m_pEnemyHpGageBack->SetScale(HPGAGE_SCALE);
	m_pEnemyHpGageBack->SetDisplay(HPGAGE_DISPLAY.x, HPGAGE_DISPLAY.y);
	//敵のHpゲージ枠
	m_pEnemyHpGageFrame->SetPosition(ENEMY_HPFRAME_POS);
	m_pEnemyHpGageFrame->SetScale(HPGAGE_SCALE);
	m_pEnemyHpGageFrame->SetDisplay(HPGAGE_DISPLAY.x, HPGAGE_DISPLAY.y);
}

//体力ゲージのアニメーション
void CBattleScene::HpGageAnim(std::unique_ptr<CUIObject>& gage, float hp, float maxhp, float& width)
{
	//ゲージ幅の確認
	float GageScale = 1.0f * hp / maxhp;

	// 幅を徐々に目標値に近づける
	if (std::fabs(GageScale - width) < 0.01f) {
		// 目標値と十分近い場合、直接スナップ
		width = GageScale;
	}
	else {
		// 緩やかに目標値に近づける
		width += (GageScale - width) * 0.1f;
	}

	//ゲージ幅を設定
	gage->SetDisplay(width, 1.0f);
}

//行動選択フェーズ中の処理
void CBattleScene::MoveSelect()
{
	CKeyManager*       KeyMng       = &CKeyManager::GetInstance();
	CHeroManager*      HeroMng      = &CHeroManager::GetInstance();
	CEnemyHeroManager* EnemyHeroMng = &CEnemyHeroManager::GetInstance();

	//キーマネージャーの動作
	KeyMng->Update();

	//行動選択中のアニメーション
	HeroMng->MoveSelectAnim();		//自分
	EnemyHeroMng->MoveSelectAnim(); //敵

	//カメラの演出
	MoveSelectCamera();

	//速度による行動順の判断
	SetUpToNextTurn();

	//カーソルの移動
	if (KeyMng->IsDown(VK_RIGHT))
		{
		    //選択SEの再生
		    CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Select);
		    CSoundManager::GetInstance()->Volume(CSoundManager::SE_Select, 40);

			//キー入力で選択を進める
			if (m_SelectNo < enAttackList::Max - 1) { m_SelectNo++; }
			else { m_SelectNo = 0; }
		}
		else if (KeyMng->IsDown(VK_LEFT))
		{
			//選択SEの再生
			CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Select);
			CSoundManager::GetInstance()->Volume(CSoundManager::SE_Select, 40);

			if (m_SelectNo > 0) { m_SelectNo--; }
			else { m_SelectNo = enAttackList::Max - 1; }
		}

		if (KeyMng->IsDown(VK_RETURN))
		{
			//決定SEの再生
			CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Enter);
			CSoundManager::GetInstance()->Volume(CSoundManager::SE_Enter, 40);

			//自分の攻撃の設定
			SettingAttack(m_SelectNo, m_Attack);
			
			//選択をしたフラグ
			m_SelectAttack = true;

			//敵の攻撃の選択
			m_EnemyAttackNo = CUtility::GenerateRandomValue(0, 1);

			//敵の攻撃の設定
			SettingAttack(m_EnemyAttackNo, m_EnemyAttack);

			//攻撃フェーズへ遷移
			m_BattlePhase = enBattlePhase::AttackPhase;
		}
}

void CBattleScene::Attack()
{
	CHeroManager*      HeroMng      = &CHeroManager::GetInstance();
	CEnemyHeroManager* EnemyHeroMng = &CEnemyHeroManager::GetInstance();

	if (m_IsHeroTurn)
	{
		//自分が先行の場合
		if (!EnemyHeroMng->GetDamageFlag()) 
		{
			HeroTurn();
			if (EnemyHeroMng->GetHp() > 0.0 && HeroMng->GetAttackAnimEndFlag()) {
				//敵へのダメージ処理
				switch (m_Attack)
				{
				case CBattleScene::PowerAttack:
					EnemyHeroMng->Damage(HeroMng->PowerAttack());
					break;
				case CBattleScene::MagicAttack:
					EnemyHeroMng->Damage(HeroMng->MagicAttack());
					break;
				case CBattleScene::Max:
					break;
				}
			}
		}
		else if(!EnemyHeroMng->Death())
		{
			EnemyHeroTurn();
			if (HeroMng->GetHp() > 0.0f) {
				//自分へのダメージ処理
				switch (m_EnemyAttack)
				{
				case CBattleScene::PowerAttack:
					HeroMng->Damage(EnemyHeroMng->PowerAttack());
					break;
				case CBattleScene::MagicAttack:
					HeroMng->Damage(EnemyHeroMng->MagicAttack());
					break;
				case CBattleScene::Max:
					break;
				}
			}
		}
	}
	else if(!HeroMng->Death())
	{
		//敵が先行の場合
		if (!HeroMng->GetDamageFlag())
		{
			EnemyHeroTurn();
			if (EnemyHeroMng->GetHp() > 0.0f && EnemyHeroMng->GetAttackAnimEndFlag()) {
				//自分へのダメージ処理
				switch (m_EnemyAttack)
				{
				case CBattleScene::PowerAttack:
					HeroMng->Damage(EnemyHeroMng->PowerAttack());
					break;
				case CBattleScene::MagicAttack:
					HeroMng->Damage(EnemyHeroMng->MagicAttack());
					break;
				}
			}
		}
		else
		{
			HeroTurn();
			if (HeroMng->GetHp() > 0.0f && HeroMng->GetAttackAnimEndFlag()) {
				//敵へのダメージ処理
				switch (m_Attack)
				{
				case CBattleScene::PowerAttack:
					EnemyHeroMng->Damage(HeroMng->PowerAttack());
					break;
				case CBattleScene::MagicAttack:
					EnemyHeroMng->Damage(HeroMng->MagicAttack());
					break;
				}
			}
		}
	}

	//準備フェーズへ移動
	if (HeroMng->GetDamageAnimEndFlag() && EnemyHeroMng->GetDamageAnimEndFlag())
	{
		//自分、敵の初期化
		HeroMng->BattleInitialize();
		EnemyHeroMng->Initialize();

		//行動を未選択とする
		m_SelectAttack = false;

		//自分、敵のアニメーション終了フラグを下す
		HeroMng->SetAttackAnimEndFlag(false);
		EnemyHeroMng->SetAttackAnimEndFlag(false);

		//行動選択中のカメラ演出を初めからにする
		m_MoveSelectCut = 0;

		//バトルのフェーズを行動選択に戻す
		m_BattlePhase = enBattlePhase::MoveSelectPhase;

	}
}

//次のターンの準備中の処理
void CBattleScene::SetUpToNextTurn()
{
	CHeroManager*      HeroMng      = &CHeroManager::GetInstance();
	CEnemyHeroManager* EnemyHeroMng = &CEnemyHeroManager::GetInstance();

	//自分と敵のスピードを比較
	if (HeroMng->GetBattleParamData().Speed > EnemyHeroMng->GetBattleParamData().Speed)
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

//行動選択中のカメラワーク
void CBattleScene::MoveSelectCamera()
{
	CHeroManager*      HeroMng      = &CHeroManager::GetInstance();
	CEnemyHeroManager* EnemyHeroMng = &CEnemyHeroManager::GetInstance();

	switch (m_MoveSelectCut)
	{
	case 0:
		m_pCamera->SetPos(INIT_CAMPOS);
		m_pCamera->SetLook(INIT_CAMLOOK);

		m_AnimCnt++;

		if (m_AnimCnt >= CHANGE_CUT * 3)
		{
			m_MoveSelectCut = 1;
			m_AnimCnt = 0;
		}
		break;
	case 1:
		m_pCamera->SetPos(m_MoveCamPos.x, START_CAMPOS_FAST_Y, START_CAMPOS_FAST_Z);
		m_pCamera->SetLook(START_CAMLOOK_FAST);

		if (m_MoveCamPos.x <= MAX_MOVE_CAMPOS_FAST_X)
		{
			m_MoveCamPos.x  += CAM_MOVESPEED;
		}
		else
		{
			m_AnimCnt++;

			if (m_AnimCnt >= CHANGE_CUT)
			{
				//カメラを動かす値の初期化
				m_MoveCamPos.x = INIT_MOVE_CAMPOS.x;
				//カウントの初期化
				m_AnimCnt = 0;
				//次のカットへ
				m_MoveSelectCut = 2;
			}
		}
	    break;
	case 2:
		m_pCamera->SetPos(HeroMng->GetPosition().x + SHIFT_CAMPOS_SECOND_Y, m_MoveCamPos.y, HeroMng->GetPosition().z - SHIFT_CAMPOS_SECOND_Z);
		m_pCamera->SetLook(HeroMng->GetPosition().x, m_MoveCamLook.y, HeroMng->GetPosition().z);

		if (m_MoveCamPos.y <= MAX_MOVE_CAMPOS_SECOND_Y)
		{
			m_MoveCamPos.y  += CAM_MOVESPEED/2;
			m_MoveCamLook.y += CAM_MOVESPEED/2;
		}
		else
		{
			//次のカットの前に少し止める
			m_AnimCnt++;
			if (m_AnimCnt >= CHANGE_CUT)
			{
				//カウントの初期化
				m_AnimCnt = 0;
				//カメラを動かす値の初期化
				m_MoveCamPos.y  = 0.0f;
				m_MoveCamLook.y = 0.0f;
				//次のカットへ
				m_MoveSelectCut = 3;
			}
		}
		break;
	case 3:
		m_pCamera->SetPos(HeroMng->GetPosition().x + SHIFT_CAMPOS_THIRD_Y, m_MoveCamPos.y, HeroMng->GetPosition().z + SHIFT_CAMPOS_THIRD_Z);
		m_pCamera->SetLook(EnemyHeroMng->GetPosition().x, m_MoveCamLook.y, EnemyHeroMng->GetPosition().z);

		if (m_MoveCamPos.y <= MAX_MOVE_CAMPOS_THIRD_Y)
		{
			m_MoveCamPos.y  += CAM_MOVESPEED/2;
			m_MoveCamLook.y += CAM_MOVESPEED/2;
		}
		else
		{
			//次のカットの前に少し止める
			m_AnimCnt++;

			if (m_AnimCnt >= CHANGE_CUT)
			{
				//カウントの初期化
				m_AnimCnt = 0;
				//カメラを動かす値の初期化
				m_MoveCamPos.y = 0.0f;
				m_MoveCamLook.y = 0.0f;
				//次のカットへ
				m_MoveSelectCut = 4;
			}
		}
		break;
	case 4:
		m_pCamera->SetPos(INIT_CAMPOS.x, INIT_CAMPOS.y, m_MoveCamPos.z);
		m_pCamera->SetLook(INIT_CAMLOOK);

		//カメラをだんだん下げる
		if (m_MoveCamPos.z >= INIT_CAMPOS.z)
		{
			m_MoveCamPos.z -= CAM_MOVESPEED;
		}
		else
		{
			//カメラを動かす値の初期化
			m_MoveCamPos.z = 0;
			m_MoveSelectCut = 0;
		}
		break;
	default:
		break;
	}
}

//自分のターンに行う処理
void CBattleScene::HeroTurn()
{	
	CHeroManager*      HeroMng      = &CHeroManager::GetInstance();
	CEnemyHeroManager* EnemyHeroMng = &CEnemyHeroManager::GetInstance();


	//現在どちらのターンか
	m_CurrentTurn = false;

	//自分の攻撃
	switch (m_Attack)
	{
	case CBattleScene::PowerAttack:
		//攻撃アニメーションが終わっていなければ
		if (!HeroMng->GetAttackAnimEndFlag()) 
		{
			m_pCamera->SetPos(ATTACK_CAMPOS);
			m_pCamera->SetLook(ATTACK_CAMLOOK);
		}

		//自分の筋力攻撃のアニメーション
		HeroMng->PowerAttackAnim(ANIM_VECTOR_VALUE);

		if (HeroMng->GetAttackAnimEndFlag()) //攻撃アニメーションが終わったら
		{
			m_pCamera->SetPos(ENEMY_ATTACK_CAMPOS);
			m_pCamera->SetLook(ENEMY_ATTACK_CAMLOOK);
			EnemyHeroMng->DamageAnim(1.0f);//敵のダメージアニメーション
		}

		break;
	case CBattleScene::MagicAttack:  
		
		//攻撃アニメーションが終わっていなければ
		if (!HeroMng->GetAttackAnimEndFlag())
		{
			m_pCamera->SetPos(ATTACK_CAMPOS);
			m_pCamera->SetLook(ATTACK_CAMLOOK);
		}
		
		//自分の魔力攻撃のアニメーション
		HeroMng->MagicAttackAnim(ANIM_VECTOR_VALUE);

		if (HeroMng->GetAttackAnimEndFlag()) //攻撃アニメーションが終わったら
		{
			m_pCamera->SetPos(ENEMY_ATTACK_CAMPOS);
			m_pCamera->SetLook(ENEMY_ATTACK_CAMLOOK);
			EnemyHeroMng->DamageAnim(ANIM_VECTOR_VALUE); //敵のダメージアニメーション
		}
		break;
	}
}

//自分のターン中のUI等描画処理
void CBattleScene::DrawHeroTurn()
{
	WriteText* Text = WriteText::GetInstance();
	Text->Draw_Text(L"HERO TURN", WriteText::HeroTurnText,HERO_TURNTEXT_POS);
}

//敵のターンに行う処理
void CBattleScene::EnemyHeroTurn()
{
	CHeroManager*      HeroMng      = &CHeroManager::GetInstance();
	CEnemyHeroManager* EnemyHeroMng = &CEnemyHeroManager::GetInstance();

	//現在どちらのターンか
	m_CurrentTurn = true;

	//敵の攻撃
	switch (m_EnemyAttack)
	{
	case CBattleScene::PowerAttack:
		//攻撃アニメーションが終わっていなければ
		if (!EnemyHeroMng->GetAttackAnimEndFlag())
		{
			m_pCamera->SetPos(ENEMY_ATTACK_CAMPOS);
			m_pCamera->SetLook(ENEMY_ATTACK_CAMLOOK);
		}
		//敵の攻撃アニメーション
		EnemyHeroMng->PowerAttackAnim(-ANIM_VECTOR_VALUE);
		if (EnemyHeroMng->GetAttackAnimEndFlag())	 //攻撃アニメーションが終わったら
		{
			m_pCamera->SetPos(ATTACK_CAMPOS);
			m_pCamera->SetLook(ATTACK_CAMLOOK);
			HeroMng->DamageAnim(-ANIM_VECTOR_VALUE); //敵のダメージアニメーション
		}
		break;
	case CBattleScene::MagicAttack: 
		//攻撃アニメーションが終わっていなければ
		if (!EnemyHeroMng->GetAttackAnimEndFlag())
		{
			m_pCamera->SetPos(ENEMY_ATTACK_CAMPOS);
			m_pCamera->SetLook(ENEMY_ATTACK_CAMLOOK);
		}
		//敵の攻撃アニメーション
		EnemyHeroMng->MagicAttackAnim(-ANIM_VECTOR_VALUE);
		if (EnemyHeroMng->GetAttackAnimEndFlag()) //攻撃アニメーションが終わったら
		{
			m_pCamera->SetPos(ATTACK_CAMPOS);
			m_pCamera->SetLook(ATTACK_CAMLOOK);
			HeroMng->DamageAnim(-ANIM_VECTOR_VALUE); //敵のダメージアニメーション
		}
		break;
	}

}

//敵のターン中の描画処理
void CBattleScene::DrawEnemyHeroTurn()
{
	WriteText* Text = WriteText::GetInstance();

	Text->Draw_Text(L"ENEMYHERO TURN", WriteText::EnemyHeroTurnText, ENEMY_TURNTEXT_POS);
}

//ターンごとの攻撃の設定
void CBattleScene::SettingAttack(int no, enAttackList& attacklist)
{
	switch (no)
	{
	case 0: attacklist = enAttackList::PowerAttack; break;
	case 1: attacklist = enAttackList::MagicAttack; break;
	}
}
