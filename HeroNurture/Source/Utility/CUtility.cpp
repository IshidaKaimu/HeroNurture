#include "CUtility.h"

CUtility::CUtility()
{
}

CUtility::~CUtility()
{
}

//�����N�̕`��
void CUtility::DrawRank(float value, int typeno, float x, float y)
{
    //�e�����N�̊�l�̐ݒ�
    switch (typeno)
    {
    case 1:
        //�����]�����̕`��
        if (value < 3500.0f){ m_Rank = S; }
        if (value < 2000.0f){ m_Rank = A; }
        if (value < 1600.0f){ m_Rank = B; }
        if (value < 1200.0f){ m_Rank = C; }
        if (value < 800.0f) { m_Rank = D; }
        if (value < 400.0f) { m_Rank = E; }
        break;
    case 2:    
        //�琬���̕`��
        if (value < 650.0f){ m_Rank = S; }
        if (value < 550.0f){ m_Rank = A; }
        if (value < 450.0f){ m_Rank = B; }
        if (value < 350.0f){ m_Rank = C; }
        if (value < 250.0f){ m_Rank = D; }
        if (value < 150.0f){ m_Rank = E; }
        break;
    default:
        break;
    }

    WriteText* Text = WriteText::GetInstance();

    //���ꂼ��̃����N�̃e�L�X�g�^�C�v�̕ϐ�
    WriteText::enFontType TypeS;
    WriteText::enFontType TypeA;
    WriteText::enFontType TypeB;
    WriteText::enFontType TypeC;
    WriteText::enFontType TypeD;
    WriteText::enFontType TypeE;

    //�琬���ɕ`�悷��ꍇ
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

    //�e�����N�̕`��
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

//�l�`�掞�̌����ɂ��ʒu�␳
D3DXVECTOR2 CUtility::PosCorrection(double value, float digit, float x, float y)
{
    //����(�l�𕶎���ɕϊ����Č������擾)
    int DigitCount = static_cast<int>(std::to_wstring(static_cast<int>(value)).length());
    //�����ɉ������␳
    float OffsetX = (DigitCount == digit) ? -35.0f : 0.0f;

    return D3DXVECTOR2(x + OffsetX, y);
}

