#include "CJson.h"
#include <iostream> 

CJson::CJson()
{
}

CJson::~CJson()
{
}

//�t�@�C�����쐬/��������
void CJson::CreateOrWrite( const std::string& hierarchy, json& jsondata)
{
    //�t�@�C��������
    std::string FileName  = jsondata["Name"];
    //�g���q
    std::string Extension = ".json";
    //�t�@�C�����Ɋg���q������
    std::string FilePath =  hierarchy + FileName + Extension;

    //�t�@�C��������Ώ������݁A�Ȃ���΍쐬
    std::ofstream writing_file;
    writing_file.open(FilePath, std::ios::out );
    writing_file << jsondata.dump(true) << std::endl;
    writing_file.close();

}

//�t�@�C���̓ǂݍ���
bool CJson::Load( json& jsondata, const std::string& filename )
{
    //�g���q
    std::string Extension = ".json";
    //�t�@�C���p�X�̐ݒ�
    std::string FilePath = filename + Extension;

    //�w�肳�ꂽ�t�@�C���̓ǂݍ���
    std::ifstream ifs(FilePath.c_str());
    
    //�J���Ȃ������ꍇ�X���[
    if (!ifs.is_open()) { return false; }

    //�t�@�C���̃f�[�^�������ɑ��
    if (ifs.good())
    {
        ifs >> jsondata;
    }

    return true;
}

