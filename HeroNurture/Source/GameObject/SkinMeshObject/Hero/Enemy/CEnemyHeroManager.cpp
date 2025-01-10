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

//初期化関数
void CEnemyHeroManager::Initialize()
{
    m_pEnemyHero->EnemyInit();
}

//メッシュデータの設定
void CEnemyHeroManager::LoadMeshData()
{
    m_pEnemyHero->LoadMeshData();
}

//更新関数
void CEnemyHeroManager::Update()
{
    m_pEnemyHero->Update();
}

//描画関数
void CEnemyHeroManager::Draw()
{
    m_pEnemyHero->Draw();
}

//デバッグ関数
void CEnemyHeroManager::Debug()
{
    m_pEnemyHero->Debug();
}

//作成するヒーローの設定
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

