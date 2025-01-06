#include "CTraningScene.h"
#include "ImGui\ImGuiManager\ImGuiManager.h"
#include "KeyManager\CKeyManager.h"
#include "Scene\CSceneManager.h"
#include "WriteText\WriteText.h"
#include "SkinMeshObject\Hero\CHeroManager.h"
#include "Sprite2D\UIManager\CUIManager.h"

CTraningScene::CTraningScene()
    : m_pCamera ( &CCameraManager::GetInstance() )
    , m_pSky    ()
    , m_pGround ()
    , m_pBack   ()
    , m_TextNo  ()
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

    //育成関連のシーンで共通するUIのインスタンス生成
    CNatureScene::CreateNatureUI(m_pStaminaGage,m_pStaminaBack);

}
//破棄関数
void CTraningScene::Releace()
{
}
//データ読み込み関数
void CTraningScene::LoadData()
{
    //----クラスのインスタンスを変数に代入----
    //テキスト描画クラス
    WriteText* Text = WriteText::GetInstance();
    //ヒーローマネージャークラス
    CHeroManager* HeroMng = &CHeroManager::GetInstance();

    //地面のメッシュデータ設定
    m_pGround->LoadData();

    //育成関連のシーンで共通するUIのスプライトデータ設定
    CNatureScene::LoadNatureUI(m_pStaminaGage,m_pStaminaBack);

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

}
//初期化関数
void CTraningScene::Initialize()
{
    CSceneManager::GetInstance()->InitWhiteFade();

    //育成関連のシーンで共通するUI
    CNatureScene::InitNatureUI(m_pStaminaGage,m_pStaminaBack);

    m_pBack->SetPosition(0.0f, 0.0f, 0.0f);
    m_pBack->SetScale(1.0f, 1.0f, 1.0f);
    m_pBack->SetDisplay(1.0f, 1.0f);
}

//更新関数
void CTraningScene::Update()
{
    //フェードイン処理
    if (!FadeIn()) { return; }

   //キーマネージャーの更新処理
   CKeyManager::GetInstance()->Update();

   //シーンマネージャークラス
   CSceneManager* SceneMng = CSceneManager::GetInstance();

   //テキストの描画を進める
   if (CKeyManager::GetInstance()->IsDown(VK_RETURN) && m_ParamInc.size())
   {
       m_TextNo++;
   }

   //上昇したパラメータのテキストを追加
   AddText();

#if _DEBUG
   ImGui::Begin(JAPANESE("テキストの番号"));
   ImGui::Text(JAPANESE("m_TextNo:%d"), m_TextNo);
   ImGui::Text(JAPANESE("m_TextNo:%d"), m_ParamInc.size());
   ImGui::Text(JAPANESE("m_Stamina:%f"),CHeroManager::GetInstance().GetStamina());
   ImGui::Text(JAPANESE("スタミナゲージの幅:%f"),CSceneManager::GetInstance()->GetStaminaWidth());
   ImGui::End();
#endif

   //テキストの描画が全て終わり次第シーン遷移
   //トレーニングが成功していれば
   if (!CHeroManager::GetInstance().GetFailure())
   {
       if (m_TextNo >= m_ParamInc.size() && !m_SceneTransitionFlg)
       {
           m_SceneTransitionFlg = true;
       }
   }
   else
   {
       //失敗した場合エンターキーで遷移
       if (CKeyManager::GetInstance()->IsDown(VK_RETURN))
       {
           m_SceneTransitionFlg = true;
       }
   }

   //フェードが終わり次第シーン遷移
   if (m_SceneTransitionFlg && FadeOut())
   {
       //休息フラグが立っていたら降ろす
       if (SceneMng->GetRestFlag()) { SceneMng->SetRestFlag(false); }

       CSceneManager::GetInstance()->LoadCreate(CSceneManager::Nature);
   }
}
//描画関数
void CTraningScene::Draw()
{
    //クラスのインスタンスを変数に代入----
    //シーンマネージャー
    CSceneManager* SceneMng = CSceneManager::GetInstance();

    m_pGround->Draw();

    //各トレーニング背景UIの描画
    m_pBack->Draw();
    
    //上昇量テキストの描画
    DrawTraningText();

    //深度を無視する
    SceneMng->GetDx11()->SetDepth(false);
    //育成関連のシーンで共通して表示するUI
    CNatureScene::DrawNatureUI(m_pStaminaGage,m_pStaminaBack);
    //深度を戻す
    SceneMng->GetDx11()->SetDepth(true);

}

////各トレーニングのアニメーション
//void CTraningScene::TraningAnimation()
//{    
//    //----クラスのインスタンスを変数に代入----
//    //テキスト描画クラス
//    WriteText* Text = WriteText::GetInstance();
//    //ヒーローマネージャークラス
//    CHeroManager* HeroMng = &CHeroManager::GetInstance();
//
//    switch (HeroMng->GetTraining())
//    {
//    case CHeroManager::PowerTraining:
//        HeroMng->PowerTraningAnimation();
//        break;
//    case CHeroManager::MagicTraining:
//        HeroMng->MagicTraningAnimation();
//        break;
//    case CHeroManager::SpeedTraining:
//        HeroMng->SpeedTraningAnimation();
//        break;
//    case CHeroManager::HpTraining:
//        HeroMng->HpTraningAnimation();
//        break;
//    default:
//        break;
//    }
//}

//配列にテキストを追加する関数
void CTraningScene::AddText()
{
    //テキスト描画クラスのインスタンスを変数に代入
    WriteText* Text = WriteText::GetInstance();
    //ヒーローマネージャーのインスタンスを変数に代入
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
    bool IsRecoveryStamina = Hero->GetBeforeStamina() <= Hero->GetStamina();
    bool IsReduceStamina = Hero->GetBeforeStamina() >= Hero->GetStamina();
    float StaminaInc = std::abs(Hero->GetStamina() - Hero->GetBeforeStamina());

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
    //----クラスのインスタンスを変数に代入----
    //テキスト描画クラス
    WriteText* Text = WriteText::GetInstance();
    //ヒーローマネージャークラス
    CHeroManager* HeroMng = &CHeroManager::GetInstance();
    //シーンマネージャークラス
    CSceneManager* SceneMng = CSceneManager::GetInstance();

    //----テキストを変数に代入----
    //失敗したか同課によって返すテキストを変える
    std::wstring ResultText = HeroMng->GetFailure() ? L"失敗..." : L"成功!!";

    //トレーニングが失敗したかの条件文
    bool Failure = HeroMng->GetFailure();
    //休息が選択されていたかの条件文
    bool Rest = SceneMng->GetRestFlag();

    //休憩が選択されていない場合
    if (!Rest)
    {
        //トレーニング成功
        if (!Failure)
        {
            //「成功!!」のテキスト描画
            Text->Draw_Text(ResultText, WriteText::Success, RESULTTEXT_OFFSET);
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
    //----クラスのインスタンスを変数に代入----
    //テキスト描画クラス
    WriteText* Text = WriteText::GetInstance();
    //ヒーローマネージャークラス
    CHeroManager* HeroMng = &CHeroManager::GetInstance();

    //描画位置の設定
    //テキストの描画位置を設定
    //初期位置
    D3DXVECTOR2 InitOffset = PARAMTEXT_OFFSET;
    //数値テキストの位置
    D3DXVECTOR2 ValueOffset = VALUETEXT_OFFSET;

    //素早さ、スタミナの場合の調整
    if (param.ParamName == L"素早さが") { ValueOffset.x += 30.0f; }
    else if (param.ParamName == L"スタミナが") { ValueOffset.x += 40.0f; }


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

