#include "CNurtureHeroSelectScene.h"
#include "Scene\CSceneManager.h"
#include "KeyManager\CKeyManager.h"
#include "StaticMesh\MeshManager\CMeshManager.h"
#include "SkinMesh\SkinMeshManager\CSkinMeshManager.h"
#include "Sound\CSoundManager.h"
#include "ImGui\ImGuiManager\ImGuiManager.h"
#include "Camera\CameraManager\CCameraManager.h"
#include "SkinMeshObject\Hero\CHeroManager.h"
#include "SkinMeshObject\Hero\Yui\CYui.h"
#include "SkinMeshObject\Hero\Kaito\CKaito.h"
#include "Sprite2D\UIManager\CUIManager.h"
#include <cmath>
#include <fstream>
#include <sstream>

//定数の名前空間
using namespace Constant_NurtureHeroSelectScene;

CNurtureHeroSelectScene::CNurtureHeroSelectScene()
    : m_pCamera    (&CCameraManager::GetInstance())
    , m_pYui       ()
    , m_pKaito     ()
    , m_UserName   ()
    , m_pLeftArrow ()
    , m_pRightArrow()
{
}

CNurtureHeroSelectScene::~CNurtureHeroSelectScene()
{
}

//構築関数
void CNurtureHeroSelectScene::Create()
{
   //----スキンメッシュ----
    m_pYui    = make_unique<CYui>();  //ユイ
   m_pKaito   = make_unique<CKaito>();//カイト

   //----UI----
   m_pLeftArrow  = make_unique<CUIObject>(); //左矢印
   m_pRightArrow = make_unique<CUIObject>(); //右矢印
}

//データ設定関数
void CNurtureHeroSelectScene::LoadData()
{
    //----各ヒーロークラスのメッシュデータ設定----
    m_pYui->AttachMesh(CSkinMeshManager::GetMesh(CSkinMeshManager::Yui));    //ユイ
    m_pKaito->AttachMesh(CSkinMeshManager::GetMesh(CSkinMeshManager::Kaito));//カイト

    //----UI----
    m_pLeftArrow->AttachSprite(CUIManager::GetSprite(CUIManager::Arrow)); //矢印左
    m_pRightArrow->AttachSprite(CUIManager::GetSprite(CUIManager::Arrow));//矢印右
}

//破棄関数
void CNurtureHeroSelectScene::Releace()
{
}

//初期化関数
void CNurtureHeroSelectScene::Initialize()
{

#ifdef DEBUG
    CamPos  = D3DXVECTOR3(0.0f, 4.0f, -9.0f);
    CamLook = D3DXVECTOR3(0.0f, 4.0f, 3.0f);
#endif

    //カメラ位置の設定
    m_pCamera->SetPos(CAMPOS_NS);
    //カメラの注視点の設定
    m_pCamera->SetLook(CAMLOOK_NS);

    //----各ヒーロークラスの初期化----
    //ユイ
    m_pYui->Initialize();
    //カイト
    m_pKaito->Initialize();

}

//更新関数
void CNurtureHeroSelectScene::Update()
{
    CSceneManager* SceneMng = &CSceneManager::GetInstance();

    //フェードイン処理
    if (!FadeIn()) { return; }

    //モード選択画面のBGM停止
    CSoundManager::GetInstance()->Stop(CSoundManager::BGM_ModeSelect);

    //育成ヒーローBGMの再生
    CSoundManager::GetInstance()->PlayLoop(CSoundManager::BGM_NurtureHeroSelect);
    CSoundManager::GetInstance()->Volume(CSoundManager::BGM_NurtureHeroSelect, 40);

    CKeyManager* KeyMng = &CKeyManager::GetInstance();
    CHeroManager* HeroMng = &CHeroManager::GetInstance();

    //キーマネージャの動作処理
    CKeyManager::GetInstance().Update();

    //カーソルの移動
    if (KeyMng->IsDown(VK_RIGHT))
    {
        //選択SEの再生
        CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Select);
        CSoundManager::GetInstance()->Volume(CSoundManager::SE_Select, 40);

        //キー入力で選択を進める
        if (m_SelectNo < CHeroBase::enHeroList::Max-1) { m_SelectNo++; }
        else { m_SelectNo = 0; }
    }
    else if (KeyMng->IsDown(VK_LEFT))
    {
        //選択SEの再生
        CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Select);
        CSoundManager::GetInstance()->Volume(CSoundManager::SE_Select, 40);

        if (m_SelectNo > 0) { m_SelectNo--; }
        else { m_SelectNo = 1; }
    }

#ifdef DEBUG 

    ImGui::InputFloat3(JAPANESE("カメラ座標"),CamPos);
    ImGui::InputFloat3(JAPANESE("注視点"), CamLook);
    CCameraManager::GetInstance().SetPos(CamPos);
    CCameraManager::GetInstance().SetLook(CamLook);
#endif

#ifdef DEBUG
    ImGui::Begin(JAPANESE("選択状況"));
    if (m_SelectNo == 0) { ImGui::Text(JAPANESE("ユイ")); }
    if (m_SelectNo == 1) { ImGui::Text(JAPANESE("カイト")); }
    ImGui::End();
#endif

    //シーン遷移
    if (CKeyManager::GetInstance().IsDown(VK_RETURN))
    {
        //決定SEの再生
        CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Enter);
        CSoundManager::GetInstance()->Volume(CSoundManager::SE_Enter, 40);

        //オープニングシーンへ
        m_SceneTransitionFlg = true;
    }

    //前のシーンに戻す
    if (CKeyManager::GetInstance().IsDown(VK_ESCAPE))
    {
        //決定SEの再生
        CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Enter);
        CSoundManager::GetInstance()->Volume(CSoundManager::SE_Enter, 40);

        //選択番号を2にする
        m_SelectNo = 2;

        //モード選択シーンへ
        m_SceneTransitionFlg = true;
    }

    //フェードアウト処理
    if (m_SceneTransitionFlg && FadeOut())
    {
        switch (m_SelectNo)
        {
        case Yui:
            HeroMng->SelectHero(CHeroManager::Yui);
            break;
        case Kaito:
            HeroMng->SelectHero(CHeroManager::Kaito);
            break;
        default:
            break;
        }
        //選択番号が2以外なら
        if (m_SelectNo != 2) 
        {
            SceneMng->LoadCreate(CSceneManager::Nurture);
        }
        else
        {
            //前のシーンへ
            SceneMng->LoadCreate(CSceneManager::ModeSelect);
        }
    }
}

//描画関数
void CNurtureHeroSelectScene::Draw()
{  
    CHeroManager* Hero = &CHeroManager::GetInstance();
    CSceneManager* SceneMng = &CSceneManager::GetInstance();
    WriteText* Text = WriteText::GetInstance();

    //カメラの動作
    m_pCamera->CameraUpdate();

    SceneMng->GetDx11()->SetDepth(false);
    DrawBasicBackGround();
    SceneMng->GetDx11()->SetDepth(true);

    //選択中ヒーローの描画・アニメーション・カメラ配置
    switch (m_SelectNo)
    {
    case 0:
        //ユイ
        m_pYui->NurtureHeroSelectAnimation();
        m_pYui->Draw();
        Text->Draw_Text(L"YUI", WriteText::B_Big, HERONAME_POS_NS);
        break;
    case 1:
        //カイト
        m_pKaito->NurtureHeroSelectAnimation();
        m_pKaito->Draw();
        Text->Draw_Text(L"KAITO", WriteText::D_Big, HERONAME_POS_NS);
        break;
    default:
        break;
    }

    //シーン名,指示の描画
    Text->Draw_Text(L"Nurture Hero Select", WriteText::Normal, SCENENAME_POS_NS);    

    //操作方法指示バーの描画
    DrawControlBar(true);

    //矢印の描画
    DrawArrow();
}

//矢印の描画
void CNurtureHeroSelectScene::DrawArrow()
{
    //設定
    //左
    m_pLeftArrow->SetPosition(ARROW_LEFT_POS_NS);
    m_pLeftArrow->SetScale(ARROW_SCALE);
    m_pLeftArrow->SetRotation(ARROW_LEFT_ROTATE);
    m_pLeftArrow->SetDisplay(ARROW_DISP.x, ARROW_DISP.y);
    m_pLeftArrow->SetAlpha(ARROW_ALPHA);
    //右
    m_pRightArrow->SetPosition(ARROW_RIGHT_POS_NS);
    m_pRightArrow->SetScale(ARROW_SCALE);
    m_pRightArrow->SetDisplay(ARROW_DISP.x, ARROW_DISP.y);
    m_pRightArrow->SetAlpha(ARROW_ALPHA);

    //描画
    m_pLeftArrow->Draw();
    m_pRightArrow->Draw();
}

