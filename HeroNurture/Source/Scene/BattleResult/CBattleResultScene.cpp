#include "CBattleResultScene.h"
#include "Scene\CSceneManager.h"
#include "ModeManager\Battle\CBattleManager.h"
#include "SkinMeshObject\Hero\CHeroManager.h"	
#include "KeyManager\CKeyManager.h"
#include "Camera\CameraManager\CCameraManager.h"
#include "StaticMesh\MeshManager\CMeshManager.h"
#include "SkinMeshObject\Hero\CHeroManager.h"
#include "SkinMeshObject\Hero\Enemy\CEnemyHeroManager.h"
#include "Sound\CSoundManager.h"
#include <cmath>
#include "ImGui\ImGuiManager\ImGuiManager.h"
#include "Json\CJson.h"
#include "Utility\CUtility.h"
#include "Sprite2D\UIManager\CUIManager.h" 

//定数の名前空間
using namespace Constant_BattleResultScene;


CBattleResultScene::CBattleResultScene()
    : m_pCamera(&CCameraManager::GetInstance())
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
    //地面
    m_pGround = std::make_unique<CGround>();
    //----------------------------
}

void CBattleResultScene::Releace()
{
    m_pCamera = nullptr;
}

void CBattleResultScene::LoadData()
{
    CSceneManager*     SceneMng     = &CSceneManager::GetInstance();
    CHeroManager*      HeroMng      = &CHeroManager::GetInstance();
    CEnemyHeroManager* EnemyHeroMng = &CEnemyHeroManager::GetInstance();
    CBattleManager*    BattleMng    = &CBattleManager::GetInstance();

    //----スタティックメッシュ----
    m_pGround->AttachMesh(CMeshManager::GetMesh(CMeshManager::Ground));//地面
    //----------------------------

    //----スキンメッシュ----
    switch (BattleMng->GetBattleResult())
    {
    case BattleMng->Win:    
        HeroMng->LoadMeshData();
        break;
    case BattleMng->Lose:
        EnemyHeroMng->LoadMeshData();
        break;
    default:
        break;
    }
    //---------------------
}

void CBattleResultScene::Initialize()
{
    CSceneManager* SceneMng         = &CSceneManager::GetInstance();
    CHeroManager* HeroMng           = &CHeroManager::GetInstance();
    CEnemyHeroManager* EnemyHeroMng = &CEnemyHeroManager::GetInstance();
    CBattleManager* BattleMng       = &CBattleManager::GetInstance();


    //カメラの初期位置
    switch (BattleMng->GetBattleResult())
    {
    case BattleMng->Win:
        m_pCamera->SetPos(WIN_CAM_POS);
        m_pCamera->SetLook(WIN_CAM_LOOK);
        HeroMng->Initialize();
        break;
    case BattleMng->Lose:
        m_pCamera->SetPos(LOSE_CAM_POS);
        m_pCamera->SetLook(LOSE_CAM_LOOK);
        EnemyHeroMng->Initialize();
        break;
    default:
        break;
    }
}

//更新関数
void CBattleResultScene::Update()
{
    CSceneManager* SceneMng   = &CSceneManager::GetInstance();
    CKeyManager* KeyMng       = &CKeyManager::GetInstance();
    CBattleManager* BattleMng = &CBattleManager::GetInstance();

    KeyMng->Update();

    //フェードイン処理
    if (!FadeIn()) { return; }

    //モード選択画面のBGM停止
    CSoundManager::GetInstance()->Stop(CSoundManager::BGM_Battle);

    switch (BattleMng->GetBattleResult())
    {
    case BattleMng->Win:
        //勝利時BGMの再生
        CSoundManager::GetInstance()->PlayLoop(CSoundManager::BGM_Win);
        CSoundManager::GetInstance()->Volume(CSoundManager::BGM_Win, 40);
        break;
    case BattleMng->Lose:
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
    CSceneManager* SceneMng         = &CSceneManager::GetInstance();
    CHeroManager* HeroMng           = &CHeroManager::GetInstance();
    CEnemyHeroManager* EnemyHeroMng = &CEnemyHeroManager::GetInstance();
    CBattleManager* BattleMng       = &CBattleManager::GetInstance();

    //カメラの動作
    m_pCamera->CameraUpdate();

    //地面の描画
    m_pGround->Draw();

    //空の描画
    DrawSky();

    //勝敗に応じて描画を変える
    switch (BattleMng->GetBattleResult())
    {
    case BattleMng->Win:
        HeroMng->MoveSelectAnim();
        HeroMng->Draw();
        break;
    case BattleMng->Lose:
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
    WriteText* Text           = WriteText::GetInstance();
    CSceneManager* SceneMng   = &CSceneManager::GetInstance();
    CBattleManager* BattleMng = &CBattleManager::GetInstance();

    switch (BattleMng->GetBattleResult())
    {
    case BattleMng->Win:
        Text->Draw_Text(L"WIN", WriteText::Win,RESULTTEXT_POS);
        break;
    case BattleMng->Lose:
        Text->Draw_Text(L"LOSE", WriteText::Lose,RESULTTEXT_POS);
        break;
    default:
        break;
    }  
}

