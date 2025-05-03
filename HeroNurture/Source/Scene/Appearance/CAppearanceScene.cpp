#include "Scene\Appearance\CAppearanceScene.h"
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
#include "StaticMeshObject\Ground\CGround.h"

//定数の名前空間
using namespace Constant_AppearanceScene;

CAppearanceScene::CAppearanceScene()
	:m_pCamera         (&CCameraManager::GetInstance())
	,m_pHero	       (&CHeroManager::GetInstance())
	,m_pEnemyHero      (&CEnemyHeroManager::GetInstance())
	,m_pRaccoonDog     ()
	,m_pGround	       ()
	,m_YuiHiddenFlag   ()
	,m_KaitoHiddenFlag ()
	,m_YuiAnimEndFlag  ()
	,m_KaitoAnimEndFlag()
{
}

CAppearanceScene::~CAppearanceScene()
{
}

void CAppearanceScene::Create()
{
	//選択されたヒーローのインスタンス生成
	if (m_pHero->GetSelectHeroName() == "Yui")
	{
		m_pHero->CreateHero(CHeroManager::Yui);
		//選択されなかったヒーローを敵として生成
		m_pEnemyHero->CreateEnemyHero(CHeroManager::Kaito);
	}
	else if (m_pHero->GetSelectHeroName() == "Kaito")
	{
		m_pHero->CreateHero(CHeroManager::Kaito);
		//選択されなかったヒーローを敵として生成
		m_pEnemyHero->CreateEnemyHero(CHeroManager::Yui);
	}

	//タヌキ
	m_pRaccoonDog = make_unique<CRaccoonDog>();

	//地面
	m_pGround = make_unique<CGround>();
}

void CAppearanceScene::Releace()
{
    m_pCamera    = nullptr;
    m_pHero      = nullptr;
	m_pEnemyHero = nullptr;
}

void CAppearanceScene::LoadData()
{
	//選択されているヒーローのメッシュデータ設定
	m_pHero->LoadMeshData();
	//敵のヒーローのメッシュデータ設定
	m_pEnemyHero->LoadMeshData();

	//タヌキのメッシュデータ設定
	m_pRaccoonDog->AttachMesh(CSkinMeshManager::GetMesh(CSkinMeshManager::RaccoonDog));
	//地面のメッシュデータ設定
	m_pGround->AttachMesh(CMeshManager::GetMesh(CMeshManager::Ground));
}

void CAppearanceScene::Initialize()
{
	//カメラ初期設定
	if (m_pHero->GetSelectHeroName() == "Yui")
	{
		m_pCamera->SetPos(YUI_CAMPOS);	 //初期座標
		m_pCamera->SetLook(YUI_CAMLOOK); //初期注視点
	}
	else
	{
		m_pCamera->SetPos(KAITO_CAMPOS);	 //初期座標
		m_pCamera->SetLook(KAITO_CAMLOOK); //初期注視点
	}

	//タヌキの初期化
	m_pRaccoonDog->Initialize();

	//各ヒーローの初期化
	m_pHero->AppearanceInitialize();      //自分
	m_pEnemyHero->AppearanceInitialize(); //敵

	//カメラを動かす値の初期値
	m_MoveCamPos = { 0.0f, 0.0f, 0.0f };
}

void CAppearanceScene::Update()
{
	CKeyManager* KeyMng = &CKeyManager::GetInstance();
	CSceneManager* SceneMng = CSceneManager::GetInstance();

	//フェードイン処理
	if (!FadeIn()) { return; }

	
	//自分がユイを選択していた場合
	if (m_pHero->GetSelectHeroName() == "Yui")
	{
		//タヌキのユイ登場時アニメーション
		m_pRaccoonDog->AppearanceAnim(YUI_CAMPOS.z);
		//ユイのアニメーション
		YuiAppearance();
		//ユイのアニメーションが終了したら
		if (m_YuiAnimEndFlag)
		{
			//カイトのアニメーションへ
			KaitoAppearance();
		}
	}

	//自分がカイトを選択していた場合
	if (m_pHero->GetSelectHeroName() == "Kaito")
	{
		//カイトのアニメーション
		KaitoAppearance();
		//カイトのアニメーションが終了したら
		if (m_KaitoAnimEndFlag)
		{
			//タヌキのユイ登場時アニメーション
			m_pRaccoonDog->AppearanceAnim(YUI_CAMPOS.z);
			//ユイのアニメーション
			YuiAppearance();
		}
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

void CAppearanceScene::Draw()
{
	//カメラの動作
	m_pCamera->CameraUpdate();

	if (!m_YuiAnimEndFlag) 
	{
		//タヌキの描画
		m_pRaccoonDog->Draw();
		//ユイの描画
		YuiDraw();
	}

	//地面の描画
	m_pGround->Draw();
}

void CAppearanceScene::Debug()
{
	ImGui::Begin(JAPANESE("デバッグ"));
	//ImGui::InputFloat3(JAPANESE("カメラ位置:%f"), m_DebugCamPos);
	//ImGui::InputFloat3(JAPANESE("カメラ注視点:%f"), m_DebugCamLook);
	ImGui::InputFloat3(JAPANESE("タヌキ回転:%f"), m_DebugRotate);
	ImGui::End();

	//m_pCamera->SetPos(m_DebugCamPos);
	//m_pCamera->SetLook(m_DebugCamLook);
	m_pRaccoonDog->SetRotation(D3DXVECTOR3(D3DXToRadian(m_DebugRotate.x), D3DXToRadian(m_DebugRotate.y), D3DXToRadian(m_DebugRotate.z)));
}

void CAppearanceScene::YuiAppearance()
{
	switch (m_Scene)
	{
	case 0:
		//動かすカメラの値をセット
		m_pCamera->SetPos(YUI_CAMPOS.x + m_MoveCamPos.x, YUI_CAMPOS.y + m_MoveCamPos.y, YUI_CAMPOS.z + m_MoveCamPos.z);

		//白フェード
		if (m_pRaccoonDog->GetPosition().z <= FLICK_WHITEFADE)
		{
			PlayWhiteFade(0, 0.06f, 1.0f);
		}

		//タヌキがカメラのZ座標を超えたら
		if (m_pRaccoonDog->GetPosition().z <= YUI_CAMPOS.z)
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
		}
		break;
	case 1:
		//自分がユイを選択していた場合
		if (m_pHero->GetSelectHeroName() == "Yui")
		{
			m_pHero->AppearanceAnimation();
			//カメラの設定
			YuiSetCamera(D3DXVECTOR3(m_MoveCamPos.x - 2.0f, m_MoveCamPos.y, m_pHero->GetPosition().z - 2.0f),
						 D3DXVECTOR3(m_pHero->GetPosition().x, m_MoveCamLook.y, m_pHero->GetPosition().z));
		}
		//敵がユイの場合
		else if (m_pHero->GetAppealanceAnimEndFlag())
		{
			//カメラの設定
			YuiSetCamera(D3DXVECTOR3(m_MoveCamPos.x - 2.0f, m_MoveCamPos.y, m_pEnemyHero->GetPosition().z - 2.0f),
				         D3DXVECTOR3(m_pEnemyHero->GetPosition().x, m_pEnemyHero->GetPosition().y, m_pEnemyHero->GetPosition().z));
		}

		//カメラが一定の高さになるまで
		if (!m_pHero->GetAppealanceAnimEndFlag())
		{
			//座標と注視点をあげる
			m_MoveCamPos.y += CAM_MOVE_SPEED;
			m_MoveCamLook.y += CAM_MOVE_SPEED;
		}
		else
		{
			m_AnimCnt++;
		}

		if(m_AnimCnt >= 60)
		{
			m_Scene = 2;
			//動かすカメラのy軸
			m_MoveCamPos.y  = 2.0f;  //座標
			m_MoveCamLook.y = 2.0f; //注視点
			//アニメーションカウントのリセット
			m_AnimCnt = 0;
		}
		break;
	case 2:
		//自分がユイを選択していた場合
		if (m_pHero->GetSelectHeroName() == "Yui")
		{
			m_pHero->AppearanceAnimation();
			//カメラの設定
			YuiSetCamera(D3DXVECTOR3(m_MoveCamPos.x, m_MoveCamPos.y, m_pHero->GetPosition().z - 4.0f),
				         D3DXVECTOR3(m_pHero->GetPosition().x, m_MoveCamLook.y, m_pHero->GetPosition().z));
		}
		//敵がユイの場合
		else if (m_pHero->GetAppealanceAnimEndFlag())
		{
			//カメラの設定
			YuiSetCamera(D3DXVECTOR3(m_MoveCamPos.x, m_MoveCamPos.y, m_pEnemyHero->GetPosition().z - 4.0f),
				         D3DXVECTOR3(m_pEnemyHero->GetPosition().x, m_pEnemyHero->GetPosition().y, m_pEnemyHero->GetPosition().z));
		}

		//カメラが一定の高さになるまで
		if (m_MoveCamPos.y <= YUI_CAMPOS.y + 2.5f)
		{
			//座標と注視点をあげる
			m_MoveCamPos.y += CAM_MOVE_SPEED;
			m_MoveCamLook.y += CAM_MOVE_SPEED;
		}
		else
		{
			PlayWhiteFade(1, 0.02f, 1.0f);
			m_AnimCnt++;
			if (m_AnimCnt >= 50)
			{
				//ユイの非表示
				m_YuiHiddenFlag= true;
			}

			if (m_AnimCnt >= 60)
			{
				//ユイのアニメーションの終了
				m_YuiAnimEndFlag = true;
			}
		}
		break;
	case 3:
		break;
	}
}

void CAppearanceScene::KaitoAppearance()
{
}

void CAppearanceScene::YuiSetCamera(D3DXVECTOR3 pos, D3DXVECTOR3 look)
{
	m_pCamera->SetPos(pos);
	m_pCamera->SetLook(look);
}

void CAppearanceScene::YuiDraw()
{
	//自分がユイを使用している場合の描画
	if (m_pHero->GetSelectHeroName() == "Yui" && !m_YuiHiddenFlag)
	{
		if (m_pRaccoonDog->GetHiddenFlag())
		{
			m_pHero->Draw();
		}
	}
	//敵がユイの場合の描画
	else if (m_KaitoAnimEndFlag)
	{
		if (m_pRaccoonDog->GetHiddenFlag())
		{
			m_pEnemyHero->Draw();
		}
	}
}
