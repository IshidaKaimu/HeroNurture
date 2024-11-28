#pragma once
#include "SkinMeshObject\CSkinMeshObject.h"
#include "json.hpp"
#include "Json\CJson.h"

//Json�g�p�ɕK�v�Ȗ��O��Ԃ̊i�[
using json = nlohmann::json;

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
	virtual void LoadData(const json& jsondata) {};

	//�X�V�֐�
	virtual void Update();

	//�`��֐�
	virtual void Draw( LIGHT& light );

	//�A�j���[�V�����֐�
	virtual void Animation();

public:

	//----�X�e�[�^�X�㏸�֐�----
	//�ؗ�
	void PowerUp(int power )	    { m_Para.Power += power; }
	//����
	void MagicUp(int magic )	    { m_Para.Magic += magic; }
	//�f����
	void SpeedUp(int speed)         { m_Para.Speed += speed; }
	//�̗�
	void HpUp(int hp)		        { m_Para.Hp += hp; }

	//----�Q�b�^�[�E�Z�b�^�[----
	//���݂̃X�e�[�^�X�擾
	enStatus GetStatus() { return m_Para; }

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