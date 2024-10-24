#include "CTitle.h"
#include "Scene/CSceneManager.h"
#include "KeyManager/CKeyManager.h"
#include "StaticMesh/MeshManager/CMeshManager.h"
#include "Sound/CSoundManager.h"
#include <cmath>
#include <iostream>
#include "ImGui/ImGuiManager/ImGuiManager.h"
#include <fstream>
#include <codecvt>

//タイトルシーン
CTitle::CTitle()
    : m_pSky    ()
    , m_pGround ()
    , m_Opening(false)
    , m_BossApp(false)
    , m_BossEvo(false)
    , m_Special(false)
    , m_Time   (-10.0f)
    , m_pPlayer()
{
    //カメラ位置初期設定
    CCamera::GetInstance()->SetPos(D3DXVECTOR3(0.0f, 1.0f, 0.0f));
    //カメラ注視点初期設定
    CCamera::GetInstance()->SetLook(D3DXVECTOR3(0.0f, 0.0f, 4.0f));

    //ライト情報
    m_Light.vDirection = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //ライト方向
}

CTitle::~CTitle()
{
}

//構築関数
void CTitle::Create()
{
    m_pSky = new CSky();
    m_pGround = new CGround();
    m_pPlayer = new CPlayer();
    m_pGameMain = new CGameMain();
}

//データ設定関数
void CTitle::LoadData()
{
    //メッシュマネージャーのインスタンスを変数に代入
    CMeshManager* MMng = CMeshManager::GetInstance();
    m_pSky->AttachMesh(CMeshManager::GetMesh(CMeshManager::Sky));
    m_pGround->AttachMesh(CMeshManager::GetMesh(CMeshManager::Ground));
}

//破棄関数
void CTitle::Releace()
{
    SAFE_DELETE(m_pSky);
    SAFE_DELETE(m_pGround);
    SAFE_DELETE(m_pGameMain);
}

//更新関数
void CTitle::Update()
{

    
    //フェードイン処理
    if (!FadeIn()) { return; }

    //ユーザー名入力処理
    InputName();

    //シーン遷移(仮)
    if (CKeyManager::GetInstance()->IsDown(VK_RETURN))
    {
        //オープニングシーンへ
        m_SceneTransitionFlg = true;
        m_Opening = true;
    }
    //フェードアウト処理
    if (m_SceneTransitionFlg && FadeOut()) 
    {
        if (m_Opening == true) {
            //ユーザーネームが登録されていたら
            if (!m_UserName.empty()) 
            {
                m_pGameMain->SetUserName(m_UserName);
                CSceneManager::GetInstance()->LoadCreate(CSceneManager::GameMain);
            }
            else
            {
                std::wcerr << L"ユーザーネームが設定されていません。" << std::endl;
            }
        }
    }


}

//描画関数
void CTitle::Draw()
{

    CCamera::GetInstance()->Projection();
    CCamera::GetInstance()->Update();
    m_mProj = CCamera::GetInstance()->GetProjection();
    m_mView = CCamera::GetInstance()->GetViewMatrix();


    if (m_Time <= 5.0f) {
        m_Time += 0.1f;
    }

    //スカイボックスの描画
    m_pSky->Draw(m_mView, m_mProj, m_Light, m_Camera);

    //地面の描画
    m_pGround->Draw(m_mView, m_mProj, m_Light, m_Camera);

    //文字の入力
    WriteText::GetInstance()->Draw_Text(m_UserName, WriteText::Select, D3DXVECTOR2(0.0f, 0.0f));
}

//イージング
float CTitle::Easing(float x)
{
    const float c1 = 1.70158;
    const float c3 = c1 + 1.0f;

    return c3 * x * x * x - c1 * x * x;
}

//名前入力処理
void CTitle::InputName()
{
    //キーマネージャのインスタンスを変数に代入
    CKeyManager* KeyMng = CKeyManager::GetInstance();

    //キーマネージャの常に行う処理
    KeyMng->Update();

    //キー全部を調べる
    for (int key = 0x30; key <= 0x5A; key++)
    {
        if (KeyMng->IsDown(key))
        {
            //入力された文字を追加
            m_UserName += wchar_t(key);
        }
    }

    //テキストが空ではないなら
    if (!m_UserName.empty()) 
    {
        //バックスペースが押されたら
        if (KeyMng->IsDown(VK_BACK))
        {
            //最後の文字を削除
            m_UserName.pop_back();
        }
    }
}
