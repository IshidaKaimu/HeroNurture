#pragma once
#include "SkinMeshObject/CSkinMeshObject.h"
#include "json.hpp"
#include "CJson.h"

//json�֌W�g���̂ɕK�v�Ȗ��O��Ԃ��`
using namespace nlohmann;

/**************************************************
*	�v���C���[�N���X.
**/
class CPlayer
	: public CSkinMeshObject
{
public :
	//�X�e�[�^�X�\����
	struct enStatus
	{
		//�ؗ�
		int Power;
		//����
		int Magic;
		//�f����
		int Speed;
		//�̗�
		int HP;
	};

public:
	CPlayer();
	virtual ~CPlayer() override;


	//�X�V����
	virtual void Update() override;

	//�`�揈��
	virtual void Draw(D3DXMATRIX& View, D3DXMATRIX& Proj,
		LIGHT& Light, CAMERA& Camera) override;



public:

	//���[�U�[�l�[���̐ݒ�
	void SetUserName(const std::string& name) { m_UserName = name; }

	//�t�@�C���f�[�^�ǂݍ���
	void Fromjson(const json& j);

	//�t�@�C���f�[�^�ۑ��֐�
	void Tojson(json& j);

	//�X�e�[�^�X�Z�b�g�֐�
	bool LoadStatus(const std::string& name);

	//�X�e�[�^�X�ۑ��֐�
	bool SaveStatus(const std::string& name);



protected:
	//�v���C���[�̃p�����[�^�\����
	enStatus m_Para;

	//json�N���X
	std::unique_ptr<CJson> m_pJson;

	//���[�U�[�l�[��
	std::string m_UserName;

	//�X�e�[�^�X�t�@�C��
	json Status;


};