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
        m_Stamina += CUtility::GenerateRandomValue(25.0f,50.0f);
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





