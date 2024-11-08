#include "CHeroManager.h"

CHeroManager::CHeroManager()
    :m_Hero ()
{
    m_Hero = std::make_unique<CHeroBase>();
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
