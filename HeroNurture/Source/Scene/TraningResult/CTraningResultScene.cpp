#include "Scene\TraningResult\CTraningResultScene.h"
#include "Scene\CSceneManager.h"
#include "KeyManager\CKeyManager.h"
#include "Sprite2D\UIManager\CUIManager.h"
#include "SkinMesh\SkinMeshManager\CSkinMeshManager.h"
#include "Sound\CSoundManager.h"
#include "ImGui\ImGuiManager\ImGuiManager.h"
#include "Camera\CameraManager\CCameraManager.h"
#include "SkinMeshObject\Hero\CHeroManager.h"
#include "Json\CJson.h"
#include <cmath>
#include <fstream>
#include <sstream>


CTraningResultScene::CTraningResultScene()
    : m_pCamera(&CCameraManager::GetInstance())
    , m_pParamList  ()
    , m_pJson       ()
    , m_ResultWriter()
{
}

CTraningResultScene::~CTraningResultScene()
{
}

//構築関数
void CTraningResultScene::Create()
{
    //パラメータ背景UIのインスタンス生成
    m_pParamList = std::make_unique<CUIObject>();
}

//データ設定関数
void CTraningResultScene::LoadData()
{
    //----クラスのインスタンスを変数に代入----
    //ヒーローマネージャー
    CHeroManager* HeroMng = &CHeroManager::GetInstance();
    //UIマネージャー
    CUIManager* UIMng = CUIManager::GetInstance();

    //セットされたヒーローのメッシュ設定
    HeroMng->LoadMeshData();

    //パラメータの背景のスプライト設定
    m_pParamList->AttachSprite(CUIManager::GetSprite(CUIManager::ResultParamList));
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

    //パラメータ背景UI情報の初期化
    m_pParamList->SetPosition(PARAMBACK_POSX_TR,PARAMBACK_POSY_TR,0.0);
    m_pParamList->SetScale(PARAMBACK_SCALE_TR);
    m_pParamList->SetAlpha(1.0f);
    m_pParamList->SetDisplay(1.0f,1.0f);

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
    CHeroManager* HeroMng = &CHeroManager::GetInstance();

    //キーマネージャの動作処理
    KeyMng->Update();

    //育成結果を保存するファイルの階層
    std::string SaveHierarchy = "Data\\Hero\\Result\\";

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
        CSceneManager::GetInstance()->SetIsDataLoaded(false);
        m_pJson->SaveNatureData(HeroMng->GetHeroName(), m_ResultWriter, SaveHierarchy);
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

    //「最終評価」テキストの描画
    std::wstring ResultText = L"最終評価";
    Text->Draw_Text(ResultText, WriteText::Normal, RESULTTEXT_POS, false, true);

    //パラメータの背景の描画
    m_pParamList->Draw();

    //各パラメータの値、ランクの描画
    DrawParamUI(HeroMng->GetParam().Power, 0);
    DrawParamUI(HeroMng->GetParam().Magic, 1);
    DrawParamUI(HeroMng->GetParam().Speed, 2);
    DrawParamUI(HeroMng->GetParam().Hp, 3);


    //ランクの描画
    CUtility::GetInstance().DrawRank(ParamTotal(), 1, RANK_POSX, RANK_POSY_TR);
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

//パラメータUIの描画
void CTraningResultScene::DrawParamUI(float paramvalue, int no)
{
    //----クラスのインスタンスを変数に代入----
    //テキスト描画クラス
    WriteText* Text = WriteText::GetInstance();
    //汎用クラス
    CUtility* Utility = &CUtility::GetInstance();

    //----各パラメータのUIの描画(背景,値,ランク)----
    Text->Draw_Text(std::to_wstring(static_cast<int>(paramvalue)), WriteText::Normal, D3DXVECTOR2(PARAMVALUE_POSX_TR, PARAMVALUE_POSY_TR + (PARAMVALUE_INTERVAL_TR* no)));
    Utility->DrawRank(paramvalue, 2, PARAMRANK_POSX_TR, PARAMRANK_POSY_TR + (PARAMRANK_INTERVAL_TR * no));
}
