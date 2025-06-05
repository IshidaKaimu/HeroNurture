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
#include "WriteText\WriteText.h"

//定数の名前空間
using namespace Constant_KaitoAppearanceScene;

CKaitoAppearanceScene::CKaitoAppearanceScene()
	:m_pCamera     (&CCameraManager::GetInstance())
	, m_pKaito     ()
	, m_pGround	   ()
	, m_HiddenFlag ()
	, m_AnimEndFlag()
	, m_SkipFlag   ()
{
}

CKaitoAppearanceScene::~CKaitoAppearanceScene()
{
}

void CKaitoAppearanceScene::Create()
{
	CHeroManager* HeroMng = &CHeroManager::GetInstance();

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
	m_pCamera->SetPos(INIT_CAMPOS);	  //初期座標
	m_pCamera->SetLook(INIT_CAMLOOK); //初期注視点

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
	CSceneManager* SceneMng = &CSceneManager::GetInstance();
	CEffect* Eff = CEffect::GetInstance();

	//バトルヒーロー選択BGMを停止
	CSoundManager::GetInstance()->Stop(CSoundManager::BGM_BattleHeroSelect);

	//バトルBGMの再生
	CSoundManager::GetInstance()->PlayLoop(CSoundManager::BGM_Battle);
	CSoundManager::GetInstance()->Volume(CSoundManager::BGM_Battle, 40);

	//キーマネージャの動作
	KeyMng->Update();

	//フェードイン処理
	if (!FadeIn()) { return; }

	//自分がカイトを選択していた場合
	//カイトのアニメーション
	KaitoAppearance();

	//スキップ
	if (KeyMng->IsDown(VK_RETURN))
	{
		//演出スキップフラグを立てる
		m_SkipFlag = true;

		//全てのエフェクトを止める
		Eff->StopAll();

		//バトルシーンへ
		m_SceneTransitionFlg = true;
	}


	//シーン遷移(仮)
	if (m_AnimEndFlag)
	{
		//オープニングシーンへ
		m_SceneTransitionFlg = true;
	}
	//フェードアウト処理
	if (m_SceneTransitionFlg && FadeOut())
	{
		if (HeroMng->GetBattleHeroName() == "Kaito")
		{
		   SceneMng->LoadCreate(CSceneManager::YuiAppearance);
		}
		else 
		{
			SceneMng->LoadCreate(CSceneManager::Battle);
		}

		//演出スキップフラグが立っていればバトルシーンへ
		if (m_SkipFlag)
		{
			SceneMng->LoadCreate(CSceneManager::Battle);
		}
	}

#if DEBUG
	//デバッグ処理
	Debug();
#endif
}

void CKaitoAppearanceScene::Draw()
{
	CHeroManager* HeroMng   = &CHeroManager::GetInstance();
	WriteText* Text	        = WriteText::GetInstance();
	CSceneManager* SceneMng = &CSceneManager::GetInstance();

	//カメラの動作
	m_pCamera->CameraUpdate();

	//カイトのアニメーション中の描画
	if (!m_HiddenFlag)
	{
		m_pKaito->Draw();
	}

	//地面の描画
	m_pGround->Draw();

	//空の描画
	DrawSky();

	//操作方法指示バーの描画
	DrawControlBar(false);

	//演出スキップ指示の描画
	Text->Draw_Text(L"Enter 演出スキップ", WriteText::Control, ENTERTEXT_POS);

}

void CKaitoAppearanceScene::Debug()
{
#if DEBUG
	ImGui::Begin(JAPANESE("デバッグ"));
	//ImGui::InputFloat3(JAPANESE("カメラ位置:%f"), m_DebugCamPos);
	//ImGui::InputFloat3(JAPANESE("カメラ注視点:%f"), m_DebugCamLook);
	ImGui::End();

	//m_pCamera->SetPos(m_DebugCamPos);
	//m_pCamera->SetLook(m_DebugCamLook);
#endif
}

void CKaitoAppearanceScene::KaitoAppearance()
{
	CSceneManager* SceneMng = &CSceneManager::GetInstance();
	CHeroManager* HeroMng = &CHeroManager::GetInstance();
	CEffect* Eff = CEffect::GetInstance();
	//エフェクトハンドルの用意
	static ::EsHandle hMagicSircle = -1;	//魔法陣エフェクト
	static ::EsHandle hLaser       = 3;	    //光エフェクト
	//----魔法陣エフェクトの設定----
	Eff->Speed(hMagicSircle, 1.0f);
	Eff->Scale(hMagicSircle,  MAGICSIRCLE_SCALE);
	Eff->Rotate(hMagicSircle, MAGICSIRCLE_ROTATE);
	//----光エフェクトの設定----
	Eff->Speed(hLaser, 1.0f);
	Eff->Scale(hLaser,  LASER_SCALE);
	Eff->Rotate(hLaser, LASER_ROTATE);

	switch (m_Scene)
	{
	case 0:
		//カメラの設定
		SetCamera(D3DXVECTOR3(MAGICSIRCLE_CAMPOS.x, MAGICSIRCLE_CAMPOS.y + m_MoveCamPos.y, MAGICSIRCLE_CAMPOS.z),
			D3DXVECTOR3(MAGICSIRCLE_POS));

		//カメラのy軸の座標を一定の値まで上げる
		if (m_MoveCamPos.y <= ANIMCHANGE_CAMPOS_Y)
		{
			m_MoveCamPos.y += CAM_MOVE_SPEED;
		}
		else
		{
			//アニメーションカウント増加
			m_AnimCnt++;
			//魔法陣エフェクトの再生
			if (m_AnimCnt == 1)
			{
				hMagicSircle = Eff->Play(CEffect::enList::MagicSircle, MAGICSIRCLE_POS);
				//魔法陣SEの再生
				CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_MagicSircle);
				CSoundManager::GetInstance()->Volume(CSoundManager::SE_MagicSircle, 40);
			}
			//カウントが一定値を超えたら魔法陣エフェクトの再生
			if (m_AnimCnt >= ANIMCHANGE_CNT) 
			{
				m_Scene = 1;
				m_AnimCnt = 0;
			}
		}

		break;
	case 1:
		//カメラの設定
		SetCamera(D3DXVECTOR3(MAGICSIRCLE_CAMPOS.x - m_MoveCamPos.x, MAGICSIRCLE_CAMPOS.y + m_MoveCamPos.y, MAGICSIRCLE_CAMPOS.z - m_MoveCamPos.z),
			      D3DXVECTOR3(MAGICSIRCLE_POS.x, MAGICSIRCLE_POS.y + m_MoveCamLook.y, MAGICSIRCLE_POS.z));
		//カメラをz軸方向に移動
		if (m_MoveCamPos.z <= MOVE_CAMPOS_MAX.z)
		{
			m_MoveCamPos.z += CAM_MOVE_SPEED;
		}
		else
		{
			m_AnimCnt++;
		}

		//カメラをx軸方向に移動
		if (m_MoveCamPos.x <= MOVE_CAMPOS_MAX.x)
		{
			m_MoveCamPos.x += CAM_MOVE_SPEED;
		}

		//カメラをy軸方向に移動
		if (m_MoveCamPos.y >= MOVE_CAMPOS_MAX.y)
		{
			m_MoveCamPos.y -= CAM_MOVE_SPEED;
		}

		//注視点のy軸方向の移動
		if (m_MoveCamLook.y <= MOVE_CAMLOOK_MAX_Y)
		{
			m_MoveCamLook.y += CAM_MOVE_SPEED;
		}

		//光エフェクトの再生
		if (m_AnimCnt == 1)
		{
			hLaser = Eff->Play(CEffect::Laser, MAGICSIRCLE_POS);
		}

		if (m_AnimCnt == 120)
		{
			//光SEの再生
			CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Laser);
			CSoundManager::GetInstance()->Volume(CSoundManager::SE_Laser, 40);
		}

		//シーンを進める
		if (m_AnimCnt >= SCENECHANGE_CNT_FAST)
		{
			m_Scene = 2;

			//アニメーションカウントの初期化
			m_AnimCnt = 0;
			//次のシーンでの動かすカメラの値の初期値
			m_MoveCamPos = MOVE_CAMPOS_INIT;
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

		if (m_MoveCamPos.y <= MOVE_CAMPOS_MAX_Y)
		{
			m_MoveCamPos.y  += CAM_MOVE_SPEED;
			m_MoveCamLook.y += CAM_MOVE_SPEED;
		}
		else
		{
			//アニメーションカウントの加算
			m_AnimCnt++;
			
			//カメラが止まってからしばらく経ってから
			if (m_AnimCnt >= SCENECEND_CNT_SECOND)
			{
				m_AnimEndFlag = true;
				//魔法陣エフェクトの停止
				Eff->Stop(hMagicSircle);
			}
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

