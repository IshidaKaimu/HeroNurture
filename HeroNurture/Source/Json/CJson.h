#pragma once
#pragma once
#include <fstream>
#include <iostream>
#include "json.hpp"

//=====================================
// 前方宣言
//=====================================
//ヒーローマネージャー
class CHeroManager;

//Json使用に必要な名前空間の格納
using json = nlohmann::json;

//---------------------
//  Jsonクラス
//---------------------
class CJson
{
public:
	CJson();
	~CJson();

	//ファイルを作成/書き込み
	void CreateOrWrite( const std::string& hierarchy, json& jsondata );

	//ファイルの読み込み
	bool Load( json& jsondata,const std::string& filename );

	//育成情報の書き込み
	void SaveNatureData(const std::string& heroname, json& json, std::string& savelocation);


private:
	//jsonファイルのデータ
	json m_JsonData;
};
