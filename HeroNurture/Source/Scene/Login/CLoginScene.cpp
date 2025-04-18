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
    , m_pJson      ()
{
}

CLoginScene::~CLoginScene()
{
}

void CLoginScene::Create()
{
    //----UI----
    m_pNameSpace = std::make_unique<CUIObject>();
}

void CLoginScene::Releace()
{
}

void CLoginScene::LoadData()
{
    m_pNameSpace->AttachSprite(CUIManager::GetSprite(CUIManager::NameSpace));
}

void CLoginScene::Initialize()
{
    //名前入力スペースの位置初期化
    m_pNameSpace->SetPosition(NAMESPACE_POS.x, NAMESPACE_POS.y, NAMESPACE_POS.z);
    //名前入力スペースのスケール初期化
    m_pNameSpace->SetScale(NAMESPACE_SCALE.x, NAMESPACE_SCALE.y, NAMESPACE_SCALE.z);
    //名前入力スペースの幅初期化
    m_pNameSpace->SetDisplay(NAMESPACE_DISP.x, NAMESPACE_DISP.y);
}

void CLoginScene::Update()
{
    //フェードイン処理
    if (!FadeIn()) { return; }

    CKeyManager* KeyMng = &CKeyManager::GetInstance();
    CSceneManager* SceneMng = CSceneManager::GetInstance();
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
            //モード選択シーンへ
            m_SceneTransitionFlg = true;
        }
    }
    //フェードアウト処理
    if (m_SceneTransitionFlg && FadeOut())
    {
        SceneMng->LoadCreate(CSceneManager::ModeSelect);
    }
}

void CLoginScene::Draw()
{
    WriteText* Text = WriteText::GetInstance();

    //名前入力スペースの描画
    m_pNameSpace->Draw();

    //シーン名の描画
    Text->Draw_Text(L"ログイン", WriteText::D_Big, D3DXVECTOR2(0.0f, -20.0f));

    if (m_UserName.empty())
    {
        //入力された文字の描画
        Text->Draw_Text(L"ここに名前を入力...", WriteText::NameInfo, D3DXVECTOR2(NAME_STARTPOS.x, NAME_STARTPOS.y));
    }

    //入力された文字の描画
    Text->Draw_Text(m_UserName, WriteText::InputName, D3DXVECTOR2(NAME_STARTPOS.x, NAME_STARTPOS.y));
}


