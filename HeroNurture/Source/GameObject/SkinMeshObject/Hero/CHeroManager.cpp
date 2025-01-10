#include "CHeroManager.h"
#include "SkinMeshObject\Hero\Yui\CYui.h"
#include "SkinMeshObject\Hero\Kaito\CKaito.h"

CHeroManager::CHeroManager()
    : m_pHero         ()
    , m_SelectHero     ()
    , m_Traning      ()
    , m_HeroName     ()
    , m_Stamina      ()
    , m_BeforeStamina()
    , m_AfterStamina ()
{
    m_pHero = std::make_unique<CYui>();
}

CHeroManager::~CHeroManager()
{
}

//�������֐�
void CHeroManager::Initialize()
{
    m_pHero->Initialize();
}

//�o�g���V�[���݂̂Ŏg�p���鏉����
void CHeroManager::BattleInitialize()
{
    m_pHero->BattleInitialize();
}

//�f�[�^�ǂݍ��݊֐�
void CHeroManager::LoadMeshData()
{
    m_pHero->LoadMeshData();
}

//�p�����[�^���̓ǂݍ���
void CHeroManager::LoadParamData(const json& jsondata)
{
    m_pHero->LoadParamData(jsondata);
}

//�X�V�֐�
void CHeroManager::Update()
{
    m_pHero->Update();
}

//�`��֐�
void CHeroManager::Draw()
{
    m_pHero->Draw();
}

//�f�o�b�O�֐�
void CHeroManager::Debug()
{
    m_pHero->Debug();
}

//�q�[���[�\�z�֐�
void CHeroManager::CreateHero(enHeroList list)
{
    m_pHero = Create(list);
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

//�q�[���[�I���V�[���̃A�j���[�V����
void CHeroManager::NatureHeroSelectAnimation()
{
    m_pHero->NatureHeroSelectAnimation();
}

//�琬�V�[���̃A�j���[�V����
void CHeroManager::NatureAnimation(int no)
{
    m_pHero->NatureAnimation(no);
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

//�q�[���[���𕶎���ŕԂ��֐�
std::string CHeroManager::GetHeroName()
{
    switch (m_SelectHero)
    {
    case CHeroManager::Yui:
        m_HeroName = "Yui";
        break;
    case CHeroManager::Kaito:
        m_HeroName = "Kaito";
        break;
    default:
        break;
    }
    return m_HeroName;
}





