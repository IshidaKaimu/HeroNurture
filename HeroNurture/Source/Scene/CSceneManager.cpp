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
    m_Scene = std::make_unique<CSceneSelect>();   //make_unique:�C���X�^���X�𐶐����āA�g��Ȃ��Ȃ����珟��ɔj�����Ă����
}


CSceneManager::~CSceneManager()
{
}

//�\�z�A�f�[�^�ǂݍ���
void CSceneManager::Create(CDirectX9& pDx9, CDirectX11& pDx11, HWND hwnd)
{
    m_pDx9 = &pDx9;
    m_pDx11 = &pDx11;
    m_hWnd = hwnd;
    
    //�e�L�X�g�\���̏���
    WriteText::GetInstance()->SetDx11(*m_pDx11);
    WriteText::GetInstance()->Init();

    m_Scene->Create();
    m_Scene->LoadData();
}

void CSceneManager::Update()
{        
    ImGui::Begin(JAPANESE("�V�[��"));
    if (ImGui::Button(JAPANESE("�I��"))) { LoadCreate(enSceneList::SceneSelect); }
    if (ImGui::Button(JAPANESE("���C��"))) { LoadCreate(enSceneList::GameMain); }
    ImGui::End();
    m_Scene->Update();  //�����Ă�V�[���̓�����s��   
}

void CSceneManager::Draw()
{
    m_Scene->Draw();       //�����Ă�V�[���̕`����s��

    m_pDx11->SetDepth(false);
    CSceneBase::Draw();  //�V�[���x�[�X
    m_pDx11->SetDepth(true);
}

void CSceneManager::LoadCreate(enSceneList List)
{
    //��x�j��
    m_Scene.release();

    m_Scene = Create(List);
    //�e�V�[���̍\�z
    m_Scene->Create();
    //�e�V�[���̃f�[�^�ǂݍ���
    m_Scene->LoadData();
    //�e�V�[���̏�����
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
    //���݂̃V�[���̃C���X�^���X��Ԃ�
    switch (List)
    {
    case CSceneManager::SceneSelect:    return std::make_unique<CSceneSelect>();
    case CSceneManager::GameMain:       return std::make_unique<CGameMain>();
    case CSceneManager::Max:            return nullptr;
    case CSceneManager::none:           return nullptr;
    default:                            return nullptr;
    }
}




