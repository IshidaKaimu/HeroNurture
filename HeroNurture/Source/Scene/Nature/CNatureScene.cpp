#include "CNatureScene.h"
#include "ImGui\ImGuiManager\ImGuiManager.h"
#include "SkinMesh\SkinMeshManager\CSkinMeshManager.h"
#include "Camera\CameraManager\CCameraManager.h"
#include "SkinMeshObject\Hero\CHeroManager.h"
#include "StaticMesh\MeshManager\CMeshManager.h"
#include "Sprite2D\UIManager\CUIManager.h"
#include "Scene\CSceneManager.h"
#include "WriteText\WriteText.h"
#include "Json\CJson.h"


CNatureScene::CNatureScene()
    : m_pCamera  ( &CCameraManager::GetInstance() )
    , m_pHero    ( &CHeroManager::GetInstance() )
    , m_pJson    ()
    , m_Name     ()
    , m_pGround  ()
    , m_pSky     ()
    , m_CharaData()
    , m_ParamData()
    , m_Turn     ()
{
}

CNatureScene::~CNatureScene()
{
}

//構築関数
void CNatureScene::Create()
{
    //----インスタンス生成----
 
    //----セットされたヒーローのクラスのインスタンス生成----
    switch (m_pHero->GetSelectHero())
    {
    case CHeroManager::Yui:
        //ユイ
        m_pHero->SetHero(CHeroManager::Yui);
        //ファイルの作成、読み込み
        CreateHeroData(m_Name.Yui);
        break;
    case CHeroManager::Kaito:
        //カイト
        m_pHero->SetHero(CHeroManager::Kaito);
        //ファイルの作成、読み込み
        CreateHeroData(m_Name.Kaito);
        break;
    default:
        break;
    }
    
    //----スタティックメッシュ----
    //地面
    m_pGround = std::make_unique<CGround>();
    //スカイボックス
    m_pSky    = std::make_unique<CSky>();

    //----UI----
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
    //セットされたヒーローのクラスのデータ読み込み
    CHeroManager::GetInstance().LoadData(m_ParamData);

    //地面
    m_pGround->AttachMesh(CMeshManager::GetMesh(CMeshManager::Ground));

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

    //----ライト情報----
    //位置
    m_Light.Position   = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    //向き
    m_Light.vDirection = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //ライト方向

    //育成残りターン数の初期化
    m_Turn = MAX_TURN;

    //----各種パラメータのUIの設定----
    //筋力
    m_pPowerParam->SetPosition(300.0f,300.0f,0.0f);
    m_pPowerParam->SetScale(1.0f,1.0f,1.0f);
    m_pPowerParam->SetAlpha(1.0f);

}


//更新関数
void CNatureScene::Update()
{
    //フェードイン処理
    if (!FadeIn()) { return; }

    //セットされたヒーローのクラスの更新
    m_pHero->Update();

    //セットされたヒーローのクラスのアニメーション
    m_pHero->Animation();



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
    ImGui::Text(JAPANESE("筋力:%d"), m_pHero->GetStatus().Power);
    ImGui::Text(JAPANESE("魔力:%d"), m_pHero->GetStatus().Magic);
    ImGui::Text(JAPANESE("素早さ:%d"), m_pHero->GetStatus().Speed);
    ImGui::Text(JAPANESE("体力:%d"), m_pHero->GetStatus().Hp);
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
void CNatureScene::CreateHeroData( const std::string& heroname )
{
    //ファイル名と階層を結合
    std::string FilePath = "Data\\Hero\\HeroData";

    //jsonに保存されたデータの読み込み
    if (!m_pJson->Load(m_ParamData, FilePath))
    {
        return;
    }
}

//残りターン数の描画
void CNatureScene::DrawRemainingTurn()
{
    //整数をwstring型に変換
    std::wstring Turn = std::to_wstring(m_Turn);

    //テキスト描画クラスのインスタンスを変数に代入
    WriteText* Text =  WriteText::GetInstance();

    //残りターン数の描画
    Text->Draw_Text(L"残り",WriteText::Normal, D3DXVECTOR2(0.0, -20.0));
    Text->Draw_Text(Turn,WriteText::Turn, D3DXVECTOR2(110.0, -30.0));
    Text->Draw_Text(L"ターン",WriteText::Normal, D3DXVECTOR2(160.0, -20.0));
}

//各種パラメータの描画
void CNatureScene::DrawParam()
{
    //----各種パラメータのUI描画----
    //筋力
    m_pPowerParam->Draw();
    //魔力
    m_pMagicParam->Draw();
    //素早さ
    m_pSpeedParam->Draw();
    //体力
    m_pHpParam->Draw();
}


