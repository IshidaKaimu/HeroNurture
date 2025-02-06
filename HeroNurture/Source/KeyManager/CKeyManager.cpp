#include "CKeyManager.h"
#include <windows.h>

CKeyManager::CKeyManager()
    :m_OldKeys()
    ,m_NowKeys()
{
}

CKeyManager::~CKeyManager()
{
}


void CKeyManager::Update()
{
    //まず過去のキーを格納していた配列を空にする
    m_OldKeys.clear();

    //現在のキーの配列が空でなければ
    if (!m_NowKeys.empty())
    {
        m_OldKeys = m_NowKeys;
    }

    //現在のキーを格納していた配列を空にする
    m_NowKeys.clear();

    //どのキーが押されても対応可能なように255まで調べる
    for (int key = 0; key <= 255; key++)
    {
        if (GetAsyncKeyState(key) & 0x8000)
        {
            m_NowKeys.push_back(key);
        }
    }
}

//キーを離したとき
bool CKeyManager::IsUp(int input)
{
    if (KeyCore(input, m_OldKeys) == true &&
        KeyCore(input, m_NowKeys) == false)
    {
        return true;
    }

    return false;
}

//キーを押したとき
bool CKeyManager::IsDown(int input)
{
    if (KeyCore(input, m_OldKeys) == false &&
        KeyCore(input, m_NowKeys) == true)
    {
        return true;
    }

    return false;
}

//キーを押し続けているとき
bool CKeyManager::IsKeep(int input)
{
    if (KeyCore(input, m_OldKeys) == true &&
        KeyCore(input, m_NowKeys) == true)
    {
        return true;
    }

    return false;
}

//IsUp,IsDown,IsKeepで使用している関数
bool CKeyManager::KeyCore(int input, vector<int> keymax)
{
    //Vector配列の要素数分回して調べる
    for (auto i : keymax)
    {
        /*入力されたキーと配列に割り当てられたキーナンバーが
        合致したときのみ出力する*/
        if (input == i)
        {
            return true;
        }
    }
    return false;
}

