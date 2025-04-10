#include "CLoginScene.h"
#include "KeyManager\CKeyManager.h"
#include "Sound\CSoundManager.h"
#include "Scene\CSceneManager.h"
#include "Sprite2D\UIManager\CUIManager.h"
#include "Json\CJson.h"
//定数の名前空間
using namespace Constant_LoginScene;

CLoginScene::CLoginScene()
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

    //リアルタイム入力処理
    InputName();

    CKeyManager* KeyMng = &CKeyManager::GetInstance();
    CSceneManager* SceneMng = CSceneManager::GetInstance();

    //シーン遷移(仮)
    if (KeyMng->IsDown(VK_RETURN))
    {
        //スタートSEの再生
        CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Start);
        CSoundManager::GetInstance()->Volume(CSoundManager::SE_Start, 40);

        //オープニングシーンへ
        m_SceneTransitionFlg = true;
    }
    //フェードアウト処理
    if (m_SceneTransitionFlg && FadeOut())
    {
        SceneMng->LoadCreate(CSceneManager::Login);
    }
}

void CLoginScene::Draw()
{
    WriteText* Text = WriteText::GetInstance();

    //名前入力スペースの描画
    m_pNameSpace->Draw();

    if (m_UserName.empty())
    {
        //入力された文字の描画
        Text->Draw_Text(L"ここに名前を入力...", WriteText::NameInfo, D3DXVECTOR2(NAME_STARTPOS.x, NAME_STARTPOS.y));
    }

    //入力された文字の描画
    Text->Draw_Text(m_UserName, WriteText::InputName, D3DXVECTOR2(NAME_STARTPOS.x, NAME_STARTPOS.y));
}

//名前入力処理
void CLoginScene::InputName()
{
    CKeyManager* KeyMng = &CKeyManager::GetInstance();

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

