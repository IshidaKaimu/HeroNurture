#include "CUtility.h"

CUtility::CUtility()
{
}

CUtility::~CUtility()
{
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

//�����̓���
//���O���͏���
void CUtility::InputText(std::wstring& text,int maxlength)
{
    CKeyManager* KeyMng = &CKeyManager::GetInstance();

    //�L�[�}�l�[�W���̏�ɍs������
    KeyMng->Update();

    //�L�[�S���𒲂ׂ�
    for (int key = 0x30; key <= 0x5A; key++)
    {
        if (KeyMng->IsDown(key))
        {
            //����������
            if (text.length() >= maxlength)
            {
                continue;
            }

            //���͂��ꂽ������ǉ�
            text += wchar_t(key);
        }
    }

    //�e�L�X�g����ł͂Ȃ��Ȃ�
    if (!text.empty())
    {
        //�o�b�N�X�y�[�X�������ꂽ��
        if (KeyMng->IsDown(VK_BACK))
        {
            //�Ō�̕������폜
            text.pop_back();
        }
    }
}

//wstring��string�ɕϊ�
std::string CUtility::WstringToString(std::wstring owstring)
{
    //wstring����SJIS
    int iBufferSize =
        WideCharToMultiByte(CP_OEMCP, 0, owstring.c_str(), -1, (char*)NULL, 0, NULL, NULL);

    //�o�b�t�@�̎擾
    CHAR* cpMultiByte = new CHAR[iBufferSize];

    //wstring����SJIS
    WideCharToMultiByte(CP_OEMCP, 0, owstring.c_str(), -1, cpMultiByte, iBufferSize, NULL, NULL);

    //string�̐���
    std::string oRet(cpMultiByte, cpMultiByte + iBufferSize - 1);

    //�o�b�t�@�̔j��
    delete[] cpMultiByte;

    return (oRet);
}
