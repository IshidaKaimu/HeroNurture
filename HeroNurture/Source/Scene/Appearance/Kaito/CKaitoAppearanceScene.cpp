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
	, m_AnimEndFlag()
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
	m_pCamera->SetPos(CAMPOS);	 //初期座標
	m_pCamera->SetLook(CAMLOOK); //初期注視点

	//カイト初期化
	m_pKaito->AppearanceInitialize(); 

	//カメラを動かす値の初期値
	m_MoveCamPos = { 0.0f, 0.0f, 0.0f };

	//カイトの非表示フラグ初期化
	m_HiddenFlag = true;
}

void CKaitoAppearanceScene::Update()
{
	CHeroManager* HeroMng = &CHeroManager::GetInstance();

	CKeyManager* KeyMng = &CKeyManager::GetInstance();
	CSceneManager* SceneMng = CSceneManager::GetInstance();

	//フェードイン処理
	if (!FadeIn()) { return; }

	//自分がカイトを選択していた場合
	//カイトのアニメーション
	KaitoAppearance();

	//シーン遷移(仮)
	if (m_AnimEndFlag)
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
	if (!m_HiddenFlag)
	{
		m_pKaito->Draw();
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
	CSceneManager* SceneMng = CSceneManager::GetInstance();
	CEffect* Eff = CEffect::GetInstance();
	//エフェクトハンドルの用意
	static ::EsHandle hMagicSircle = -1;	//魔法陣エフェクト
	static ::EsHandle hLaser       = 3;	    //光エフェクト
	//----魔法陣エフェクトの設定----
	Eff->Speed(hMagicSircle, 1.0f);
	Eff->Scale(hMagicSircle, 4.0f, 4.0f, 4.0f);
	Eff->Rotate(hMagicSircle, D3DXToRadian(90.0f), 1.0f, 1.0f);
	//----光エフェクトの設定----
	Eff->Speed(hLaser, 1.0f);
	Eff->Scale(hLaser, 5.0f, 5.0f, 5.0f);
	Eff->Rotate(hLaser, D3DXToRadian(270.0f), 1.0f, 1.0f);


	CHeroManager* HeroMng = &CHeroManager::GetInstance();

	switch (m_Scene)
	{
	case 0:
		//カメラの設定
		SetCamera(D3DXVECTOR3(MAGICSIRCLE_CAMPOS.x, MAGICSIRCLE_CAMPOS.y + m_MoveCamPos.y, MAGICSIRCLE_CAMPOS.z),
			D3DXVECTOR3(MAGICSIRCLE_POS));

		m_AnimCnt++;
		if (m_AnimCnt == 1)
		{
			hMagicSircle = Eff->Play(CEffect::enList::MagicSircle, MAGICSIRCLE_POS);
		}

		//カメラのy軸の座標を一定の値まで上げる
		if (m_MoveCamPos.y <= 10.0f)
		{
			m_MoveCamPos.y += CAM_MOVE_SPEED;
		}
		else
		{
			//シーンを進める
			m_Scene = 1;
			m_AnimCnt = 0;
		}
		break;
	case 1:
		//カメラの設定
		SetCamera(D3DXVECTOR3(MAGICSIRCLE_CAMPOS.x - m_MoveCamPos.x, MAGICSIRCLE_CAMPOS.y + m_MoveCamPos.y, MAGICSIRCLE_CAMPOS.z - m_MoveCamPos.z),
			      D3DXVECTOR3(MAGICSIRCLE_POS.x, MAGICSIRCLE_POS.y + m_MoveCamLook.y, MAGICSIRCLE_POS.z));
		//カメラをz軸方向に移動
		if (m_MoveCamPos.z <= 12.0f)
		{
			m_MoveCamPos.z += CAM_MOVE_SPEED;
		}
		else
		{
			m_AnimCnt++;
		}


		if (m_MoveCamPos.x <= 1.0f)
		{
			m_MoveCamPos.x += CAM_MOVE_SPEED;
		}

		if (m_MoveCamPos.y >= 6.0f)
		{
			m_MoveCamPos.y -= CAM_MOVE_SPEED;
		}

		if (m_MoveCamLook.y <= 4.0f)
		{
			m_MoveCamLook.y += CAM_MOVE_SPEED;
		}

		//光エフェクトの再生
		if (m_AnimCnt == 1)
		{
			hLaser = Eff->Play(CEffect::Laser, MAGICSIRCLE_POS);
		}

		//シーンを進める
		if (m_AnimCnt >= 240)
		{
			m_Scene = 2;

			//次のシーンでの動かすカメラの値の初期値
			m_MoveCamPos = { 0.0f, 1.0f, 5.0f };
			m_MoveCamLook.y = 1.0f;
		}

		break;
	case 2:
		//カメラの設定
		SetCamera(D3DXVECTOR3(0.0f, MAGICSIRCLE_CAMPOS.y + m_MoveCamPos.y, MAGICSIRCLE_CAMPOS.z - m_MoveCamPos.z),
			D3DXVECTOR3(MAGICSIRCLE_POS.x, m_MoveCamLook.y, MAGICSIRCLE_POS.z));

		//カイトの登場シーンのアニメーション
		m_pKaito->AppearanceAnimation();

		//非表示フラグをおろす
		m_HiddenFlag = false;

		if (m_MoveCamPos.y <= 6.5f)
		{
			m_MoveCamPos.y  += CAM_MOVE_SPEED;
			m_MoveCamLook.y += CAM_MOVE_SPEED;
		}
		else
		{
			m_AnimEndFlag = true;
		}

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

