#pragma once
#include <fstream>
#include <iostream>
#include "json.hpp"

//Json�g�p�ɕK�v�Ȗ��O��Ԃ̊i�[
using json =  nlohmann::json;

//---------------------
//  Json�N���X
//---------------------
class CJson
{
public:
	CJson();
	~CJson();

	//�t�@�C�����쐬/�J��
	bool CreateOrLoad(const std::string& filepath);

	//�t�@�C���̕ۑ�
	bool Save(const std::string& filepath);

private:
	json JsonData;
};
