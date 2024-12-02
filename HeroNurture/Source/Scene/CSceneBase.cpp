#include "CSceneBase.h"
#include "Sprite2D\UIManager\CUIManager.h"

CSceneBase::CSceneBase()
    : m_Light     ()
    , m_CamPos    ()
    , m_CamLook   ()
    , m_IsScene   (true)
    , m_SelectNo  ()
    , m_pFade     (nullptr)
    , m_FadeTime  (0)
    , m_FadeAlpha (1.0f)	//不透過に設定
    , m_FadeOutFlg(false)
{
    m_pFade = new CUIObject();		//フェード
    m_pFade->AttachSprite(CUIManager::GetSprite(CUIManager::Fade));
    m_pFade->SetAlpha(m_FadeAlpha);
}

CSceneBase::~CSceneBase()
{
	//破棄
	SAFE_DELETE( m_pFade );		//フェード
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
	//描画
	m_pFade->Draw();	//フェード
}

//破棄関数
void CSceneBase::Releace()
{
}

//ロード回数制限フラグの操作
void CSceneBase::IsDataLoaded(bool loaded)
{
    m_IsDataLoaded = loaded;
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

