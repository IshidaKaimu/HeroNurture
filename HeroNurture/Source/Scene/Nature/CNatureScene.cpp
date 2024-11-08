#include "CNatureScene.h"
#include "ImGui\ImGuiManager\ImGuiManager.h"
#include "SkinMesh\SkinMeshManager\CSkinMeshManager.h"
#include "Camera\CameraManager\CCameraManager.h"

CNatureScene::CNatureScene()
    : m_pHero()
    , m_pCamera( &CCameraManager::GetInstance() )
{
}

CNatureScene::~CNatureScene()
{
}

//構築関数
void CNatureScene::Create()
{
    //----インスタンス生成----
    m_pHero = std::make_unique<CHeroBase>();
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
}

//初期化関数
void CNatureScene::Initialize()
{
}


//更新関数
void CNatureScene::Update()
{
}

//描画クラス
void CNatureScene::Draw()
{
    //----オブジェクトの描画----
    
}
