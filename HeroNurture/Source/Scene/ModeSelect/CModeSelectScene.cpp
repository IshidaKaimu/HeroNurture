#include "CModeSelectScene.h"
#include "Scene\CSceneManager.h"
#include "KeyManager\CKeyManager.h"
#include "StaticMesh\MeshManager\CMeshManager.h"
#include "Sound\CSoundManager.h"
#include <cmath>
#include "ImGui\ImGuiManager\ImGuiManager.h"
#include "Json\CJson.h"
#include "Utility\CUtility.h"
#include "Sprite2D\UIManager\CUIManager.h" 
//定数の名前空間
using namespace Constant_ModeSelectScene;

CModeSelectScene::CModeSelectScene()
{
    //ライト情報
    m_Light.vDirection = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //ライト方向
}

CModeSelectScene::~CModeSelectScene()
{
}

void CModeSelectScene::Create()
{
    //----UI----
    m_pNatureMode = std::make_unique<CUIObject>(); //育成モード
    m_pBattleMode = std::make_unique<CUIObject>(); //バトルモード
    m_pCover      = std::make_unique<CUIObject>(); //カバー
}

void CModeSelectScene::Releace()
{
}

void CModeSelectScene::LoadData()
{   
    //----UI----
    m_pNatureMode->AttachSprite(CUIManager::GetSprite(CUIManager::ModeSelectLeft));
    m_pBattleMode->AttachSprite(CUIManager::GetSprite(CUIManager::ModeSelectRight));
    m_pCover->AttachSprite(CUIManager::GetSprite(CUIManager::ModeSelectCover));
}

void CModeSelectScene::Initialize()
{
}

//更新関数
void CModeSelectScene::Update()
{
    CKeyManager* KeyMng = &CKeyManager::GetInstance();
    CSceneManager* SceneMng = CSceneManager::GetInstance();

    //フェードイン処理
    if (!FadeIn()) { return; }

    //タイトルBGM、戦闘結果BGMの停止
    CSoundManager::GetInstance()->Stop(CSoundManager::BGM_Title);
    CSoundManager::GetInstance()->Stop(CSoundManager::BGM_NatureResult);
    CSoundManager::GetInstance()->Stop(CSoundManager::BGM_Win);
    CSoundManager::GetInstance()->Stop(CSoundManager::BGM_Lose);

    //モード選択BGMの再生
    CSoundManager::GetInstance()->PlayLoop(CSoundManager::BGM_ModeSelect);
    CSoundManager::GetInstance()->Volume(CSoundManager::BGM_ModeSelect, 40);


    //キーマネージャーの更新
    KeyMng->Update();

    //カーソルの移動
    if (KeyMng->IsDown(VK_RIGHT))
    {
        //選択SEの再生
        CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Select);
        CSoundManager::GetInstance()->Volume(CSoundManager::SE_Select, 40);

        //キー入力で選択を進める
        if (m_SelectNo < enModeList::Max-1) { m_SelectNo++; }
        else { m_SelectNo = 0; }
    }
    else if (KeyMng->IsDown(VK_LEFT))
    {
        //選択SEの再生
        CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Select);
        CSoundManager::GetInstance()->Volume(CSoundManager::SE_Select, 40);

        if (m_SelectNo > 0) { m_SelectNo--; }
        else { m_SelectNo = enModeList::Max-1; }
    }



    //シーン遷移(仮)
    if (CKeyManager::GetInstance().IsDown(VK_RETURN))
    {
        //決定SEの再生
        CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Enter);
        CSoundManager::GetInstance()->Volume(CSoundManager::SE_Enter, 40);

        //オープニングシーンへ
        m_SceneTransitionFlg = true;
    }

    //フェードアウト処理
    if (m_SceneTransitionFlg && FadeOut())
    {
        switch (m_SelectNo)
        {
        case 0:
            SceneMng->LoadCreate(CSceneManager::NatureHeroSelect);           //育成モード
            break;
        case 1:
            SceneMng->LoadCreate(CSceneManager::BattleHeroSelect); //バトルモード
            break;
        default:
            break;
        }
    }
}

void CModeSelectScene::Draw()
{
    //UIの描画
    DrawUI();
}

//モード選択画面の描画
void CModeSelectScene::DrawUI()
{
    WriteText* Text = WriteText::GetInstance();

    //----各UIの設定----
    //育成モード
    m_pNatureMode->SetPosition(NATUREMODE_POS);         //位置
    m_pNatureMode->SetScale(MODE_SCALE);                //拡縮
    m_pNatureMode->SetDisplay(MODE_DISP.x,MODE_DISP.y); //幅
    m_pNatureMode->SetAlpha(MODE_ALPHA);                //α値
    //バトルモード
    m_pBattleMode->SetPosition(BATTLEMODE_POS);         //位置
    m_pBattleMode->SetScale(MODE_SCALE);                //拡縮
    m_pBattleMode->SetDisplay(MODE_DISP.x,MODE_DISP.y); //幅
    m_pBattleMode->SetAlpha(MODE_ALPHA);                //α値

    //選択されていない方に被せる画像
    //位置
    switch (m_SelectNo)
    {
    case 0:
        m_pCover->SetPosition(BATTLEMODE_POS);
        break;
    case 1:
        m_pCover->SetPosition(NATUREMODE_POS);
        break;
    default:
        break;
    }

    m_pCover->SetScale(MODE_SCALE);               //拡縮
    m_pCover->SetDisplay(MODE_DISP.x,MODE_DISP.y);//幅
    m_pCover->SetAlpha(COVER_ALPHA);              //α値

    CSceneManager::GetInstance()->GetDx11()->SetDepth(false);
    //育成モード描画
    m_pNatureMode->Draw();
    //バトルモード描画
    m_pBattleMode->Draw();
    //選択されていない方に被せる画像
    m_pCover->Draw();
    //シーン名の描画
    Text->Draw_Text(L"MODE SELECT", WriteText::Normal, SCENENAME_POS);
    CSceneManager::GetInstance()->GetDx11()->SetDepth(true);
}
