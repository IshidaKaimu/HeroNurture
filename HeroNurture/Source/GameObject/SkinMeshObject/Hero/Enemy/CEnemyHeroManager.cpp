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


//作成するヒーローの設定
void CEnemyHeroManager::CreateEnemyHero(enHeroList list)
{
    //敵になったヒーローの生成
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
    //体力が0以下で、ダメージアニメーションが終了している場合
    if (m_pEnemyHero->GetHp() <= 0.0f)
    {
       return true;
    }

    return false;
}

//敵に設定されているヒーローの名前を文字列で返す
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

