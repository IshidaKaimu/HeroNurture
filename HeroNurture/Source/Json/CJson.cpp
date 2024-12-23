#include "CJson.h"
#include <iostream> 
#include "SkinMeshObject\Hero\CHeroManager.h"

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

//�琬���̏�������
void CJson::SaveNatureData(const std::string& heroname, json& jsondata, std::string& savelocation)
{
    //�q�[���[�}�l�[�W���[�N���X�̃C���X�^���X��ϐ��ɑ��
    CHeroManager* HeroMng = &CHeroManager::GetInstance();

    //�������ޏ��̊i�[
    //----�p�����[�^----
    jsondata["Name"] = heroname;
    jsondata["Parameter"]["Power"] = HeroMng->GetParam().Power;
    jsondata["Parameter"]["Magic"] = HeroMng->GetParam().Magic;
    jsondata["Parameter"]["Speed"] = HeroMng->GetParam().Speed;
    jsondata["Parameter"]["Hp"] = HeroMng->GetParam().Hp;
    //----�K����----
    jsondata["Appropriate"]["Power"] = HeroMng->GetApp().PowerApp;
    jsondata["Appropriate"]["Magic"] = HeroMng->GetApp().MagicApp;
    jsondata["Appropriate"]["Speed"] = HeroMng->GetApp().SpeedApp;
    jsondata["Appropriate"]["Hp"] = HeroMng->GetApp().HpApp;

    //�t�@�C���ɏ�������
    CreateOrWrite(savelocation, jsondata );
}

