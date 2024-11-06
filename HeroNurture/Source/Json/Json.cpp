#include "Json.h"

CJson::CJson()
{
}

CJson::~CJson()
{
}

//�t�@�C�����쐬/�J��
bool CJson::CreateOrLoad(const std::string& filepath)
{
    //�t�@�C��������΃��[�h�A�Ȃ���΍쐬
    std::ifstream file(filepath);

    //���݂��Ȃ��ꍇ
    if (!file.is_open())
    {
        //���Json���쐬�A�ۑ�
        JsonData = json::object();
        return Save(filepath);
    }
    else
    {
        //���[�h
        file >> JsonData;
        file.close();
    }

    return true;
}

//�t�@�C���̕ۑ�
bool CJson::Save(const std::string& filepath)
{
    std::ofstream file(filepath);

    //�J���Ȃ����false��Ԃ�
    if (!file.is_open())
    {
        return false;
    }
    else
    {
        //Json�t�@�C����ۑ�
        file << JsonData;
        file.close();
    }

    return true;
}


