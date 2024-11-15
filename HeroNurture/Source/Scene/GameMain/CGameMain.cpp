#include "CGameMain.h"
#include "Scene\CSceneManager.h"
#include "KeyManager\CKeyManager.h"
#include "StaticMesh\MeshManager\CMeshManager.h"
#include "SkinMesh\SkinMeshManager\CSkinMeshManager.h"
#include "Sound\CSoundManager.h"
#include "ImGui\ImGuiManager\ImGuiManager.h"
#include "Camera\CameraManager\CCameraManager.h"
#include "SkinMeshObject\Hero\CHeroManager.h"
#include <cmath>
#include <fstream>
#include <sstream>


CGameMain::CGameMain()
    : m_pCamera (  &CCameraManager::GetInstance() )
    , m_pSky    ()
    , m_pGround ()
    , m_UserName()
{
}

CGameMain::~CGameMain()
{
}


//構築関数
void CGameMain::Create()
{
    //スカイボックスのインスタンス生成
    m_pSky    = new CSky();
    //地面のインスタンス生成
    m_pGround = new CGround();
}

//データ設定関数
void CGameMain::LoadData()
{
    //メッシュマネージャーのインスタンスを変数に代入
    CMeshManager* MMng = CMeshManager::GetInstance();

    //スキンメッシュマネージャーのインスタンスを変数に代入
    CSkinMeshManager* SKMng = CSkinMeshManager::GetInstance();

    //スカイボックスのメッシュ設定
    m_pSky->AttachMesh(CMeshManager::GetMesh(CMeshManager::Sky));
    //地面のメッシュ設定
    m_pGround->AttachMesh(CMeshManager::GetMesh(CMeshManager::Ground));
    
}

//破棄関数
void CGameMain::Releace()
{
    SAFE_DELETE(m_pSky);
    SAFE_DELETE(m_pGround);
}

//初期化関数
void CGameMain::Initialize()
{

    //初期カメラ座標の設定
    m_pCamera->Initialize();

    //ライト情報
    m_Light.Position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

    m_Light.vDirection = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //ライト方向
}


//更新関数
void CGameMain::Update()
{

    //フェードイン処理
    if (!FadeIn()) { return; }

    CKeyManager::GetInstance()->Update();

#ifdef DEBUG 

    ImGui::InputFloat3(JAPANESE("カメラ座標"),CamPos);
    ImGui::InputFloat3(JAPANESE("注視点"), CamLook);
    //m_pCamera->SetPos(CamPos);
    m_pCamera->SetLook(CamLook);

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
        CHeroManager::GetInstance().SelectHero(CHeroManager::Kaito);
       CSceneManager::GetInstance()->LoadCreate(CSceneManager::Nature);
    }
}

//描画関数
void CGameMain::Draw()
{  
    //カメラの動作
    m_pCamera->CameraUpdate();
    
    //空の描画
    m_pSky->Draw( m_Light );

    //地面の描画
    m_pGround->Draw( m_Light );
}

