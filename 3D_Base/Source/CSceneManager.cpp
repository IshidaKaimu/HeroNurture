#include "CSceneManager.h"
#include "COpening.h"
#include "CBossAppearance.h"
#include "CSceneSelect.h"
#include "CBossEvolution.h"
#include "CSpecialMove.h"
#include "CBossDeath.h"

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

void CSceneManager::Create()
{
    //テキスト表示の準備
    WriteText::GetInstance()->Init();

    m_Scene->Create();
}

void CSceneManager::Update()
{    
    m_Scene->Update();  //入ってるシーンの動作を行う   
}

void CSceneManager::Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera)
{
    m_Scene->Draw(View, Proj, Light, Camera);       //入ってるシーンの描画を行う
    m_pDx11->SetDepth(false);
    CSceneBase::Draw( View, Proj, Light, Camera );  //シーンベース
    m_pDx11->SetDepth(true);
}

void CSceneManager::LoadCreate(enSceneList List)
{
    CSceneManager::GetInstance()->m_Scene = Create(List);
}

void CSceneManager::LoadScene()
{
    m_Scene->LoadScene();
}

void CSceneManager::Initialize()
{
    m_Scene->Initialize();
}

void CSceneManager::LoadData()
{
    //初期化
    m_Scene->LoadData();    //読み込み処理
}

std::unique_ptr<CSceneBase> CSceneManager::Create(enSceneList List)
{
    //現在のシーンのインスタンスを返す
    switch (List)
    {
    case CSceneManager::SceneSelect:    return std::make_unique<CSceneSelect>();
    case CSceneManager::Opening:        return std::make_unique<COpening>();
    case CSceneManager::BossApp:        return std::make_unique<CBossAppearance>();
    case CSceneManager::BossEvo:        return std::make_unique<CBossEvolution>();
    case CSceneManager::Special:        return std::make_unique<CSpecialMove>();
    case CSceneManager::BossDeath:      return std::make_unique<CBossDeath>();
    case CSceneManager::Max:            return nullptr;
    case CSceneManager::none:           return nullptr;
    default:                            return nullptr;
    }
}




