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
    json ExistingData = json::array();
    std::ifstream ResultFile(FilePath, std::ios::in);

    //ファイルの内容をロード
    if (ResultFile.is_open())
    {
        //配列としてファイル内のデータを読み取り
        //※try-catch : 例外(エラー)が発生した際にそれを捕まえて安全に処理を続行できるようにする
        try
        {
            //json配列として読み込む
            ResultFile >> ExistingData;
            //万が一オブジェクト型だった場合は配列に変換
            if (ExistingData.is_object())
            {
                json temp = ExistingData;
                ExistingData = json::array();
                ExistingData.push_back(temp);
            }
        }
        catch (const std::exception&)
        {
            //読み込みに失敗した場合は初期化
            ExistingData = json::array();
        }
        ResultFile.close();
    }

    //データにナンバリングを追加(番号からステータスを呼び出せるように)
    jsondata["Number"] = ExistingData.size() + 1;

    //データを配列に追加
    ExistingData.push_back(jsondata);

    //ファイルに書き込み
    std::ofstream writing_file(FilePath, std::ios::out);
    if (writing_file.is_open())
    {
        //情報を整形したうえで追記
        writing_file << ExistingData.dump(4) << std::endl;
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
    CHeroManager* HeroMng = &CHeroManager::GetInstance();

    //書き込む情報の格納
    //----パラメータ----
    jsondata["Name"] = heroname;
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
    CreateOrWrite(hierarchy, jsondata );
}

void CJson::SaveResult(const std::string& heroname, json& jsondata)
{
    CHeroManager* HeroMng = &CHeroManager::GetInstance();

    //育成結果を保存するファイルの階層
    std::string SaveHierarchy = "Data\\Acount\\Hero\\Result\\";

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
    PostScript(SaveHierarchy, jsondata);

}

//バトルに使用するデータの保存
void CJson::SaveBattleData(json& data, json& writer, int selectno)
{
    CHeroManager* HeroMng = &CHeroManager::GetInstance();

    //バトルに使用するデータを保存するファイルの階層
    std::string SaveHierarchy = "Data\\Acount\\Hero\\BattleData\\";

    //書き込む情報
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
    //ファイルに書き込み
    CreateOrWrite(SaveHierarchy, writer);
}

