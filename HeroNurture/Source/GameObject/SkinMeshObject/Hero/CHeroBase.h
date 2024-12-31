#pragma once
#include "SkinMeshObject\CSkinMeshObject.h"
#include "json.hpp"
#include "Json\CJson.h"
#include "Utility\CUtility.h"

//Json�g�p�ɕK�v�Ȗ��O��Ԃ̊i�[
using json = nlohmann::json;

// =======================
// �萔�錾
// =======================
//----�g���[�j���O�֘A----		
//�g���[�j���O�̊�{�㏸�l
constexpr float INCREASE_VALUE = 20.0f;
//----�X�^�~�i�Q�[�W�֘A----
//�X�^�~�i�̍ő�l
constexpr float MAX_STAMINA = 100.0f;
//�X�^�~�i�̊�{������
constexpr float REDUSE_STAMINA = 25.0f;
//�X�^�~�i�̊�{�񕜗�
constexpr float RECOVERY_STAMINA = 25.0f;


//=====================================
//�q�[���[���N���X
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
	void PowerUp( float stamina );
	//����
	void MagicUp( float stamina );
	//�f����
	void SpeedUp( float stamina );
	//�̗�
	void HpUp( float stamina );

	// =======================
	// �Q�b�^�[�E�Z�b�^�[�֐�
	// =======================		
	//�琬���̃p�����[�^
	enParam GetParam()      { return  m_Param; }
	//�L�������Ƃ̓K����
	enAppropriate GetApp()  { return  m_App; }
	//�X�V�O�̃p�����[�^
	enParam GetBeforeParam() { return m_BeforeParam; }
	void SetBeforeParam(enParam before) { m_BeforeParam = before; }
	//�g���[�j���O���s�t���O
	bool GetFailure() { return m_Failure; }
	void SetFailure(bool failure) { m_Failure = failure; }
	//�o�g���Ɏg�p����p�����[�^
	enParam GetBattleParam() { return m_BattleParam; }
	void SetBattleParam(enParam battle) { m_BattleParam = battle; }
	void SetBattlePower(float power) { m_BattleParam.Power = power; }
	void SetBattleMagic(float magic) { m_BattleParam.Magic = magic; }
	void SetBattleSpeed(float speed) { m_BattleParam.Speed = speed; }
	void SetBattleHp   (float hp)    { m_BattleParam.Hp = hp; }


protected :	
	// =======================
	// json�t�@�C���֘A�֐�
	// =======================		
	//�e�q�[���[�̏����p�����[�^�擾
	void LoadParam(const json& jsondata , const std::string& heroname);
	//�e�q�[���[�̃p�����[�^�X�V
	void UpdateParam(const json& jsondata, const std::string& heroname);

private:
	//�c��X�^�~�i�ʂɂ��␳�֐�
	void CorrectionByStamina(float stamina);
	//���s����Ԃ��֐�
	int FailureRate(float stamina);
	//�g���[�j���O���ʊ֐�
	void TraningResult(float stamina, float app, float& param);

protected:
	// =======================
	// �p�����[�^
	// =======================		
	//�琬��
	enParam m_Param;
	//�o�g��
	enParam m_BattleParam;

	//�q�[���[�̓K�����\����
	enAppropriate m_App;

	//json�N���X
	std::unique_ptr<CJson> m_pJson;

	//���[�U�[�l�[��
	std::string m_UserName;

private:
	//�p�����[�^�X�V�O�̃p�����[�^���
	enParam m_BeforeParam;

	//�c��X�^�~�i�ɂ��␳
	float m_Correction;

	//�g���[�j���O�����s�����ۂɗ��Ă�t���O
	bool m_Failure;

};