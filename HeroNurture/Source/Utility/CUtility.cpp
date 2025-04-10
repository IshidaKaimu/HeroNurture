#include "CUtility.h"

CUtility::CUtility()
{
}

CUtility::~CUtility()
{
}

//’l•`‰æ‚ÌŒ…”‚É‚æ‚éˆÊ’u•â³
D3DXVECTOR2 CUtility::PosCorrection(double value, float digit, float x, float y)
{
    //Œ…”(’l‚ğ•¶š—ñ‚É•ÏŠ·‚µ‚ÄŒ…”‚ğæ“¾)
    int DigitCount = static_cast<int>(std::to_wstring(static_cast<int>(value)).length());
    //Œ…”‚É‰‚¶‚½•â³
    float OffsetX = (DigitCount == digit) ? -35.0f : 0.0f;

    return D3DXVECTOR2(x + OffsetX, y);
}

