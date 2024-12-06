#pragma once
#include "DirectWriteCustomFont/DirectWriteCustomFont.h"
#include "CDirectX11.h"

class WriteText
{
public:
    //�t�H���g�^�C�v�񋓌^
    enum enFontType
    {
        Normal = 0,     //�����ݒ�
        Select,         //�I����
        Name,           //���O
        Turn,           //�^�[����
        Inc,            //�㏸�l

        Max,    //�ő�l
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
        { 60, DWRITE_FONT_WEIGHT_NORMAL, D2D1::ColorF(D2D1::ColorF::Black), 0 },     //�����l
        { 60, DWRITE_FONT_WEIGHT_NORMAL, D2D1::ColorF(D2D1::ColorF::White), 0 },     //�I����
        { 30, DWRITE_FONT_WEIGHT_NORMAL, D2D1::ColorF(D2D1::ColorF::Black), 0 },     //�I����������
        { 80, DWRITE_FONT_WEIGHT_NORMAL, D2D1::ColorF(D2D1::ColorF::LightBlue), 0 }, //�^�[����
        { 60, DWRITE_FONT_WEIGHT_NORMAL, D2D1::ColorF(D2D1::ColorF::Orange), 0 }, //�^�[����
    };
};

