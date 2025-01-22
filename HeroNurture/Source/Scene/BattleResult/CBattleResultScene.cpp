#include "CBattleResultScene.h"
#include "Scene\CSceneManager.h"
#include "KeyManager\CKeyManager.h"
#include "StaticMesh\MeshManager\CMeshManager.h"
#include "SkinMeshObject\Hero\CHeroManager.h"
#include "SkinMeshObject\Hero\Enemy\CEnemyHeroManager.h"
#include "Sound\CSoundManager.h"
#include <cmath>
#include "ImGui\ImGuiManager\ImGuiManager.h"
#include "Json\CJson.h"
#include "Utility\CUtility.h"
#include "Sprite2D\UIManager\CUIManager.h" 

CBattleResultScene::CBattleResultScene()
    : m_pCamera(&CCameraManager::GetInstance())
    , m_pSky()
    , m_pGround()
{
    //ライト情報
    m_Light.vDirection = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //ライト方向
}

CBattleResultScene::~CBattleResultScene()
{
}

void CBattleResultScene::Create()
{
    //----スタティックメッシュ----
    //スカイボックス
    m_pSky = std::make_unique<CSky>();
    //地面
    m_pGround = std::make_unique<CGround>();
}

void CBattleResultScene::Releace()
{
    m_pCamera = nullptr;
}

void CBattleResultScene::LoadData()
{
    CSceneManager* SceneMng = CSceneManager::GetInstance();
    CHeroManager* HeroMng = &CHeroManager::GetInstance();
    CEnemyHeroManager* EnemyHeroMng = &CEnemyHeroManager::GetInstance();


    //----スタティックメッシュ----
    m_pSky->AttachMesh(CMeshManager::GetMesh(CMeshManager::Sky));      //空
    m_pGround->AttachMesh(CMeshManager::GetMesh(CMeshManager::Ground));//地面

    //----スキンメッシュ----
    switch (SceneMng->GetBattleResult())
    {
    case CSceneManager::Win:    
        HeroMng->LoadMeshData();
        break;
    case CSceneManager::Lose:
        EnemyHeroMng->LoadMeshData();
        break;
    default:
        break;
    }
}

void CBattleResultScene::Initialize()
{
    CSceneManager* SceneMng = CSceneManager::GetInstance();
    CHeroManager* HeroMng = &CHeroManager::GetInstance();
    CEnemyHeroManager* EnemyHeroMng = &CEnemyHeroManager::GetInstance();

    //カメラの初期位置

    switch (SceneMng->GetBattleResult())
    {
    case CSceneManager::Win:
        m_pCamera->SetPos(-2.4f, 2.0f, 1.1f);
        m_pCamera->SetLook(-5.0f, 2.0f, -1.0f);
        HeroMng->Initialize();
        break;
    case CSceneManager::Lose:
        m_pCamera->SetPos(-0.3f, 1.8f, 1.8f);
        m_pCamera->SetLook(2.0f, 2.0f, 1.0f);
        EnemyHeroMng->Initialize();
        break;
    default:
        break;
    }

}

//更新関数
void CBattleResultScene::Update()
{
    CSceneManager* SceneMng = CSceneManager::GetInstance();
    CKeyManager* KeyMng = CKeyManager::GetInstance();

    KeyMng->Update();

    //フェードイン処理
    if (!FadeIn()) { return; }

    //モード選択画面のBGM停止
    CSoundManager::GetInstance()->Stop(CSoundManager::BGM_Battle);


    switch (SceneMng->GetBattleResult())
    {
    case CSceneManager::Win:
        //勝利時BGMの再生
        CSoundManager::GetInstance()->PlayLoop(CSoundManager::BGM_Win);
        CSoundManager::GetInstance()->Volume(CSoundManager::BGM_Win, 40);
        break;
    case CSceneManager::Lose:
        //敗北時BGMの再生
        CSoundManager::GetInstance()->PlayLoop(CSoundManager::BGM_Lose);
        CSoundManager::GetInstance()->Volume(CSoundManager::BGM_Lose, 40);
        break;
    default:
        break;
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
        SceneMng->LoadCreate(CSceneManager::ModeSelect);
    }
}

void CBattleResultScene::Draw()
{
    CSceneManager* SceneMng = CSceneManager::GetInstance();
    CHeroManager* HeroMng = &CHeroManager::GetInstance();
    CEnemyHeroManager* EnemyHeroMng = &CEnemyHeroManager::GetInstance();

    //カメラの動作
    m_pCamera->CameraUpdate();

    //スカイボックスの描画
    m_pSky->Draw();

    //地面の描画
    m_pGround->Draw();


    switch (SceneMng->GetBattleResult())
    {
    case CSceneManager::Win:
        HeroMng->MoveSelectAnim();
        HeroMng->Draw();
        break;
    case CSceneManager::Lose:
        EnemyHeroMng->MoveSelectAnim();
        EnemyHeroMng->Draw();
        break;
    default:
        break;
    }


    //UI
    DrawUI();

    //デバッグ
    Debug();
}

void CBattleResultScene::Debug()
{
#if DEBUG
    ImGui::Begin(JAPANESE("カメラ位置"));
    ImGui::Text(JAPANESE("座標X:%f\n座標Y:%f\n座標Z:%f"), m_pCamera->GetPos().x,m_pCamera->GetPos().y,m_pCamera->GetPos().z);
    ImGui::InputFloat3(JAPANESE("注視点:%f"), m_CamLook);
    CCameraManager::GetInstance().SetLook(m_CamLook);
    ImGui::End();
#endif

}

//タイトル画面の描画
void CBattleResultScene::DrawUI()
{
    WriteText* Text = WriteText::GetInstance();
    CSceneManager* SceneMng = CSceneManager::GetInstance();

    switch (SceneMng->GetBattleResult())
    {
    case CSceneManager::Win:
        Text->Draw_Text(L"WIN", WriteText::Win, RESULTTEXT_POS);
        break;
    case CSceneManager::Lose:
        Text->Draw_Text(L"LOSE", WriteText::Lose, RESULTTEXT_POS);
        break;
    default:
        break;
    }  
}

