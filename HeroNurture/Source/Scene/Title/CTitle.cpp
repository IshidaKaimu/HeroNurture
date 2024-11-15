#include "CTitle.h"
#include "Scene\CSceneManager.h"
#include "KeyManager\CKeyManager.h"
#include "StaticMesh\MeshManager\CMeshManager.h"
#include "Sound\CSoundManager.h"
#include <cmath>
#include "ImGui\ImGuiManager\ImGuiManager.h"
#include "CJson.h"

//タイトルシーン
CTitle::CTitle()
    : m_pCamera ( &CCameraManager::GetInstance() )
    , m_pHero()
    , m_pSky    ()
    , m_pGround ()
    , m_Opening(false)
    , m_BossApp(false)
    , m_BossEvo(false)
    , m_Special(false)
    , m_Time   (-10.0f)
{
    //ライト情報
    m_Light.vDirection = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //ライト方向
}

CTitle::~CTitle()
{
}

//構築関数
void CTitle::Create()
{
    //スカイボックスクラス
    m_pSky = new CSky();
    //地面クラス
    m_pGround = new CGround();
    //jsonクラス
    m_pJson = std::make_unique<CJson>();
}

//破棄関数
void CTitle::Releace()
{
    SAFE_DELETE(m_pSky);
    SAFE_DELETE(m_pGround);
    m_pCamera = nullptr;
}


//データ設定関数
void CTitle::LoadData()
{
    //メッシュマネージャーのインスタンスを変数に代入
    CMeshManager* MMng = CMeshManager::GetInstance();
    m_pSky->AttachMesh(CMeshManager::GetMesh(CMeshManager::Sky));
    m_pGround->AttachMesh(CMeshManager::GetMesh(CMeshManager::Ground));

    Initialize();
}

void CTitle::Initialize()
{
    //カメラの初期化
    m_pCamera->Initialize();
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
                //あればロード、なければ作成する関数
                m_pJson->CreateOrLoadAcount( WstringToString(m_UserName));
                //名前をプレイヤーに渡す
                m_pHero->SetUserName( WstringToString(m_UserName) );
                //シーンのロード
                CSceneManager::GetInstance()->LoadCreate(CSceneManager::GameMain);
            }
        }
    }


}

//描画関数
void CTitle::Draw()
{
    if (m_Time <= 5.0f) {
        m_Time += 0.1f;
    }

    //カメラの動作
    m_pCamera->CameraUpdate();

    //スカイボックスの描画
    m_pSky->Draw( m_Light );

    //地面の描画
    m_pGround->Draw( m_Light );

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

//wstringをstringに変換
std::string CTitle::WstringToString(std::wstring owstring)
{
    //wstringからSJIS
    int iBufferSize = 
        WideCharToMultiByte( CP_OEMCP, 0, owstring.c_str(), -1, (char * )NULL, 0, NULL, NULL );

    //バッファの取得
    CHAR* cpMultiByte = new CHAR[ iBufferSize ];

    //wstringからSJIS
    WideCharToMultiByte(CP_OEMCP, 0, owstring.c_str(), -1, cpMultiByte, iBufferSize, NULL, NULL);

    //stringの生成
    std::string oRet( cpMultiByte, cpMultiByte + iBufferSize -1 );

    //バッファの破棄
    delete [] cpMultiByte;

    return (oRet);
}
