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
#include "Light\LightManager\CLightManager.h"
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

    //---------------------------

    
    //----スキンメッシュ----
    
    //ユイ
    m_pYui = std::make_unique<CYui>();
   
    //カイト
    m_pKaito = std::make_unique<CKaito>();
    
    //----------------------

    //----UI----
   
    //選択矢印
    m_pSelectArrow = std::make_unique<CUIObject>();

    //----------
}

void CTitleScene::Releace()
{
    m_pCamera = nullptr;
}

void CTitleScene::LoadData()
{
    CMeshManager* MeshMng = CMeshManager::GetInstance();
    CUIManager* UiMng = &CUIManager::GetInstance();
    //----スタティックメッシュ----
  
    //地面
    m_pGround->AttachMesh(MeshMng->GetMesh(CMeshManager::Ground));
   
    //----------------------------

    //----タイトル画面に表示するヒーローのメッシュ設定----
    
     //ユイ
    m_pYui->LoadMeshData();  

    //カイト
    m_pKaito->LoadMeshData();    
    
    //----------------------------------------------------

    //----UI----

    //選択肢矢印
    m_pSelectArrow->AttachSprite(UiMng->GetSprite(CUIManager::SelectArrow)); 

    //----------
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

    //選択肢矢印の初期設定
    m_pSelectArrow->SetPosition(SELECTARROW_POS);                       //座標
    m_pSelectArrow->SetScale(SELECTARROW_SCALE);                        //拡縮
    m_pSelectArrow->SetDisplay(SELECTARROW_DISP.x, SELECTARROW_DISP.y); //幅
}

//更新関数
void CTitleScene::Update()
{   
    CSceneManager* SceneMng = &CSceneManager::GetInstance();
    CKeyManager* KeyMng     = &CKeyManager::GetInstance();

    KeyMng->Update();

    //モード選択BGMを停止
    CSoundManager::GetInstance()->Stop(CSoundManager::BGM_ModeSelect);

    //タイトルBGMの再生
    CSoundManager::GetInstance()->PlayLoop(CSoundManager::BGM_Title);
    CSoundManager::GetInstance()->Volume(CSoundManager::BGM_Title, 40);

    //フェードイン処理
    if (!FadeIn()) { return; }

    //選択矢印の動き
    MoveArrow();

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
        switch (m_SelectNo)
        {
        case 0: SceneMng->LoadCreate(CSceneManager::CreateAcount); break;
        case 1: SceneMng->LoadCreate(CSceneManager::Login);        break;
        case 2: DestroyWindow(SceneMng->GetWnd());                 break;
        default:                                                   break;
        }
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

    //地面の描画
    m_pGround->Draw();


    //各ヒーローの描画,アニメーション
    switch (m_HeroNo)
    {
    case 0:
        //ユイ
        m_pYui->MoveSelectAnim();
        m_pYui->Draw();
        break;
    case 1:
        //カイト
        m_pKaito->MoveSelectAnim();
        m_pKaito->Draw();
        break;
    }

    //空の描画
    DrawSky();

    //UI
    DrawUI();

}

void CTitleScene::Debug()
{
#ifdef DEBUG
    ImGui::Begin(JAPANESE("カメラ"));
    ImGui::InputFloat3(JAPANESE("カメラ座標"), m_CamPos);
    ImGui::InputFloat3(JAPANESE("注視点"), m_CamLook);
    ImGui::InputFloat3(JAPANESE("カイト座標"), m_KaitoPos);
    ImGui::InputFloat3(JAPANESE("ユイ座標"), m_YuiPos);
    ImGui::InputFloat3(JAPANESE("カイト回転"), m_KaitoRot);
    ImGui::InputFloat3(JAPANESE("ユイ回転"), m_YuiRot);
    //CCameraManager::GetInstance().SetPos(m_CamPos);
    //CCameraManager::GetInstance().SetLook(m_CamLook);
    m_pKaito->SetPosition(m_KaitoPos);
    m_pYui->SetPosition(m_YuiPos);
    m_pKaito->SetRotation(m_KaitoRot);
    m_pYui->SetRotation(m_YuiRot);
    ImGui::End();

#endif // DEBUG
}

//タイトル画面の描画
void CTitleScene::DrawUI()
{
    WriteText* Text = WriteText::GetInstance();

    //選択矢印
    m_pSelectArrow->SetPosition(SELECTARROW_POS.x + m_MoveArrow, SELECTARROW_POS.y + (SELECT_INTERVAL * m_SelectNo), SELECTARROW_POS.z);

    //選択矢印の描画
    m_pSelectArrow->Draw();

    //タイトル
    Text->Draw_Text(L"HeroNurture", WriteText::B_Big, D3DXVECTOR2(TITLE_POS)); 
    //「アカウント作成」テキスト
    Text->Draw_Text(L"アカウント作成", WriteText::Select, D3DXVECTOR2(SELECT_POS));
    //「ログイン」テキスト
    Text->Draw_Text(L"ログイン", WriteText::Select, D3DXVECTOR2(SELECT_POS.x,SELECT_POS.y + SELECT_INTERVAL));
    //「ゲーム終了」テキスト
    Text->Draw_Text(L"ゲーム終了", WriteText::Select, D3DXVECTOR2(SELECT_POS.x,SELECT_POS.y + SELECT_INTERVAL*2));
}

//矢印の動き
void CTitleScene::MoveArrow()
{
    CKeyManager* KeyMng = &CKeyManager::GetInstance();
    //選択肢移動
    if (KeyMng->IsDown('S'))
    {

        if (m_SelectNo < 2)
        {
            //選択SEの再生
            CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Select);
            CSoundManager::GetInstance()->Volume(CSoundManager::SE_Select, 40);

            m_SelectNo++;
        }
        else
        {
            m_SelectNo = 2;
        }
    }

    if (KeyMng->IsDown('W'))
    {

        if (m_SelectNo > 0)
        {
            //選択SEの再生
            CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Select);
            CSoundManager::GetInstance()->Volume(CSoundManager::SE_Select, 40);

            m_SelectNo--;
        }
        else
        {
            m_SelectNo = 0;
        }
    }


    if (m_MoveArrow <= SELECTARROW_RANGE && !m_SwitchArrowFlag)
    {
        m_MoveArrow += 0.1f;
    }
    else
    {
        m_SwitchArrowFlag = true;
    }

    if (m_SwitchArrowFlag)
    {
        if (m_MoveArrow >= 0.0f)
        {
            m_MoveArrow -= 0.1f;
        }
        else
        {
            m_SwitchArrowFlag = false;
        }
    }

}
