#include "WriteText.h"
#include "Scene/CSceneManager.h"

WriteText::WriteText()
    : m_pDWrite     ()
    , m_pDx11       ()
    , m_SetData    ()
{
}

WriteText::~WriteText()
{
    //破棄
    for( int i = enFontType::Max - 1; i > 0; i-- ) {
        SAFE_DELETE( m_pDWrite[i]);
    }
}

void WriteText::Init()
{
    for( int i = 0; i <= enFontType::Max - 1; i++ )
    {
        //インスタンス作成
        m_pDWrite[i] = new DirectWriteCustomFont( &m_SetData[i]);
        m_pDWrite[i]->Init(m_pDx11->GetSwapChain());

        //フォントデータの設定
        m_SetData[i].fontSize   = m_FontData[i].size;   //サイズ
        m_SetData[i].fontWeight = m_FontData[i].weight; //幅
        m_SetData[i].Color      = m_FontData[i].color;  //カラー
        m_SetData[i].font       = m_pDWrite[i]->GetFontName( m_FontData[i].fontNo );   //種類

        //フォントの設定をセット
        m_pDWrite[i]->SetFont(m_SetData[i]);
    }
}

void WriteText::Update()
{
}

//文字列を表示する関数
void WriteText::Draw_Text( std::wstring wstr, enFontType type, D3DXVECTOR2 pos, bool centering, bool Right_alignment)
{
    m_pDWrite[type]->DrawString(wstr, pos, D2D1_DRAW_TEXT_OPTIONS_NONE, centering, Right_alignment);
}
