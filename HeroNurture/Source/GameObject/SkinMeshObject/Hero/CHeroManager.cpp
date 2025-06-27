#include "CHeroManager.h"
#include "SkinMeshObject\Hero\Yui\CYui.h"
#include "SkinMeshObject\Hero\Kaito\CKaito.h"

CHeroManager::CHeroManager()
    : m_pHero           ()
    , m_SelectHero      ()
    , m_Traning         ()
    , m_HeroName        ()
    , m_Stamina         ()
    , m_BeforeStamina   ()
    , m_AfterStamina    ()
{
    m_pHero = std::make_unique<CYui>();
}

CHeroManager::~CHeroManager()
{
}

//ヒーロー構築関数
void CHeroManager::CreateHero(enHeroList list)
{
    //選択されたヒーローのクラスを生成
    m_pHero = Create(list);

    //選択されたヒーローの名前を保存
    m_SelectHero = list;
    
}

//各ヒーロークラスのインスタンス生成
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

void CHeroManager::InitStamina()
{
    m_Stamina = MAX_STAMINA;
}

//スタミナの減少関数
void CHeroManager::ReduceStamina()
{
    if (m_Stamina > 0.0f) {
        m_Stamina -= REDUSE_STAMINA;
    }
    else
    {
        m_Stamina -= 0.0f;
    }
    //減少後のスタミナを保存
    m_AfterStamina = m_Stamina;
}

//スタミナの回復処理
void CHeroManager::StaminaRecovery()
{
    if (m_Stamina < 100.0f) {
        m_Stamina += CUtility::GenerateRandomValue(25.0f,50.0f);
    }
    else
    {
        m_Stamina += 0.0f;
    }
    
    //回復後のスタミナを保存
    m_AfterStamina = m_Stamina;

}

bool CHeroManager::Death()
{
    //体力が0以下で、ダメージアニメーションが終了している場合
    if (m_pHero->GetHp() <= 0.0f)
    {
       return true;
    }

    return false;
}

void CHeroManager::BattleInitPos()
{
    m_pHero->SetPosition(BATTLEINIT_POS);
}

//ヒーロー名を文字列で返す関数
std::string CHeroManager::GetSelectHeroName()
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





