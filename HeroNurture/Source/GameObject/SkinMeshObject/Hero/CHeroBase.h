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

	// =======================
	// �V�[�����Ƃ̃A�j���[�V�����֐�
	// =======================		
	//�q�[���[�I���V�[��
	virtual void SelectAnimation() {};
	//�琬�V�[��
	virtual void NatureAnimation(int no) {};

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
	void PowerUpEvent(float power) { m_Param.Power += power; };
	//����
	void MagicUpEvent(float magic) { m_Param.Magic += magic; }
	//�f����
	void SpeedUpEvent(float speed) { m_Param.Speed += speed; }
	//�̗�
	void HpUpEvent(float hp){ m_Param.Hp += hp; }

	// =======================
	// �Q�b�^�[�E�Z�b�^�[�֐�
	// =======================		
	//���݂̃p�����[�^
	enParam GetParam()      { return  m_Param; }
	//�L�������Ƃ̓K����
	enAppropriate GetApp()  { return  m_App; }
	//�X�V�O�̃p�����[�^
	enParam GetBeforeParam() { return m_BeforeParam; }
	void SetBeforeParam(enParam before) { m_BeforeParam = before; }
	//���݂̃X�^�~�i��
	float GetStamina() { return m_Stamina; }

protected :	
	// =======================
	// json�t�@�C���֘A�֐�
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

	//�X�^�~�i
	//�ǂ̃q�[���[�ł�����
	float m_Stamina;

private:
	//�p�����[�^�X�V�O�̃p�����[�^���
	enParam m_BeforeParam;
};