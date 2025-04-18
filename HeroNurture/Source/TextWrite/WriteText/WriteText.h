#pragma once
#include "DirectWriteCustomFont/DirectWriteCustomFont.h"
#include "CDirectX11.h"

//=====================================
// �e�L�X�g�`��N���X
//=====================================

class WriteText
{
public:
    //�t�H���g�^�C�v�񋓌^
    enum enFontType
    {
        Normal = 0,     //�����ݒ�
        Select,         //�I����
        NameInfo,       //���O���͑O�w��
        InputName,      //���O(���͎�)
        Turn,           //�^�[����
        TurnText,       //�^�[�����֘A�e�L�X�g
        Inc,            //�㏸�l
        Dec,            //�����l
        S_Small,        //S�����N(��)
        A_Small,        //A�����N(��)
        B_Small,        //B�����N(��)
        C_Small,        //C�����N(��)
        D_Small,        //D�����N(��)
        E_Small,        //D�����N(��)
        S_Big,          //S�����N(��)
        A_Big,          //A�����N(��)
        B_Big,          //B�����N(��)
        C_Big,          //C�����N(��)
        D_Big,          //D�����N(��)
        E_Big,          //E�����N(��)
        Error,          //�G���[���b�Z�[�W
        Success,        //�g���[�j���O����(����)
        Failure,        //�g���[�j���O����(���s)
        Win,            //�o�g�����s(����)
        Lose,           //�o�g�����s(�s�k)
        Max,            //�ő�l
    };
    //�t�H���g�f�[�^�\����
    struct FONTDATA
    {
        FLOAT               size;		// �t�H���g�T�C�Y
        DWRITE_FONT_WEIGHT  weight;     // �t�H���g�̑���
        D2D1_COLOR_F        color;		// �t�H���g�̐F
        int                 fontNo;		// �t�H���g��(�ԍ�)
    };
public:
    ~WriteText();

    void Init();

    void Update();

    //�������\������֐�
    void Draw_Text(
        std::wstring wstr,          //������
        enFontType type,            //���
        D3DXVECTOR2 pos,            //�ʒu
        bool centering = false,     //���������̗L�� ��false:��,true:�L
        bool Right_alignment = false//�E����

    );

    void SetDx11(CDirectX11& Dx11) { m_pDx11 = &Dx11; }

    //�V���O���g����
    static WriteText* GetInstance() {
        static WriteText s_Instance;
        return &s_Instance;
    }
private:
    WriteText();
    WriteText(const WriteText& rhs) = delete;
    WriteText& operator = (const WriteText& rhs) = delete;

private:
    //DirectWrite�`��N���X
    DirectWriteCustomFont* m_pDWrite[enFontType::Max];
    //DirectX11
    CDirectX11* m_pDx11;
    //�t�H���g�f�[�^
    FontData m_SetData[enFontType::Max];    //�Z�b�g�p
    FONTDATA m_FontData[enFontType::Max] =  //���͗p
    {
        //�T�C�Y�A�����A�F�A��
        { 60, DWRITE_FONT_WEIGHT_NORMAL, D2D1::ColorF(D2D1::ColorF::Black), 0 },         //�����l
        { 60, DWRITE_FONT_WEIGHT_NORMAL, D2D1::ColorF(D2D1::ColorF::White), 0 },         //�I����
        { 60, DWRITE_FONT_WEIGHT_NORMAL, D2D1::ColorF(D2D1::ColorF::Gray), 0 },          //�I����
        { 70, DWRITE_FONT_WEIGHT_NORMAL, D2D1::ColorF(D2D1::ColorF::Black), 0 },         //�I����������
        { 85, DWRITE_FONT_WEIGHT_NORMAL, D2D1::ColorF(D2D1::ColorF::DarkBlue), 0 },      //�^�[����
        { 80, DWRITE_FONT_WEIGHT_NORMAL, D2D1::ColorF(D2D1::ColorF::Black), 0 },         //�^�[�����֘A�e�L�X�g
        { 60, DWRITE_FONT_WEIGHT_NORMAL, D2D1::ColorF(D2D1::ColorF::Orange), 0 },        //�㏸�l
        { 60, DWRITE_FONT_WEIGHT_NORMAL, D2D1::ColorF(D2D1::ColorF::DarkBlue), 0 },      //�����l
        { 60, DWRITE_FONT_WEIGHT_NORMAL, D2D1::ColorF(D2D1::ColorF::Gold), 0 },          //S�����N(��)
        { 60, DWRITE_FONT_WEIGHT_NORMAL, D2D1::ColorF(D2D1::ColorF::PaleVioletRed), 0 }, //A�����N(��)
        { 60, DWRITE_FONT_WEIGHT_NORMAL, D2D1::ColorF(D2D1::ColorF::Pink), 0 },          //B�����N(��)
        { 60, DWRITE_FONT_WEIGHT_NORMAL, D2D1::ColorF(D2D1::ColorF::LightGreen), 0 },    //C�����N(��)
        { 60, DWRITE_FONT_WEIGHT_NORMAL, D2D1::ColorF(D2D1::ColorF::LightBlue), 0 },     //D�����N(��)
        { 60, DWRITE_FONT_WEIGHT_NORMAL, D2D1::ColorF(D2D1::ColorF::DarkGray), 0 },      //E�����N(��)
        { 120, DWRITE_FONT_WEIGHT_NORMAL, D2D1::ColorF(D2D1::ColorF::Gold), 0 },         //S�����N(��)
        { 120, DWRITE_FONT_WEIGHT_NORMAL, D2D1::ColorF(D2D1::ColorF::PaleVioletRed), 0 },//A�����N(��)
        { 120, DWRITE_FONT_WEIGHT_NORMAL, D2D1::ColorF(D2D1::ColorF::Pink), 0 },         //B�����N(��)
        { 120, DWRITE_FONT_WEIGHT_NORMAL, D2D1::ColorF(D2D1::ColorF::LightGreen), 0 },   //C�����N(��)
        { 120, DWRITE_FONT_WEIGHT_NORMAL, D2D1::ColorF(D2D1::ColorF::LightBlue), 0 },    //D�����N(��)
        { 120, DWRITE_FONT_WEIGHT_NORMAL, D2D1::ColorF(D2D1::ColorF::DarkGray), 0 },     //E�����N(��)
        { 50, DWRITE_FONT_WEIGHT_NORMAL, D2D1::ColorF(D2D1::ColorF::IndianRed), 0 },     //E�����N(��)
        { 100, DWRITE_FONT_WEIGHT_NORMAL, D2D1::ColorF(D2D1::ColorF::Orange), 1 },       //�g���[�j���O����(����)
        { 100, DWRITE_FONT_WEIGHT_NORMAL, D2D1::ColorF(D2D1::ColorF::DarkBlue), 1 },     //�g���[�j���O����(���s)
        { 200, DWRITE_FONT_WEIGHT_NORMAL, D2D1::ColorF(D2D1::ColorF::Orange), 1 },       //�o�g�����s(����)
        { 200, DWRITE_FONT_WEIGHT_NORMAL, D2D1::ColorF(D2D1::ColorF::DarkBlue), 1 },     //�o�g�����s(�s�k)
    };
};

