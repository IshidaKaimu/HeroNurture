#include "CEnemyHeroManager.h"
#include "SkinMeshObject\Hero\Yui\CYui.h"
#include "SkinMeshObject\Hero\Kaito\CKaito.h"

CEnemyHeroManager::CEnemyHeroManager()
{
    m_pEnemyHero = std::make_unique<CKaito>();
}

CEnemyHeroManager::~CEnemyHeroManager()
{
}


//�쐬����q�[���[�̐ݒ�
void CEnemyHeroManager::CreateEnemyHero(enHeroList list)
{
    //�G�ɂȂ����q�[���[�̐���
    m_pEnemyHero = Create(list);
    m_SelectEnemyHero = list;
}

std::unique_ptr<CHeroBase> CEnemyHeroManager::Create(enHeroList list)
{
    switch (list)
    {
    case CHeroManager::Yui:     return std::make_unique<CYui>();
    case CHeroManager::Kaito:   return std::make_unique<CKaito>();
    case CHeroManager::Max:     return nullptr;
    default:                    return nullptr;
    }
}

bool CEnemyHeroManager::Death()
{
    //�̗͂�0�ȉ��ŁA�_���[�W�A�j���[�V�������I�����Ă���ꍇ
    if (m_pEnemyHero->GetHp() <= 0.0f)
    {
       return true;
    }

    return false;
}

//�G�ɐݒ肳��Ă���q�[���[�̖��O�𕶎���ŕԂ�
std::string CEnemyHeroManager::GetEnemyHeroName()
{
    switch (m_SelectEnemyHero)
    {
    case CHeroBase::Yui:
        m_EnemyHeroName = "Yui";
        break;
    case CHeroBase::Kaito:
        m_EnemyHeroName = "Kaito";
        break;
    }
    return m_EnemyHeroName;
}

