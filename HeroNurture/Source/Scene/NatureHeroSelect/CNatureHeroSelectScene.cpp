#include "CNatureHeroSelectScene.h"
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
#include <cmath>
#include <fstream>
#include <sstream>


CNatureHeroSelectScene::CNatureHeroSelectScene()
    : m_pCamera (  &CCameraManager::GetInstance() )
    , m_pSky    ()
    , m_pGround ()
    , m_UserName()
{
}

CNatureHeroSelectScene::~CNatureHeroSelectScene()
{
}

//構築関数
void CNatureHeroSelectScene::Create()
{
   //----ヒーロークラスのインスタンス生成----
   //ユイ
    m_pYui    = make_unique<CYui>();
   //カイト
   m_pKaito   = make_unique<CKaito>();

   //スカイボックスのインスタンス生成
   m_pSky    = make_unique<CSky>();

   //地面のインスタンス生成
   m_pGround = make_unique<CGround>();
}

//データ設定関数
void CNatureHeroSelectScene::LoadData()
{
    CMeshManager* MMng = CMeshManager::GetInstance();
    CSkinMeshManager* SKMng = CSkinMeshManager::GetInstance();
    CHeroManager* Hero = &CHeroManager::GetInstance();

    //----各ヒーロークラスのメッシュデータ設定----
    //ユイ
    m_pYui->AttachMesh(CSkinMeshManager::GetMesh(CSkinMeshManager::Yui));
    //カイト
    m_pKaito->AttachMesh(CSkinMeshManager::GetMesh(CSkinMeshManager::Kaito));

    //スカイボックスのメッシュデータ設定
    m_pSky->AttachMesh(CMeshManager::GetMesh(CMeshManager::Sky));

    //地面のメッシュ設定
    m_pGround->AttachMesh(CMeshManager::GetMesh(CMeshManager::Ground));
    
}

//破棄関数
void CNatureHeroSelectScene::Releace()
{
}

//初期化関数
void CNatureHeroSelectScene::Initialize()
{

#ifdef DEBUG
    CamPos  = D3DXVECTOR3(0.0f, 4.0f, -9.0f);
    CamLook = D3DXVECTOR3(0.0f, 4.0f, 3.0f);
#endif

    //カメラ位置の設定
    m_pCamera->SetPos(CAMPOS_NS);
    //カメラの注視点の設定
    m_pCamera->SetLook(CAMLOOK_NS);

    //ライト情報
    m_Light.Position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

    //方向選択
    m_Light.vDirection = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //ライト方向

    //----各ヒーロークラスの初期化----
    //ユイ
    m_pYui->Initialize();
    //カイト
    m_pKaito->Initialize();

}

//更新関数
void CNatureHeroSelectScene::Update()
{

    //フェードイン処理
    if (!FadeIn()) { return; }

    CKeyManager* KeyMng = CKeyManager::GetInstance();
    CHeroManager* HeroMng = &CHeroManager::GetInstance();

    //キーマネージャの動作処理
    CKeyManager::GetInstance()->Update();

    //カーソルの移動
    if (KeyMng->IsDown(VK_RIGHT))
    {
        //キー入力で選択を進める
        if (m_SelectNo < CHeroBase::enHeroList::Max-1) { m_SelectNo++; }
        else { m_SelectNo = 0; }
    }
    else if (KeyMng->IsDown(VK_LEFT))
    {
        if (m_SelectNo > 0) { m_SelectNo--; }
        else { m_SelectNo = 1; }
    }

#ifdef DEBUG 

    ImGui::InputFloat3(JAPANESE("カメラ座標"),CamPos);
    ImGui::InputFloat3(JAPANESE("注視点"), CamLook);
    CCameraManager::GetInstance().SetPos(CamPos);
    CCameraManager::GetInstance().SetLook(CamLook);
#endif

#ifdef _DEBUG
    ImGui::Begin(JAPANESE("選択状況"));
    if (m_SelectNo == 0) { ImGui::Text(JAPANESE("ユイ")); }
    if (m_SelectNo == 1) { ImGui::Text(JAPANESE("カイト")); }
    ImGui::End();
#endif

    //シーン遷移(仮)
    if (CKeyManager::GetInstance()->IsDown(VK_RETURN))
    {
        //オープニングシーンへ
        m_SceneTransitionFlg = true;
    }

    //フェードアウト処理
    if (m_SceneTransitionFlg && FadeOut())
    {
        switch (m_SelectNo)
        {
        case 0:
            HeroMng->SelectHero(CHeroManager::Yui);
            break;
        case 1:
            HeroMng->SelectHero(CHeroManager::Kaito);
            break;
        default:
            break;
        }
       CSceneManager::GetInstance()->LoadCreate(CSceneManager::Nature);
    }
}

//描画関数
void CNatureHeroSelectScene::Draw()
{  
    CHeroManager* Hero = &CHeroManager::GetInstance();

    //カメラの動作
    m_pCamera->CameraUpdate();
    
    //空の描画
    m_pSky->Draw();

    //地面の描画
    m_pGround->Draw();

    //選択中ヒーローの描画・アニメーション・カメラ配置
    switch (m_SelectNo)
    {
    case 0:
        //ユイ
        m_pYui->NatureHeroSelectAnimation();
        m_pYui->Draw();
        break;
    case 1:
        //カイト
        m_pKaito->NatureHeroSelectAnimation();
        m_pKaito->Draw();
        break;
    default:
        break;
    }

}

