#include "CSceneManager.h"
#include "Scene\Title\CTitleScene.h"
#include "CreateAcount\CCreateAcountScene.h"
#include "Scene\Login\CLoginScene.h"
#include "Scene\Nature\CNatureScene.h"
#include "Scene\ModeSelect\CModeSelectScene.h"
#include "Scene\NatureHeroSelect\CNatureHeroSelectScene.h"
#include "Scene\Traning\CTraningScene.h"
#include "Scene\NatureResult\CNatureResultScene.h"
#include "Scene\BattleHeroSelect\CBattleHeroSelectScene.h"
#include "Scene\Battle\CBattleScene.h"
#include "Scene\Battle\UniqueAttack\CUniqueAttack.h"
#include "Scene\BattleResult\CBattleResultScene.h"
#include "ImGui\ImGuiManager\ImGuiManager.h"

CSceneManager::CSceneManager()
    : m_Scene       ()
    , m_hWnd        ()
    , m_pDx9        ( nullptr )
    , m_pDx11       ( nullptr )
    , m_Turn        ()
    , m_UserName    ()
    , m_GageWidth   (1.0f)
    , m_RoleList    ()
    , m_BattleResult()
    , m_Rest        ()
    , m_IsDataLoaded()
{
    m_Scene = std::make_unique<CTitleScene>();   //make_unique:�C���X�^���X�𐶐����āA�g��Ȃ��Ȃ����珟��ɔj�����Ă����
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
#if _DEBUG
    ImGui::Begin(JAPANESE("�V�[��"));
    if (ImGui::Button(JAPANESE("�^�C�g��")))           { LoadCreate(enSceneList::Title); }
    if (ImGui::Button(JAPANESE("�A�J�E���g�쐬")))     { LoadCreate(enSceneList::CreateAcount); }
    if (ImGui::Button(JAPANESE("���O�C��")))           { LoadCreate(enSceneList::Login); }
    if (ImGui::Button(JAPANESE("�q�[���[�I��")))       { LoadCreate(enSceneList::NatureHeroSelect); }
    if (ImGui::Button(JAPANESE("�琬")))               { LoadCreate(enSceneList::Nature); }
    if (ImGui::Button(JAPANESE("�C�s")))               { LoadCreate(enSceneList::Training); }
    if (ImGui::Button(JAPANESE("�琬����")))           { LoadCreate(enSceneList::NatureResult); }
    if (ImGui::Button(JAPANESE("�o�g���q�[���[�I��"))) { LoadCreate(enSceneList::BattleHeroSelect); }
    if (ImGui::Button(JAPANESE("�o�g��")))             { LoadCreate(enSceneList::Battle); }
    if (ImGui::Button(JAPANESE("�o�g������")))         { LoadCreate(enSceneList::BattleResult); }
    ImGui::End();
#endif
    m_Scene->Update();  //�����Ă�V�[���̓�����s��   
}

//�`��֐�
void CSceneManager::Draw()
{
    m_Scene->Draw();       //�����Ă�V�[���̕`����s��

    m_pDx11->SetDepth(false);
    CSceneBase::Draw();    //�V�[���x�[�X
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
    case CSceneManager::Title:            return std::make_unique<CTitleScene>();
    case CSceneManager::CreateAcount:     return std::make_unique<CCreateAcountScene>();
    case CSceneManager::Login:            return std::make_unique<CLoginScene>();
    case CSceneManager::ModeSelect:       return std::make_unique<CModeSelectScene>();
    case CSceneManager::NatureHeroSelect: return std::make_unique<CNatureHeroSelectScene>();
    case CSceneManager::Nature:           return std::make_unique<CNatureScene>();
    case CSceneManager::Training:         return std::make_unique<CTraningScene>();
    case CSceneManager::NatureResult:     return std::make_unique<CNatureResultScene>();
    case CSceneManager::BattleHeroSelect: return std::make_unique<CBattleHeroSelectScene>();
    case CSceneManager::Battle:           return std::make_unique<CBattleScene>();
    case CSceneManager::BattleResult:     return std::make_unique<CBattleResultScene>();
    case CSceneManager::UniqueAttack:     return std::make_unique<CUniqueAttack>();
    case CSceneManager::Max_S:            return nullptr;
    case CSceneManager::none:             return nullptr;
    default:                              return nullptr;
    }
}




