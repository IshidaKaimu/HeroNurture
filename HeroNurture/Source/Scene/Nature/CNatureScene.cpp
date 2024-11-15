#include "CNatureScene.h"
#include "ImGui\ImGuiManager\ImGuiManager.h"
#include "SkinMesh\SkinMeshManager\CSkinMeshManager.h"
#include "Camera\CameraManager\CCameraManager.h"
#include "SkinMeshObject\Hero\CHeroManager.h"
#include "StaticMesh\MeshManager\CMeshManager.h"

CNatureScene::CNatureScene()
    : m_pCamera( &CCameraManager::GetInstance() )
{
}

CNatureScene::~CNatureScene()
{
}

//構築関数
void CNatureScene::Create()
{

    //----インスタンス生成----
    //セットされたヒーローのクラスのインスタンス生成
    switch (CHeroManager::GetInstance().GetSelectHero())
    {
    case CHeroManager::Yui:
        //ユイ
        CHeroManager::GetInstance().SetHero(CHeroManager::Yui);
        break;
    case CHeroManager::Kaito:
        //カイト
        CHeroManager::GetInstance().SetHero(CHeroManager::Kaito);
        break;
    default:
        break;
    }
    
    //地面
    m_pGround = new CGround();

    //スカイボックス
    m_pSky = new CSky();


}

//破棄関数
void CNatureScene::Releace()
{
    //----破棄----
    m_pCamera = nullptr;
}


//データ読み込み関数
void CNatureScene::LoadData()
{  
    //セットされたヒーローのクラスのデータ読み込み
    CHeroManager::GetInstance().LoadData();

    //地面
    m_pGround->AttachMesh(CMeshManager::GetMesh(CMeshManager::Ground));

}

//初期化関数
void CNatureScene::Initialize()
{
    //カメラの初期化
    m_pCamera->Initialize();

    //セットされたヒーローのクラスの初期化
    CHeroManager::GetInstance().Initialize();

    //ライト情報
    m_Light.Position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

    m_Light.vDirection = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //ライト方向

}


//更新関数
void CNatureScene::Update()
{
    //フェードイン処理
    if (!FadeIn()) { return; }

    //セットされたヒーローのクラスの更新
    CHeroManager::GetInstance().Update();

    //セットされたヒーローのクラスのアニメーション
    CHeroManager::GetInstance().Animation();

}

//描画クラス
void CNatureScene::Draw()
{
    //カメラの更新処理
    m_pCamera->CameraUpdate();

    //セットされたヒーローのクラスの描画
    CHeroManager::GetInstance().Draw( m_Light );

    //地面クラスの描画
    m_pGround->Draw( m_Light );

}
