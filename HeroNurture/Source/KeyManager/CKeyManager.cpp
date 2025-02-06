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
    //�܂��ߋ��̃L�[���i�[���Ă����z�����ɂ���
    m_OldKeys.clear();

    //���݂̃L�[�̔z�񂪋�łȂ����
    if (!m_NowKeys.empty())
    {
        m_OldKeys = m_NowKeys;
    }

    //���݂̃L�[���i�[���Ă����z�����ɂ���
    m_NowKeys.clear();

    //�ǂ̃L�[��������Ă��Ή��\�Ȃ悤��255�܂Œ��ׂ�
    for (int key = 0; key <= 255; key++)
    {
        if (GetAsyncKeyState(key) & 0x8000)
        {
            m_NowKeys.push_back(key);
        }
    }
}

//�L�[�𗣂����Ƃ�
bool CKeyManager::IsUp(int input)
{
    if (KeyCore(input, m_OldKeys) == true &&
        KeyCore(input, m_NowKeys) == false)
    {
        return true;
    }

    return false;
}

//�L�[���������Ƃ�
bool CKeyManager::IsDown(int input)
{
    if (KeyCore(input, m_OldKeys) == false &&
        KeyCore(input, m_NowKeys) == true)
    {
        return true;
    }

    return false;
}

//�L�[�����������Ă���Ƃ�
bool CKeyManager::IsKeep(int input)
{
    if (KeyCore(input, m_OldKeys) == true &&
        KeyCore(input, m_NowKeys) == true)
    {
        return true;
    }

    return false;
}

//IsUp,IsDown,IsKeep�Ŏg�p���Ă���֐�
bool CKeyManager::KeyCore(int input, vector<int> keymax)
{
    //Vector�z��̗v�f�����񂵂Ē��ׂ�
    for (auto i : keymax)
    {
        /*���͂��ꂽ�L�[�Ɣz��Ɋ��蓖�Ă�ꂽ�L�[�i���o�[��
        ���v�����Ƃ��̂ݏo�͂���*/
        if (input == i)
        {
            return true;
        }
    }
    return false;
}

