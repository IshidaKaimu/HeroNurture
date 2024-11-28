#pragma once
#pragma once
#include <fstream>
#include <iostream>
#include "json.hpp"

//Json�g�p�ɕK�v�Ȗ��O��Ԃ̊i�[
using json = nlohmann::json;

//---------------------
//  Json�N���X
//---------------------
class CJson
{
public:
	CJson();
	~CJson();

	//�t�@�C�����쐬/��������
	void CreateOrWrite( const std::string& hierarchy, json& jsondata );

	//�t�@�C���̓ǂݍ���
	bool Load( json& jsondata,const std::string& filename );

private:
	//json�t�@�C���̃f�[�^
	json m_JsonData;
};
