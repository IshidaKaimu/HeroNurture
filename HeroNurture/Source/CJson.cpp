#include "CJson.h"

CJson::CJson()
{
}

CJson::~CJson()
{
}

//ファイルを作成/開く
bool CJson::CreateOrLoad(const std::string& filepath)
{
    //ファイルがあればロード、なければ作成
    std::ifstream file(filepath + ".json");

    //存在しない場合
    if (!file.is_open())
    {
        //空のJsonを作成、保存
        JsonData = json::object();
        return Save(filepath);
    }
    else
    {
        //ロード
        file >> JsonData;
        file.close();
    }

    return true;
}

//ファイルの保存
bool CJson::Save(const std::string& filepath)
{
    std::ofstream file(filepath + ".json" );

    //開けなければfalseを返す
    if (!file.is_open())
    {
        return false;
    }
    else
    {
        //Jsonファイルを保存
        file << JsonData;
        file.close();
    }

    return true;
}

//アカウント用ファイルの作成
bool CJson::CreateOrLoadAcount(const std::string& filepath)
{
    //ファイルがあればロード、なければ作成
    std::ifstream file( "Data\\Acount\\" + filepath + ".json");

    //存在しない場合
    if (!file.is_open())
    {
        //空のJsonを作成、保存
        JsonData = json::object();
        return Save("Data\\Acount\\" + filepath);
    }
    else
    {
        //ロード
        file >> JsonData;
        file.close();
    }

    return true;
}


