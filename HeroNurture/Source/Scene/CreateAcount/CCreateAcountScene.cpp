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
{
}

CCreateAcountScene::~CCreateAcountScene()
{
}

void CCreateAcountScene::Create()
{
    //----UI----
    m_pNameSpace = std::make_unique<CUIObject>();
}

void CCreateAcountScene::Releace()
{
}

void CCreateAcountScene::LoadData()
{
    m_pNameSpace->AttachSprite(CUIManager::GetSprite(CUIManager::NameSpace));
}

void CCreateAcountScene::Initialize()
{
    //名前入力スペースの位置初期化
    m_pNameSpace->SetPosition(NAMESPACE_POS.x, NAMESPACE_POS.y, NAMESPACE_POS.z);
    //名前入力スペースのスケール初期化
    m_pNameSpace->SetScale(NAMESPACE_SCALE.x, NAMESPACE_SCALE.y, NAMESPACE_SCALE.z);
    //名前入力スペースの幅初期化
    m_pNameSpace->SetDisplay(NAMESPACE_DISP.x, NAMESPACE_DISP.y);
}

void CCreateAcountScene::Update()
{
    //フェードイン処理
    if (!FadeIn()) { return; }

    CKeyManager* KeyMng = &CKeyManager::GetInstance();
    CSceneManager* SceneMng = CSceneManager::GetInstance();

    //リアルタイム入力処理
    CUtility::GetInstance().InputText(m_UserName,NAME_MAXLENGTH);

    //コピー元フォルダのパス
    m_SorceDir = "Data\\Acount\\Hero";
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
            }

            //オープニングシーンへ
            m_SceneTransitionFlg = true;
        }
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

