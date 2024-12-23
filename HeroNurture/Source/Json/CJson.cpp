#include "CJson.h"
#include <iostream> 
#include "SkinMeshObject\Hero\CHeroManager.h"

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
    writing_file.open(FilePath, std::ios::out);
    writing_file << jsondata.dump(true) << std::endl;
    writing_file.close();
}

//ファイルに追記(ナンバリング機能有り)
void CJson::PostScript(const std::string& hierarchy, json& jsondata)
{
    //ファイル名を代入
    std::string FileName = jsondata["Name"];
    //拡張子
    std::string Extension = ".json";
    //ファイル名に拡張子を結合
    std::string FilePath = hierarchy + FileName + Extension;

    //既存のデータ格納用
    json ExistingData;
    std::ifstream ResultFile(FilePath, std::ios::in);

    //既存データの行数を確認
    int RecordCount = 1;
    //ファイルの内容をロード
    if (ResultFile.is_open())
    {
        //行数
        std::string Line;
        while (std::getline(ResultFile,Line))
        {
            RecordCount++;
        }
        ResultFile.close();
    }

    //データにナンバリングを追加(番号からステータスを呼び出せるように)
    jsondata["Number"] = RecordCount;

    //ファイルに書き込み
    std::ofstream writing_file(FilePath, std::ios::out | std::ios::app);
    if (writing_file.is_open())
    {
        //情報を整形したうえで追記
        writing_file << jsondata.dump(4) << std::endl;
        writing_file.close();
    }
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

//育成情報の書き込み
void CJson::SaveNatureData(const std::string& heroname, json& jsondata, std::string& hierarchy)
{
    //ヒーローマネージャークラスのインスタンスを変数に代入
    CHeroManager* HeroMng = &CHeroManager::GetInstance();

    //書き込む情報の格納
    //----パラメータ----
    jsondata["Name"] = "Result";
    jsondata["HeroName"] = heroname;
    jsondata["Parameter"]["Power"] = HeroMng->GetParam().Power;
    jsondata["Parameter"]["Magic"] = HeroMng->GetParam().Magic;
    jsondata["Parameter"]["Speed"] = HeroMng->GetParam().Speed;
    jsondata["Parameter"]["Hp"] = HeroMng->GetParam().Hp;
    //----適正率----
    jsondata["Appropriate"]["Power"] = HeroMng->GetApp().PowerApp;
    jsondata["Appropriate"]["Magic"] = HeroMng->GetApp().MagicApp;
    jsondata["Appropriate"]["Speed"] = HeroMng->GetApp().SpeedApp;
    jsondata["Appropriate"]["Hp"] = HeroMng->GetApp().HpApp;

    //ファイルに書き込み
    PostScript(hierarchy, jsondata );
}

