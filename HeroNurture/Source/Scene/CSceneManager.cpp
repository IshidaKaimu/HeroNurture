#include "CSceneManager.h"
#include "Scene/Title/CSceneSelect.h"
#include "Scene/GameMain/CGameMain.h"
#include "ImGui/ImGuiManager/ImGuiManager.h"
CSceneManager::CSceneManager()
    : m_Scene       ()
    , m_hWnd        ()
    , m_pDx9        ( nullptr )
    , m_pDx11       ( nullptr )
{
    m_Scene = std::make_unique<CSceneSelect>();   //make_unique:インスタンスを生成して、使わなくなったら勝手に破棄してくれる
}


CSceneManager::~CSceneManager()
{
}

//構築、データ読み込み
void CSceneManager::Create(CDirectX9& pDx9, CDirectX11& pDx11, HWND hwnd)
{
    m_pDx9 = &pDx9;
    m_pDx11 = &pDx11;
    m_hWnd = hwnd;
    
    //テキスト表示の準備
    WriteText::GetInstance()->SetDx11(*m_pDx11);
    WriteText::GetInstance()->Init();

    m_Scene->Create();
    m_Scene->LoadData();
}

void CSceneManager::Update()
{        
    ImGui::Begin(JAPANESE("シーン"));
    if (ImGui::Button(JAPANESE("選択"))) { LoadCreate(enSceneList::SceneSelect); }
    if (ImGui::Button(JAPANESE("メイン"))) { LoadCreate(enSceneList::GameMain); }
    ImGui::End();
    m_Scene->Update();  //入ってるシーンの動作を行う   
}

void CSceneManager::Draw()
{
    m_Scene->Draw();       //入ってるシーンの描画を行う

    m_pDx11->SetDepth(false);
    CSceneBase::Draw();  //シーンベース
    m_pDx11->SetDepth(true);
}

void CSceneManager::LoadCreate(enSceneList List)
{
    //一度破棄
    m_Scene.release();

    m_Scene = Create(List);
    //各シーンの構築
    m_Scene->Create();
    //各シーンのデータ読み込み
    m_Scene->LoadData();
    //各シーンの初期化
    m_Scene->Initialize();

}

void CSceneManager::LoadScene()
{
    m_Scene->LoadScene();
}

void CSceneManager::Release()
{
    m_Scene->Releace();
}

void CSceneManager::Initialize()
{
    m_Scene->Initialize();
}

std::unique_ptr<CSceneBase> CSceneManager::Create(enSceneList List)
{
    //現在のシーンのインスタンスを返す
    switch (List)
    {
    case CSceneManager::SceneSelect:    return std::make_unique<CSceneSelect>();
    case CSceneManager::GameMain:       return std::make_unique<CGameMain>();
    case CSceneManager::Max:            return nullptr;
    case CSceneManager::none:           return nullptr;
    default:                            return nullptr;
    }
}




