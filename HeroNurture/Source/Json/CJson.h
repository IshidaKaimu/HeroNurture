#pragma once
#pragma once
#include <fstream>
#include <iostream>
#include "json.hpp"

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

private:
	//jsonファイルのデータ
	json m_JsonData;
};
