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
    m_pScene = std::make_unique<CTitleScene>();   //make_unique:�C���X�^���X�𐶐����āA�g��Ȃ��Ȃ����珟��ɔj�����Ă����
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

    m_pScene->Create();
    m_pScene->LoadData();
}

//�j���֐�
void CSceneManager::Release()
{
    m_pScene->Releace();
}

//�������֐�
void CSceneManager::Initialize()
{
    m_pScene->Initialize();
}

//�X�V�֐�
void CSceneManager::Update()
{        
#if DEBUG
    ImGui::Begin(JAPANESE("�V�[��"));
    if (ImGui::Button(JAPANESE("�^�C�g��")))           { LoadCreate(enSceneList::Title); }
    if (ImGui::Button(JAPANESE("�A�J�E���g�쐬")))     { LoadCreate(enSceneList::CreateAcount); }
    if (ImGui::Button(JAPANESE("���O�C��")))           { LoadCreate(enSceneList::Login); }
    if (ImGui::Button(JAPANESE("���[�h�I��")))         { LoadCreate(enSceneList::ModeSelect); }
    if (ImGui::Button(JAPANESE("�q�[���[�I��")))       { LoadCreate(enSceneList::NurtureHeroSelect); }
    if (ImGui::Button(JAPANESE("�琬")))               { LoadCreate(enSceneList::Nurture); }
    if (ImGui::Button(JAPANESE("�C�s")))               { LoadCreate(enSceneList::Training); }
    if (ImGui::Button(JAPANESE("�琬����")))           { LoadCreate(enSceneList::NurtureResult); }
    if (ImGui::Button(JAPANESE("�o�g���q�[���[�I��"))) { LoadCreate(enSceneList::BattleHeroSelect); }
    if (ImGui::Button(JAPANESE("���C�̓o��V�[��")))   { LoadCreate(enSceneList::YuiAppearance); }
    if (ImGui::Button(JAPANESE("�J�C�g�̓o��V�[��"))) { LoadCreate(enSceneList::KaitoAppearance); }
    if (ImGui::Button(JAPANESE("�o�g��")))             { LoadCreate(enSceneList::Battle); }
    if (ImGui::Button(JAPANESE("�o�g������")))         { LoadCreate(enSceneList::BattleResult); }
    ImGui::End();
#endif
    m_pScene->Update();  //�����Ă�V�[���̓�����s��   
}

//�`��֐�
void CSceneManager::Draw()
{
    m_pScene->Draw();       //�����Ă�V�[���̕`����s��

    m_pDx11->SetDepth(false);
    CSceneBase::Draw();    //�V�[���x�[�X
    m_pDx11->SetDepth(true);
}

//�\�z�E�f�[�^�ǂݍ��݊֐�
void CSceneManager::LoadCreate(enSceneList List)
{
    //��x�j��
    m_pScene.release();
    //�V�[���}�l�[�W���[�ł̍\�z
    m_pScene = Create(List);
    //�e�V�[���̍\�z
    m_pScene->Create();
    //�e�V�[���̃f�[�^�ǂݍ���
    m_pScene->LoadData();
    //�e�V�[���̏�����
    m_pScene->Initialize();
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




