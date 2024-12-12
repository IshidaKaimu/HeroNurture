#include "CTraning.h"
#include "ImGui\ImGuiManager\ImGuiManager.h"
#include "KeyManager\CKeyManager.h"
#include "Scene\CSceneManager.h"
#include "WriteText\WriteText.h"
#include "SkinMeshObject\Hero\CHeroManager.h"

CTraning::CTraning()
    : m_pCamera (&CCameraManager::GetInstance())
    , m_pSky    ()
    , m_pGround ()
    , m_TextNo  ()
{
}

CTraning::~CTraning()
{
}

//構築関数
void CTraning::Create()
{
    //----インスタンス生成----
    //スタティックメッシュオブジェクト
    //空
    m_pSky = make_unique<CSky>();
    //地面
    m_pGround = make_unique<CGround>();

    //育成関連のシーンで共通するUIのインスタンス生成
    CNatureScene::CreateNatureUI(m_pStaminaGage);

}
//破棄関数
void CTraning::Releace()
{
}
//データ読み込み関数
void CTraning::LoadData()
{
    //地面のメッシュデータ設定
    m_pGround->LoadData();

    //育成関連のシーンで共通するUIのスプライトデータ設定
    CNatureScene::LoadNatureUI(m_pStaminaGage);
}
//初期化関数
void CTraning::Initialize()
{
    //育成関連のシーンで共通するUI
    CNatureScene::InitNatureUI(m_pStaminaGage);
}

//更新関数
void CTraning::Update()
{
    //フェードイン処理
    if (!FadeIn()) { return; }

   //キーマネージャーの更新処理
   CKeyManager::GetInstance()->Update();

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
   if (m_TextNo >= m_ParamInc.size() && !m_SceneTransitionFlg)
   {
       m_SceneTransitionFlg = true;
   }

   if (m_SceneTransitionFlg && FadeOut())
   {
       CSceneManager::GetInstance()->LoadCreate(CSceneManager::Nature);
   }
}
//描画関数
void CTraning::Draw()
{
    m_pGround->Draw();
    //上昇量テキストの描画(仮)
    DrawUpText();

    //育成関連のシーンで共通して表示するUI
    CNatureScene::DrawNatureUI(m_pStaminaGage);
}

//配列にテキストを追加する関数
void CTraning::AddText()
{
    //テキスト描画クラスのインスタンスを変数に代入
    WriteText* Text = WriteText::GetInstance();
    //ヒーローマネージャーのインスタンスを変数に代入
    CHeroManager* Hero = &CHeroManager::GetInstance();

    //----それぞれのパラメータが上昇していた場合の条件文----
    //筋力
    bool IsPowerUp = Hero->GetBeforeParam().Power < Hero->GetParam().Power;
    //魔力
    bool IsMagicUp = Hero->GetBeforeParam().Magic < Hero->GetParam().Magic;
    //素早さ
    bool IsSpeedUp = Hero->GetBeforeParam().Speed < Hero->GetParam().Speed;
    //体力
    bool IsHpUp = Hero->GetBeforeParam().Hp < Hero->GetParam().Hp;

    //条件を満たしていれば構造体配列に格納                                   パラメータ名,上昇量
    if (IsPowerUp && !AlreadyAddCheck(L"筋力が"))   { m_ParamInc.push_back({L"筋力が",static_cast<int>(Hero->GetParam().Power - Hero->GetBeforeParam().Power)}); }
    if (IsMagicUp && !AlreadyAddCheck(L"魔力が"))   { m_ParamInc.push_back({ L"魔力が",static_cast<int>(Hero->GetParam().Magic - Hero->GetBeforeParam().Magic) }); }
    if (IsSpeedUp && !AlreadyAddCheck(L"素早さが")) { m_ParamInc.push_back({ L"素早さが",static_cast<int>(Hero->GetParam().Speed - Hero->GetBeforeParam().Speed) }); }
    if (IsHpUp    && !AlreadyAddCheck(L"体力が"))   { m_ParamInc.push_back({ L"体力が",static_cast<int>(Hero->GetParam().Hp - Hero->GetBeforeParam().Hp) }); }

}

//配列に追加済みでないか調べる関数
bool CTraning::AlreadyAddCheck(std::wstring paramname)
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

//上昇量テキストの描画
void CTraning::DrawUpText()
{
    //テキスト描画クラスのインスタンスを変数に代入
    WriteText* Text = WriteText::GetInstance();
    //ヒーローマネージャーのインスタンスを変数に代入
    CHeroManager* Hero = &CHeroManager::GetInstance();

    //「上昇した!」テキスト
    std::wstring UpText = L"上昇した！";

    //テキストの描画位置を設定
    //1行文の高さ
    D3DXVECTOR2 TextOffset = { 0.0f, 60.0f };
    //初期位置
    D3DXVECTOR2 InitOffset = PARAMTEXT_OFFSET;
    //数値テキストの位置
    D3DXVECTOR2 ValueOffset = VALUETEXT_OFFSET;

    if (m_TextNo < m_ParamInc.size())
    {
        const auto& Increase = m_ParamInc[m_TextNo];
        
        //素早さの時のみ位置をずらす
        if (Increase.ParamName == L"素早さが") { ValueOffset.x += 30.0f; }

        Text->Draw_Text(Increase.ParamName, WriteText::Normal, InitOffset);
        Text->Draw_Text(std::to_wstring(Increase.IncValue) + L"上昇した！", WriteText::Inc, ValueOffset);
    }
}

