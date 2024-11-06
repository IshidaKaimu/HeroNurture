#pragma once
#include "SkinMeshObject/CSkinMeshObject.h"
#include "json.hpp"

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
	struct enParamater
	{
		//���[�U�[��
		std::string Username;
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

	//���[�U�[�l�[���̐ݒ�
	void SetUserName(std::wstring& name) { m_UserName = name; }

	//�f�[�^�ǂݍ��݊֐�
	void SetData(std::wstring& name);

	//�f�[�^�쐬�֐�
	void MakeData(std::wstring& name);

	//�X�e�[�^�X�������݊֐�
	void WriteData(std::wstring name,int power,int magic, int speed,int hp);


protected:
	//�v���C���[�̃p�����[�^�\����
	enParamater m_Para;

	//���[�U�[�l�[��
	std::wstring m_UserName;

	//�X�e�[�^�X�t�@�C��
	json Status;


};