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

//初期化関数
void CHeroManager::Initialize()
{
    m_pHero->Initialize();
}

//バトルシーンのみで使用する初期化
void CHeroManager::BattleInitialize()
{
    m_pHero->BattleInitialize();
}

//データ読み込み関数
void CHeroManager::LoadMeshData()
{
    m_pHero->LoadMeshData();
}

//パラメータ情報の読み込み
void CHeroManager::LoadParamData(const json& jsondata)
{
    m_pHero->LoadParamData(jsondata);
}

//更新関数
void CHeroManager::Update()
{
    m_pHero->Update();
}

//描画関数
void CHeroManager::Draw()
{
    m_pHero->Draw();
}

//デバッグ関数
void CHeroManager::Debug()
{
    m_pHero->Debug();
}

//ヒーロー構築関数
void CHeroManager::CreateHero(enHeroList list)
{
    m_pHero = Create(list);
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

//ヒーロー選択シーンのアニメーション
void CHeroManager::NatureHeroSelectAnimation()
{
    m_pHero->NatureHeroSelectAnimation();
}

//育成シーンのアニメーション
void CHeroManager::NatureAnimation(int no)
{
    m_pHero->NatureAnimation(no);
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
        m_Stamina += RECOVERY_STAMINA;
    }
    else
    {
        m_Stamina += 0.0f;
    }
    //回復後のスタミナを保存
    m_AfterStamina = m_Stamina;

}

//ヒーロー名を文字列で返す関数
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





