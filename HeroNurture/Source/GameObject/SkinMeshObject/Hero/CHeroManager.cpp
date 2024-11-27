#include "CHeroManager.h"
#include "SkinMeshObject\Hero\Yui\CYui.h"
#include "SkinMeshObject\Hero\Kaito\CKaito.h"

CHeroManager::CHeroManager()
    :m_Hero ()
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
void CHeroManager::LoadData()
{
    //各ヒーロークラスのデータ読み込み
    m_Hero->LoadData();
}

//更新関数
void CHeroManager::Update()
{
    //各ヒーロークラスの更新関数
    m_Hero->Update();
}

//描画関数
void CHeroManager::Draw( LIGHT& light )
{
    //各ヒーロークラスの更新関数
    m_Hero->Draw( light );
}

//アニメーション関数
void CHeroManager::Animation()
{
    m_Hero->Animation();
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


