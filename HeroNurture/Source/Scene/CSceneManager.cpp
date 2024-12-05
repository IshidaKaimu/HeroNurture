#include "CSceneManager.h"
#include "Scene\Title\CTitle.h"
#include "Scene\Nature\CNatureScene.h"
#include "Scene\HeroSelect\CHeroSelect.h"
#include "Scene\Traning\CTraning.h"
#include "ImGui\ImGuiManager\ImGuiManager.h"
CSceneManager::CSceneManager()
    : m_Scene       ()
    , m_hWnd        ()
    , m_pDx9        ( nullptr )
    , m_pDx11       ( nullptr )
{
    m_Scene = std::make_unique<CTitle>();   //make_unique:�C���X�^���X�𐶐����āA�g��Ȃ��Ȃ����珟��ɔj�����Ă����
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

//�j���֐�
void CSceneManager::Release()
{
    m_Scene->Releace();
}

//�������֐�
void CSceneManager::Initialize()
{
    m_Scene->Initialize();
}

//�X�V�֐�
void CSceneManager::Update()
{        
    ImGui::Begin(JAPANESE("�V�[��"));
    if (ImGui::Button(JAPANESE("�^�C�g��"))) { LoadCreate(enSceneList::Title); }
    if (ImGui::Button(JAPANESE("�q�[���[�I��"))) { LoadCreate(enSceneList::HeroSelect); }
    if (ImGui::Button(JAPANESE("�琬"))) { LoadCreate(enSceneList::Nature); }
    if (ImGui::Button(JAPANESE("�C�s"))) { LoadCreate(enSceneList::Training); }
    ImGui::End();
    m_Scene->Update();  //�����Ă�V�[���̓�����s��   
}

//�`��֐�
void CSceneManager::Draw()
{
    m_Scene->Draw();       //�����Ă�V�[���̕`����s��

    m_pDx11->SetDepth(false);
    CSceneBase::Draw();  //�V�[���x�[�X
    m_pDx11->SetDepth(true);
}

//�\�z�E�f�[�^�ǂݍ��݊֐�
void CSceneManager::LoadCreate(enSceneList List)
{
    //��x�j��
    m_Scene.release();
    //�V�[���}�l�[�W���[�ł̍\�z
    m_Scene = Create(List);
    //�e�V�[���̍\�z
    m_Scene->Create();
    //�e�V�[���̃f�[�^�ǂݍ���
    m_Scene->LoadData();
    //�e�V�[���̏�����
    m_Scene->Initialize();

}

//�\�z�֐�
std::unique_ptr<CSceneBase> CSceneManager::Create(enSceneList List)
{
    //���݂̃V�[���̃C���X�^���X��Ԃ�
    switch (List)
    {
    case CSceneManager::Title:          return std::make_unique<CTitle>();
    case CSceneManager::HeroSelect:     return std::make_unique<CHeroSelect>();
    case CSceneManager::Nature:         return std::make_unique<CNatureScene>();
    case CSceneManager::Training:       return std::make_unique<CTraning>();
    case CSceneManager::Max_S:          return nullptr;
    case CSceneManager::none:           return nullptr;
    default:                            return nullptr;
    }
}




