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

