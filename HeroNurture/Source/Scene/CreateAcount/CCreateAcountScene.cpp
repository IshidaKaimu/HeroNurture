#include "CCreateAcountScene.h"
#include "Json\CJson.h"
#include "KeyManager\CKeyManager.h"
#include "Sound\CSoundManager.h"
#include "Scene\CSceneManager.h"
#include "Sprite2D\UIManager\CUIManager.h"
#include "Utility\CUtility.h"
//定数の名前空間
using namespace Constant_CreateAcountScene;

CCreateAcountScene::CCreateAcountScene()
    : m_pCamera    ()
    , m_SorceDir   ()
    , m_DestDir    ()
    , m_UserName   ()
    , m_pNameSpace ()
    , m_pJson      ()
    , m_Duplication()
{
}

CCreateAcountScene::~CCreateAcountScene()
{
}

void CCreateAcountScene::Create()
{
    //----UI----
    //名前入力空間
    m_pNameSpace = std::make_unique<CUIObject>();
    //背景
    m_pBack = std::make_unique<CUIObject>();
    //----------
}

void CCreateAcountScene::Releace()
{
}

void CCreateAcountScene::LoadData()
{
    //----UI----
    //名前入力空間
    m_pNameSpace->AttachSprite(CUIManager::GetSprite(CUIManager::NameSpace));
    //背景
    m_pBack->AttachSprite(CUIManager::GetSprite(CUIManager::BasicBack));
    //---------
}

void CCreateAcountScene::Initialize()
{
    //名前入力スペース
    m_pNameSpace->SetPosition(NAMESPACE_POS);                    //座標
    m_pNameSpace->SetScale(NAMESPACE_SCALE);                     //拡縮
    m_pNameSpace->SetDisplay(NAMESPACE_DISP.x, NAMESPACE_DISP.y);//幅
    //背景
    m_pBack->SetPosition(BACK_POS);                         //座標
    m_pBack->SetScale(BACK_SCALE);                          //拡縮
    m_pBack->SetDisplay(BACK_DISP.x, BACK_DISP.y);          //幅
}

void CCreateAcountScene::Update()
{
    //タイトルBGMの再生
    CSoundManager::GetInstance()->PlayLoop(CSoundManager::BGM_Title);
    CSoundManager::GetInstance()->Volume(CSoundManager::BGM_Title, 40);

    CKeyManager* KeyMng = &CKeyManager::GetInstance();
    CSceneManager* SceneMng = &CSceneManager::GetInstance();
    WriteText* Text = WriteText::GetInstance();

    //フェードイン処理
    if (!FadeIn()) { return; }

    //リアルタイム入力処理
    CUtility::GetInstance().InputText(m_UserName,NAME_MAXLENGTH);

    //コピー元フォルダのパス
    m_SorceDir = "Data\\Acount\\Base";
    //コピー先フォルダのパス
    m_DestDir = "Data\\Acount\\" + CUtility::GetInstance().WstringToString(m_UserName);

    //シーン遷移(仮)
    if (KeyMng->IsDown(VK_RETURN))
    {
        //スタートSEの再生
        CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Start);
        CSoundManager::GetInstance()->Volume(CSoundManager::SE_Start, 40);

        if (!m_UserName.empty()) {

            //コピー先のフォルダが存在していなければ
            if (!std::filesystem::exists(m_DestDir))
            {
                //フォルダのコピー
                std::filesystem::copy(
                    m_SorceDir,     //コピー元のパス
                    m_DestDir,      //コピー先のパス
                    std::filesystem::copy_options::recursive    //フォルダ内のファイル等もコピー
                );
                
                //重複の表示をなくす
                m_Duplication = false;

                //オープニングシーンへ
                m_SceneTransitionFlg = true;
            }
            else
            {
                //重複していることを表示する
                m_Duplication = true;
            }
        }
    }

    //前の画面に戻す
    if (KeyMng->IsDown(VK_ESCAPE))
    {
        m_SceneTransitionFlg = true;
    }

    //フェードアウト処理
    if (m_SceneTransitionFlg && FadeOut())
    {
        SceneMng->LoadCreate(CSceneManager::Title);
    }
}

void CCreateAcountScene::Draw()
{
    WriteText* Text = WriteText::GetInstance();
    CSceneManager* SceneMng = &CSceneManager::GetInstance();


    //深度を無効にする
    SceneMng->GetDx11()->SetDepth(false);

    //汎用背景の描画
    DrawBasicBackGround();

    //操作方法指示バーの描画
    DrawControlBar(true);

    //名前入力スペースの描画
    m_pNameSpace->Draw();

    //深度を有効にする
    SceneMng->GetDx11()->SetDepth(true);

    //シーン名の描画
    Text->Draw_Text(L"アカウントを作成", WriteText::Select, SCENENAME_POS);

    //何も入力されていなければ
    if (m_UserName.empty())
    {
        //入力された文字の描画
        Text->Draw_Text(L"ここに名前を入力...", WriteText::NameInfo, D3DXVECTOR2(NAME_STARTPOS.x, NAME_STARTPOS.y));
    }

    //入力された文字の描画
    Text->Draw_Text(m_UserName, WriteText::InputName, D3DXVECTOR2(NAME_STARTPOS.x, NAME_STARTPOS.y));

    if (m_Duplication)
    {
        Text->Draw_Text(L"※このアカウント名は既に使用されています", WriteText::Error, D3DXVECTOR2(300.0f, 450.0f));
    }
}

