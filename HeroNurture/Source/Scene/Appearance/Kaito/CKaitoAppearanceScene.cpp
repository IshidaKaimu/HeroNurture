#include "Scene\Appearance\Kaito\CKaitoAppearanceScene.h"
#include "Scene\CSceneManager.h"
#include "StaticMesh\MeshManager\CMeshManager.h"
#include "Sprite2D\UIManager\CUIManager.h"
#include "SkinMesh\SkinMeshManager\CSkinMeshManager.h"
#include "Sound\CSoundManager.h"
#include "ImGui\ImGuiManager\ImGuiManager.h"
#include "Camera\CameraManager\CCameraManager.h"
#include "SkinMeshObject\Hero\CHeroManager.h"
#include "SkinMeshObject\Hero\Enemy\CEnemyHeroManager.h"
#include "KeyManager\CKeyManager.h"
#include "Effect\CEffect.h"
#include "SkinMeshObject\Event\RaccoonDog\CRaccoonDog.h"
#include "SkinMeshObject\Hero\Yui\CYui.h"
#include "SkinMeshObject\Hero\Kaito\CKaito.h"
#include "StaticMeshObject\Ground\CGround.h"

//定数の名前空間
using namespace Constant_KaitoAppearanceScene;

CKaitoAppearanceScene::CKaitoAppearanceScene()
	:m_pCamera(&CCameraManager::GetInstance())
	, m_pYui()
	, m_pKaito()
	, m_pGround()
	, m_HiddenFlag()
{
}

CKaitoAppearanceScene::~CKaitoAppearanceScene()
{
}

void CKaitoAppearanceScene::Create()
{
	CHeroManager* HeroMng = &CHeroManager::GetInstance();

	//ユイ
	m_pYui = make_unique<CYui>();
	//カイト
	m_pKaito = make_unique<CKaito>();

	//地面
	m_pGround = make_unique<CGround>();
}

void CKaitoAppearanceScene::Releace()
{
	m_pCamera = nullptr;
}

void CKaitoAppearanceScene::LoadData()
{
	//ヒーローのメッシュデータ設定
	m_pKaito->LoadMeshData();

	//地面のメッシュデータ設定
	m_pGround->AttachMesh(CMeshManager::GetMesh(CMeshManager::Ground));
}

void CKaitoAppearanceScene::Initialize()
{
	CHeroManager* HeroMng = &CHeroManager::GetInstance();

	//カメラ初期設定
	m_pCamera->SetPos(KAITO_CAMPOS);	 //初期座標
	m_pCamera->SetLook(KAITO_CAMLOOK); //初期注視点

	//各ヒーローの初期化
	m_pYui->AppearanceInitialize();   //自分
	m_pKaito->AppearanceInitialize(); //敵

	//カメラを動かす値の初期値
	m_MoveCamPos = { 0.0f, 0.0f, 0.0f };
}

void CKaitoAppearanceScene::Update()
{
	CHeroManager* HeroMng = &CHeroManager::GetInstance();

	CKeyManager* KeyMng = &CKeyManager::GetInstance();
	CSceneManager* SceneMng = CSceneManager::GetInstance();

	//フェードイン処理
	if (!FadeIn()) { return; }

	//自分がカイトを選択していた場合
	if (HeroMng->GetBattleHeroName() == "Kaito")
	{
		//カイトのアニメーション
		KaitoAppearance();
	}

	//シーン遷移(仮)
	if (KeyMng->IsDown(VK_RETURN))
	{
		//決定SEの再生
		CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Enter);
		CSoundManager::GetInstance()->Volume(CSoundManager::SE_Enter, 40);

		//オープニングシーンへ
		m_SceneTransitionFlg = true;
	}
	//フェードアウト処理
	if (m_SceneTransitionFlg && FadeOut())
	{
		SceneMng->LoadCreate(CSceneManager::Battle);
	}

#if DEBUG
	//デバッグ処理
	Debug();
#endif
}

void CKaitoAppearanceScene::Draw()
{
	CHeroManager* HeroMng = &CHeroManager::GetInstance();

	//カメラの動作
	m_pCamera->CameraUpdate();

	//カイトのアニメーション中の描画
	if (HeroMng->GetBattleHeroName() == "Kaito")
	{
	  KaitoDraw();
	}

	//地面の描画
	m_pGround->Draw();
}

void CKaitoAppearanceScene::Debug()
{
	ImGui::Begin(JAPANESE("デバッグ"));
	//ImGui::InputFloat3(JAPANESE("カメラ位置:%f"), m_DebugCamPos);
	//ImGui::InputFloat3(JAPANESE("カメラ注視点:%f"), m_DebugCamLook);
	ImGui::End();

	//m_pCamera->SetPos(m_DebugCamPos);
	//m_pCamera->SetLook(m_DebugCamLook);
}

void CKaitoAppearanceScene::KaitoAppearance()
{
	CEffect* Eff = CEffect::GetInstance();
	//エフェクトハンドルの用意
	static ::EsHandle hMagicSircle = -1;	//魔法陣エフェクト
	Eff->Speed(hMagicSircle, 1.0f);
	Eff->Scale(hMagicSircle, 4.0f, 4.0f, 4.0f);
	Eff->Rotate(hMagicSircle, D3DXToRadian(90.0f), 1.0f, 1.0f);

	CHeroManager* HeroMng = &CHeroManager::GetInstance();

	switch (m_Scene)
	{
	case 0:
		SetCamera(D3DXVECTOR3(MAGICSIRCLE_CAMPOS.x, MAGICSIRCLE_CAMPOS.y + m_MoveCamPos.y, MAGICSIRCLE_CAMPOS.z),
			D3DXVECTOR3(MAGICSIRCLE_POS));

		m_AnimCnt++;
		if (m_AnimCnt == 1)
		{
			hMagicSircle = Eff->Play(CEffect::enList::MagicSircle, MAGICSIRCLE_POS);
		}

		if (m_MoveCamPos.y <= 20.0f)
		{
			m_MoveCamPos.y += CAM_MOVE_SPEED;
		}
		break;
	case 1:
		break;
	default:
		break;
	}
}

void CKaitoAppearanceScene::SetCamera(D3DXVECTOR3 pos, D3DXVECTOR3 look)
{
	m_pCamera->SetPos(pos);
	m_pCamera->SetLook(look);
}

void CKaitoAppearanceScene::KaitoDraw()
{
	CHeroManager* HeroMng = &CHeroManager::GetInstance();

	//自分がカイトを使用している場合の描画
	if (HeroMng->GetSelectHeroName() == "Kaito" && !m_HiddenFlag)
	{
		m_pKaito->Draw();
	}
}
