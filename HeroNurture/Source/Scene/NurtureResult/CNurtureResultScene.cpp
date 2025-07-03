#include "Scene\NurtureResult\CNurtureResultScene.h"
#include "Scene\CSceneManager.h"
#include "ModeManager\Nurture\CNurtureManager.h"
#include "KeyManager\CKeyManager.h"
#include "Sprite2D\UIManager\CUIManager.h"
#include "SkinMesh\SkinMeshManager\CSkinMeshManager.h"
#include "Sound\CSoundManager.h"
#include "ImGui\ImGuiManager\ImGuiManager.h"
#include "Camera\CameraManager\CCameraManager.h"
#include "SkinMeshObject\Hero\CHeroManager.h"
#include "Json\CJson.h"
#include "Utility\CUtility.h"
#include "Rank\CRank.h"
#include <cmath>
#include <fstream>
#include <sstream>

//定数の名前空間
using namespace Constant_NurtureResultScene;

CNurtureResultScene::CNurtureResultScene()
    : m_pCamera(&CCameraManager::GetInstance())
    , m_pParamList  ()
    , m_pJson       ()
    , m_ResultWriter()
{
}

CNurtureResultScene::~CNurtureResultScene()
{
}

//構築関数
void CNurtureResultScene::Create()
{
    //パラメータ背景UIのインスタンス生成
    m_pParamList = std::make_unique<CUIObject>();
}

//データ設定関数
void CNurtureResultScene::LoadData()
{
    CHeroManager* HeroMng = &CHeroManager::GetInstance();

    //セットされたヒーローのメッシュ設定
    HeroMng->LoadMeshData();

    //パラメータの背景のスプライト設定
    m_pParamList->AttachSprite(CUIManager::GetSprite(CUIManager::ResultParamList));
}

//破棄関数
void CNurtureResultScene::Releace()
{
}

//初期化関数
void CNurtureResultScene::Initialize()
{
    CHeroManager* HeroMng = &CHeroManager::GetInstance();

    //セットされているヒーローの初期化
    HeroMng->Initialize();

    //パラメータ背景UI情報の初期化
    m_pParamList->SetPosition(PARAMBACK_POS);
    m_pParamList->SetScale(PARAMBACK_SCALE);
    m_pParamList->SetAlpha(1.0f);
    m_pParamList->SetDisplay(1.0f,1.0f);

    //カメラ位置の設定
    m_pCamera->SetPos(CAMPOS);
    //カメラ注視点の設定
    m_pCamera->SetLook(CAMLOOK);
}

//更新関数
void CNurtureResultScene::Update()
{
    CKeyManager*     KeyMng     = &CKeyManager::GetInstance();
    CHeroManager*    HeroMng    = &CHeroManager::GetInstance();
    CSceneManager*   SceneMng   = &CSceneManager::GetInstance();
    CNurtureManager* NurtureMng = &CNurtureManager::GetInstance();


    //フェードイン処理
    if (!FadeIn()) { return; }

    //モード選択画面のBGM停止
    CSoundManager::GetInstance()->Stop(CSoundManager::BGM_Nurture);

    //育成結果BGMの再生
    CSoundManager::GetInstance()->PlayLoop(CSoundManager::BGM_NurtureResult);
    CSoundManager::GetInstance()->Volume(CSoundManager::BGM_NurtureResult, BGM_VOLUME);


    //キーマネージャの動作処理
    KeyMng->Update();

    //シーン遷移(仮)
    if (CKeyManager::GetInstance().IsDown(VK_RETURN))
    {
        //決定SEの再生
        CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Enter);
        CSoundManager::GetInstance()->Volume(CSoundManager::SE_Enter, SE_VOLUME);

        //オープニングシーンへ
        m_SceneTransitionFlg = true;
    }

    //フェードアウト処理
    if (m_SceneTransitionFlg && FadeOut())
    {
        NurtureMng->SetIsDataLoaded(false);
        m_pJson->SaveResult(HeroMng->GetSelectHeroName(), m_ResultWriter);
        SceneMng->LoadCreate(CSceneManager::ModeSelect);
    }
}

//描画関数
void CNurtureResultScene::Draw()
{
    WriteText*    Text = WriteText::GetInstance();
    CHeroManager* Hero = &CHeroManager::GetInstance();

    //カメラの動作
    m_pCamera->CameraUpdate();


    CSceneManager::GetInstance().GetDx11()->SetDepth(false);

    //汎用背景の描画
    DrawBasicBackGround();

    //育成結果の描画
    DrawResult();

    CSceneManager::GetInstance().GetDx11()->SetDepth(true);

    //セットされたヒーローの描画
    Hero->Draw();

    //操作方法指示バーの描画
    DrawControlBar(false);
    //操作方法指示「Enter モード選択へ」テキストの描画
    Text->Draw_Text(L"Enter モード選択へ", WriteText::Control, ENTERTEXT_POS);

    //デバッグ処理
    Debug();
}

//デバッグ処理
void CNurtureResultScene::Debug()
{
#ifdef DEBUG 
    ImGui::Begin(JAPANESE("カメラ"));
    ImGui::InputFloat3(JAPANESE("カメラ座標"), m_CamPos);
    ImGui::InputFloat3(JAPANESE("注視点"), m_CamLook);
    CCameraManager::GetInstance().SetPos(m_CamPos);
    CCameraManager::GetInstance().SetLook(m_CamLook);
    ImGui::End();
#endif
}

//育成結果の描画
void CNurtureResultScene::DrawResult()
{
    WriteText*    Text    = WriteText::GetInstance();
    CHeroManager* HeroMng = &CHeroManager::GetInstance();

    //「育成ランク」テキストの描画
    std::wstring ResultText = L"育成ランク";
    Text->Draw_Text(ResultText, WriteText::Normal, RESULTTEXT_POS, false, true);

    //パラメータの背景の描画
    m_pParamList->Draw();

    //各パラメータの値、ランクの描画
    DrawParamUI(HeroMng->GetParam().Power, 0);
    DrawParamUI(HeroMng->GetParam().Magic, 1);
    DrawParamUI(HeroMng->GetParam().Speed, 2);
    DrawParamUI(HeroMng->GetParam().Hp, 3);

    //ランクの描画
    CRank::GetInstance().DrawRank(ParamTotal(), 1, RANK_POS);
}

//パラメータの合計値
float CNurtureResultScene::ParamTotal()
{
    //セット中のヒーローのステータスを変数に代入
    CHeroManager::enParam HeroParam = CHeroManager::GetInstance().GetParam();

    //ステータスの合計を計算、代入
    float Total = HeroParam.Power + HeroParam.Magic + HeroParam.Speed + HeroParam.Hp;

    return Total;
}

//パラメータUIの描画
void CNurtureResultScene::DrawParamUI(float paramvalue, int no)
{
    WriteText* Text    = WriteText::GetInstance();
    CRank*     Rank    = &CRank::GetInstance();
    CUtility*  Utility = &CUtility::GetInstance();

    //----各パラメータのUIの描画(背景,値,ランク)----
    Text->Draw_Text(std::to_wstring(static_cast<int>(paramvalue)), WriteText::Normal, Utility->PosCorrection(static_cast<int>(paramvalue),3,D3DXVECTOR2(PARAMVALUE_POS.x, PARAMVALUE_POS.y + (PARAMVALUE_INTERVAL* no))));
    Rank->DrawRank(paramvalue, 2, D3DXVECTOR2(PARAMRANK_POS.x, PARAMRANK_POS.y + (PARAMRANK_INTERVAL * no)));
}
