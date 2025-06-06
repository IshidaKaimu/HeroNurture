#include "CNurtureScene.h"
#include "ImGui\ImGuiManager\ImGuiManager.h"
#include "Scene\CSceneManager.h"
#include "ModeManager\Nurture\CNurtureManager.h"
#include "SkinMesh\SkinMeshManager\CSkinMeshManager.h"
#include "Camera\CameraManager\CCameraManager.h"
#include "Light\LightManager\CLightManager.h"
#include "SkinMeshObject\Hero\CHeroManager.h"
#include "StaticMesh\MeshManager\CMeshManager.h"
#include "Sprite2D\UIManager\CUIManager.h"
#include "KeyManager\CKeyManager.h"
#include "WriteText\WriteText.h"
#include "Utility\CUtility.h"
#include "Rank\CRank.h"
#include "Sound\CSoundManager.h"

//定数の名前空間
using namespace Constant_NurtureScene;


CNurtureScene::CNurtureScene()
    : m_pCamera      ( &CCameraManager::GetInstance() )
    , m_Name         ()
    , m_pGround      ()
    , m_pParamBack   ()
    , m_pPowerTraning()
    , m_pMagicTraning()
    , m_pSpeedTraning()
    , m_pHpTraning   ()
    , m_pRest        ()
    , m_pStaminaGage ()
    , m_pStaminaBack ()
    , m_pStaminaFrame()
    , m_pTurnBack    ()
    , m_pSafeBack    ()
    , m_pAnxietyBack ()
    , m_pDangerBack  ()
    , m_GageWidth    ( CNurtureManager::GetInstance().GetStaminaWidth() )
    , m_pJson        ()
    , m_ParamWriter  ()
    , m_ParamData    ()
{
}

CNurtureScene::~CNurtureScene()
{
}

void CNurtureScene::Create()
{
    CHeroManager* HeroMng = &CHeroManager::GetInstance();

    //セットされたヒーローのクラスのインスタンス生成
    switch (HeroMng->GetSelectHero())
    {
    case CHeroManager::Yui:
        //ユイ
        HeroMng->CreateHero(CHeroManager::Yui);
        //ファイルの作成、読み込み
        LoadHeroData(m_Name.Yui);
        break;
    case CHeroManager::Kaito:
        //カイト
        HeroMng->CreateHero(CHeroManager::Kaito);
        //ファイルの作成、読み込み
        LoadHeroData(m_Name.Kaito);
        break;
    default:
        break;
    }
    
    //----スタティックメッシュオブジェクト----
    //地面
    m_pGround = std::make_unique<CGround>();

    //----UIオブジェクト----
    //パラメータの背景
    m_pParamBack = std::make_unique<CUIObject>();
    //各種トレーニングUI
    m_pPowerTraning = std::make_unique<CUIObject>();
    m_pMagicTraning = std::make_unique<CUIObject>();
    m_pSpeedTraning = std::make_unique<CUIObject>();
    m_pHpTraning    = std::make_unique<CUIObject>();
    m_pRest         = std::make_unique<CUIObject>();
    //失敗率背景
    m_pSafeBack     = std::make_unique<CUIObject>();
    m_pAnxietyBack  = std::make_unique<CUIObject>();
    m_pDangerBack   = std::make_unique<CUIObject>();

    //育成関連のシーンで共通して表示するUIのインスタンス生成
    CreateNurtureUI(m_pStaminaGage,m_pStaminaBack,m_pStaminaFrame,m_pTurnBack);
}

void CNurtureScene::Releace()
{
    //----破棄----
    //カメラ
    m_pCamera = nullptr;
}

void CNurtureScene::LoadData()
{   
    //セットされたヒーローのクラスのメッシュデータの読み込み
    CHeroManager::GetInstance().LoadMeshData();

    CHeroManager::GetInstance().LoadParamData(m_ParamData);

    //地面のメッシュデータ設定
    m_pGround->LoadData();

    //パラメータの背景UIのスプライト設定
    m_pParamBack->AttachSprite(CUIManager::GetSprite(CUIManager::ParamList));
    //各種トレーニングUIのスプライト設定
    m_pPowerTraning->AttachSprite(CUIManager::GetSprite(CUIManager::PowerTraning));
    m_pMagicTraning->AttachSprite(CUIManager::GetSprite(CUIManager::MagicTraning));
    m_pSpeedTraning->AttachSprite(CUIManager::GetSprite(CUIManager::SpeedTraning));
    m_pHpTraning   ->AttachSprite(CUIManager::GetSprite(CUIManager::HpTraning));
    m_pRest        ->AttachSprite(CUIManager::GetSprite(CUIManager::Rest));
    //各失敗率背景のスプライト設定
    m_pSafeBack->AttachSprite(CUIManager::GetSprite(CUIManager::Safe));
    m_pAnxietyBack->AttachSprite(CUIManager::GetSprite(CUIManager::Anxiety));
    m_pDangerBack->AttachSprite(CUIManager::GetSprite(CUIManager::Danger));

    //スタミナゲージのUIのスプライト設定
    LoadNurtureUI(m_pStaminaGage, m_pStaminaBack,m_pStaminaFrame, m_pTurnBack);
}

void CNurtureScene::Initialize()
{
    CHeroManager* HeroMng = &CHeroManager::GetInstance();

    //セットされたヒーローのクラスの初期化
    HeroMng->Initialize();

    //各ヒーローのカメラ位置、カメラの注視点の設定
    switch (HeroMng->GetSelectHero())
    {
    case CHeroManager::Yui:
        //ユイ
        m_pCamera->SetPos (CAMERAPOS_YUI);
        m_pCamera->SetLook(CAMERALOOK_YUI);
        break;
    case CHeroManager::Kaito:
        //カイト
        m_pCamera->SetPos (CAMERAPOS_KAITO);
        m_pCamera->SetLook(CAMERALOOK_KAITO);
        break;
    default:
        break;
    }

    //----ライト情報----
    //位置
    m_Light.Position   = D3DXVECTOR3(LIGHT_POS);
    //向き
    m_Light.vDirection = D3DXVECTOR3(LIGHT_DIR); 
   
    //----パラメータの値を除くUIの初期設定----
    //パラメータの背景
    UIInit(m_pParamBack, PARAMBACK_POS, 0, PARAMBACK_SCALE, 0);
    //各種トレーニング
    UIInit(m_pPowerTraning, TRANING_POS, 0, TRANING_SCALE, 0);                //筋力
    UIInit(m_pMagicTraning, TRANING_POS, TRANING_INTERVAL, TRANING_SCALE, 1); //魔力
    UIInit(m_pSpeedTraning, TRANING_POS, TRANING_INTERVAL, TRANING_SCALE, 2); //素早さ
    UIInit(m_pHpTraning,    TRANING_POS, TRANING_INTERVAL, TRANING_SCALE, 3); //体力
    UIInit(m_pRest,         TRANING_POS, TRANING_INTERVAL, TRANING_SCALE, 4); //休息
    //各失敗率背景
    FailureRateBackInit(m_pSafeBack,D3DXVECTOR3(20.0f,400.0f,0.0f));
    FailureRateBackInit(m_pAnxietyBack,D3DXVECTOR3(20.0f,400.0f,0.0f));
    FailureRateBackInit(m_pDangerBack,D3DXVECTOR3(20.0f,400.0f,0.0f));


    //育成関連のシーンで共通のUIの初期化
    InitNurtureUI(m_pStaminaGage,m_pStaminaBack,m_pStaminaFrame, m_pTurnBack);
}

void CNurtureScene::Update()
{
    CKeyManager*     KeyMng     = &CKeyManager::GetInstance();
    CHeroManager*    HeroMng    = &CHeroManager::GetInstance();
    CSceneManager*   SceneMng   = &CSceneManager::GetInstance();
    CNurtureManager* NurtureMng = &CNurtureManager::GetInstance();

    //フェードイン処理
    if (!FadeIn()) { return; }

    //モード選択画面のBGM停止
    CSoundManager::GetInstance()->Stop(CSoundManager::BGM_NurtureHeroSelect);

    //育成BGMの再生
    CSoundManager::GetInstance()->PlayLoop(CSoundManager::BGM_Nurture);
    CSoundManager::GetInstance()->Volume(CSoundManager::BGM_Nurture, 40);

    //セットされたヒーローのクラスの更新
    HeroMng->Update();

    //キーマネージャーの更新処理
    CKeyManager::GetInstance().Update();

    //カーソルの移動
    if (KeyMng->IsDown(VK_RIGHT))
    {
        //選択SEの再生
        CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Select);
        CSoundManager::GetInstance()->Volume(CSoundManager::SE_Select, 40);

        //キー入力で選択を進める
        if (m_SelectNo < CHeroManager::enTraningList::Max_T-1) { m_SelectNo++; }
        else { m_SelectNo = 0; }
    }
    else if (KeyMng->IsDown(VK_LEFT))
    {
        //選択SEの再生
        CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Select);
        CSoundManager::GetInstance()->Volume(CSoundManager::SE_Select, 40);

        if (m_SelectNo > 0) { m_SelectNo--; }
        else { m_SelectNo = 4; }
    }

    //セットされたヒーローのクラスのアニメーション
    HeroMng->NurtureAnimation(m_SelectNo);


    //トレーニングの決定
    if (KeyMng->IsDown(VK_RETURN) && !m_SceneTransitionFlg)
    {
        //決定SEの再生
        CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Enter);
        CSoundManager::GetInstance()->Volume(CSoundManager::SE_Enter, 40);

        m_SceneTransitionFlg = true;

        //選択肢の位置に応じたトレーニングをセット
        switch (m_SelectNo)
        {
        case 0:  HeroMng->SetTraning(CHeroManager::PowerTraining); break;
        case 1:  HeroMng->SetTraning(CHeroManager::MagicTraining); break;
        case 2:  HeroMng->SetTraning(CHeroManager::SpeedTraining); break;
        case 3:  HeroMng->SetTraning(CHeroManager::HpTraining); break;
        case 4:  HeroMng->SetTraning(CHeroManager::Rest); break;
        }

    }

    if (NurtureMng->GetRemainingTurn() <= 0) 
    {
        m_SceneTransitionFlg = true;
    }

    //フェードが終わったら
    if (m_SceneTransitionFlg && FadeOut())
    {
        if (NurtureMng->GetRemainingTurn() > 0)
        {
            //パラメータ処理
            SelectTraning();
            SceneMng->LoadCreate(CSceneManager::Training);
        }
        else
        {
            SceneMng->LoadCreate(CSceneManager::NurtureResult);
        }
    }

    //デバッグ処理
    Debug();
}

void CNurtureScene::Draw()
{
    CHeroManager*  HeroMng  = &CHeroManager::GetInstance();
    CSceneManager* SceneMng = &CSceneManager::GetInstance();
    WriteText*     Text     = WriteText::GetInstance();

    //カメラの更新処理
    m_pCamera->CameraUpdate();

    //セットされたヒーローのクラスの描画
    HeroMng->Draw();

    //地面クラスの描画
    m_pGround->Draw();

    //空の描画
    DrawSky();

    //深度を無視する
    SceneMng->GetDx11()->SetDepth(false);

    //育成関連シーンで共通のUIの描画
    DrawNurtureUI(m_pStaminaGage, m_pStaminaBack, m_pStaminaFrame,m_pTurnBack);

    //各トレーニングの描画
    DrawTraning();

    //各パラメータUIの描画
    DrawParam();

    //失敗率の取得
    int FailureRate = 100 - HeroMng->GetSuccessRate(HeroMng->GetStamina());
    //失敗率に応じた背景の描画
    if (FailureRate <= SAFE) { m_pSafeBack->Draw(); }
    if (FailureRate > SAFE && FailureRate <= ANXIETY) { m_pAnxietyBack->Draw(); }
    if (FailureRate > ANXIETY) { m_pDangerBack->Draw(); }
    //「失敗率」テキスト描画
    Text->Draw_Text(L"失敗率", WriteText::Select, D3DXVECTOR2(FAILURETEXT_POS));
    //失敗率の描画
    Text->Draw_Text(std::to_wstring(FailureRate) + L"%", WriteText::Select, D3DXVECTOR2(FAILURERATE_POS));

    //深度を戻す
    SceneMng->GetDx11()->SetDepth(true);
}

void CNurtureScene::Debug()
{
#ifdef DEBUG 
    ImGui::Begin(JAPANESE("カメラ"));
    ImGui::InputFloat3(JAPANESE("カメラ座標"), m_CamPos);
    ImGui::InputFloat3(JAPANESE("注視点"), m_CamLook);
    CCameraManager::GetInstance().SetPos(m_CamPos);
    CCameraManager::GetInstance().SetLook(m_CamLook);
    ImGui::End();
#endif

#ifdef DEBUG 
    ImGui::Begin(JAPANESE("パラメータ"));
    ImGui::Text(JAPANESE("筋力:%f"), HeroMng->GetParam().Power);
    ImGui::Text(JAPANESE("魔力:%f"), HeroMng->GetParam().Magic);
    ImGui::Text(JAPANESE("素早さ:%f"), HeroMng->GetParam().Speed);
    ImGui::Text(JAPANESE("体力:%f"), HeroMng->GetParam().Hp);
    ImGui::Text(JAPANESE("スタミナ:%f"), HeroMng->GetStamina());
    ImGui::Text(JAPANESE("スタミナの幅:%f"), CSceneManager::GetInstance()->GetStaminaWidth());
    ImGui::End();

    ImGui::Begin(JAPANESE("トレーニング選択状況"));
    if (m_SelectNo == 0) { ImGui::Text(JAPANESE("筋力")); }
    if (m_SelectNo == 1) { ImGui::Text(JAPANESE("魔力")); }
    if (m_SelectNo == 2) { ImGui::Text(JAPANESE("素早さ")); }
    if (m_SelectNo == 3) { ImGui::Text(JAPANESE("体力")); }
    if (m_SelectNo == 4) { ImGui::Text(JAPANESE("休息")); }
    ImGui::End();
#endif

    //ライトマネージャー
#ifdef DEBUG 
    CLightManager::GetInstance().Debug();
#endif
}

//育成関連UIのインスタンス生成
void CNurtureScene::CreateNurtureUI(
    std::unique_ptr<CUIObject>& gage, 
    std::unique_ptr<CUIObject>& back, 
    std::unique_ptr<CUIObject>& frame,
    std::unique_ptr<CUIObject>& turnback)
{
    //スタミナゲージ
    gage = std::make_unique<CUIObject>();
    //ゲージ背景
    back = std::make_unique<CUIObject>();
    //ゲージ枠
    frame = std::make_unique<CUIObject>();
    //ターン背景
    turnback = std::make_unique<CUIObject>();
}
//育成関連UIのスプライトデータの読み込み
void CNurtureScene::LoadNurtureUI(
    std::unique_ptr<CUIObject>& gage, 
    std::unique_ptr<CUIObject>& back, 
    std::unique_ptr<CUIObject>& frame,
    std::unique_ptr<CUIObject>& turnback)
{
    //スタミナゲージ
    gage->AttachSprite(CUIManager::GetSprite(CUIManager::StaminaGage));
    //ゲージ背景
    back->AttachSprite(CUIManager::GetSprite(CUIManager::StaminaBack));
    //ゲージ枠
    frame->AttachSprite(CUIManager::GetSprite(CUIManager::StaminaFrame));
    //ターン数背景
    turnback->AttachSprite(CUIManager::GetSprite(CUIManager::TurnBack));
}
//育成関連UIの初期化
void CNurtureScene::InitNurtureUI(
    std::unique_ptr<CUIObject>& gage,
    std::unique_ptr<CUIObject>& back,
    std::unique_ptr<CUIObject>& frame,
    std::unique_ptr<CUIObject>& turnback)
{
    CSceneManager*   SceneMng   = &CSceneManager::GetInstance();
    CNurtureManager* NurtureMng = &CNurtureManager::GetInstance();
    CHeroManager*    HeroMng    = &CHeroManager::GetInstance();

    //読み込みが初回であるなら
    if (!NurtureMng->GetIsDataLoaded())
    {
        //ターン数・HPの値の初期化
        //ターン数
        NurtureMng->InitTurn();
        gage->SetWidth(1.0f);
        //スタミナの初期化
        HeroMng->InitStamina();
    }
    else
    {
        //スタミナに減少後の値をセット
        HeroMng->SetStamina(HeroMng->GetAfterStamina());
        //現在のスタミナ幅を取得し、設定する
        gage->SetWidth(NurtureMng->GetStaminaWidth());
    }

    //スタミナゲージ
    gage->SetScale(BASIC_SCALE);            
    gage->SetPosition(STAMINA_POS);  

    //スタミナゲージ背景
    back->SetScale(BASIC_SCALE);              
    back->SetPosition(STAMINA_POS);  
    back->SetDisplay(BASIC_DISPLAY.x, BASIC_DISPLAY.y);         
    
    //スタミナゲージ枠
    frame->SetScale(BASIC_SCALE);             
    frame->SetPosition(STAMINAFRAME_POS);   
    frame->SetDisplay(BASIC_DISPLAY.x, BASIC_DISPLAY.y);

    //ターン数背景
    turnback->SetScale(BASIC_SCALE);          
    turnback->SetPosition(TURNBACK_POS);  
    turnback->SetDisplay(BASIC_DISPLAY.x, BASIC_DISPLAY.y);
}
//描画
void CNurtureScene::DrawNurtureUI(
    std::unique_ptr<CUIObject>& gage,
    std::unique_ptr<CUIObject>& back,
    std::unique_ptr<CUIObject>& frame,
    std::unique_ptr<CUIObject>& turnback)
{
    //スタミナゲージのアニメーション
    StaminaGageAnim();
    //ターン数背景
    turnback->Draw();
    //ゲージ枠
    frame->Draw();
    //ゲージ背景
    back->Draw();
    //スタミナゲージ
    gage->Draw();
    //残りターン数の描画
    DrawRemainingTurn();
}

//各ヒーローのデータ読み込み
void CNurtureScene::LoadHeroData( const std::string& heroname )
{
    CSceneManager*   SceneMng   = &CSceneManager::GetInstance();
    CNurtureManager* NurtureMng = &CNurtureManager::GetInstance();

    //設定されているユーザー名の取得
    std::string UserName = SceneMng->GetStringName();

    //読み込むファイルのパス
    //初回の読み込み時に読み込む初期ステータスファイル
    std::string InitFilePath = "Data\\Acount\\" + UserName + "\\HeroData";
    //パラメータ情報更新時に読み込むファイル
    std::string ParamFilePath = "Data\\Acount\\" + UserName + "\\Parameter\\" + heroname;

    //jsonに保存されたデータの読み込み
    //読み込み回数に応じて読み込むファイルを変える
    if (!NurtureMng->GetIsDataLoaded())
    {
        //初回の読み込み時
        if (!m_pJson->Load(m_ParamData, InitFilePath)) { return; }
    }
    else
    {
        //2度目以降の読み込み時
        if (!m_pJson->Load(m_ParamData, ParamFilePath)) { return; }
    }
}

//トレーニング選択処理
void CNurtureScene::SelectTraning()
{
    CSceneManager*   SceneMng   = &CSceneManager::GetInstance();
    CNurtureManager* NurtureMng = &CNurtureManager::GetInstance();
    CHeroManager*    HeroMng    = &CHeroManager::GetInstance();


    //更新前のパラメータを保存
     HeroMng->SetBeforeParam(HeroMng->GetParam());
    //更新前のスタミナを保存
     HeroMng->SetBeforeStamina(HeroMng->GetStamina());

    //それぞれのパラメータの増加
    switch (HeroMng->GetTraining())
    {
    case::CHeroManager::PowerTraining: HeroMng->PowerUp(HeroMng->GetStamina()); break; //筋力
    case::CHeroManager::MagicTraining: HeroMng->MagicUp(HeroMng->GetStamina()); break; //魔力
    case::CHeroManager::SpeedTraining: HeroMng->SpeedUp(HeroMng->GetStamina()); break; //素早さ
    case::CHeroManager::HpTraining: HeroMng->HpUp(HeroMng->GetStamina()); break;       //体力
    case::CHeroManager::Rest: NurtureMng->SetRestFlag(true); break;                      //休息
    }

    //スタミナの減少または回復
    //休息フラグが立っていなければ減少
    if (!NurtureMng->GetRestFlag()) { HeroMng->ReduceStamina(); }
    else { HeroMng->StaminaRecovery(); }

    //更新後パラメータの保存
    SaveParam();

    //初回のみ読み込むものを読み込まなくする
    NurtureMng->SetIsDataLoaded(true);

}

//各種トレーニングUI初期設定
void CNurtureScene::UIInit(std::unique_ptr<CUIObject>& ui, D3DXVECTOR3 pos, float interval, D3DXVECTOR3 scale, int no)
{
    //位置
    ui->SetPosition(pos.x + (interval * no), pos.y, 0.0f);
    //拡縮
    ui->SetScale(scale);
    //α値
    ui->SetAlpha(1.0f);
    //幅、高さ
    ui->SetDisplay(1.0f, 1.0f);
}

//失敗率背景の初期設定
void CNurtureScene::FailureRateBackInit(std::unique_ptr<CUIObject>& back, D3DXVECTOR3 pos)
{
    back->SetPosition(FAILUREBACK_POS);
    back->SetScale(FAILUREBACK_SCALE);
    back->SetAlpha(FAILUREBACK_ALPHA);
    back->SetDisplay(FAILUREBACK_DISP.x, FAILUREBACK_DISP.y);
}


//ヒーローごとのパラメータ書き込み
void CNurtureScene::SaveParam()
{
    CSceneManager* SceneMng = &CSceneManager::GetInstance();
    CHeroManager*  HeroMng  = &CHeroManager::GetInstance();

    //設定されているユーザー名の取得
    std::string UserName = SceneMng->GetStringName();

    //トレーニング実行時にパラメータ情報を書き込むファイルの階層
    std::string ParamFileHierarchy = "Data\\Acount\\" + UserName + "\\Parameter\\";
    //セットされたヒーローのパラメータ情報の書き込み
    m_pJson->SaveNurtureData(HeroMng->GetSelectHeroName(), m_ParamWriter, ParamFileHierarchy);
}

//各種パラメータの描画
void CNurtureScene::DrawParam()
{
    WriteText*    Text    = WriteText::GetInstance();
    CUtility*     Utility = &CUtility::GetInstance();
    CHeroManager* HeroMng = &CHeroManager::GetInstance();

    //----各種パラメータのUI描画(背景,値,ランク)----
    //背景
    m_pParamBack->Draw();
    //筋力
    Text->Draw_Text(std::to_wstring(static_cast<int>(HeroMng->GetParam().Power)), WriteText::Normal, Utility->PosCorrection(HeroMng->GetParam().Power,CORRECTION_DIGIT,PARAMVALUE_POS));
    CRank::GetInstance().DrawRank(HeroMng->GetParam().Power, 2, RANK_POS);
    //魔力
    Text->Draw_Text(std::to_wstring(static_cast<int>(HeroMng->GetParam().Magic)), WriteText::Normal, Utility->PosCorrection(HeroMng->GetParam().Magic, CORRECTION_DIGIT, D3DXVECTOR2(PARAMVALUE_POS.x + PARAMVALUE_INTERVAL, PARAMVALUE_POS.y)));
    CRank::GetInstance().DrawRank(HeroMng->GetParam().Magic, 2, D3DXVECTOR2(RANK_POS.x + RANK_INTERVAL, RANK_POS.y));
    //素早さ
    Text->Draw_Text(std::to_wstring(static_cast<int>(HeroMng->GetParam().Speed)), WriteText::Normal, Utility->PosCorrection(HeroMng->GetParam().Speed, CORRECTION_DIGIT, D3DXVECTOR2(PARAMVALUE_POS.x + (PARAMVALUE_INTERVAL * 2), PARAMVALUE_POS.y)));
    CRank::GetInstance().DrawRank(HeroMng->GetParam().Speed, 2, D3DXVECTOR2(RANK_POS.x + (RANK_INTERVAL * 2), RANK_POS.y));
    //体力
    Text->Draw_Text(std::to_wstring(static_cast<int>(HeroMng->GetParam().Hp)), WriteText::Normal, Utility->PosCorrection(HeroMng->GetParam().Hp, CORRECTION_DIGIT, D3DXVECTOR2(PARAMVALUE_POS.x + (PARAMVALUE_INTERVAL * 3), PARAMVALUE_POS.y)));
    CRank::GetInstance().DrawRank(HeroMng->GetParam().Hp, 2, D3DXVECTOR2(RANK_POS.x + (RANK_INTERVAL * 3), RANK_POS.y));
}

//各種トレーニングの描画
void CNurtureScene::DrawTraning()
{
    //選択されたときそれぞれの位置を上げる変数
    float PosUp = 20.0f;

    //筋力トレーニング選択時
    if (m_SelectNo == 0) { m_pPowerTraning->SetPositionY(TRANING_POS.y - PosUp); }
    else { m_pPowerTraning->SetPositionY(TRANING_POS.y); }
    //魔力トレーニング選択時
    if (m_SelectNo == 1) { m_pMagicTraning->SetPositionY(TRANING_POS.y - PosUp); }
    else { m_pMagicTraning->SetPositionY(TRANING_POS.y); }
    //素早さトレーニング選択時
    if (m_SelectNo == 2) { m_pSpeedTraning->SetPositionY(TRANING_POS.y  - PosUp); }
    else { m_pSpeedTraning->SetPositionY(TRANING_POS.y); }
    //体力トレーニング選択時
    if (m_SelectNo == 3) { m_pHpTraning->SetPositionY(TRANING_POS.y - PosUp); }
    else { m_pHpTraning->SetPositionY(TRANING_POS.y); }
    //休息選択時
    if (m_SelectNo == 4) { m_pRest->SetPositionY(TRANING_POS.y - PosUp); }
    else { m_pRest->SetPositionY(TRANING_POS.y); }

    m_pPowerTraning->Draw();
    m_pMagicTraning->Draw();
    m_pSpeedTraning->Draw();
    m_pHpTraning->Draw();
    m_pRest->Draw();
}

//残りターン数の描画
void CNurtureScene::DrawRemainingTurn()
{
    WriteText*       Text       = WriteText::GetInstance();
    CUtility*        Utility    = &CUtility::GetInstance();
    CSceneManager*   SceneMng   = &CSceneManager::GetInstance();
    CNurtureManager* NurtureMng = &CNurtureManager::GetInstance();

    //整数をwstring型に変換
    std::wstring Turn = std::to_wstring(NurtureMng->GetRemainingTurn());

    //残りターン数の描画
    Text->Draw_Text(L"残り", WriteText::TurnText, REMAININGTEXT_POS);
    Text->Draw_Text(Turn, WriteText::Turn, Utility->PosCorrection(NurtureMng->GetRemainingTurn(),2,TURN_POS));
    Text->Draw_Text(L"ターン", WriteText::TurnText, TURNTEXT_POS);
}


//スタミナゲージのアニメーション
void CNurtureScene::StaminaGageAnim()
{
    CSceneManager*   SceneMng   = &CSceneManager::GetInstance();
    CNurtureManager* NurtureMng = &CNurtureManager::GetInstance();
    CHeroManager*    HeroMng    = &CHeroManager::GetInstance();


    //ゲージ幅の確認
    float GageScale = 1.0f * HeroMng->GetStamina() / STAMINA_MAX;

    //高ければ
    if (GageScale < m_GageWidth) { m_GageWidth -= 0.01f; }
    //低ければ
    if (GageScale > m_GageWidth){ m_GageWidth += 0.01f; }

    //現在のゲージ幅をシーンマネージャの変数に代入
    NurtureMng->SetStaminaWidth(m_GageWidth);

    //スタミナゲージの幅高さを設定
    if (NurtureMng->GetIsDataLoaded()) {
        m_pStaminaGage->SetDisplay(m_GageWidth, 1.0f);
    }
    else
    {
        //不自然なゲージの動きをなくす
        m_pStaminaGage->SetDisplay(1.0f, 1.0f);
    }
}
