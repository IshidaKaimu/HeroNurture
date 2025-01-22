#include "CTitleScene.h"
#include "Scene\CSceneManager.h"
#include "KeyManager\CKeyManager.h"
#include "StaticMesh\MeshManager\CMeshManager.h"
#include "Sound\CSoundManager.h"
#include "SkinMeshObject\Hero\CHeroManager.h"
#include "ImGui\ImGuiManager\ImGuiManager.h"
#include "Json\CJson.h"
#include "Utility\CUtility.h"
#include "Sprite2D\UIManager\CUIManager.h" 
#include <cmath>


CTitleScene::CTitleScene()
    : m_pCamera ( &CCameraManager::GetInstance() )
    , m_pYui    ()
    , m_pKaito  ()
    , m_pSky    ()
    , m_pGround ()
    , m_HeroNo  ()
{
    //ライト情報
    m_Light.vDirection = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //ライト方向
}

CTitleScene::~CTitleScene()
{
}

void CTitleScene::Create()
{
    //----スタティックメッシュ----
    //スカイボックス
    m_pSky = std::make_unique<CSky>();
    //地面
    m_pGround = std::make_unique<CGround>();
    
    //----スキンメッシュ----
    //ユイ
    m_pYui = std::make_unique<CYui>();
    //カイト
    m_pKaito = std::make_unique<CKaito>();

    //json
    m_pJson = std::make_unique<CJson>();

    //----UI----
    //タイトル背景
    m_pTitleBack = std::make_unique<CUIObject>();
    //タイトル指示テキスト背景
    m_pTitleInfoBack = std::make_unique<CUIObject>();
}

void CTitleScene::Releace()
{
    m_pCamera = nullptr;
}

void CTitleScene::LoadData()
{
    CMeshManager* MMng = CMeshManager::GetInstance();
    //----スタティックメッシュ----
    m_pSky->AttachMesh(CMeshManager::GetMesh(CMeshManager::Sky));      //空
    m_pGround->AttachMesh(CMeshManager::GetMesh(CMeshManager::Ground));//地面

    //----タイトル画面に表示するヒーローのメッシュ設定----
    m_pYui->LoadMeshData();  //ユイ
    m_pKaito->LoadMeshData();//カイト

    //----UI----
    m_pTitleBack->AttachSprite(CUIManager::GetSprite(CUIManager::TitleBack));
    m_pTitleInfoBack->AttachSprite(CUIManager::GetSprite(CUIManager::TitleInfoBack));
}

void CTitleScene::Initialize()
{
    //カメラの初期位置
    m_pCamera->SetPos(5.0f, 4.0f, -5.0f);
    m_pCamera->SetLook(0.0f, 4.0f, 0.0f);

    //どちらのヒーローを表示するか、乱数で設定
    m_HeroNo = CUtility::GetInstance().GenerateRandomValue(0,1);

    //設定されたヒーローの初期化
    switch (m_HeroNo)
    {
    case 0:
        m_pYui->Initialize();
        break;
    case 1:
        m_pKaito->Initialize();
        break;
    default:
        break;
    }
}

//更新関数
void CTitleScene::Update()
{   
    CSceneManager* SceneMng = CSceneManager::GetInstance();
    CKeyManager* KeyMng = CKeyManager::GetInstance();

    KeyMng->Update();

    //タイトルBGMの再生
    CSoundManager::GetInstance()->PlayLoop(CSoundManager::BGM_Title);
    CSoundManager::GetInstance()->Volume(CSoundManager::BGM_Title, 40);


    //フェードイン処理
    if (!FadeIn()) { return; }

    //シーン遷移(仮)
    if (KeyMng->IsDown(VK_RETURN))
    {
        //スタートSEの再生
        CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Start);
        CSoundManager::GetInstance()->Volume(CSoundManager::SE_Start,40);

        //オープニングシーンへ
        m_SceneTransitionFlg = true;
    }
    //フェードアウト処理
    if (m_SceneTransitionFlg && FadeOut()) 
    {
        SceneMng->LoadCreate(CSceneManager::ModeSelect);
    }
}

void CTitleScene::Draw()
{
    //カメラの動作
    m_pCamera->CameraUpdate();

    //スカイボックスの描画
    m_pSky->Draw();

    //地面の描画
    m_pGround->Draw();

    //表示を切り替える
    switch (m_HeroNo)
    {
    case 0:
        m_pYui->MoveSelectAnim();
        m_pYui->Draw();
        break;
    case 1:
        m_pKaito->MoveSelectAnim();
        m_pKaito->Draw();
        break;
    default:
        break;
    }

    //UI
    DrawUI();
}

//イージング
float CTitleScene::Easing(float x)
{
    const float c1 = 1.70158f;
    const float c3 = c1 + 1.0f;

    return c3 * x * x * x - c1 * x * x;
}

//名前入力処理
void CTitleScene::InputName()
{
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

//タイトル画面の描画
void CTitleScene::DrawUI()
{
    WriteText* Text = WriteText::GetInstance();

    //タイトル背景UI初期設定
    m_pTitleBack->SetPosition(260.0f, 200.0f,0.0f);
    m_pTitleBack->SetScale(1.5f, 0.8f, 1.5f);
    m_pTitleBack->SetDisplay(1.0f, 1.0f);
    m_pTitleBack->SetAlpha(0.9f);
    //タイトル指示テキスト背景
    m_pTitleInfoBack->SetPosition(420.0f, 445.0f, 0.0f);
    m_pTitleInfoBack->SetScale(1.0f, 1.0f, 1.0f);
    m_pTitleInfoBack->SetDisplay(1.0f, 1.0f);
    m_pTitleInfoBack->SetAlpha(0.9f);

    //タイトル背景描画
    m_pTitleBack->Draw();
    //タイトル指示テキスト背景描画
    m_pTitleInfoBack->Draw();

    Text->Draw_Text(L"HeroNature", WriteText::B_Big, D3DXVECTOR2(305.0f, 165.0f));   //タイトル
    Text->Draw_Text(L"Press Enter", WriteText::B_Small, D3DXVECTOR2(480.0f, 450.0f)); //指示

}

//wstringをstringに変換
std::string CTitleScene::WstringToString(std::wstring owstring)
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
