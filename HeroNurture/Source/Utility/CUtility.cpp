#include "CUtility.h"

CUtility::CUtility()
{
}

CUtility::~CUtility()
{
}

//値描画時の桁数による位置補正
D3DXVECTOR2 CUtility::PosCorrection(double value, float digit, float x, float y)
{
    //桁数(値を文字列に変換して桁数を取得)
    int DigitCount = static_cast<int>(std::to_wstring(static_cast<int>(value)).length());
    //桁数に応じた補正
    float OffsetX = (DigitCount == digit) ? -35.0f : 0.0f;

    return D3DXVECTOR2(x + OffsetX, y);
}

//文字の入力
//名前入力処理
void CUtility::InputText(std::wstring& text,int maxlength)
{
    CKeyManager* KeyMng = &CKeyManager::GetInstance();

    //キーマネージャの常に行う処理
    KeyMng->Update();

    //キー全部を調べる
    for (int key = 0x30; key <= 0x5A; key++)
    {
        if (KeyMng->IsDown(key))
        {
            //文字数制限
            if (text.length() >= maxlength)
            {
                continue;
            }

            //入力された文字を追加
            text += wchar_t(key);
        }
    }

    //テキストが空ではないなら
    if (!text.empty())
    {
        //バックスペースが押されたら
        if (KeyMng->IsDown(VK_BACK))
        {
            //最後の文字を削除
            text.pop_back();
        }
    }
}

//wstringをstringに変換
std::string CUtility::WstringToString(std::wstring owstring)
{
    //wstringからSJIS
    int iBufferSize =
        WideCharToMultiByte(CP_OEMCP, 0, owstring.c_str(), -1, (char*)NULL, 0, NULL, NULL);

    //バッファの取得
    CHAR* cpMultiByte = new CHAR[iBufferSize];

    //wstringからSJIS
    WideCharToMultiByte(CP_OEMCP, 0, owstring.c_str(), -1, cpMultiByte, iBufferSize, NULL, NULL);

    //stringの生成
    std::string oRet(cpMultiByte, cpMultiByte + iBufferSize - 1);

    //バッファの破棄
    delete[] cpMultiByte;

    return (oRet);
}
