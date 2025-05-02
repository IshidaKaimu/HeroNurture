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
	:m_pCamera    (&CCameraManager::GetInstance())
	,m_pHero	  (&CHeroManager::GetInstance())
	,m_pEnemyHero (&CEnemyHeroManager::GetInstance())
	,m_pRaccoonDog()
	,m_pGround	  ()
{
}

CAppearanceScene::~CAppearanceScene()
{
}

void CAppearanceScene::Create()
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
	m_pCamera->SetPos(YUI_CAMPOS);	 //初期座標
	m_pCamera->SetLook(YUI_CAMLOOK); //初期注視点

	//タヌキの初期化
	m_pRaccoonDog->Initialize();

	//各ヒーローの初期化
	m_pHero->AppearanceInitialize();      //自分
	m_pEnemyHero->AppearanceInitialize(); //敵

	//カメラを動かす値の初期値
	m_MoveCam = { 0.0f, 0.0f, 0.0f };
}

void CAppearanceScene::Update()
{
	CKeyManager* KeyMng = &CKeyManager::GetInstance();
	CSceneManager* SceneMng = CSceneManager::GetInstance();


	//フェードイン処理
	if (!FadeIn()) { return; }

	//タヌキのユイ登場時アニメーション
	m_pRaccoonDog->AppearanceAnim(YUI_CAMPOS.z);

	//ユイの登場時に行う処理
	YuiAppearance();

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

	//タヌキの描画
	m_pRaccoonDog->Draw();

	//ユイの描画
	YuiDraw();

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
	//動かすカメラの値をセット
	m_pCamera->SetPos(YUI_CAMPOS.x + m_MoveCam.x, YUI_CAMPOS.y + m_MoveCam.y, YUI_CAMPOS.z + m_MoveCam.z);

	switch (m_Scene)
	{
	case 0:
		//白フェード
		if (m_pRaccoonDog->GetPosition().z <= FLICK_WHITEFADE)
		{
			PlayWhiteFade(0, 0.06f, 1.0f);
		}

		//タヌキがカメラのZ座標を超えたら
		if (m_pRaccoonDog->GetPosition().z <= YUI_CAMPOS.z)
		{
			if (m_MoveCam.z >= -CAM_FLICK_DISTANCE)
			{
				m_MoveCam.z -= CAM_FLICK_SPEED;
			}
		
		}
		//タヌキが非表示になったら
		if (m_pRaccoonDog->GetHiddenFlag())
		{
			//シーンを進める
			m_Scene = 1;
		}
		break;
	case 1:
		if (m_pHero->GetHeroName() == "Yui") { m_pHero->AppearanceAnimation(); }
		if (m_pEnemyHero->GetEnemyHeroName() == "Yui") { m_pEnemyHero->AppearanceAnimation(); }
		break;
	}
}

void CAppearanceScene::KaitoAppearance()
{
}

void CAppearanceScene::YuiDraw()
{
	//自分がユイを使用している場合の描画
	if (m_pHero->GetHeroName() == "Yui")
	{
		if (m_pRaccoonDog->GetHiddenFlag())
		{
			m_pHero->Draw();
		}
	}
	//敵がユイの場合の描画
	if (m_pEnemyHero->GetEnemyHeroName() == "Yui")
	{
		if (m_pRaccoonDog->GetHiddenFlag())
		{
			m_pEnemyHero->Draw();
		}
	}
}
