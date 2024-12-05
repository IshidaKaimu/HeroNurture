#pragma once
#include "SkinMeshObject\CSkinMeshObject.h"
#include "json.hpp"
#include "Json\CJson.h"

//Json�g�p�ɕK�v�Ȗ��O��Ԃ̊i�[
using json = nlohmann::json;

//�g���[�j���O���㏸�l�̊�b
constexpr float INCREASE_VALUE = 20.0f;

//=====================================
//�q�[���[���N���X
//����ҁF�Γc�D��
//=====================================

class CHeroBase
	: public CSkinMeshObject
{
public :
	//�p�����[�^�\����
	struct enParam
	{
		//�ؗ�
		float Power;
		//����
		float Magic;
		//�f����
		float Speed;
		//�̗�
		float Hp;
	};

	//�K�����\����
	struct enAppropriate
	{
		//�ؗ�
		float PowerApp;
		//����
		float MagicApp;
		//�f����
		float SpeedApp;
		//�̗�
		float HpApp;
	};

	//�L�����N�^�[���X�g�\����
	enum enCharacterList : char
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
	virtual void LoadMeshData() {};

	//�p�����[�^���ǂݍ���
	virtual void LoadParamData(const json& jsondata) {};

	//�X�V�֐�
	virtual void Update();

	//�`��֐�
	virtual void Draw();

	//�A�j���[�V�����֐�
	virtual void Animation();

public:
	// =======================
	// �X�e�[�^�X�㏸�֐�
	// =======================		
	//----�g���[�j���O�ɂ��㏸----
	//�ؗ�
	void PowerUp();
	//����
	void MagicUp();
	//�f����
	void SpeedUp();
	//�̗�
	void HpUp();

	//----�C�x���g�ɂ��㏸----
    //�ؗ�
	void PowerUpEvent(float power) 
	{
		m_Param.Power += power; 
		//�㏸�ʕ`��p�̒l
		m_PowerUpValue = power;
	};
	//����
	void MagicUpEvent(float magic) 
	{
		m_Param.Magic += magic; 
		//�㏸�ʕ`��p�̒l
		m_MagicUpValue = magic;
	}
	//�f����
	void SpeedUpEvent(float speed) 
	{
		m_Param.Speed += speed;
		//�㏸�ʕ`��p�̒l
		m_SpeedUpValue = speed;
	}
	//�̗�
	void HpUpEvent(float hp)
	{ 
		m_Param.Hp += hp; 
		//�㏸�ʕ`��p�̒l
		m_HpUpValue = hp;
	}

	// =======================
	// �Q�b�^�[�E�Z�b�^�[
	// =======================		
	//���݂̃p�����[�^�擾
	enParam GetParam()      { return  m_Param; }
	//�L�������Ƃ̓K�����擾
	enAppropriate GetApp()  { return  m_App; }

	//�X�V�O�̃p�����[�^
	enParam GetBeforeParam() { return m_BeforeParam; }
	void SetBeforeParam(enParam before) { m_BeforeParam = before; }

	//�㏸��
	//�ؗ�
	float GetPowerUpValue() { return m_PowerUpValue; }
	//����
	float GetMagicUpValue() { return m_MagicUpValue; }
	//�f����
	float GetSpeedUpValue() { return m_SpeedUpValue; }
	//�̗�
	float GetHpUpValue()    { return m_HpUpValue; }

protected :	
	// =======================
	// json�t�@�C���֘A
	// =======================		
	//�e�q�[���[�̏����p�����[�^�擾
	void LoadParam( const json& jsondata , const std::string& heroname );
	//�e�q�[���[�̃p�����[�^�X�V
	void UpdateParam( const json& jsondata, const std::string& heroname );

protected:
	//�q�[���[�̃p�����[�^�\����
	enParam m_Param;

	//�q�[���[�̓K�����\����
	enAppropriate m_App;

	//json�N���X
	std::unique_ptr<CJson> m_pJson;

	//���[�U�[�l�[��
	std::string m_UserName;

private:
	//�p�����[�^�X�V�O�̃p�����[�^���
	enParam m_BeforeParam;

	//----�X�e�[�^�X�㏸�l----
	//�ؗ�
	float m_PowerUpValue;
	//����
	float m_MagicUpValue;
	//�f����
	float m_SpeedUpValue;
	//�̗�
	float m_HpUpValue;
};