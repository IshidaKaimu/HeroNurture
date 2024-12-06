#pragma once
#include "DirectWriteCustomFont/DirectWriteCustomFont.h"
#include "CDirectX11.h"

class WriteText
{
public:
    //フォントタイプ列挙型
    enum enFontType
    {
        Normal = 0,     //初期設定
        Select,         //選択肢
        Name,           //名前
        Turn,           //ターン数
        Inc,            //上昇値

        Max,    //最大値
    };
    //フォントデータ構造体
    struct FONTDATA
    {
        FLOAT               size;		// フォントサイズ
        DWRITE_FONT_WEIGHT  weight;     // フォントの太さ
        D2D1_COLOR_F        color;		// フォントの色
        int                 fontNo;		// フォント名(番号)
    };
public:
    ~WriteText();

    void Init();

    void Update();

    //文字列を表示する関数
    void Draw_Text(
        std::wstring wstr,          //文字列
        enFontType type,            //種類
        D3DXVECTOR2 pos,            //位置
        bool centering = false,     //中央揃えの有無 ※false:無,true:有
        bool Right_alignment = false//右揃え
    );

    void SetDx11(CDirectX11& Dx11) { m_pDx11 = &Dx11; }

    //シングルトン化
    static WriteText* GetInstance() {
        static WriteText s_Instance;
        return &s_Instance;
    }
private:
    WriteText();
    WriteText(const WriteText& rhs) = delete;
    WriteText& operator = (const WriteText& rhs) = delete;

private:
    //DirectWrite描画クラス
    DirectWriteCustomFont* m_pDWrite[enFontType::Max];
    //DirectX11
    CDirectX11* m_pDx11;
    //フォントデータ
    FontData m_SetData[enFontType::Max];    //セット用
    FONTDATA m_FontData[enFontType::Max] =  //入力用
    {
        //サイズ、太さ、色、名
        { 60, DWRITE_FONT_WEIGHT_NORMAL, D2D1::ColorF(D2D1::ColorF::Black), 0 },     //初期値
        { 60, DWRITE_FONT_WEIGHT_NORMAL, D2D1::ColorF(D2D1::ColorF::White), 0 },     //選択肢
        { 30, DWRITE_FONT_WEIGHT_NORMAL, D2D1::ColorF(D2D1::ColorF::Black), 0 },     //選択肢内説明
        { 80, DWRITE_FONT_WEIGHT_NORMAL, D2D1::ColorF(D2D1::ColorF::LightBlue), 0 }, //ターン数
        { 60, DWRITE_FONT_WEIGHT_NORMAL, D2D1::ColorF(D2D1::ColorF::Orange), 0 }, //ターン数
    };
};

