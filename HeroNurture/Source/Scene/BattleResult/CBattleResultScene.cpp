#include "CBattleResultScene.h"
#include "Scene\CSceneManager.h"
#include "KeyManager\CKeyManager.h"
#include "StaticMesh\MeshManager\CMeshManager.h"
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
    CMeshManager* MMng = CMeshManager::GetInstance();
    //----スタティックメッシュ----
    m_pSky->AttachMesh(CMeshManager::GetMesh(CMeshManager::Sky));      //空
    m_pGround->AttachMesh(CMeshManager::GetMesh(CMeshManager::Ground));//地面
}

void CBattleResultScene::Initialize()
{
    //カメラの初期位置
    m_pCamera->SetPos(5.0f, 4.0f, -5.0f);
    m_pCamera->SetLook(0.0f, 4.0f, 0.0f);
}

//更新関数
void CBattleResultScene::Update()
{
    CSceneManager* SceneMng = CSceneManager::GetInstance();
    CKeyManager* KeyMng = CKeyManager::GetInstance();

    KeyMng->Update();

    //フェードイン処理
    if (!FadeIn()) { return; }

    //シーン遷移(仮)
    if (KeyMng->IsDown(VK_RETURN))
    {
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
    //カメラの動作
    m_pCamera->CameraUpdate();

    //スカイボックスの描画
    m_pSky->Draw();

    //地面の描画
    m_pGround->Draw();

    //UI
    DrawUI();
}

//タイトル画面の描画
void CBattleResultScene::DrawUI()
{
    WriteText* Text = WriteText::GetInstance();
    CSceneManager* SceneMng = CSceneManager::GetInstance();

    switch (SceneMng->GetBattleResult())
    {
    case CSceneManager::Win:
        Text->Draw_Text(L"WIN", WriteText::Success, RESULTTEXT_POS);
        break;
    case CSceneManager::Lose:
        Text->Draw_Text(L"LOSE", WriteText::Failure, RESULTTEXT_POS);
        break;
    default:
        break;
    }  
}

