#include "CSceneManager.h"
#include "Scene\Title\CTitleScene.h"
#include "CreateAcount\CCreateAcountScene.h"
#include "Scene\Login\CLoginScene.h"
#include "Scene\Nurture\CNurtureScene.h"
#include "Scene\ModeSelect\CModeSelectScene.h"
#include "Scene\NurtureHeroSelect\CNurtureHeroSelectScene.h"
#include "Scene\Traning\CTraningScene.h"
#include "Scene\NurtureResult\CNurtureResultScene.h"
#include "Scene\BattleHeroSelect\CBattleHeroSelectScene.h"
#include "Scene\Battle\CBattleScene.h"
#include "Scene\Appearance\Yui\CYuiAppearanceScene.h"
#include "Scene\Appearance\Kaito\CKaitoAppearanceScene.h"
#include "Scene\BattleResult\CBattleResultScene.h"
#include "ImGui\ImGuiManager\ImGuiManager.h"

CSceneManager::CSceneManager()
    : m_pScene       ()
    , m_hWnd        ()
    , m_pDx9        ( nullptr )
    , m_pDx11       ( nullptr )
    , m_UserName    ()
{
    m_pScene = std::make_unique<CTitleScene>();   //make_unique:インスタンスを生成して、使わなくなったら勝手に破棄してくれる
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

    m_pScene->Create();
    m_pScene->LoadData();
}

//破棄関数
void CSceneManager::Release()
{
    m_pScene->Releace();
}

//初期化関数
void CSceneManager::Initialize()
{
    m_pScene->Initialize();
}

//更新関数
void CSceneManager::Update()
{        
#if DEBUG
    ImGui::Begin(JAPANESE("シーン"));
    if (ImGui::Button(JAPANESE("タイトル")))           { LoadCreate(enSceneList::Title); }
    if (ImGui::Button(JAPANESE("アカウント作成")))     { LoadCreate(enSceneList::CreateAcount); }
    if (ImGui::Button(JAPANESE("ログイン")))           { LoadCreate(enSceneList::Login); }
    if (ImGui::Button(JAPANESE("モード選択")))         { LoadCreate(enSceneList::ModeSelect); }
    if (ImGui::Button(JAPANESE("ヒーロー選択")))       { LoadCreate(enSceneList::NurtureHeroSelect); }
    if (ImGui::Button(JAPANESE("育成")))               { LoadCreate(enSceneList::Nurture); }
    if (ImGui::Button(JAPANESE("修行")))               { LoadCreate(enSceneList::Training); }
    if (ImGui::Button(JAPANESE("育成結果")))           { LoadCreate(enSceneList::NurtureResult); }
    if (ImGui::Button(JAPANESE("バトルヒーロー選択"))) { LoadCreate(enSceneList::BattleHeroSelect); }
    if (ImGui::Button(JAPANESE("ユイの登場シーン")))   { LoadCreate(enSceneList::YuiAppearance); }
    if (ImGui::Button(JAPANESE("カイトの登場シーン"))) { LoadCreate(enSceneList::KaitoAppearance); }
    if (ImGui::Button(JAPANESE("バトル")))             { LoadCreate(enSceneList::Battle); }
    if (ImGui::Button(JAPANESE("バトル結果")))         { LoadCreate(enSceneList::BattleResult); }
    ImGui::End();
#endif
    m_pScene->Update();  //入ってるシーンの動作を行う   
}

//描画関数
void CSceneManager::Draw()
{
    m_pScene->Draw();       //入ってるシーンの描画を行う

    m_pDx11->SetDepth(false);
    CSceneBase::Draw();    //シーンベース
    m_pDx11->SetDepth(true);
}

//構築・データ読み込み関数
void CSceneManager::LoadCreate(enSceneList List)
{
    //一度破棄
    m_pScene.release();
    //シーンマネージャーでの構築
    m_pScene = Create(List);
    //各シーンの構築
    m_pScene->Create();
    //各シーンのデータ読み込み
    m_pScene->LoadData();
    //各シーンの初期化
    m_pScene->Initialize();
}

//構築関数
std::unique_ptr<CSceneBase> CSceneManager::Create(enSceneList List)
{
    //現在のシーンのインスタンスを返す
    switch (List)
    {
    case CSceneManager::Title:            return std::make_unique<CTitleScene>();
    case CSceneManager::CreateAcount:     return std::make_unique<CCreateAcountScene>();
    case CSceneManager::Login:            return std::make_unique<CLoginScene>();
    case CSceneManager::ModeSelect:       return std::make_unique<CModeSelectScene>();
    case CSceneManager::NurtureHeroSelect: return std::make_unique<CNurtureHeroSelectScene>();
    case CSceneManager::Nurture:           return std::make_unique<CNurtureScene>();
    case CSceneManager::Training:         return std::make_unique<CTraningScene>();
    case CSceneManager::NurtureResult:     return std::make_unique<CNurtureResultScene>();
    case CSceneManager::BattleHeroSelect: return std::make_unique<CBattleHeroSelectScene>();
    case CSceneManager::YuiAppearance:    return std::make_unique<CYuiAppearanceScene>();
    case CSceneManager::KaitoAppearance:  return std::make_unique<CKaitoAppearanceScene>();
    case CSceneManager::Battle:           return std::make_unique<CBattleScene>();
    case CSceneManager::BattleResult:     return std::make_unique<CBattleResultScene>();
    case CSceneManager::Max_S:            return nullptr;
    case CSceneManager::none:             return nullptr;
    default:                              return nullptr;
    }
}




