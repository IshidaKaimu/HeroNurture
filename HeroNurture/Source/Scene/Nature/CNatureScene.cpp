#include "CNatureScene.h"
#include "ImGui\ImGuiManager\ImGuiManager.h"
#include "SkinMesh\SkinMeshManager\CSkinMeshManager.h"
#include "Camera\CameraManager\CCameraManager.h"
#include "Light\LightManager\CLightManager.h"
#include "SkinMeshObject\Hero\CHeroManager.h"
#include "StaticMesh\MeshManager\CMeshManager.h"
#include "Sprite2D\UIManager\CUIManager.h"
#include "Scene\CSceneManager.h"
#include "KeyManager\CKeyManager.h"
#include "WriteText\WriteText.h"
#include "Utility\CUtility.h"

CNatureScene::CNatureScene()
    : m_pCamera     ( &CCameraManager::GetInstance() )
    , m_pHero       ( &CHeroManager::GetInstance() )
    , m_Name        ()
    , m_pGround     ()
    , m_pSky        ()
    , m_pParamBack  ()
    , m_pPowerTraning()
    , m_pMagicTraning()
    , m_pSpeedTraning()
    , m_pHpTraning()
    , m_pRest()
    , m_pStaminaGage()
    , m_pStaminaBack()
    , m_GageWidth   ( CSceneManager::GetInstance()->GetStaminaWidth() )
    , m_pJson()
    , m_ParamWriter ()
    , m_ParamData   ()
{
}

CNatureScene::~CNatureScene()
{
}

//構築関数
void CNatureScene::Create()
{
    //セットされたヒーローのクラスのインスタンス生成
    switch (m_pHero->GetSelectHero())
    {
    case CHeroManager::Yui:
        //ユイ
        m_pHero->SetHero(CHeroManager::Yui);
        //ファイルの作成、読み込み
        LoadHeroData(m_Name.Yui);
        break;
    case CHeroManager::Kaito:
        //カイト
        m_pHero->SetHero(CHeroManager::Kaito);
        //ファイルの作成、読み込み
        LoadHeroData(m_Name.Kaito);
        break;
    default:
        break;
    }
    
    //----スタティックメッシュオブジェクト----
    //地面
    m_pGround = std::make_unique<CGround>();
    //スカイボックス
    m_pSky    = std::make_unique<CSky>();

    //----UIオブジェクト----
    //パラメータの背景
    m_pParamBack = std::make_unique<CUIObject>();
    //各種トレーニングUI
    m_pPowerTraning = std::make_unique<CUIObject>();
    m_pMagicTraning = std::make_unique<CUIObject>();
    m_pSpeedTraning = std::make_unique<CUIObject>();
    m_pHpTraning    = std::make_unique<CUIObject>();
    m_pRest         = std::make_unique<CUIObject>();

    //育成関連のシーンで共通して表示するUIのインスタンス生成
    CreateNatureUI(m_pStaminaGage,m_pStaminaBack);
}

//破棄関数
void CNatureScene::Releace()
{
    //----破棄----
    //カメラ
    m_pCamera = nullptr;
    //ヒーローマネージャー
    m_pHero   = nullptr;
}


//データ読み込み関数
void CNatureScene::LoadData()
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

    //スタミナゲージのUIのスプライト設定
    LoadNatureUI(m_pStaminaGage, m_pStaminaBack);
}

//初期化関数
void CNatureScene::Initialize()
{
    //セットされたヒーローのクラスの初期化
    m_pHero->Initialize();

    //各ヒーローのカメラ位置、カメラの注視点の設定
    switch (m_pHero->GetSelectHero())
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
    m_Light.Position   = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    //向き
    m_Light.vDirection = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //ライト方向
   
    //----パラメータの値を除くUIの初期設定----
    //パラメータの背景
    UIInit(m_pParamBack, PARAMBACK_POSX_N, PARAMBACK_POSY_N, 0, PARAMBACK_SCALE_N, 0);
    //各種トレーニング
    UIInit(m_pPowerTraning, TRANING_POSX_N, TRANING_POSY_N, 0, TRANING_SCALE_N, 0);
    UIInit(m_pMagicTraning, TRANING_POSX_N, TRANING_POSY_N, TRANING_INTERVAL_N, TRANING_SCALE_N, 1);
    UIInit(m_pSpeedTraning, TRANING_POSX_N, TRANING_POSY_N, TRANING_INTERVAL_N, TRANING_SCALE_N, 2);
    UIInit(m_pHpTraning,    TRANING_POSX_N, TRANING_POSY_N, TRANING_INTERVAL_N, TRANING_SCALE_N, 3);
    UIInit(m_pRest,    TRANING_POSX_N, TRANING_POSY_N, TRANING_INTERVAL_N, TRANING_SCALE_N, 4);

    //育成関連のシーンで共通のUIの初期化
    InitNatureUI(m_pStaminaGage,m_pStaminaBack);
}

//更新関数
void CNatureScene::Update()
{
    //----クラスのインスタンスを変数に代入----
    //キーマネージャー
    CKeyManager* KeyMng = CKeyManager::GetInstance();
    //ヒーローマネージャー
    CHeroManager* HeroMng = &CHeroManager::GetInstance();
    //シーンマネージャー
    CSceneManager* SceneMng = CSceneManager::GetInstance();

    //フェードイン処理
    if (!FadeIn()) { return; }

    //セットされたヒーローのクラスの更新
    m_pHero->Update();

    //キーマネージャーの更新処理
    CKeyManager::GetInstance()->Update();

    //筋力トレーニング
    //カーソルの移動
    if (KeyMng->IsDown(VK_RIGHT))
    {
        //キー入力で選択を進める
        if (m_SelectNo < CHeroManager::enTraningList::Max_T-1) { m_SelectNo++; }
        else { m_SelectNo = 0; }
    }
    else if (KeyMng->IsDown(VK_LEFT))
    {
        if (m_SelectNo > 0) { m_SelectNo--; }
        else { m_SelectNo = 4; }
    }

    //セットされたヒーローのクラスのアニメーション
    m_pHero->NatureAnimation(m_SelectNo);


    //トレーニングの決定
    if (KeyMng->IsDown(VK_RETURN) && !m_SceneTransitionFlg)
    {
        //選択肢の位置に応じたトレーニングをセット
        switch (m_SelectNo)
        {
        case 0:  m_pHero->SetTraning(CHeroManager::PowerTraining); break;
        case 1:  m_pHero->SetTraning(CHeroManager::MagicTraining); break;
        case 2:  m_pHero->SetTraning(CHeroManager::SpeedTraining); break;
        case 3:  m_pHero->SetTraning(CHeroManager::HpTraining); break;
        case 4:  m_pHero->SetTraning(CHeroManager::Rest); break;
        }
        //パラメータ処理
        SelectTraning();

        m_SceneTransitionFlg = true;
    }

    if (SceneMng->GetRemainingTurn() <= 0) 
    {
        m_SceneTransitionFlg = true;
    }

    if (m_SceneTransitionFlg && FadeOut())
    {
        if (SceneMng->GetRemainingTurn() > 0)
        {
            SceneMng->LoadCreate(CSceneManager::Training);
        }
        else
        {
            SceneMng->LoadCreate(CSceneManager::NatureResult);
        }
    }

    //デバッグ処理
    Debug();
}

//描画関数
void CNatureScene::Draw()
{
    //----クラスのインスタンスを変数に代入----
    //シーンマネージャー
    CSceneManager* SceneMng = CSceneManager::GetInstance();

    //カメラの更新処理
    m_pCamera->CameraUpdate();

    //セットされたヒーローのクラスの描画
    m_pHero->Draw();

    //地面クラスの描画
    m_pGround->Draw();

    //深度を無視する
    SceneMng->GetDx11()->SetDepth(false);

    //育成関連シーンで共通のUIの描画
    DrawNatureUI(m_pStaminaGage, m_pStaminaBack);

    //各トレーニングの描画
    DrawTraning();

    //各パラメータUIの描画
    DrawParam();

    //深度を戻す
    SceneMng->GetDx11()->SetDepth(true);
}

void CNatureScene::Debug()
{
#ifdef DEBUG 
    ImGui::Begin(JAPANESE("カメラ"));
    ImGui::InputFloat3(JAPANESE("カメラ座標"), m_CamPos);
    ImGui::InputFloat3(JAPANESE("注視点"), m_CamLook);
    CCameraManager::GetInstance().SetPos(m_CamPos);
    CCameraManager::GetInstance().SetLook(m_CamLook);
    ImGui::End();
#endif

#ifdef _DEBUG 
    ImGui::Begin(JAPANESE("パラメータ"));
    ImGui::Text(JAPANESE("筋力:%f"), m_pHero->GetParam().Power);
    ImGui::Text(JAPANESE("魔力:%f"), m_pHero->GetParam().Magic);
    ImGui::Text(JAPANESE("素早さ:%f"), m_pHero->GetParam().Speed);
    ImGui::Text(JAPANESE("体力:%f"), m_pHero->GetParam().Hp);
    ImGui::Text(JAPANESE("スタミナ:%f"), m_pHero->GetStamina());
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
void CNatureScene::CreateNatureUI(std::unique_ptr<CUIObject>& gage, std::unique_ptr<CUIObject>& back)
{
    //スタミナゲージ
    gage = std::make_unique<CUIObject>();
    //ゲージ背景
    back = std::make_unique<CUIObject>();
}
//育成関連UIのスプライトデータの読み込み
void CNatureScene::LoadNatureUI(std::unique_ptr<CUIObject>& gage, std::unique_ptr<CUIObject>& back)
{
    //スタミナゲージ
    gage->AttachSprite(CUIManager::GetSprite(CUIManager::StaminaGage));
    //ゲージ背景
    back->AttachSprite(CUIManager::GetSprite(CUIManager::StaminaBack));
}
//育成関連UIの初期化
void CNatureScene::InitNatureUI(std::unique_ptr<CUIObject>& gage, std::unique_ptr<CUIObject>& back)
{
    //読み込みが初回であるなら
    if (!CSceneManager::GetInstance()->GetIsDataLoaded())
    {
        //ターン数・HPの値の初期化
        //ターン数
        CSceneManager::GetInstance()->InitTurn();
        gage->SetWidth(1.0f);
        //スタミナの初期化
        m_pHero->InitStamina();
    }
    else
    {
        //スタミナに減少後の値をセット
        m_pHero->SetStamina(m_pHero->GetAfterStamina());
        //現在のスタミナ幅を取得し、設定する
        gage->SetWidth(CSceneManager::GetInstance()->GetStaminaWidth());
    }

    //拡縮
    gage->SetScale(1.0f, 1.0f, 1.0f);     //ゲージ
    back->SetScale(1.0f, 1.0f, 1.0f);     //ゲージ背景
    //位置
    gage->SetPosition(350.0f, 0.0f, 0.0f);//ゲージ
    back->SetPosition(350.0f, 0.0f, 0.0f);//ゲージ背景
    //ゲージ背景の幅
    back->SetDisplay(1.0f, 1.0f);
}
//描画
void CNatureScene::DrawNatureUI(std::unique_ptr<CUIObject>& gage, std::unique_ptr<CUIObject>& back)
{
    //スタミナゲージのアニメーション
    GageAnim();
    //ゲージ背景
    back->Draw();
    //スタミナゲージ
    gage->Draw();
    //残りターン数の描画
    DrawRemainingTurn();
}

//各ヒーローのデータ読み込み
void CNatureScene::LoadHeroData( const std::string& heroname )
{
    //読み込むファイルのパス
    //初回の読み込み時に読み込む初期ステータスファイル
    std::string InitFilePath = "Data\\Hero\\HeroData";
    //パラメータ情報更新時に読み込むファイル
    std::string ParamFilePath = "Data\\Hero\\Parameter\\" + heroname;

    //jsonに保存されたデータの読み込み
    //読み込み回数に応じて読み込むファイルを変える
    if (!CSceneManager::GetInstance()->GetIsDataLoaded()) 
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
void CNatureScene::SelectTraning()
{
    //シーンマネージャのインスタンスを変数に代入
    CSceneManager* SceneMng = CSceneManager::GetInstance();

    //更新前のパラメータを保存
     m_pHero->SetBeforeParam(m_pHero->GetParam());
    //更新前のスタミナを保存
     m_pHero->SetBeforeStamina(m_pHero->GetStamina());

    //それぞれのパラメータの増加
    switch (m_pHero->GetTraining())
    {
    //筋力
    case::CHeroManager::PowerTraining: m_pHero->PowerUp(m_pHero->GetStamina()); break;
    //魔力
    case::CHeroManager::MagicTraining: m_pHero->MagicUp(m_pHero->GetStamina()); break;
    //素早さ
    case::CHeroManager::SpeedTraining: m_pHero->SpeedUp(m_pHero->GetStamina()); break;
    //体力
    case::CHeroManager::HpTraining: m_pHero->HpUp(m_pHero->GetStamina()); break;
    //休息
    case::CHeroManager::Rest: SceneMng->SetRestFlag(true); break;
    }

    //スタミナの減少または回復
    //休息フラグが立っていなければ減少
    if (!SceneMng->GetRestFlag()) { m_pHero->ReduceStamina(); }
    else { m_pHero->StaminaRecovery(); }

    //更新後パラメータの保存
    SaveParam();

    //初回のみ読み込むものを読み込まなくする
    CSceneManager::GetInstance()->SetIsDataLoaded(true);

}

//各種UI初期設定
void CNatureScene::UIInit(std::unique_ptr<CUIObject>& ui, float x, float y, float interval, D3DXVECTOR3 scale, int no)
{
    //位置
    ui->SetPosition(x + (interval * no), y, 0.0f);
    //拡縮
    ui->SetScale(scale);
    //α値
    ui->SetAlpha(1.0f);
    //幅、高さ
    ui->SetDisplay(1.0f, 1.0f);
}


//ヒーローごとのパラメータ書き込み
void CNatureScene::SaveParam()
{
    //トレーニング実行時にパラメータ情報を書き込むファイルの階層
    std::string ParamFileHierarchy = "Data\\Hero\\Parameter\\";
    //セットされたヒーローのパラメータ情報の書き込み
    m_pJson->SaveNatureData(m_pHero->GetHeroName(), m_ParamWriter, ParamFileHierarchy);
}

//各種パラメータの描画
void CNatureScene::DrawParam()
{
    //----クラスのインスタンスを変数に代入----
    //テキスト描画クラス
    WriteText* Text = WriteText::GetInstance();
    //汎用クラス
    CUtility* Utility = &CUtility::GetInstance();

    //----各種パラメータのUI描画(背景,値,ランク)----
    //背景
    m_pParamBack->Draw();
    //筋力
    Text->Draw_Text(std::to_wstring(static_cast<int>(m_pHero->GetParam().Power)), WriteText::Normal, Utility->PosCorrection(m_pHero->GetParam().Power,CORRECTION_DIGIT,PARAMVALUE_POSX_N, PARAMVALUE_POSY_N));
    CUtility::GetInstance().DrawRank(m_pHero->GetParam().Power, 2, RANK_POSX_N, RANK_POSY_N);
    //魔力
    Text->Draw_Text(std::to_wstring(static_cast<int>(m_pHero->GetParam().Magic)), WriteText::Normal, Utility->PosCorrection(m_pHero->GetParam().Magic, CORRECTION_DIGIT, PARAMVALUE_POSX_N + PARAMVALUE_INTERVAL_N, PARAMVALUE_POSY_N));
    CUtility::GetInstance().DrawRank(m_pHero->GetParam().Magic, 2, RANK_POSX_N + RANK_INTERVAL_N, RANK_POSY_N);
    //素早さ
    Text->Draw_Text(std::to_wstring(static_cast<int>(m_pHero->GetParam().Speed)), WriteText::Normal, Utility->PosCorrection(m_pHero->GetParam().Speed, CORRECTION_DIGIT, PARAMVALUE_POSX_N + (PARAMVALUE_INTERVAL_N * 2), PARAMVALUE_POSY_N));
    CUtility::GetInstance().DrawRank(m_pHero->GetParam().Speed, 2, RANK_POSX_N + (RANK_INTERVAL_N * 2), RANK_POSY_N);
    //体力
    Text->Draw_Text(std::to_wstring(static_cast<int>(m_pHero->GetParam().Hp)), WriteText::Normal, Utility->PosCorrection(m_pHero->GetParam().Hp, CORRECTION_DIGIT, PARAMVALUE_POSX_N
        + (PARAMVALUE_INTERVAL_N * 3), PARAMVALUE_POSY_N));
    CUtility::GetInstance().DrawRank(m_pHero->GetParam().Hp, 2, RANK_POSX_N + (RANK_INTERVAL_N * 3), RANK_POSY_N);
}

//各種トレーニングの描画
void CNatureScene::DrawTraning()
{
    //選択されたときそれぞれの位置を上げる変数
    float PosUp = 20.0f;

    //筋力トレーニング選択時
    if (m_SelectNo == 0) { m_pPowerTraning->SetPositionY(TRANING_POSY_N - PosUp); }
    else { m_pPowerTraning->SetPositionY(TRANING_POSY_N); }
    //魔力トレーニング選択時
    if (m_SelectNo == 1) { m_pMagicTraning->SetPositionY(TRANING_POSY_N - PosUp); }
    else { m_pMagicTraning->SetPositionY(TRANING_POSY_N); }
    //素早さトレーニング選択時
    if (m_SelectNo == 2) { m_pSpeedTraning->SetPositionY(TRANING_POSY_N  - PosUp); }
    else { m_pSpeedTraning->SetPositionY(TRANING_POSY_N); }
    //体力トレーニング選択時
    if (m_SelectNo == 3) { m_pHpTraning->SetPositionY(TRANING_POSY_N - PosUp); }
    else { m_pHpTraning->SetPositionY(TRANING_POSY_N); }
    //休息選択時
    if (m_SelectNo == 4) { m_pRest->SetPositionY(TRANING_POSY_N - PosUp); }
    else { m_pRest->SetPositionY(TRANING_POSY_N); }

    m_pPowerTraning->Draw();
    m_pMagicTraning->Draw();
    m_pSpeedTraning->Draw();
    m_pHpTraning->Draw();
    m_pRest->Draw();
}

//残りターン数の描画
void CNatureScene::DrawRemainingTurn()
{
    //----クラスのインスタンスを変数に代入----
    //テキスト描画クラス
    WriteText* Text = WriteText::GetInstance();
    //汎用クラス
    CUtility* Utility = &CUtility::GetInstance();
    //シーンマネージャー
    CSceneManager* SceneMng = CSceneManager::GetInstance();

    //整数をwstring型に変換
    std::wstring Turn = std::to_wstring(CSceneManager::GetInstance()->GetRemainingTurn());

    //残りターン数の描画
    Text->Draw_Text(L"残り", WriteText::Normal, D3DXVECTOR2(0.0, -20.0));
    Text->Draw_Text(Turn, WriteText::Turn, Utility->PosCorrection(SceneMng->GetRemainingTurn(),2,140,-40.0f));
    Text->Draw_Text(L"ターン", WriteText::Normal, D3DXVECTOR2(200.0, -20.0));
}


//スタミナゲージのアニメーション
void CNatureScene::GageAnim()
{
    //クラスのインスタンスを変数に代入
    //シーンマネージャー
    CSceneManager* SceneMng = CSceneManager::GetInstance();

    //ゲージ幅の確認
    float GageScale = 1.0f * m_pHero->GetStamina() / STAMINA_MAX;

    //高ければ
    if (GageScale < m_GageWidth) { m_GageWidth -= 0.01f; }
    //低ければ
    if (GageScale > m_GageWidth){ m_GageWidth += 0.01f; }

    //現在のゲージ幅をシーンマネージャの変数に代入
    CSceneManager::GetInstance()->SetStaminaWidth(m_GageWidth);

    //スタミナゲージの幅高さを設定
    if (SceneMng->GetIsDataLoaded()) {
        m_pStaminaGage->SetDisplay(m_GageWidth, 1.0f);
    }
    else
    {
        //不自然なゲージの動きをなくす
        m_pStaminaGage->SetDisplay(1.0f, 1.0f);
    }


}
