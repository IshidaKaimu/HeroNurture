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
    m_Scene = std::make_unique<CLoginScene>();   //make_unique:�C���X�^���X�𐶐����āA�g��Ȃ��Ȃ����珟��ɔj�����Ă����
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
    if (ImGui::Button(JAPANESE("���O�C��"))) { LoadCreate(enSceneList::Login); }
    if (ImGui::Button(JAPANESE("�q�[���[�I��"))) { LoadCreate(enSceneList::HeroSelect); }
    if (ImGui::Button(JAPANESE("�琬"))) { LoadCreate(enSceneList::Nature); }
    if (ImGui::Button(JAPANESE("�C�s"))) { LoadCreate(enSceneList::Training); }
    if (ImGui::Button(JAPANESE("�琬����"))) { LoadCreate(enSceneList::TrainingResult); }
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




