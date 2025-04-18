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
    writing_file.open(FilePath, std::ios::out);
    writing_file << jsondata.dump(true) << std::endl;
    writing_file.close();
}


//�t�@�C���ɒǋL(�i���o�����O�@�\�L��)
void CJson::PostScript(const std::string& hierarchy, json& jsondata)
{
    //�t�@�C��������
    std::string FileName = jsondata["Name"];
    //�g���q
    std::string Extension = ".json";
    //�t�@�C�����Ɋg���q������
    std::string FilePath = hierarchy + FileName + Extension;

    //�����̃f�[�^�i�[�p
    json ExistingData = json::array();
    std::ifstream ResultFile(FilePath, std::ios::in);

    //�t�@�C���̓��e�����[�h
    if (ResultFile.is_open())
    {
        //�z��Ƃ��ăt�@�C�����̃f�[�^��ǂݎ��
        //��try-catch : ��O(�G���[)�����������ۂɂ����߂܂��Ĉ��S�ɏ����𑱍s�ł���悤�ɂ���
        try
        {
            //json�z��Ƃ��ēǂݍ���
            ResultFile >> ExistingData;
            //������I�u�W�F�N�g�^�������ꍇ�͔z��ɕϊ�
            if (ExistingData.is_object())
            {
                json temp = ExistingData;
                ExistingData = json::array();
                ExistingData.push_back(temp);
            }
        }
        catch (const std::exception&)
        {
            //�ǂݍ��݂Ɏ��s�����ꍇ�͏�����
            ExistingData = json::array();
        }
        ResultFile.close();
    }

    //�f�[�^�Ƀi���o�����O��ǉ�(�ԍ�����X�e�[�^�X���Ăяo����悤��)
    jsondata["Number"] = ExistingData.size() + 1;

    //�f�[�^��z��ɒǉ�
    ExistingData.push_back(jsondata);

    //�t�@�C���ɏ�������
    std::ofstream writing_file(FilePath, std::ios::out);
    if (writing_file.is_open())
    {
        //���𐮌`���������ŒǋL
        writing_file << ExistingData.dump(4) << std::endl;
        writing_file.close();
    }
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
void CJson::SaveNatureData(const std::string& heroname, json& jsondata, std::string& hierarchy)
{
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
    CreateOrWrite(hierarchy, jsondata );
}

void CJson::SaveResult(const std::string& heroname, json& jsondata)
{
    CHeroManager* HeroMng = &CHeroManager::GetInstance();

    //�琬���ʂ�ۑ�����t�@�C���̊K�w
    std::string SaveHierarchy = "Data\\Acount\\Hero\\Result\\";

    //�������ޏ��̊i�[
    //----�p�����[�^----
    jsondata["Name"] = "Result";
    jsondata["HeroName"] = heroname;
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
    PostScript(SaveHierarchy, jsondata);

}

//�o�g���Ɏg�p����f�[�^�̕ۑ�
void CJson::SaveBattleData(json& data, json& writer, int selectno)
{
    CHeroManager* HeroMng = &CHeroManager::GetInstance();

    //�o�g���Ɏg�p����f�[�^��ۑ�����t�@�C���̊K�w
    std::string SaveHierarchy = "Data\\Acount\\Hero\\BattleData\\";

    //�������ޏ��
    for (const auto& battledata : data)
    {
        if (battledata["Number"] == selectno)
        {
            writer["Name"] = "BattleParam";
            HeroMng->SetBattleHeroName(battledata["HeroName"]);
            writer["Parameter"]["Power"] = battledata["Parameter"]["Power"];
            writer["Parameter"]["Magic"] = battledata["Parameter"]["Magic"];
            writer["Parameter"]["Speed"] = battledata["Parameter"]["Speed"];
            writer["Parameter"]["Hp"] = battledata["Parameter"]["Hp"];
        }
    }
    //�t�@�C���ɏ�������
    CreateOrWrite(SaveHierarchy, writer);
}

