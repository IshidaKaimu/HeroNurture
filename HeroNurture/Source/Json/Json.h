#pragma once
#include <fstream>
#include <iostream>
#include "json.hpp"

//Json使用に必要な名前空間の格納
using json =  nlohmann::json;

//---------------------
//  Jsonクラス
//---------------------
class CJson
{
public:
	CJson();
	~CJson();

	//ファイルを作成/開く
	bool CreateOrLoad(const std::string& filepath);

	//ファイルの保存
	bool Save(const std::string& filepath);

private:
	json JsonData;
};
