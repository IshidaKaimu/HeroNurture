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
    //���C�g���
    m_Light.vDirection = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //���C�g����
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

//�X�V�֐�
void CModeSelectScene::Update()
{
    //�t�F�[�h�C������
    if (!FadeIn()) { return; }

    //�V�[���J��(��)
    if (CKeyManager::GetInstance()->IsDown(VK_RETURN))
    {
        //�I�[�v�j���O�V�[����
        m_SceneTransitionFlg = true;
    }
    //�t�F�[�h�A�E�g����
    if (m_SceneTransitionFlg && FadeOut())
    {
    }
}

void CModeSelectScene::Draw()
{
    //UI�̕`��
    DrawUI();
}

//�^�C�g����ʂ̕`��
void CModeSelectScene::DrawUI()
{
    WriteText* Text = WriteText::GetInstance();

    //�^�C�g���w�iUI�����ݒ�
    m_pTitleBack->SetPosition(260.0f, 200.0f, 0.0f);
    m_pTitleBack->SetScale(1.5f, 0.8f, 1.5f);
    m_pTitleBack->SetDisplay(1.0f, 1.0f);
    m_pTitleBack->SetAlpha(0.9f);
    //�^�C�g���w���e�L�X�g�w�i
    m_pTitleInfoBack->SetPosition(420.0f, 445.0f, 0.0f);
    m_pTitleInfoBack->SetScale(1.0f, 1.0f, 1.0f);
    m_pTitleInfoBack->SetDisplay(1.0f, 1.0f);
    m_pTitleInfoBack->SetAlpha(0.9f);

    //�^�C�g���w�i�`��
    m_pTitleBack->Draw();
    //�^�C�g���w���e�L�X�g�w�i�`��
    m_pTitleInfoBack->Draw();

    Text->Draw_Text(L"HeroNature", WriteText::B_Big, D3DXVECTOR2(305.0f, 165.0f));   //�^�C�g��
    Text->Draw_Text(L"Press Enter", WriteText::B_Small, D3DXVECTOR2(480.0f, 450.0f)); //�w��
}
