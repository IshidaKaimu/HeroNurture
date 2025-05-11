#pragma once
#pragma once
#include <fstream>
#include <iostream>
#include "json.hpp"

//=====================================
// �O���錾
//=====================================
//�q�[���[�}�l�[�W���[
class CHeroManager;
//�V�[���}�l�[�W���[
class CSceneManager;

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

	//�t�@�C���ɒǋL
	void PostScript(const std::string& hierarchy, json& jsondata);

	//�t�@�C���̓ǂݍ���
	bool Load( json& jsondata,const std::string& filename );

	//�琬���̏�������
	void SaveNatureData(const std::string& heroname, json& json, std::string& hierarchy);

	//�琬���ʂ̕ۑ�
	void SaveResult(const std::string& heroname, json& json);

	//�o�g���Ɏg�p������̕ۑ�
	void SaveBattleData(json& data, json& writer, int selectno);


private:
	//json�t�@�C���̃f�[�^
	json m_JsonData;
};
