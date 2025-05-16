#include "Scene\Appearance\Yui\CYuiAppearanceScene.h"
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
#include "StaticMeshObject\Ground\CGround.h"
#include "WriteText\WriteText.h"

//定数の名前空間
using namespace Constant_AppearanceScene;

CYuiAppearanceScene::CYuiAppearanceScene()
	:m_pCamera         (&CCameraManager::GetInstance())
	,m_pYui	           ()
	,m_pRaccoonDog     ()
	,m_pGround	       ()
	,m_HiddenFlag      ()
	,m_AnimEndFlag     ()
	,m_SkipFlag		   ()
{
}

CYuiAppearanceScene::~CYuiAppearanceScene()
{
}

void CYuiAppearanceScene::Create()
{
	CHeroManager* HeroMng = &CHeroManager::GetInstance();

	//ユイ
	m_pYui = make_unique<CYui>();

	//タヌキ
	m_pRaccoonDog = make_unique<CRaccoonDog>();

	//地面
	m_pGround = make_unique<CGround>();
}

void CYuiAppearanceScene::Releace()
{
    m_pCamera    = nullptr;
}

void CYuiAppearanceScene::LoadData()
{
	//ヒーローのメッシュデータ設定
	m_pYui->LoadMeshData();

	//----スタティックメッシュ----
	//タヌキのメッシュデータ設定
	m_pRaccoonDog->AttachMesh(CSkinMeshManager::GetMesh(CSkinMeshManager::RaccoonDog));
	//地面のメッシュデータ設定
	m_pGround->AttachMesh(CMeshManager::GetMesh(CMeshManager::Ground));
}

void CYuiAppearanceScene::Initialize()
{
	CHeroManager* HeroMng = &CHeroManager::GetInstance();

	//カメラ初期設定
	m_pCamera->SetPos(INIT_CAMPOS);	 //初期座標
	m_pCamera->SetLook(INIT_CAMLOOK); //初期注視点

	//タヌキの初期化
	m_pRaccoonDog->Initialize();

	//初期化
	m_pYui->AppearanceInitialize(); 

	//カメラを動かす値の初期値
	m_MoveCamPos = { 0.0f, 0.0f, 0.0f };
}

void CYuiAppearanceScene::Update()
{
	CHeroManager* HeroMng   = &CHeroManager::GetInstance();
	CKeyManager* KeyMng     = &CKeyManager::GetInstance();
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

	
	//スキップ
	if (CKeyManager::GetInstance().IsDown(VK_RETURN))
	{
		//演出スキップフラグを立てる
		m_SkipFlag = true;

		//全てのエフェクトを止める
		Eff->StopAll();

		//バトルシーンへ
		m_SceneTransitionFlg = true;
	}



	//自分がユイを選択していた場合
	if (!m_AnimEndFlag)
	 {
	     //タヌキのユイ登場時アニメーション
	     if (!m_pRaccoonDog->GetHiddenFlag()) 
	     {
	       m_pRaccoonDog->AppearanceAnim(INIT_CAMPOS.z);
	     }
		 //ユイのアニメーション
		 YuiAppearance();
	  }
	  //ユイのアニメーションが終了したら
	  else 
	  {
		  //シーン段階のリセット
		  m_Scene = 0;
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
		if (HeroMng->GetBattleHeroName() == "Yui")
		{
			SceneMng->LoadCreate(CSceneManager::KaitoAppearance);
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

void CYuiAppearanceScene::Draw()
{
	CHeroManager*  HeroMng  = &CHeroManager::GetInstance();
	CSceneManager* SceneMng = &CSceneManager::GetInstance();
	WriteText*     Text     = WriteText::GetInstance();

	//カメラの動作
	m_pCamera->CameraUpdate();

	//地面の描画
	m_pGround->Draw();

	//ユイのアニメーション中
	//タヌキの描画
	if (!m_pRaccoonDog->GetHiddenFlag())
	{
		m_pRaccoonDog->Draw();
	}
	else 
	{
		//ユイの描画
		m_pYui->Draw();
	}

	//操作方法指示バーの描画
	DrawControlBar(false);

	//演出スキップ指示の描画
	Text->Draw_Text(L"Enter 演出スキップ", WriteText::Control, ENTERTEXT_POS);

}

void CYuiAppearanceScene::Debug()
{
#if DEBUG
	ImGui::Begin(JAPANESE("デバッグ"));
	//ImGui::InputFloat3(JAPANESE("カメラ位置:%f"), m_DebugCamPos);
	//ImGui::InputFloat3(JAPANESE("カメラ注視点:%f"), m_DebugCamLook);
	ImGui::InputFloat3(JAPANESE("タヌキ回転:%f"), m_DebugRotate);
	ImGui::End();

	//m_pCamera->SetPos(m_DebugCamPos);
	//m_pCamera->SetLook(m_DebugCamLook);
	m_pRaccoonDog->SetRotation(D3DXVECTOR3(D3DXToRadian(m_DebugRotate.x), D3DXToRadian(m_DebugRotate.y), D3DXToRadian(m_DebugRotate.z)));
#endif
}

void CYuiAppearanceScene::YuiAppearance()
{
	CHeroManager* HeroMng = &CHeroManager::GetInstance();

	switch (m_Scene)
	{
	case 0:
		//動かすカメラの値をセット
		m_pCamera->SetPos(INIT_CAMPOS.x + m_MoveCamPos.x, INIT_CAMPOS.y + m_MoveCamPos.y, INIT_CAMPOS.z + m_MoveCamPos.z);

		//白フェード
		if (m_pRaccoonDog->GetPosition().z <= FLICK_WHITEFADE)
		{
			PlayWhiteFade(0, 0.06f, 1.0f);
			m_AnimCnt++;
			if (m_AnimCnt == 1)
			{
				//衝突SEの再生
				CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_RaccoonCollision);
				CSoundManager::GetInstance()->Volume(CSoundManager::SE_RaccoonCollision, 60);
			}
		}

		//タヌキがカメラのZ座標を超えたら
		if (m_pRaccoonDog->GetPosition().z <= INIT_CAMPOS.z)
		{
			if (m_MoveCamPos.z >= -CAM_FLICK_DISTANCE)
			{
				m_MoveCamPos.z -= CAM_FLICK_SPEED;
			}		
		}
		//タヌキが非表示になったら
		if (m_pRaccoonDog->GetHiddenFlag())
		{
			//シーンを進める
			m_Scene = 1;
			//動かすカメラのy軸
			m_MoveCamPos.y = 1.5f;
			//アニメーションカウントの初期化
			m_AnimCnt = 0;
		}
		break;
	case 1:
		//自分がユイを選択していた場合
		m_pYui->AppearanceAnimation();
		//カメラの設定
		SetCamera(D3DXVECTOR3(m_MoveCamPos.x - SHIFT_CAMPOS, m_MoveCamPos.y, m_pYui->GetPosition().z - SHIFT_CAMPOS),
						 D3DXVECTOR3(m_pYui->GetPosition().x, m_MoveCamLook.y, m_pYui->GetPosition().z));

		//カメラが一定の高さになるまで
		if (!m_pYui->GetAppealanceAnimEndFlag())
		{
			//座標と注視点をあげる
			m_MoveCamPos.y += CAM_MOVE_SPEED;
			m_MoveCamLook.y += CAM_MOVE_SPEED;
		}
		else
		{
			m_AnimCnt++;
		}

		if(m_AnimCnt >= ANIMCHANGE_CNT)
		{
			m_Scene = 2;
			//動かすカメラのy軸
			m_MoveCamPos.y  = MOVE_INIT_CAMPOS_Y;  //座標
			m_MoveCamLook.y = MOVE_INIT_CAMLOOK_Y; //注視点
			//アニメーションカウントのリセット
			m_AnimCnt = 0;
		}
		break;
	case 2:
		//自分がユイを選択していた場合
		m_pYui->AppearanceAnimation();
		//カメラの設定
		SetCamera(D3DXVECTOR3(m_MoveCamPos.x, m_MoveCamPos.y, m_pYui->GetPosition().z - 4.0f),
				         D3DXVECTOR3(m_pYui->GetPosition().x, m_MoveCamLook.y, m_pYui->GetPosition().z));

		//カメラが一定の高さになるまで
		if (m_MoveCamPos.y <= MOVEMENT_RANGE_MAX_Y)
		{
			//座標と注視点をあげる
			m_MoveCamPos.y += CAM_MOVE_SPEED;
			m_MoveCamLook.y += CAM_MOVE_SPEED;
		}
		else
		{
			m_AnimCnt++;
			if (m_AnimCnt >= SCENECEND_CNT_SECOND)
			{
				m_AnimCnt = 0;
				//ユイのアニメーションの終了
				m_AnimEndFlag = true;
			}
		}
		break;
	}
}

void CYuiAppearanceScene::SetCamera(D3DXVECTOR3 pos, D3DXVECTOR3 look)
{
	m_pCamera->SetPos(pos);
	m_pCamera->SetLook(look);
}


