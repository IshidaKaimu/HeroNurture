#include "CUtility.h"
#include <random>

CUtility::CUtility()
{
}

CUtility::~CUtility()
{
}

//��������
int CUtility::GenerateRandomValue(int min, int max)
{
    //�V�[�h�l
    std::random_device rd;
    //����������
    std::mt19937 gen(rd());
    //���z�ɗ����������n�����Ƃŗ����͈̔͂��w��
    std::uniform_int_distribution<int> rand_val(min, max);
    return rand_val(gen);
}

//�����N�̕`��
void CUtility::DrawRank(float value, int typeno, float x, float y)
{
    //�e�����N�̊�l�̐ݒ�
    if (value >= 1000.0f){ m_Rank = S; }
    if (value >= 500.0f) { m_Rank = A; }
    if (value >= 400.0f) { m_Rank = B; }
    if (value >= 300.0f) { m_Rank = C; }
    if (value >= 200.0f) { m_Rank = D; }
    if (value < 200.0f)  { m_Rank = E; }

    //�e�L�X�g�`��N���X�̃C���X�^���X��ϐ��ɑ��
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
