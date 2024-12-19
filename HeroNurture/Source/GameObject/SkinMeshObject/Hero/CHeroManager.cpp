#include "CHeroManager.h"
#include "SkinMeshObject\Hero\Yui\CYui.h"
#include "SkinMeshObject\Hero\Kaito\CKaito.h"

CHeroManager::CHeroManager()
    : m_Hero         ()
    , m_HeroList     ()
    , m_Traning      ()
    , m_Stamina      ()
    , m_BeforeStamina()
    , m_AfterStamina ()
{
    m_Hero = std::make_unique<CYui>();
}

CHeroManager::~CHeroManager()
{
}

//�������֐�
void CHeroManager::Initialize()
{
    //�e�q�[���[�N���X�̏�����
    m_Hero->Initialize();
}

//�f�[�^�ǂݍ��݊֐�
void CHeroManager::LoadMeshData()
{
    //�e�q�[���[�N���X�̃f�[�^�ǂݍ���
    m_Hero->LoadMeshData();
}

//�p�����[�^���̓ǂݍ���
void CHeroManager::LoadParamData(const json& jsondata)
{
    m_Hero->LoadParamData(jsondata);
}

//�X�V�֐�
void CHeroManager::Update()
{
    //�e�q�[���[�N���X�̍X�V�֐�
    m_Hero->Update();
}

//�`��֐�
void CHeroManager::Draw()
{
    //�e�q�[���[�N���X�̍X�V�֐�
    m_Hero->Draw();
}

//�q�[���[�I���V�[���̃A�j���[�V����
void CHeroManager::SelectAnimation()
{
    m_Hero->SelectAnimation();
}

//�琬�V�[���̃A�j���[�V����
void CHeroManager::NatureAnimation(int no)
{
    m_Hero->NatureAnimation(no);
}

//�X�^�~�i�̌����֐�
void CHeroManager::ReduceStamina()
{
    if (m_Stamina > 0.0f) {
        m_Stamina -= REDUSE_STAMINA;
    }
    else
    {
        m_Stamina -= 0.0f;
    }
    //������̃X�^�~�i��ۑ�
    m_AfterStamina = m_Stamina;
}

//�X�^�~�i�̉񕜏���
void CHeroManager::StaminaRecovery()
{
    if (m_Stamina < 100.0f) {
        m_Stamina += RECOVERY_STAMINA;
    }
    else
    {
        m_Stamina += 0.0f;
    }
    //�񕜌�̃X�^�~�i��ۑ�
    m_AfterStamina = m_Stamina;

}

//�q�[���[�ݒ�֐�
void CHeroManager::SetHero(enHeroList list)
{
    //�q�[���[��ݒ�
    m_Hero = Create(list);
}


//�e�q�[���[�N���X�̃C���X�^���X����
std::unique_ptr<CHeroBase> CHeroManager::Create(enHeroList list)
{
    switch (list)
    {
    case CHeroManager::Yui:     return std::make_unique<CYui>();
    case CHeroManager::Kaito:   return std::make_unique<CKaito>();
    case CHeroManager::Max:     return nullptr;
    default:                    return nullptr;

    }
}


