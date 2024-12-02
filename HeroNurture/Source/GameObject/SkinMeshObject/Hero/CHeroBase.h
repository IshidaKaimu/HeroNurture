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
	virtual void Draw();

	//�A�j���[�V�����֐�
	virtual void Animation();

public:
	//----�X�e�[�^�X�㏸�֐�----
    //�ؗ�
	void PowerUp(int power) 
	{
		m_Param.Power += power; 
		//�㏸�ʕ`��p�̒l
		m_PowerUpValue = power;
	};
	//����
	void MagicUp(int magic) 
	{
		m_Param.Magic += magic; 
		//�㏸�ʕ`��p�̒l
		m_MagicUpValue = magic;
	}
	//�f����
	void SpeedUp(int speed) 
	{
		m_Param.Speed += speed;
		//�㏸�ʕ`��p�̒l
		m_SpeedUpValue = speed;
	}
	//�̗�
	void HpUp(int hp)
	{ 
		m_Param.Hp += hp; 
		//�㏸�ʕ`��p�̒l
		m_HpUpValue = hp;
	}

	//----�Q�b�^�[�E�Z�b�^�[----
	//���݂̃p�����[�^�擾
	enStatus GetParam()   { return  m_Param; }
	//�㏸�ʂ̎擾
	//�ؗ�
	int GetPowerUpValue() { return m_PowerUpValue; }
	//����
	int GetMagicUpValue() { return m_MagicUpValue; }
	//�f����
	int GetSpeedUpValue() { return m_SpeedUpValue; }
	//�̗�
	int GetHpUpValue()    { return m_HpUpValue; }

protected :	
	//----json�֘A----
	//�e�q�[���[�̏����p�����[�^�擾
	void LoadParam( const json& jsondata , const std::string& heroname );

protected:
	//�v���C���[�̃p�����[�^�\����
	enStatus m_Param;

	//json�N���X
	std::unique_ptr<CJson> m_pJson;

	//���[�U�[�l�[��
	std::string m_UserName;

private:
	//----�X�e�[�^�X�㏸�l----
	//�ؗ�
	int m_PowerUpValue;
	//����
	int m_MagicUpValue;
	//�f����
	int m_SpeedUpValue;
	//�̗�
	int m_HpUpValue;


};