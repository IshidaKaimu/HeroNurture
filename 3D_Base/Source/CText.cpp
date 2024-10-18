#include "CText.h"
#include "DirectWriteCustomFont.h"

CText::CText()
    : m_pDx9()
    , m_pDevice()
    , m_pFont( nullptr )
    , m_x( 0 )
    , m_y( 0 )
{

   m_pDevice = CSceneManager::GetInstance()->GetDx9()->GetDevice();

   // デバイスの有効性を確認
   if (!m_pDevice) {
       MessageBox(NULL, L"DirectX device is NULL", L"Error", MB_OK | MB_ICONERROR);
       return;
   }

   //フォントの作成
    CreateF();
}

CText::~CText()
{
    // フォントオブジェクトを解放
    if( m_pFont ) {
        m_pFont->Release();
    }
}

void CText::SetText( const std::string& text )
{
    // マルチバイト文字列をワイド文字列に変換
    std::wstring wtext( text.begin(), text.end() );
    m_text = wtext;
}

void CText::SetPosition( float x, float y )
{
    m_x = x; // X座標を設定
    m_y = y; // Y座標を設定
}

HRESULT CText::Render() {
    if( m_pFont )
    {
        RECT rect;
        SetRect( &rect, static_cast<LONG>( m_x ), static_cast<LONG>( m_y ),1920, 1080 );

        // DrawText メソッドの戻り値を HRESULT 型として取得
        HRESULT hr = m_pFont->DrawText( NULL, m_text.c_str(), -1, &rect, DT_NOCLIP, D3DCOLOR_XRGB( 255, 255, 255 ) );

        // HRESULT を返す
        return hr;
    }

    // フォントオブジェクトが NULL の場合はエラーコードを返す
    return E_FAIL;
}

void CText::CreateF()
{
    // フォントの設定
    D3DXFONT_DESC fontDesc = {
        50,                   // フォントのサイズ
        0,                    // 不要な設定
        FW_NORMAL,            // フォントの太さ
        0,                    // 不要な設定
        FALSE,                // イタリック体でない
        DEFAULT_CHARSET,      // 文字セット
        OUT_DEFAULT_PRECIS,   // 出力精度
        DEFAULT_QUALITY,      // 品質
        DEFAULT_PITCH,        // ピッチ
        _T("Arial")           // フォントファミリ
    };

    // フォントオブジェクトの作成
    HRESULT hr = D3DXCreateFontIndirect(m_pDevice, &fontDesc, &m_pFont);

    if (FAILED(hr)) {
        std::wstring errorMsg = L"Failed to create font. HRESULT: " + std::to_wstring(hr);
        MessageBox(NULL, errorMsg.c_str(), L"Error", MB_OK | MB_ICONERROR);
    }

}
