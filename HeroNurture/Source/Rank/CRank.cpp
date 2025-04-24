#include "CRank.h"

CRank::CRank()
{
}

CRank::~CRank()
{
}

//�����N�̕`��
void CRank::DrawRank(float value, int typeno,D3DXVECTOR2 pos)
{
    //�e�����N�̊�l�̐ݒ�
    switch (typeno)
    {
    case 1:
        //�����]�����̕`��
        if (value < 3500.0f) { m_Rank = S; }
        if (value < 2000.0f) { m_Rank = A; }
        if (value < 1600.0f) { m_Rank = B; }
        if (value < 1200.0f) { m_Rank = C; }
        if (value < 800.0f) { m_Rank = D; }
        if (value < 400.0f) { m_Rank = E; }
        break;
    case 2:
        //�琬���̕`��
        if (value < 650.0f) { m_Rank = S; }
        if (value < 550.0f) { m_Rank = A; }
        if (value < 450.0f) { m_Rank = B; }
        if (value < 350.0f) { m_Rank = C; }
        if (value < 250.0f) { m_Rank = D; }
        if (value < 150.0f) { m_Rank = E; }
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
    case S:Text->Draw_Text(L"S", TypeS, pos); break;
    case A:Text->Draw_Text(L"A", TypeA, pos); break;
    case B:Text->Draw_Text(L"B", TypeB, pos); break;
    case C:Text->Draw_Text(L"C", TypeC, pos); break;
    case D:Text->Draw_Text(L"D", TypeD, pos); break;
    case E:Text->Draw_Text(L"E", TypeE, pos); break;
    default:break;
    }
}
