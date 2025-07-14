#pragma once
#include <d3dx9.h> // DirectX 9のヘッダーを含めます
#include <string>
#include "CDirectX9.h"
#include "Scene/CSceneManager.h"

//=============================================================================
//	テキストクラス
//  GitHubより引用
//=============================================================================
class CText {
public:
    // コンストラクタ：Direct3Dデバイスを受け取り、フォントオブジェクトを作成します
    CText();

    // デストラクタ：フォントオブジェクトの解放を行います
    ~CText();

    //DirectX9の取得
    void SetDx9( CDirectX9& Dx9 ) { m_pDx9 = &Dx9; }

    // 表示するテキストを設定します
    void SetText( const std::string& text );

    // テキストを表示する位置を設定します
    void SetPosition( float x, float y );

    // テキストを描画します
    HRESULT Render();

    //テキストの作成
    void CreateF();

private:
    CDirectX9*         m_pDx9;
    LPDIRECT3DDEVICE9  m_pDevice; // Direct3Dデバイスへのポインタ
    LPD3DXFONT m_pFont;           // フォントオブジェクトへのポインタ
    std::wstring m_text;          // std::wstringに変更
    float m_x, m_y;               // テキストの表示位置
};