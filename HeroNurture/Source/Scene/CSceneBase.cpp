#include "CSceneBase.h"
#include "Sprite3D\CSprite3D.h"
#include "Sprite2D\CSprite2D.h"
#include "Sprite2D\UIManager\CUIManager.h"
#include "WriteText\WriteText.h"

CSceneBase::CSceneBase()
    : m_Light     ()
    , m_MoveCamPos     ()
    , m_MoveCamLook    ()
    , m_DebugPos       ()
    , m_DebugUiPos     ()
    , m_DebugCamPos    ()
    , m_DebugCamLook   ()
    , m_IsScene        (true)
    , m_SelectNo       ()
    , m_pFade          (nullptr)
    , m_FadeTime       (0)
    , m_FadeAlpha      (1.0f)	//不透過に設定
    , m_FadeOutFlg     (false)
{
    //フェード
    m_pFade = std::make_unique<CUIObject>();
    m_pFade->AttachSprite(CUIManager::GetSprite(CUIManager::Fade));
    m_pFade->SetAlpha(m_FadeAlpha);
    //白フェード
    m_pWhiteFade = std::make_unique<CUIObject>();
    m_pWhiteFade->AttachSprite(CUIManager::GetSprite(CUIManager::WhiteFade));
    m_pWhiteFade->SetAlpha(m_WhiteFadeAlpha);
    //操作方法指示バー
    m_pControlBar = std::make_unique<CUIObject>();
    m_pControlBar->AttachSprite(CUIManager::GetSprite(CUIManager::ControlBar));
}

CSceneBase::~CSceneBase()
{
}

//初期化関数
void CSceneBase::Initialize()
{
}

//更新関数
void CSceneBase::Update()
{
}

//描画関数
void CSceneBase::Draw()
{
	////描画
	m_pFade->Draw();	 //フェード
    m_pWhiteFade->Draw();//白フェード
}

//破棄関数
void CSceneBase::Releace()
{
}

//フェードアウト
bool CSceneBase::FadeOut()
{
    //デバッグフラグが有効の場合、時間短縮のため処理終了
    if( DEBUG_FLG ) {
        m_FadeAlpha = 0.0f;					//α値を初期化
        m_pFade->SetAlpha(m_FadeAlpha);
        return true;
    }

    //フェードアウトフラグ有効化
    m_FadeOutFlg = true;

    m_FadeTime++;
    m_FadeAlpha += FADESPEED;			//フェード加算
    m_pFade->SetAlpha(m_FadeAlpha);	//α値を設定
    //フェードタイマーが上限まで行けば
    if( m_FadeTime >= FADE_TIME ) {
        //初期化
        m_FadeTime = 0;
        m_FadeAlpha = 1.0f;
        m_FadeOutFlg = false;

        return true;
    }

    return false;
}

//フェードイン
bool CSceneBase::FadeIn()
{
    //フェードアウト中なら処理終了
    if( m_FadeOutFlg ) { return true; }

    //α値が0.0f以下になるまで減算
    if( m_FadeAlpha > 0.0f ) {
        if( m_FadeTime <= FADE_TIME )
        {
            m_FadeTime++;
            m_FadeAlpha -= FADESPEED;
        }
        //フェードイン終了
        if( m_FadeTime >= FADE_TIME ) {
            m_FadeTime = 0;

        }
    }
    else {
        m_FadeAlpha = 0.0f;
        return true;
    }

    m_pFade->SetAlpha(m_FadeAlpha);

    return false;
}

//操作方法指示バーテンプレートの描画
void CSceneBase::DrawControlBar()
{
    WriteText* Text = WriteText::GetInstance();

    //操作方法指示バーの設定
    m_pControlBar->SetPosition(CONTROLBAR_POS);                     //座標
    m_pControlBar->SetScale(CONTROLBAR_SCALE);                      //拡縮
    m_pControlBar->SetDisplay(CONTROLBAR_DISP.x, CONTROLBAR_DISP.y);//幅

    //操作方法指示バー描画
    m_pControlBar->Draw();

    //操作方法指示「Enter 決定」テキストの描画
    Text->Draw_Text(L"Enter 決定", WriteText::Control, ENTERTEXT_POS);
    //操作方法指示「Esc 戻る」テキストの描画
    Text->Draw_Text(L"Esc 戻る", WriteText::Control, ESCAPETEXT_POS);
}

//白フェード関連の初期化
void CSceneBase::InitWhiteFade()
{
    m_WhiteFadeCnt = 0;
    m_AlphaChange = true;
    m_WhiteFadeAlpha = 0.0f;
}

//白フェード再生
void CSceneBase::PlayWhiteFade(int max, float speed, float alpha)
{
    if (m_AlphaChange == false && m_WhiteFadeCnt <= max)
    {
        m_WhiteFadeAlpha += speed;

        if (m_WhiteFadeAlpha >= alpha)
        {
            m_AlphaChange = true;
            m_WhiteFadeCnt++;
        }
    }
    else
    {
        m_WhiteFadeAlpha -= speed;

        if (m_WhiteFadeAlpha < 0.0f)
        {
            m_WhiteFadeAlpha = 0.0f;
            m_AlphaChange = false;
        }
    }

    //α値の設定
    m_pWhiteFade->SetAlpha(m_WhiteFadeAlpha);
}


