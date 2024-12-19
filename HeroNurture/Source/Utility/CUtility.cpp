#include "CUtility.h"
#include <random>

CUtility::CUtility()
{
}

CUtility::~CUtility()
{
}

//乱数生成
int CUtility::GenerateRandomValue(int min, int max)
{
    //シード値
    std::random_device rd;
    //乱数生成器
    std::mt19937 gen(rd());
    //分布に乱数生成器を渡すことで乱数の範囲を指定
    std::uniform_int_distribution<int> rand_val(min, max);
    return rand_val(gen);
}

//ランクの描画
void CUtility::DrawRank(float value, int typeno, float x, float y)
{
    //各ランクの基準値の設定
    switch (typeno)
    {
    case 1:
        //総合評価中の描画
        if (value < 2000.0) { m_Rank = S; }
        if (value < 1500.0f){ m_Rank = A; }
        if (value < 1200.0f){ m_Rank = B; }
        if (value < 900.0f) { m_Rank = C; }
        if (value < 600.0f) { m_Rank = D; }
        if (value < 300.0f) { m_Rank = E; }
        break;
    case 2:    
        //育成中の描画
        if (value < 1000.0f){ m_Rank = S; }
        if (value < 600.0f) { m_Rank = A; }
        if (value < 500.0f) { m_Rank = B; }
        if (value < 400.0f) { m_Rank = C; }
        if (value < 300.0f) { m_Rank = D; }
        if (value < 200.0f) { m_Rank = E; }
        break;
    default:
        break;
    }

    //テキスト描画クラスのインスタンスを変数に代入
    WriteText* Text = WriteText::GetInstance();

    //それぞれのランクのテキストタイプの変数
    WriteText::enFontType TypeS;
    WriteText::enFontType TypeA;
    WriteText::enFontType TypeB;
    WriteText::enFontType TypeC;
    WriteText::enFontType TypeD;
    WriteText::enFontType TypeE;

    //育成中に描画する場合
    switch (typeno)
    {
    case 1:
        TypeS = WriteText::S_Big;
        TypeA = WriteText::A_Big;
        TypeB = WriteText::B_Big;
        TypeC = WriteText::C_Big;
        TypeD = WriteText::D_Big;
        TypeE = WriteText::E_Big;
        break;
    case 2:
        TypeS = WriteText::S_Small;
        TypeA = WriteText::A_Small;
        TypeB = WriteText::B_Small;
        TypeC = WriteText::C_Small;
        TypeD = WriteText::D_Small;
        TypeE = WriteText::E_Small;
        break;
    default:
        break;
    }

    //各ランクの描画
    switch (m_Rank)
    {
    case S:Text->Draw_Text(L"S", TypeS, D3DXVECTOR2(x,y)); break;
    case A:Text->Draw_Text(L"A", TypeA, D3DXVECTOR2(x,y)); break;
    case B:Text->Draw_Text(L"B", TypeB, D3DXVECTOR2(x,y)); break;
    case C:Text->Draw_Text(L"C", TypeC, D3DXVECTOR2(x,y)); break;
    case D:Text->Draw_Text(L"D", TypeD, D3DXVECTOR2(x,y)); break;
    case E:Text->Draw_Text(L"E", TypeE, D3DXVECTOR2(x,y)); break;
    default:break;
    }
}
