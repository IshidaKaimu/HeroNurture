#include "CTraningScene.h"
#include "ImGui\ImGuiManager\ImGuiManager.h"
#include "KeyManager\CKeyManager.h"
#include "Scene\CSceneManager.h"
#include "ModeManager\Nurture\CNurtureManager.h"
#include "WriteText\WriteText.h"
#include "SkinMeshObject\Hero\CHeroManager.h"
#include "Sprite2D\UIManager\CUIManager.h"
#include "Sound\CSoundManager.h"

//定数の名前空間
using namespace Constant_TraningScene;


CTraningScene::CTraningScene()
    : m_pCamera ( &CCameraManager::GetInstance() )
    , m_pSky    ()
    , m_pGround ()
    , m_pBack   ()
    , m_TextNo  ()
    , m_pTextBox()
    , m_TextEnd ()
{
}

CTraningScene::~CTraningScene()
{
}

//構築関数
void CTraningScene::Create()
{
    //----インスタンス生成----
    //スタティックメッシュオブジェクト
    //空
    m_pSky = make_unique<CSky>();
    //地面
    m_pGround = make_unique<CGround>();

    //UIオブジェクト
    //背景
    m_pBack = make_unique<CUIObject>();
    //テキストボックス
    m_pTextBox = make_unique<CUIObject>();

    //育成関連のシーンで共通するUIのインスタンス生成
    CNurtureScene::CreateNurtureUI(m_pStaminaGauge,m_pStaminaBack,m_pStaminaFrame, m_pTurnBack);
    //-------------------------
}
//破棄関数
void CTraningScene::Releace()
{
}
//データ読み込み関数
void CTraningScene::LoadData()
{
    WriteText* Text             = WriteText::GetInstance();
    CHeroManager* HeroMng       = &CHeroManager::GetInstance();
    CNurtureManager* NurtureMng = &CNurtureManager::GetInstance();

    //地面のメッシュデータ設定
    m_pGround->LoadData();

    //育成関連のシーンで共通するUIのスプライトデータ設定
    CNurtureScene::LoadNurtureUI(m_pStaminaGauge,m_pStaminaBack,m_pStaminaFrame, m_pTurnBack);

    //トレーニングごとの背景UIのスプライトデータ設定
    switch (HeroMng->GetTraining())
    {
    case CHeroManager::PowerTraining: m_pBack->AttachSprite(CUIManager::GetSprite(CUIManager::PowerBack));break;
    case CHeroManager::MagicTraining: m_pBack->AttachSprite(CUIManager::GetSprite(CUIManager::MagicBack));break;
    case CHeroManager::SpeedTraining: m_pBack->AttachSprite(CUIManager::GetSprite(CUIManager::SpeedBack));break;
    case CHeroManager::HpTraining:    m_pBack->AttachSprite(CUIManager::GetSprite(CUIManager::HpBack));break;
    case CHeroManager::Rest:          m_pBack->AttachSprite(CUIManager::GetSprite(CUIManager::RestBack));break;
    default:  break;
    }

    //テキストボックスのスプライトデータ設定
    m_pTextBox->AttachSprite(CUIManager::GetSprite(CUIManager::TextBox)); 

}
//初期化関数
void CTraningScene::Initialize()
{
    CSceneManager::GetInstance().InitWhiteFade();

    //育成関連のシーンで共通するUI
    CNurtureScene::InitNurtureUI(m_pStaminaGauge,m_pStaminaBack,m_pStaminaFrame, m_pTurnBack);

    //背景画像の設定
    m_pBack->SetPosition(0.0f, 0.0f, 0.0f);
    m_pBack->SetScale(1.0f, 1.0f, 1.0f);
    m_pBack->SetDisplay(1.0f, 1.0f);

    //テキストボックスの設定
    m_pTextBox->SetPosition(30.0f, 580.0f, 0.0f);
    m_pTextBox->SetScale(1.0f, 0.7f, 1.0f);
    m_pTextBox->SetDisplay(1.0f, 1.0f);

    //テキスト終了フラグの初期化
    m_TextEnd = false;
}

//更新関数
void CTraningScene::Update()
{
    CNurtureManager* NurtureMng = &CNurtureManager::GetInstance();
    CSceneManager*   SceneMng   = &CSceneManager::GetInstance();
    CKeyManager*     KeyMng     = &CKeyManager::GetInstance();

    //フェードイン処理
    if (!FadeIn()) { return; }

   //キーマネージャーの更新処理
   KeyMng->Update();


   //ステータス変化SEの再生
   if (CHeroManager::GetInstance().GetFailureFlag()) {
       m_SECnt++;
       if (m_SECnt == PLAY_SE_CNT)
       {
           CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Miss);
           CSoundManager::GetInstance()->Volume(CSoundManager::SE_Miss, SE_VOLUME);
       }
   }
   else
   {
       m_SECnt++;
       if (m_SECnt == PLAY_SE_CNT)
       {
           CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Up);
           CSoundManager::GetInstance()->Volume(CSoundManager::SE_Up, SE_VOLUME);
       }
   }


   //テキストの描画を進める
   if (KeyMng->IsDown(VK_RETURN))
   {
       //決定SEの再生
       CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Enter);
       CSoundManager::GetInstance()->Volume(CSoundManager::SE_Enter, SE_VOLUME);

       if (m_TextNo < m_ParamInc.size() - 1)
       {
           m_TextNo++;
       }
       else
       {
           //必要なテキストの描画が終了すればシーンを戻す
           m_TextEnd = true;
       }
   }

   //上昇したパラメータのテキストを追加
   AddText();

#if DEBUG
   ImGui::Begin(JAPANESE("テキストの番号"));
   ImGui::Text(JAPANESE("m_TextNo:%d"), m_TextNo);
   ImGui::Text(JAPANESE("m_TextNo:%d"), m_ParamInc.size());
   ImGui::Text(JAPANESE("m_Stamina:%f"),CHeroManager::GetInstance().GetStamina());
   ImGui::Text(JAPANESE("スタミナゲージの幅:%f"),CSceneManager::GetInstance()->GetStaminaWidth());
   ImGui::End();
#endif

   //テキストの描画が全て終わり次第シーン遷移
    if (m_TextEnd)
    {
        m_SceneTransitionFlg = true;
    }

   //フェードが終わり次第シーン遷移
   if (m_SceneTransitionFlg && FadeOut())
   {
       //休息フラグが立っていたら降ろす
       if (NurtureMng->GetRestFlag()) { NurtureMng->SetRestFlag(false); }
       //ターン経過処理
       NurtureMng->TurnProgress();
       SceneMng->LoadCreate(CSceneManager::Nurture);
       m_SECnt = 0;
   }
}
//描画関数
void CTraningScene::Draw()
{
    CSceneManager* SceneMng = &CSceneManager::GetInstance();

    m_pGround->Draw();

    //各トレーニング背景UIの描画
    m_pBack->Draw();
    
    //深度を無視する
    SceneMng->GetDx11()->SetDepth(false);

    //上昇量テキストの描画
    DrawTraningText();

    //育成関連のシーンで共通して表示するUI
    CNurtureScene::DrawNurtureUI(m_pStaminaGauge,m_pStaminaBack,m_pStaminaFrame,m_pTurnBack);

    //深度を戻す
    SceneMng->GetDx11()->SetDepth(true);

}

//配列にテキストを追加する関数
void CTraningScene::AddText()
{
    WriteText* Text = WriteText::GetInstance();
    CHeroManager* Hero = &CHeroManager::GetInstance();

    //----それぞれのパラメータが変化していた場合の条件文と上昇量・減少量の計算----
    //筋力
    bool IsPowerUp = Hero->GetBeforeParam().Power < Hero->GetParam().Power;             //上昇
    bool IsPowerDown = Hero->GetBeforeParam().Power > Hero->GetParam().Power;           //減少
    float PowerInc = std::abs(Hero->GetParam().Power - Hero->GetBeforeParam().Power);   //上昇量
    //魔力
    bool IsMagicUp = Hero->GetBeforeParam().Magic < Hero->GetParam().Magic;             //上昇
    bool IsMagicDown = Hero->GetBeforeParam().Magic > Hero->GetParam().Magic;           //減少
    float MagicInc = std::abs(Hero->GetParam().Magic - Hero->GetBeforeParam().Magic);   //上昇量
    //素早さ
    bool IsSpeedUp = Hero->GetBeforeParam().Speed < Hero->GetParam().Speed;             //上昇
    bool IsSpeedDown = Hero->GetBeforeParam().Speed > Hero->GetParam().Speed;           //減少
    float SpeedInc = std::abs(Hero->GetParam().Speed - Hero->GetBeforeParam().Speed);   //上昇量
    //体力
    bool IsHpUp = Hero->GetBeforeParam().Hp < Hero->GetParam().Hp;             //上昇
    bool IsHpDown = Hero->GetBeforeParam().Hp > Hero->GetParam().Hp;           //減少
    float HpInc = std::abs(Hero->GetParam().Hp - Hero->GetBeforeParam().Hp);   //上昇量
    //スタミナ
    bool IsRecoveryStamina = Hero->GetBeforeStamina() <= Hero->GetStamina();   //上昇
    bool IsReduceStamina = Hero->GetBeforeStamina() >= Hero->GetStamina();     //減少
    float StaminaInc = std::abs(Hero->GetStamina() - Hero->GetBeforeStamina());//上昇量

    //条件を満たしていれば構造体配列に格納                                   　　　　　　　　　　　パラメータ名,上昇量
    if ((IsPowerUp || IsPowerDown) && !AlreadyAddCheck(L"筋力が")) { m_ParamInc.push_back({ L"筋力が",static_cast<int>(PowerInc), IsPowerUp ? L"上昇した" : L"減少した"}); }
    if ((IsMagicUp || IsMagicDown) && !AlreadyAddCheck(L"魔力が")) { m_ParamInc.push_back({ L"魔力が",static_cast<int>(MagicInc), IsMagicUp ? L"上昇した" : L"減少した" }); }
    if ((IsSpeedUp || IsSpeedDown) && !AlreadyAddCheck(L"素早さが")) { m_ParamInc.push_back({ L"素早さが",static_cast<int>(SpeedInc), IsSpeedUp ? L"上昇した" : L"減少した" }); }
    if ((IsHpUp || IsHpDown) && !AlreadyAddCheck(L"体力が")) { m_ParamInc.push_back({ L"体力が",static_cast<int>(HpInc), IsHpUp ? L"上昇した" : L"減少した" }); }
    if ((IsRecoveryStamina || IsReduceStamina) && !AlreadyAddCheck(L"スタミナが")) { m_ParamInc.push_back({ L"スタミナが",static_cast<int>(StaminaInc), IsRecoveryStamina ? L"回復した" : L"減少した" }); }
}

//配列に追加済みでないか調べる関数
bool CTraningScene::AlreadyAddCheck(std::wstring paramname)
{
    //既に追加していないかの確認
    bool AlreadyAdd = std::any_of(m_ParamInc.begin(), m_ParamInc.end(), [&](IncParam param) { return param.ParamName == paramname; });
    
    //追加済みであればtrue
    if(AlreadyAdd)
    {
        return true;
    }  
    return false;
}

//トレーニング結果テキストの描画
void CTraningScene::DrawTraningText()
{
    WriteText*       Text          = WriteText::GetInstance();
    CHeroManager*    HeroMng       = &CHeroManager::GetInstance();
    CSceneManager*   SceneMng      = &CSceneManager::GetInstance();
    CNurtureManager* NurtureMng    = &CNurtureManager::GetInstance();

    //失敗したかどうかによって返すテキストを変える
    std::wstring ResultText = HeroMng->GetFailureFlag() ? L"失敗..." : L"成功!";

    //大成功時のテキスト
    std::wstring GreatSuccessText = L"大成功!!";

    //失敗
    bool Failure = HeroMng->GetFailureFlag();

    //大成功
    bool GreatSuccess = HeroMng->GetGreatSuccessFlag();

    //休息
    bool Rest = NurtureMng->GetRestFlag();


    //テキストボックスの描画
    m_pTextBox->Draw();

    //休憩が選択されていない場合
    if (!Rest)
    {
        //トレーニング成功
        if (!Failure)
        {
            if (!GreatSuccess)
            {
                //「成功!」のテキスト描画
                Text->Draw_Text(ResultText, WriteText::Success, RESULTTEXT_OFFSET);
            }
            else
            {
                //「大成功!!」のテキスト描画
                Text->Draw_Text(GreatSuccessText, WriteText::GreatSuccess, RESULTTEXT_OFFSET);
            }
        }
        else
        {
            //「失敗...」のテキスト描画
            Text->Draw_Text(ResultText, WriteText::Failure, RESULTTEXT_OFFSET);
        }
    }

    //テキスト番号が配列を超えていなければ
    if (m_TextNo < m_ParamInc.size())
    {
        DrawParamChange(m_ParamInc[m_TextNo]);
    }
}

//パラメータ変化の描画処理
void CTraningScene::DrawParamChange(const IncParam& param)
{
    WriteText* Text = WriteText::GetInstance();
    CHeroManager* HeroMng = &CHeroManager::GetInstance();

    //描画位置の設定
    //テキストの描画位置を設定
    //初期位置
    D3DXVECTOR2 InitOffset = PARAMTEXT_OFFSET;
    //数値テキストの位置
    D3DXVECTOR2 ValueOffset = VALUETEXT_OFFSET;

    //素早さ、スタミナの場合の調整
    if (param.ParamName == L"素早さが")       
    {
        ValueOffset.x += 30.0f; 
    }
    else if (param.ParamName == L"スタミナが")
    {
        ValueOffset.x += 40.0f; 
    }


    //上昇したか減少したかによって文字の色を変更する
    if (param.IncValue != 0) 
    {
        //パラメータの名前と変化の描画
        Text->Draw_Text(param.ParamName, WriteText::Normal, InitOffset);

        //パラメータが上昇、またはスタミナが回復していた場合
        if (param.ParamChangeText == L"上昇した" || param.ParamChangeText == L"回復した")
        {
            Text->Draw_Text(std::to_wstring(param.IncValue) + param.ParamChangeText, WriteText::Inc, ValueOffset);
        }
        else
        {
            Text->Draw_Text(std::to_wstring(param.IncValue) + param.ParamChangeText, WriteText::Dec, ValueOffset);
        }
    }
    else 
    {
        //スタミナが既に満タンで上昇または既に0の状態で減少した場合
        if (param.ParamName == L"スタミナが")
        {
            //パラメータの名前と変化の描画
            Text->Draw_Text(L"スタミナは", WriteText::Normal, InitOffset);
            //スタミナが既に0の状態で減少した場合
            if (HeroMng->GetStamina() <= 0)
            {
                Text->Draw_Text(L"これ以上減少しない", WriteText::Dec, ValueOffset);
            }
            else if(HeroMng->GetStamina() >= 100)
            {
                Text->Draw_Text(L"これ以上回復しない", WriteText::Inc, ValueOffset);
            }
        }
    }
}

