#include "CJson.h"

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
    std::ifstream file(filepath + ".json");

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
    std::ofstream file(filepath + ".json" );

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

//�A�J�E���g�p�t�@�C���̍쐬
bool CJson::CreateOrLoadAcount(const std::string& filepath)
{
    //�t�@�C��������΃��[�h�A�Ȃ���΍쐬
    std::ifstream file( "Data\\Acount\\" + filepath + ".json");

    //���݂��Ȃ��ꍇ
    if (!file.is_open())
    {
        //���Json���쐬�A�ۑ�
        JsonData = json::object();
        return Save("Data\\Acount\\" + filepath);
    }
    else
    {
        //���[�h
        file >> JsonData;
        file.close();
    }

    return true;
}


