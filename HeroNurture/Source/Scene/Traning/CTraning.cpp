#include "CTraning.h"
#include "KeyManager\CKeyManager.h"
#include "Scene\CSceneManager.h"
#include "WriteText\WriteText.h"
#include "SkinMeshObject\Hero\CHeroManager.h"

CTraning::CTraning()
    : m_pCamera (&CCameraManager::GetInstance())
{
}

CTraning::~CTraning()
{
}

//構築関数
void CTraning::Create()
{
    //----インスタンス生成----

    //スタティックメッシュオブジェクト
    //空
    m_pSky = make_unique<CSky>();
    //地面
    m_pGround = make_unique<CGround>();
}
//破棄関数
void CTraning::Releace()
{
}
//データ読み込み関数
void CTraning::LoadData()
{
}
//初期化関数
void CTraning::Initialize()
{
}

//更新関数
void CTraning::Update()
{
    //フェードイン処理
    if (!FadeIn()) { return; }

   //キーマネージャーの更新処理
   CKeyManager::GetInstance()->Update();

   //育成シーンへと戻る
   if (CKeyManager::GetInstance()->IsDown(VK_RETURN))
   {
       m_SceneTransitionFlg = true;
   }  
   if (m_SceneTransitionFlg && FadeOut())
   {
       CSceneManager::GetInstance()->IsDataLoaded(true);
       CSceneManager::GetInstance()->LoadCreate(CSceneManager::Nature);
   }
}
//描画関数
void CTraning::Draw()
{
    DrawUpText();
}

//上昇量テキストの描画
void CTraning::DrawUpText()
{
    //テキスト描画クラスのインスタンスを変数に代入
    WriteText* Text = WriteText::GetInstance();

    Text->Draw_Text(L"筋力が" + std::to_wstring( CHeroManager::GetInstance().GetPowerUpValue() ), WriteText::Normal, D3DXVECTOR2(0.0f, 0.0f));
}
