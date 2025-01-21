#include "CModeSelectScene.h"
#include "Scene\CSceneManager.h"
#include "KeyManager\CKeyManager.h"
#include "StaticMesh\MeshManager\CMeshManager.h"
#include "Sound\CSoundManager.h"
#include <cmath>
#include "ImGui\ImGuiManager\ImGuiManager.h"
#include "Json\CJson.h"
#include "Utility\CUtility.h"
#include "Sprite2D\UIManager\CUIManager.h" 

CModeSelectScene::CModeSelectScene()
{
    //ライト情報
    m_Light.vDirection = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //ライト方向
}

CModeSelectScene::~CModeSelectScene()
{
}

void CModeSelectScene::Create()
{
    //----UI----
    m_pTitleBack = std::make_unique<CUIObject>();
    m_pTitleInfoBack = std::make_unique<CUIObject>();
}

void CModeSelectScene::Releace()
{
}

void CModeSelectScene::LoadData()
{   
    //----UI----
    m_pTitleBack->AttachSprite(CUIManager::GetSprite(CUIManager::TitleBack));
    m_pTitleInfoBack->AttachSprite(CUIManager::GetSprite(CUIManager::TitleInfoBack));
}

void CModeSelectScene::Initialize()
{
}

//更新関数
void CModeSelectScene::Update()
{
    //フェードイン処理
    if (!FadeIn()) { return; }

    //シーン遷移(仮)
    if (CKeyManager::GetInstance()->IsDown(VK_RETURN))
    {
        //オープニングシーンへ
        m_SceneTransitionFlg = true;
    }
    //フェードアウト処理
    if (m_SceneTransitionFlg && FadeOut())
    {
    }
}

void CModeSelectScene::Draw()
{
    //UIの描画
    DrawUI();
}

//タイトル画面の描画
void CModeSelectScene::DrawUI()
{
    WriteText* Text = WriteText::GetInstance();

    //タイトル背景UI初期設定
    m_pTitleBack->SetPosition(260.0f, 200.0f, 0.0f);
    m_pTitleBack->SetScale(1.5f, 0.8f, 1.5f);
    m_pTitleBack->SetDisplay(1.0f, 1.0f);
    m_pTitleBack->SetAlpha(0.9f);
    //タイトル指示テキスト背景
    m_pTitleInfoBack->SetPosition(420.0f, 445.0f, 0.0f);
    m_pTitleInfoBack->SetScale(1.0f, 1.0f, 1.0f);
    m_pTitleInfoBack->SetDisplay(1.0f, 1.0f);
    m_pTitleInfoBack->SetAlpha(0.9f);

    //タイトル背景描画
    m_pTitleBack->Draw();
    //タイトル指示テキスト背景描画
    m_pTitleInfoBack->Draw();

    Text->Draw_Text(L"HeroNature", WriteText::B_Big, D3DXVECTOR2(305.0f, 165.0f));   //タイトル
    Text->Draw_Text(L"Press Enter", WriteText::B_Small, D3DXVECTOR2(480.0f, 450.0f)); //指示
}
