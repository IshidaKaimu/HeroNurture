#include "Scene\TraningResult\CTraningResultScene.h"
#include "Scene\CSceneManager.h"
#include "KeyManager\CKeyManager.h"
#include "Sprite2D\UIManager\CUIManager.h"
#include "SkinMesh\SkinMeshManager\CSkinMeshManager.h"
#include "Sound\CSoundManager.h"
#include "ImGui\ImGuiManager\ImGuiManager.h"
#include "Camera\CameraManager\CCameraManager.h"
#include "SkinMeshObject\Hero\CHeroManager.h"
#include <cmath>
#include <fstream>
#include <sstream>


CTraningResultScene::CTraningResultScene()
    : m_pCamera(&CCameraManager::GetInstance())
    , m_pPowerParam()
    , m_pMagicParam()
    , m_pSpeedParam()
    , m_pHpParam   ()
{
}

CTraningResultScene::~CTraningResultScene()
{
}

//構築関数
void CTraningResultScene::Create()
{
    //各パラメータ背景UIのインスタンス生成
    m_pPowerParam = std::make_unique<CUIObject>();
    m_pMagicParam = std::make_unique<CUIObject>();
    m_pSpeedParam = std::make_unique<CUIObject>();
    m_pHpParam    = std::make_unique<CUIObject>();
}

//データ設定関数
void CTraningResultScene::LoadData()
{
    //----クラスのインスタンスを変数に代入----
    //ヒーローマネージャー
    CHeroManager* Hero = &CHeroManager::GetInstance();

    //セットされたヒーローのメッシュ設定
    Hero->LoadMeshData();

    //----各パラメータのUIのスプライト設定----
    //筋力
    //m_pPowerParam->AttachSprite(CUIManager::GetSprite(CUIManager::PowerParam));
    ////魔力
    //m_pMagicParam->AttachSprite(CUIManager::GetSprite(CUIManager::MagicParam));
    ////素早さ
    //m_pSpeedParam->AttachSprite(CUIManager::GetSprite(CUIManager::SpeedParam));
    ////体力
    //m_pHpParam->AttachSprite(CUIManager::GetSprite(CUIManager::HpParam));

}

//破棄関数
void CTraningResultScene::Releace()
{
}

//初期化関数
void CTraningResultScene::Initialize()
{
    //ヒーローマネージャのインスタンスを変数に代入
    CHeroManager* Hero = &CHeroManager::GetInstance();

    //セットされているヒーローの初期化
    Hero->Initialize();

    //各パラメータ背景UIの初期化
    ParamBackUIInit(m_pPowerParam,1);
    ParamBackUIInit(m_pMagicParam,2);
    ParamBackUIInit(m_pSpeedParam,3);
    ParamBackUIInit(m_pHpParam,4);

    //カメラ位置の設定
    m_pCamera->SetPos(RESULT_CAMPOS);
    //カメラ注視点の設定
    m_pCamera->SetLook(RESULT_CAMLOOK);
}

//更新関数
void CTraningResultScene::Update()
{
    //フェードイン処理
    if (!FadeIn()) { return; }

    //----クラスのインスタンスを変数に代入----
    //キーマネージャー
    CKeyManager* KeyMng = CKeyManager::GetInstance();
    //ヒーローマネージャー
    CHeroManager* Hero = &CHeroManager::GetInstance();

    //キーマネージャの動作処理
    KeyMng->Update();

    //カーソルの移動
    if (KeyMng->IsDown(VK_RIGHT))
    {
        //キー入力で選択を進める
        if (m_SelectNo < CHeroBase::enCharacterList::max - 1) { m_SelectNo++; }
        else { m_SelectNo = 0; }
    }
    else if (KeyMng->IsDown(VK_LEFT))
    {
        if (m_SelectNo > 0) { m_SelectNo--; }
        else { m_SelectNo = 1; }
    }

    //シーン遷移(仮)
    if (CKeyManager::GetInstance()->IsDown(VK_RETURN))
    {
        //オープニングシーンへ
        m_SceneTransitionFlg = true;
    }

    //フェードアウト処理
    if (m_SceneTransitionFlg && FadeOut())
    {
        CSceneManager::GetInstance()->LoadCreate(CSceneManager::HeroSelect);
    }
}

//描画関数
void CTraningResultScene::Draw()
{
    //----クラスのインスタンスを変数に代入----
    //ヒーローマネージャー
    CHeroManager* Hero = &CHeroManager::GetInstance();

    //カメラの動作
    m_pCamera->CameraUpdate();

    //セットされたヒーローの描画
    Hero->Draw();

    //育成結果の描画
    DrawResult();

    //デバッグ処理
    Debug();
}

//デバッグ処理
void CTraningResultScene::Debug()
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
void CTraningResultScene::DrawResult()
{
    //----クラスのインスタンスを変数に代入----
    //テキスト描画クラス
    WriteText* Text = WriteText::GetInstance();
    //ヒーローマネージャー
    CHeroManager* HeroMng = &CHeroManager::GetInstance();

    //「最終評価」テキスト
    std::wstring ResultText = L"最終評価";

    Text->Draw_Text(ResultText, WriteText::Normal, D3DXVECTOR2(900.0f, 0.0f), false, true);

    //----各パラメータのUIの描画----
    //筋力
    DrawParamUI(m_pPowerParam,HeroMng->GetParam().Power,1);
    //魔力
    DrawParamUI(m_pMagicParam,HeroMng->GetParam().Magic,2);
    //素早さ
    DrawParamUI(m_pSpeedParam,HeroMng->GetParam().Speed,3);
    //体力
    DrawParamUI(m_pHpParam,HeroMng->GetParam().Hp,4);

    //ランクの描画
    CUtility::GetInstance().DrawRank(ParamTotal(), 1, RANK_POSX, RANK_POSY);
}

//パラメータの合計値
float CTraningResultScene::ParamTotal()
{
    //セット中のヒーローのステータスを変数に代入
    CHeroManager::enParam HeroParam = CHeroManager::GetInstance().GetParam();

    //ステータスの合計を計算、代入
    float Total = HeroParam.Power + HeroParam.Magic + HeroParam.Speed + HeroParam.Hp;

    return Total;
}

//パラメータUIの初期設定
void CTraningResultScene::ParamBackUIInit(std::unique_ptr<CUIObject>& param, int no)
{
    //位置
    param->SetPosition(PARAMBACK_POSX, PARAMBACK_POSY * no/4, 0.0f);
    //拡縮
    param->SetScale(PARAMBACK_SCALE);
    //α値
    param->SetAlpha(1.0f);
    //幅、高さ
    param->SetDisplay(1.0f, 1.0f);
}

//パラメータUIの描画
void CTraningResultScene::DrawParamUI(std::unique_ptr<CUIObject>& param, float paramvalue, int no)
{
    //----クラスのインスタンスを変数に代入----
    //テキスト描画クラス
    WriteText* Text = WriteText::GetInstance();
    //汎用クラス
    CUtility* Utility = &CUtility::GetInstance();

    //----各パラメータのUIの描画(背景,値,ランク)----
    param->Draw();
    Text->Draw_Text(std::to_wstring(static_cast<int>(paramvalue)), WriteText::Normal, D3DXVECTOR2(0.0f, 200.0f * no));
    Utility->DrawRank(paramvalue, 2,PARAMBACK_POSX,PARAMBACK_POSY * no/4);
}

