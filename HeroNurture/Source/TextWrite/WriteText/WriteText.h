#pragma once
#include "DirectWriteCustomFont/DirectWriteCustomFont.h"
#include "CDirectX11.h"

//=====================================
// テキスト描画クラス
//=====================================

class WriteText
{
public:
    //フォントタイプ列挙型
    enum enFontType
    {
        Normal = 0,     //初期設定
        Select,         //選択肢
        NameInfo,       //名前入力前指示
        InputName,      //名前(入力時)
        Turn,           //ターン数
        TurnText,       //ターン数関連テキスト
        Inc,            //上昇値
        Dec,            //減少値
        S_Small,        //Sランク(小)
        A_Small,        //Aランク(小)
        B_Small,        //Bランク(小)
        C_Small,        //Cランク(小)
        D_Small,        //Dランク(小)
        E_Small,        //Dランク(小)
        S_Big,          //Sランク(大)
        A_Big,          //Aランク(大)
        B_Big,          //Bランク(大)
        C_Big,          //Cランク(大)
        D_Big,          //Dランク(大)
        E_Big,          //Eランク(大)
        Error,          //エラーメッセージ
        Success,        //トレーニング結果(成功)
        Failure,        //トレーニング結果(失敗)
        Win,            //バトル勝敗(勝利)
        Lose,           //バトル勝敗(敗北)
        Max,            //最大値
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
        { 60, DWRITE_FONT_WEIGHT_NORMAL, D2D1::ColorF(D2D1::ColorF::Black), 0 },         //初期値
        { 60, DWRITE_FONT_WEIGHT_NORMAL, D2D1::ColorF(D2D1::ColorF::White), 0 },         //選択肢
        { 60, DWRITE_FONT_WEIGHT_NORMAL, D2D1::ColorF(D2D1::ColorF::Gray), 0 },          //選択肢
        { 70, DWRITE_FONT_WEIGHT_NORMAL, D2D1::ColorF(D2D1::ColorF::Black), 0 },         //選択肢内説明
        { 85, DWRITE_FONT_WEIGHT_NORMAL, D2D1::ColorF(D2D1::ColorF::DarkBlue), 0 },      //ターン数
        { 80, DWRITE_FONT_WEIGHT_NORMAL, D2D1::ColorF(D2D1::ColorF::Black), 0 },         //ターン数関連テキスト
        { 60, DWRITE_FONT_WEIGHT_NORMAL, D2D1::ColorF(D2D1::ColorF::Orange), 0 },        //上昇値
        { 60, DWRITE_FONT_WEIGHT_NORMAL, D2D1::ColorF(D2D1::ColorF::DarkBlue), 0 },      //減少値
        { 60, DWRITE_FONT_WEIGHT_NORMAL, D2D1::ColorF(D2D1::ColorF::Gold), 0 },          //Sランク(小)
        { 60, DWRITE_FONT_WEIGHT_NORMAL, D2D1::ColorF(D2D1::ColorF::PaleVioletRed), 0 }, //Aランク(小)
        { 60, DWRITE_FONT_WEIGHT_NORMAL, D2D1::ColorF(D2D1::ColorF::Pink), 0 },          //Bランク(小)
        { 60, DWRITE_FONT_WEIGHT_NORMAL, D2D1::ColorF(D2D1::ColorF::LightGreen), 0 },    //Cランク(小)
        { 60, DWRITE_FONT_WEIGHT_NORMAL, D2D1::ColorF(D2D1::ColorF::LightBlue), 0 },     //Dランク(小)
        { 60, DWRITE_FONT_WEIGHT_NORMAL, D2D1::ColorF(D2D1::ColorF::DarkGray), 0 },      //Eランク(小)
        { 120, DWRITE_FONT_WEIGHT_NORMAL, D2D1::ColorF(D2D1::ColorF::Gold), 0 },         //Sランク(大)
        { 120, DWRITE_FONT_WEIGHT_NORMAL, D2D1::ColorF(D2D1::ColorF::PaleVioletRed), 0 },//Aランク(大)
        { 120, DWRITE_FONT_WEIGHT_NORMAL, D2D1::ColorF(D2D1::ColorF::Pink), 0 },         //Bランク(大)
        { 120, DWRITE_FONT_WEIGHT_NORMAL, D2D1::ColorF(D2D1::ColorF::LightGreen), 0 },   //Cランク(大)
        { 120, DWRITE_FONT_WEIGHT_NORMAL, D2D1::ColorF(D2D1::ColorF::LightBlue), 0 },    //Dランク(大)
        { 120, DWRITE_FONT_WEIGHT_NORMAL, D2D1::ColorF(D2D1::ColorF::DarkGray), 0 },     //Eランク(大)
        { 50, DWRITE_FONT_WEIGHT_NORMAL, D2D1::ColorF(D2D1::ColorF::IndianRed), 0 },     //Eランク(大)
        { 100, DWRITE_FONT_WEIGHT_NORMAL, D2D1::ColorF(D2D1::ColorF::Orange), 1 },       //トレーニング結果(成功)
        { 100, DWRITE_FONT_WEIGHT_NORMAL, D2D1::ColorF(D2D1::ColorF::DarkBlue), 1 },     //トレーニング結果(失敗)
        { 200, DWRITE_FONT_WEIGHT_NORMAL, D2D1::ColorF(D2D1::ColorF::Orange), 1 },       //バトル勝敗(勝利)
        { 200, DWRITE_FONT_WEIGHT_NORMAL, D2D1::ColorF(D2D1::ColorF::DarkBlue), 1 },     //バトル勝敗(敗北)
    };
};

