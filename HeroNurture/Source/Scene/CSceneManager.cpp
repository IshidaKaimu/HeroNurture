#include "CSceneManager.h"
#include "Scene\Login\CLoginScene.h"
#include "Scene\Nature\CNatureScene.h"
#include "Scene\HeroSelect\CHeroSelect.h"
#include "Scene\Traning\CTraningScene.h"
#include "Scene\TraningResult\CTraningResultScene.h"
#include "ImGui\ImGuiManager\ImGuiManager.h"
CSceneManager::CSceneManager()
    : m_Scene       ()
    , m_hWnd        ()
    , m_pDx9        ( nullptr )
    , m_pDx11       ( nullptr )
    , m_GageWidth   ( 1.0f )
{
    m_Scene = std::make_unique<CLoginScene>();   //make_unique:インスタンスを生成して、使わなくなったら勝手に破棄してくれる
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

//破棄関数
void CSceneManager::Release()
{
    m_Scene->Releace();
}

//初期化関数
void CSceneManager::Initialize()
{
    m_Scene->Initialize();
}

//更新関数
void CSceneManager::Update()
{        
    ImGui::Begin(JAPANESE("シーン"));
    if (ImGui::Button(JAPANESE("ログイン"))) { LoadCreate(enSceneList::Login); }
    if (ImGui::Button(JAPANESE("ヒーロー選択"))) { LoadCreate(enSceneList::HeroSelect); }
    if (ImGui::Button(JAPANESE("育成"))) { LoadCreate(enSceneList::Nature); }
    if (ImGui::Button(JAPANESE("修行"))) { LoadCreate(enSceneList::Training); }
    if (ImGui::Button(JAPANESE("育成結果"))) { LoadCreate(enSceneList::TrainingResult); }
    ImGui::End();
    m_Scene->Update();  //入ってるシーンの動作を行う   
}

//描画関数
void CSceneManager::Draw()
{
    m_Scene->Draw();       //入ってるシーンの描画を行う

    m_pDx11->SetDepth(false);
    CSceneBase::Draw();  //シーンベース
    m_pDx11->SetDepth(true);
}

//構築・データ読み込み関数
void CSceneManager::LoadCreate(enSceneList List)
{
    //一度破棄
    m_Scene.release();
    //シーンマネージャーでの構築
    m_Scene = Create(List);
    //各シーンの構築
    m_Scene->Create();
    //各シーンのデータ読み込み
    m_Scene->LoadData();
    //各シーンの初期化
    m_Scene->Initialize();

}

//構築関数
std::unique_ptr<CSceneBase> CSceneManager::Create(enSceneList List)
{
    //現在のシーンのインスタンスを返す
    switch (List)
    {
    case CSceneManager::Login:          return std::make_unique<CLoginScene>();
    case CSceneManager::HeroSelect:     return std::make_unique<CHeroSelect>();
    case CSceneManager::Nature:         return std::make_unique<CNatureScene>();
    case CSceneManager::Training:       return std::make_unique<CTraningScene>();
    case CSceneManager::TrainingResult: return std::make_unique<CTraningResultScene>();
    case CSceneManager::Max_S:          return nullptr;
    case CSceneManager::none:           return nullptr;
    default:                            return nullptr;
    }
}




