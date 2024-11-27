#pragma once
#include "SkinMeshObject\CSkinMeshObject.h"
#include "json.hpp"
#include "CJson.h"

class CYui;
class CKaito;

//json�֌W�g���̂ɕK�v�Ȗ��O��Ԃ��`
using namespace nlohmann;

/**************************************************
*	�q�[���[���N���X.
**/

class CHeroBase
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
		int Hp;
	};

	//�L�����N�^�[���X�g�\����
	enum enCharacterList : unsigned char
	{
		Yui,
		Kaito,

		max,
	};


public:
	CHeroBase();
	virtual ~CHeroBase() override;

	//�������֐�
	//�x�[�X�Ȃ̂ŉ������Ȃ�
	virtual void Initialize() {};

	//�f�[�^�ǂݍ��݊֐�
	virtual void LoadData() {};

	//�X�V�֐�
	virtual void Update();

	//�`��֐�
	virtual void Draw( LIGHT& light );

	//�A�j���[�V�����֐�
	virtual void Animation();

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

	//----�X�e�[�^�X�㏸�֐�----
	//�ؗ�
	void PowerUp(float power ) { m_Para.Power += power; }
	//����
	void MagicPowerUp(float magic ) { m_Para.Magic += magic; }
	//�f����
	void SpeedUp(float speed) { m_Para.Speed += speed; }
	//�̗�
	void HpUp(float hp) { m_Para.Hp += hp; }

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