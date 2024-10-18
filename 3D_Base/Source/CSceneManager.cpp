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
    m_Scene = std::make_unique<CSceneSelect>();   //make_unique:�C���X�^���X�𐶐����āA�g��Ȃ��Ȃ����珟��ɔj�����Ă����
}


CSceneManager::~CSceneManager()
{
}

void CSceneManager::Create()
{
    //�e�L�X�g�\���̏���
    WriteText::GetInstance()->Init();

    m_Scene->Create();
}

void CSceneManager::Update()
{    
    m_Scene->Update();  //�����Ă�V�[���̓�����s��   
}

void CSceneManager::Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera)
{
    m_Scene->Draw(View, Proj, Light, Camera);       //�����Ă�V�[���̕`����s��
    m_pDx11->SetDepth(false);
    CSceneBase::Draw( View, Proj, Light, Camera );  //�V�[���x�[�X
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
    //������
    m_Scene->LoadData();    //�ǂݍ��ݏ���
}

std::unique_ptr<CSceneBase> CSceneManager::Create(enSceneList List)
{
    //���݂̃V�[���̃C���X�^���X��Ԃ�
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




