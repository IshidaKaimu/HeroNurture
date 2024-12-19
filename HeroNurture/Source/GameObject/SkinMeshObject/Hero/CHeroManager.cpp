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

//初期化関数
void CHeroManager::Initialize()
{
    //各ヒーロークラスの初期化
    m_Hero->Initialize();
}

//データ読み込み関数
void CHeroManager::LoadMeshData()
{
    //各ヒーロークラスのデータ読み込み
    m_Hero->LoadMeshData();
}

//パラメータ情報の読み込み
void CHeroManager::LoadParamData(const json& jsondata)
{
    m_Hero->LoadParamData(jsondata);
}

//更新関数
void CHeroManager::Update()
{
    //各ヒーロークラスの更新関数
    m_Hero->Update();
}

//描画関数
void CHeroManager::Draw()
{
    //各ヒーロークラスの更新関数
    m_Hero->Draw();
}

//ヒーロー選択シーンのアニメーション
void CHeroManager::SelectAnimation()
{
    m_Hero->SelectAnimation();
}

//育成シーンのアニメーション
void CHeroManager::NatureAnimation(int no)
{
    m_Hero->NatureAnimation(no);
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

//ヒーロー設定関数
void CHeroManager::SetHero(enHeroList list)
{
    //ヒーローを設定
    m_Hero = Create(list);
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


