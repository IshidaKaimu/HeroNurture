#include "CJson.h"
#include <iostream> 

CJson::CJson()
{
}

CJson::~CJson()
{
}

//ファイルを作成/書き込み
void CJson::CreateOrWrite( const std::string& hierarchy, json& jsondata)
{
    //ファイル名を代入
    std::string FileName  = jsondata["Name"];
    //拡張子
    std::string Extension = ".json";
    //ファイル名に拡張子を結合
    std::string FilePath =  hierarchy + FileName + Extension;

    //ファイルがあれば書き込み、なければ作成
    std::ofstream writing_file;
    writing_file.open(FilePath, std::ios::out );
    writing_file << jsondata.dump(true) << std::endl;
    writing_file.close();

}

//ファイルの読み込み
bool CJson::Load( json& jsondata, const std::string& filename )
{
    //拡張子
    std::string Extension = ".json";
    //ファイルパスの設定
    std::string FilePath = filename + Extension;

    //指定されたファイルの読み込み
    std::ifstream ifs(FilePath.c_str());
    
    //開けなかった場合スルー
    if (!ifs.is_open()) { return false; }

    //ファイルのデータを引数に代入
    if (ifs.good())
    {
        ifs >> jsondata;
    }

    return true;
}

