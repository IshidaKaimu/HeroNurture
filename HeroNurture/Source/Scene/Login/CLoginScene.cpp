#include "CLoginScene.h"
#include "Json\CJson.h"
#include "KeyManager\CKeyManager.h"
#include "Sound\CSoundManager.h"
#include "Scene\CSceneManager.h"
#include "Sprite2D\UIManager\CUIManager.h"
#include "Utility\CUtility.h"

//定数の名前空間
using namespace Constant_LoginScene;

CLoginScene::CLoginScene()
    : m_TargetPath ()
    , m_UserName   ()
    , m_pNameSpace ()
    , m_pBack      ()
    , m_pJson      ()
    , m_NonExistent()
{
}

CLoginScene::~CLoginScene()
{
}

void CLoginScene::Create()
{
    //----UI----
    //名前入力空間
    m_pNameSpace = std::make_unique<CUIObject>(); 
    //背景
    m_pBack = std::make_unique<CUIObject>();
    //----------

}

void CLoginScene::Releace()
{
}

void CLoginScene::LoadData()
{
    //----UI----
    //名前入力スペース
    m_pNameSpace->AttachSprite(CUIManager::GetSprite(CUIManager::NameSpace));
    //背景
    m_pBack->AttachSprite(CUIManager::GetSprite(CUIManager::BasicBack));
    //----------
}

void CLoginScene::Initialize()
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

void CLoginScene::Update()
{
    //モード選択BGMを停止
    CSoundManager::GetInstance()->Stop(CSoundManager::BGM_ModeSelect);

    //タイトルBGMの再生
    CSoundManager::GetInstance()->PlayLoop(CSoundManager::BGM_Title);
    CSoundManager::GetInstance()->Volume(CSoundManager::BGM_Title, 40);


    //フェードイン処理
    if (!FadeIn()) { return; }

    CKeyManager* KeyMng = &CKeyManager::GetInstance();
    CSceneManager* SceneMng = &CSceneManager::GetInstance();
    CUtility* Utility = &CUtility::GetInstance();

    //リアルタイム入力処理
    Utility->InputText(m_UserName,NAME_MAXLENGTH);


    //シーン遷移(仮)
    if (KeyMng->IsDown(VK_RETURN))
    {
        //スタートSEの再生
        CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Start);
        CSoundManager::GetInstance()->Volume(CSoundManager::SE_Start, 40);

        //string型に変換　
        std::string UserName = Utility->WstringToString(m_UserName);
        //存在確認したいフォルダのパス
        m_TargetPath = "Data\\Acount\\" + UserName;

        //入力した名前のアカウントが既に存在していれば
        if (!m_UserName.empty() && std::filesystem::exists(m_TargetPath)) {
            //名前の登録
            SceneMng->SetName(m_UserName);
            //フェード開始
            m_SceneTransitionFlg = true;
        }
        else
        {
            //一致する名前が存在しないことを表示する
            m_NonExistent = true;
        }
    }

    //前の画面に戻る
    if (KeyMng->IsDown(VK_ESCAPE))
    {
        //スタートSEの再生
        CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Start);
        CSoundManager::GetInstance()->Volume(CSoundManager::SE_Start, 40);

        //選択番号を変更する
        m_SelectNo = 1;
        //フェード開始
        m_SceneTransitionFlg = true;
    }

    //フェードアウト処理
    if (m_SceneTransitionFlg && FadeOut())
    {
        switch (m_SelectNo)
        {
        case 0: SceneMng->LoadCreate(CSceneManager::ModeSelect); break;
        case 1: SceneMng->LoadCreate(CSceneManager::Title); break;
        }
    }
}

void CLoginScene::Draw()
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
    Text->Draw_Text(L"ログイン", WriteText::Select, SCENENAME_POS);

    if (m_UserName.empty())
    {
        //入力された文字の描画
        Text->Draw_Text(L"ここに名前を入力...", WriteText::NameInfo, D3DXVECTOR2(NAME_STARTPOS.x, NAME_STARTPOS.y));
    }

    if (m_NonExistent)
    {
        //一致する名前がない場合の文を表示
        Text->Draw_Text(L"※一致するアカウント名が存在しません", WriteText::Error, D3DXVECTOR2(300.0f, 450.0f));
    }

    //入力された文字の描画
    Text->Draw_Text(m_UserName, WriteText::InputName, D3DXVECTOR2(NAME_STARTPOS.x, NAME_STARTPOS.y));

}


