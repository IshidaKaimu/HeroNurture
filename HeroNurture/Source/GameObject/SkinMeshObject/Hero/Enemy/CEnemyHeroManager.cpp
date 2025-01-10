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

//�������֐�
void CEnemyHeroManager::Initialize()
{
    m_pEnemyHero->EnemyInit();
}

//���b�V���f�[�^�̐ݒ�
void CEnemyHeroManager::LoadMeshData()
{
    m_pEnemyHero->LoadMeshData();
}

//�X�V�֐�
void CEnemyHeroManager::Update()
{
    m_pEnemyHero->Update();
}

//�`��֐�
void CEnemyHeroManager::Draw()
{
    m_pEnemyHero->Draw();
}

//�f�o�b�O�֐�
void CEnemyHeroManager::Debug()
{
    m_pEnemyHero->Debug();
}

//�쐬����q�[���[�̐ݒ�
void CEnemyHeroManager::CreateEnemyHero(enHeroList list)
{
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

