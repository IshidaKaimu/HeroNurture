#include "CTitleScene.h"
#include "Scene\CSceneManager.h"
#include "KeyManager\CKeyManager.h"
#include "StaticMesh\MeshManager\CMeshManager.h"
#include "Sound\CSoundManager.h"
#include "SkinMeshObject\Hero\CHeroManager.h"
#include "ImGui\ImGuiManager\ImGuiManager.h"
#include "Json\CJson.h"
#include "Utility\CUtility.h"
#include "Sprite2D\UIManager\CUIManager.h" 
#include <cmath>

//定数の名前空間
using namespace Constant_TitleScene;

CTitleScene::CTitleScene()
    : m_pCamera ( &CCameraManager::GetInstance() )
    , m_pYui    ()
    , m_pKaito  ()
    , m_pSky    ()
    , m_pGround ()
    , m_HeroNo  ()
{
    //ライト情報
    m_Light.vDirection = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //ライト方向
}

CTitleScene::~CTitleScene()
{
}

void CTitleScene::Create()
{
    //----スタティックメッシュ----
    //スカイボックス
    m_pSky = std::make_unique<CSky>();
    //地面
    m_pGround = std::make_unique<CGround>();
    
    //----スキンメッシュ----
    //ユイ
    m_pYui = std::make_unique<CYui>();
    //カイト
    m_pKaito = std::make_unique<CKaito>();

    //----UI----
    //タイトル背景
    m_pTitleBack = std::make_unique<CUIObject>();
}

void CTitleScene::Releace()
{
    m_pCamera = nullptr;
}

void CTitleScene::LoadData()
{
    CMeshManager* MMng = CMeshManager::GetInstance();
    //----スタティックメッシュ----
    m_pSky->AttachMesh(CMeshManager::GetMesh(CMeshManager::Sky));      //空
    m_pGround->AttachMesh(CMeshManager::GetMesh(CMeshManager::Ground));//地面

    //----タイトル画面に表示するヒーローのメッシュ設定----
    m_pYui->LoadMeshData();  //ユイ
    m_pKaito->LoadMeshData();//カイト

    //----UI----
    m_pTitleBack->AttachSprite(CUIManager::GetSprite(CUIManager::TitleBack));
}

void CTitleScene::Initialize()
{
    //カメラの初期位置
    m_pCamera->SetPos(CAM_POS);
    m_pCamera->SetLook(CAM_LOOK);

    //どちらのヒーローを表示するか、乱数で設定
    m_HeroNo = CUtility::GetInstance().GenerateRandomValue(0,1);

    //設定されたヒーローの初期化
    switch (m_HeroNo)
    {
    case 0:
        m_pYui->Initialize();
        m_pYui->SetPosition(YUI_POS);
        m_pYui->SetRotation(YUI_ROT);
        break;
    case 1:
        m_pKaito->Initialize();
        m_pKaito->SetPosition(KAITO_POS);
        m_pKaito->SetRotation(KAITO_ROT);
        break;
    default:
        break;
    }
}

//更新関数
void CTitleScene::Update()
{   
    CSceneManager* SceneMng = CSceneManager::GetInstance();
    CKeyManager* KeyMng = &CKeyManager::GetInstance();

    KeyMng->Update();

    //タイトルBGMの再生
    CSoundManager::GetInstance()->PlayLoop(CSoundManager::BGM_Title);
    CSoundManager::GetInstance()->Volume(CSoundManager::BGM_Title, 40);

    //フェードイン処理
    if (!FadeIn()) { return; }

    //シーン遷移(仮)
    if (KeyMng->IsDown(VK_RETURN))
    {
        //スタートSEの再生
        CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Start);
        CSoundManager::GetInstance()->Volume(CSoundManager::SE_Start,40);

        //オープニングシーンへ
        m_SceneTransitionFlg = true;
    }
    //フェードアウト処理
    if (m_SceneTransitionFlg && FadeOut()) 
    {
        SceneMng->LoadCreate(CSceneManager::Login);
    }

    //シーン遷移(仮)
    if (KeyMng->IsDown(VK_RETURN))
    {
        //スタートSEの再生
        CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Start);
        CSoundManager::GetInstance()->Volume(CSoundManager::SE_Start,40);

        //オープニングシーンへ
        m_SceneTransitionFlg = true;
    }
    //フェードアウト処理
    if (m_SceneTransitionFlg && FadeOut()) 
    {
        SceneMng->LoadCreate(CSceneManager::Login);
    }

    #ifdef DEBUG
        //デバッグ処理
        Debug();
    #endif
}

void CTitleScene::Draw()
{
    //カメラの動作
    m_pCamera->CameraUpdate();

    //スカイボックスの描画
    m_pSky->Draw();

    //地面の描画
    m_pGround->Draw();

    //表示を切り替える
    switch (m_HeroNo)
    {
    case 0:
        m_pYui->MoveSelectAnim();
        m_pYui->Draw();
        break;
    case 1:
        m_pKaito->MoveSelectAnim();
        m_pKaito->Draw();
        break;
    default:
        break;
    }

    //UI
    DrawUI();
}

void CTitleScene::Debug()
{
    ImGui::Begin(JAPANESE("カメラ"));
    ImGui::InputFloat3(JAPANESE("カメラ座標"), m_CamPos);
    ImGui::InputFloat3(JAPANESE("注視点"), m_CamLook);
    ImGui::InputFloat3(JAPANESE("カイト座標"), m_KaitoPos);
    ImGui::InputFloat3(JAPANESE("ユイ座標"),   m_YuiPos);
    ImGui::InputFloat3(JAPANESE("カイト回転"), m_KaitoRot);
    ImGui::InputFloat3(JAPANESE("ユイ回転"), m_YuiRot);
    //CCameraManager::GetInstance().SetPos(m_CamPos);
    //CCameraManager::GetInstance().SetLook(m_CamLook);
    m_pKaito->SetPosition(m_KaitoPos);
    m_pYui->SetPosition(m_YuiPos);
    m_pKaito->SetRotation(m_KaitoRot);
    m_pYui->SetRotation(m_YuiRot);
    ImGui::End();

}

//タイトル画面の描画
void CTitleScene::DrawUI()
{
    WriteText* Text = WriteText::GetInstance();

    //タイトル
    Text->Draw_Text(L"HeroNature", WriteText::B_Big, D3DXVECTOR2(TITLE_POS)); 
    //「アカウント作成」テキスト
    Text->Draw_Text(L"アカウント作成", WriteText::Select, D3DXVECTOR2(SELECT_POS));
    //「ログイン」テキスト
    Text->Draw_Text(L"ログイン", WriteText::Select, D3DXVECTOR2(SELECT_POS.x,SELECT_POS.y + SELECT_INTERVAL));
    //「ゲーム終了」テキスト
    Text->Draw_Text(L"ゲーム終了", WriteText::Select, D3DXVECTOR2(SELECT_POS.x,SELECT_POS.y + SELECT_INTERVAL*2));
}
