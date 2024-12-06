#include "CNatureScene.h"
#include "ImGui\ImGuiManager\ImGuiManager.h"
#include "SkinMesh\SkinMeshManager\CSkinMeshManager.h"
#include "Camera\CameraManager\CCameraManager.h"
#include "SkinMeshObject\Hero\CHeroManager.h"
#include "StaticMesh\MeshManager\CMeshManager.h"
#include "Sprite2D\UIManager\CUIManager.h"
#include "Scene\CSceneManager.h"
#include "KeyManager\CKeyManager.h"
#include "WriteText\WriteText.h"
#include "Json\CJson.h"


CNatureScene::CNatureScene()
    : m_pCamera  ( &CCameraManager::GetInstance() )
    , m_pHero    ( &CHeroManager::GetInstance() )
    , m_pJson    ()
    , m_Name     ()
    , m_pGround  ()
    , m_pSky     ()
    , m_ParamData()
{
}

CNatureScene::~CNatureScene()
{
}

//構築関数
void CNatureScene::Create()
{
    //----インスタンス生成----
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
    
    //スタティックメッシュオブジェクト
    //地面
    m_pGround = std::make_unique<CGround>();
    //スカイボックス
    m_pSky    = std::make_unique<CSky>();

    //UIオブジェクト
    //各種パラメータ
    //筋力
    m_pPowerParam = new CUIObject();
    //魔力
    m_pMagicParam = new CUIObject();
    //素早さ
    m_pSpeedParam = new CUIObject();
    //体力
    m_pHpParam    = new CUIObject();
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

    //地面
    m_pGround->LoadData();

    //各パラメータのUIのスプライト設定
    //筋力
    m_pPowerParam->AttachSprite(CUIManager::GetSprite(CUIManager::PowerParam));
    //魔力
    m_pMagicParam->AttachSprite(CUIManager::GetSprite(CUIManager::MagicParam));
    //素早さ
    m_pSpeedParam->AttachSprite(CUIManager::GetSprite(CUIManager::SpeedParam));
    //体力
    m_pHpParam->AttachSprite(CUIManager::GetSprite(CUIManager::HpParam));
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

    //ターン数の初期化
    if (!CSceneManager::GetInstance()->GetIsDataLoaded())
    {
        CSceneManager::GetInstance()->InitTurn();
    }

    //----ライト情報----
    //位置
    m_Light.Position   = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    //向き
    m_Light.vDirection = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //ライト方向
   
    //----各種パラメータUIの初期設定----
    //筋力
    ParamInit(m_pPowerParam, 1);
    //魔力
    ParamInit(m_pMagicParam, 2);
    //素早さ
    ParamInit(m_pSpeedParam, 3);
    //体力
    ParamInit(m_pHpParam, 4);

}


//更新関数
void CNatureScene::Update()
{
    //フェードイン処理
    if (!FadeIn()) { return; }

    //セットされたヒーローのクラスの更新
    m_pHero->Update();

    //キーマネージャのインスタンスを変数に代入
    CKeyManager* KeyMng = CKeyManager::GetInstance();

    //キーマネージャーの更新処理
    CKeyManager::GetInstance()->Update();

    //ヒーローマネージャのインスタンスを変数に代入
    CHeroManager* Hero = &CHeroManager::GetInstance();

    //筋力トレーニング
    //カーソルの移動
    if (KeyMng->IsDown(VK_RIGHT))
    {
        //キー入力で選択を進める
        if (m_SelectNo < CHeroManager::enTraningList::Max_T) { m_SelectNo++; }
        else { m_SelectNo = 0; }
    }
    else if (KeyMng->IsDown(VK_LEFT))
    {
        if (m_SelectNo > 0) { m_SelectNo--; }
        else { m_SelectNo = 1; }
    }

    //セットされたヒーローのクラスのアニメーション
    m_pHero->NatureAnimation(m_SelectNo);


    //トレーニングの決定
    if (KeyMng->IsDown(VK_RETURN))
    {
        //選択肢の位置に応じたトレーニングをセット
        switch (m_SelectNo)
        {
        case 0:  Hero->SetTraning(CHeroManager::PowerTraining); break;
        case 1:  Hero->SetTraning(CHeroManager::MagicTraining); break;
        case 2:  Hero->SetTraning(CHeroManager::SpeedTraining); break;
        case 3:  Hero->SetTraning(CHeroManager::HpTraining); break;
        }
        //パラメータ処理
        SelectTraning();
    }
#ifdef DEBUG 
    ImGui::Begin(JAPANESE("カメラ"));
    ImGui::InputFloat3(JAPANESE("カメラ座標"),m_CamPos);
    ImGui::InputFloat3(JAPANESE("注視点"),m_CamLook);
    CCameraManager::GetInstance().SetPos(m_CamPos);
    CCameraManager::GetInstance().SetLook(m_CamLook);
    ImGui::End();
#endif

#ifdef _DEBUG 
    ImGui::Begin(JAPANESE("パラメータ"));
    ImGui::Text(JAPANESE("筋力:%f"),   m_pHero->GetParam().Power);
    ImGui::Text(JAPANESE("魔力:%f"),   m_pHero->GetParam().Magic);
    ImGui::Text(JAPANESE("素早さ:%f"), m_pHero->GetParam().Speed);
    ImGui::Text(JAPANESE("体力:%f"),   m_pHero->GetParam().Hp);
    ImGui::End();

    ImGui::Begin(JAPANESE("トレーニング選択状況"));
    if (m_SelectNo == 0) { ImGui::Text(JAPANESE("筋力")); }
    if (m_SelectNo == 1) { ImGui::Text(JAPANESE("魔力")); }
    if (m_SelectNo == 2) { ImGui::Text(JAPANESE("素早さ")); }
    if (m_SelectNo == 3) { ImGui::Text(JAPANESE("体力")); }
    ImGui::End();
#endif
}

//描画関数
void CNatureScene::Draw()
{
    //カメラの更新処理
    m_pCamera->CameraUpdate();

    //セットされたヒーローのクラスの描画
    CHeroManager::GetInstance().Draw();

    //地面クラスの描画
    m_pGround->Draw();

    //残りターン数の描画
    DrawRemainingTurn();

    //各パラメータUIの描画
    DrawParam();
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
    //ヒーローマネージャのインスタンスを変数に代入
    CHeroManager* HeroMng = &CHeroManager::GetInstance();

    //シーンマネージャのインスタンスを変数に代入
    CSceneManager* SceneMng = CSceneManager::GetInstance();

    //更新前のパラメータを保存
     HeroMng->SetBeforeParam(m_pHero->GetParam());

    //それぞれのパラメータの増加
    switch (HeroMng->GetTraining())
    {
    //筋力
    case::CHeroManager::PowerTraining: 
        m_pHero->PowerUp();
        m_pHero->SpeedUp();
        break;
    //魔力
    case::CHeroManager::MagicTraining: m_pHero->MagicUp(); break;
    //素早さ
    case::CHeroManager::SpeedTraining: m_pHero->SpeedUp(); break;
    //体力
    case::CHeroManager::HpTraining: m_pHero->HpUp(); break;
    }

    //更新後パラメータの保存
    SaveParam();

    //ターン経過処理
    SceneMng->TurnProgress();
    SceneMng->LoadCreate(CSceneManager::Training);
}

//ヒーローごとのパラメータ書き込み
void CNatureScene::SaveParam()
{
    //ヒーローごとのパラメータ情報の書き込み
    switch (m_pHero->GetSelectHero())
    {
    case CHeroManager::Yui:
        //ユイ
        WriteParam("Yui");
        break;
    case CHeroManager::Kaito:
        //カイト
        WriteParam("Kaito");
        break;
    default:
        break;
    }
}

//パラメータ情報の書き込み
void CNatureScene::WriteParam(const std::string& heroname)
{
    //書き込む情報の格納
    //----パラメータ----
    m_ParamWriter["Name"] = heroname;
    m_ParamWriter["Parameter"]["Power"] = m_pHero->GetParam().Power;
    m_ParamWriter["Parameter"]["Magic"] = m_pHero->GetParam().Magic;
    m_ParamWriter["Parameter"]["Speed"] = m_pHero->GetParam().Speed;
    m_ParamWriter["Parameter"]["Hp"] = m_pHero->GetParam().Hp;
    //----適正率----
    m_ParamWriter["Appropriate"]["Power"] = m_pHero->GetApp().PowerApp;
    m_ParamWriter["Appropriate"]["Magic"] = m_pHero->GetApp().MagicApp;
    m_ParamWriter["Appropriate"]["Speed"] = m_pHero->GetApp().SpeedApp;
    m_ParamWriter["Appropriate"]["Hp"]    = m_pHero->GetApp().HpApp;

    //ファイルに書き込み
    m_pJson->CreateOrWrite("Data\\Hero\\Parameter\\", m_ParamWriter);
}


//各種パラメータUI初期設定
void CNatureScene::ParamInit(CUIObject* param, int no)
{
    //位置
    param->SetPosition(PARAM_POSX * no, PARAM_POSY, 0.0f);
    //拡縮
    param->SetScale(0.3f, 0.3f, 0.3f);
    //α値
    param->SetAlpha(1.0f);
}

//各種パラメータの描画
void CNatureScene::DrawParam()
{
    //テキスト描画クラスのインスタンスを変数に代入
    WriteText* Text = WriteText::GetInstance();
    //----各種パラメータのUI描画----
    //筋力
    m_pPowerParam->Draw();
    Text->Draw_Text(std::to_wstring(static_cast<int>(m_pHero->GetParam().Power)), WriteText::Normal, D3DXVECTOR2(PARAMVALUE_POSX * 1.0f, PARAM_POSY));
    //魔力
    m_pMagicParam->Draw();
    Text->Draw_Text(std::to_wstring(static_cast<int>(m_pHero->GetParam().Magic)), WriteText::Normal, D3DXVECTOR2(PARAMVALUE_POSX * 2.0f, PARAM_POSY));
    //素早さ
    m_pSpeedParam->Draw();
    Text->Draw_Text(std::to_wstring(static_cast<int>(m_pHero->GetParam().Speed)), WriteText::Normal, D3DXVECTOR2(PARAMVALUE_POSX * 3.0f, PARAM_POSY));
    //体力
    m_pHpParam->Draw();
    Text->Draw_Text(std::to_wstring(static_cast<int>(m_pHero->GetParam().Hp)), WriteText::Normal, D3DXVECTOR2(PARAMVALUE_POSX * 4.0f, PARAM_POSY));
}


//残りターン数の描画
void CNatureScene::DrawRemainingTurn()
{
    //整数をwstring型に変換
    std::wstring Turn = std::to_wstring(CSceneManager::GetInstance()->GetRemainingTurn());

    //テキスト描画クラスのインスタンスを変数に代入
    WriteText* Text = WriteText::GetInstance();

    //残りターン数の描画
    Text->Draw_Text(L"残り", WriteText::Normal, D3DXVECTOR2(0.0, -20.0));
    Text->Draw_Text(Turn, WriteText::Turn, D3DXVECTOR2(110.0, -30.0));
    Text->Draw_Text(L"ターン", WriteText::Normal, D3DXVECTOR2(160.0, -20.0));
}
