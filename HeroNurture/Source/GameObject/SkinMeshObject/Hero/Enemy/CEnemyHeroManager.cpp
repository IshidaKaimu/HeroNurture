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


//ì¬‚·‚éƒq[ƒ[‚Ìİ’è
void CEnemyHeroManager::CreateEnemyHero(enHeroList list)
{
    //“G‚É‚È‚Á‚½ƒq[ƒ[‚Ì¶¬
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

//“G‚Éİ’è‚³‚ê‚Ä‚¢‚éƒq[ƒ[‚Ì–¼‘O‚ğ•¶š—ñ‚Å•Ô‚·
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

