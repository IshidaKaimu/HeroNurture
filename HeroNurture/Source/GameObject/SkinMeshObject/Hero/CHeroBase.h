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
//�o�g���V�[���ł̏������W
const D3DXVECTOR3 BATTLEINIT_POS = { -4.5f,0.0f,0.0f }; //����
const D3DXVECTOR3 ENEMYINIT_POS  = { 2.5f,0.0f,0.0f };	//�G
//�o�g���V�[���ł̉�]
const D3DXVECTOR3 BATTLE_ROTATE = { 0.0f,D3DXToRadian(-90.0f),0.0f };//����
const D3DXVECTOR3 ENEMY_ROTATE  = { 0.0f,D3DXToRadian(90.0f),0.0f }; //�G

//=====================================
// �q�[���[���N���X
// �����:�Γc�D��
//=====================================
class CHeroBase
	: public CSkinMeshObject
{
public :
	//�q�[���[�����X�g
	enum enHeroList :char
	{
		Yui,
		Kaito,
		Max,
	};

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

public:
	CHeroBase();
	virtual ~CHeroBase() override;

	// =======================
	// �e�V�[�����Ƃ̏�����
	// =======================
	//��Ɏg�p���鏉�����֐�
	virtual void Initialize() {};
	//�o�g���V�[���Ŏg�p���鏉����
	virtual void BattleInitialize() {};
	//�G�ɂȂ����ۂ̏������֐�
	virtual void EnemyInit() {};
	//�ŗL�U���A�j���[�V�������̏�����
	virtual void UniqueInit() {};

	//�f�[�^�ǂݍ��݊֐�
	virtual void LoadMeshData() {};

	//�p�����[�^���ǂݍ���
	virtual void LoadParamData(const json& jsondata) {};

	//�o�g���p�����[�^���ǂݍ���
	virtual void SetBattleParamData(const json& jsondata) {};

	//�X�V�֐�
	virtual void Update();

	//�`��֐�
	virtual void Draw();

	//�f�o�b�O�֐�
	virtual void Debug() {};

public:
	// =======================
	// �V�[�����Ƃ̃A�j���[�V�����֐�
	// =======================		
	//�琬�q�[���[�I���V�[��
	virtual void NatureHeroSelectAnimation() {};
	//�o�g���q�[���[�I���V�[��
	virtual void BattleHeroSelectAnimation() {};
	//�琬�V�[��
	virtual void NatureAnimation(int no) {};

    // =======================
	// �U���֐�
	// =======================
	//�U��1(�ؗ͂ɂ��U��)
	virtual float PowerAttack();
	//�U��1(���͂ɂ��U��)
	virtual float MagicAttack();
	//�ŗL�U��(�e�q�[���[�̈�ԍ����X�e�[�^�X�𔽉f�����U��)
	virtual float UniqueAttack() { return 0; }

	// =======================
	// �e�o�g���t�F�[�Y�ł̃A�j���[�V����
	// =======================
	// �s���I�𒆂̃A�j���[�V����
	virtual void MoveSelectAnim() {};
	//----�U���t�F�[�Y----
	//�U��1���̃A�j���[�V����
	virtual void PowerAttackAnim(float vector) {};
	//�U��2���̃A�j���[�V����
	virtual void MagicAttackAnim(float vector) {};
	//�ŗL�U�����̃A�j���[�V����
	virtual void UniqueAttackAnim() {};
	//�_���[�W�A�j���[�V����
	virtual void DamageAnim(float vector) {};

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

	//�_���[�W�֐�
	void Damage(float damage);

	// =======================
	// �Q�b�^�[�E�Z�b�^�[�֐�
	// =======================		
	//�琬���̃p�����[�^
	enParam GetParam()       { return  m_Param; }
	//�o�g���Ɏg�p����p�����[�^
	enParam GetBattleParamData() { return m_BattleParam; }
	//�o�g���Ɏg�p����q�[���[�̖��O
	std::string GetBattleHeroName() { return m_BattleHeroName; }
	void SetBattleHeroName(std::string heroname) { m_BattleHeroName = heroname; }
	//�L�������Ƃ̓K����
	enAppropriate GetApp()  { return  m_App; }
	//�X�V�O�̃p�����[�^
	enParam GetBeforeParam() { return m_BeforeParam; }
	void SetBeforeParam(enParam before) { m_BeforeParam = before; }
	//�g���[�j���O���s�t���O
	bool GetFailure() { return m_Failure; }
	void SetFailure(bool failure) { m_Failure = failure; }
	//�o�g���Ɏg�p����p�����[�^���̐ݒ�
	void SetBattleParam(const json& jsondata);
	//�o�g������HP
	float GetHp() { return m_Hp; }
	void SetHp(float hp) { m_Hp = hp; }
	//�ŗL�U���Q�[�W
	int GetUniqueGage() { return m_UniqueGage; }
	//�_���[�W�t���O
	bool GetDamageFlag() { return m_Damage; }
	void SetDamageFlag(bool damage) { m_Damage = damage; }
	//�A�j���[�V�����I���t���O
	bool GetAnimEndFlag() { return m_AnimEnd; }
	void SetAnimEndFlag(bool animend) { m_AnimEnd = animend; }
	//�_���[�W�A�j���[�V�����I���t���O
	bool GetDamageAnimEndFlag() { return m_DamageAnimEnd; }
	void SetDamageAnimEndFlag(bool damageanimend) { m_DamageAnimEnd = damageanimend; }

	//�A�j���[�V�����؂�ւ��֐�
	virtual void AnimChange(int animno);

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

	//�o�g������q�[���[�̖��O
	std::string m_BattleHeroName;

	//�q�[���[�̓K�����\����
	enAppropriate m_App;

	//json�N���X
	std::unique_ptr<CJson> m_pJson;

	//���[�U�[�l�[��
	std::string m_UserName;

	//----�f�o�b�O�p----
	D3DXVECTOR3 DebugPos;
	D3DXVECTOR3 DebugScale;

	//���݂̗̑�
	float m_Hp;

	//���݂̌ŗL�U���Q�[�W
	int m_UniqueGage;

	//�A�j���[�V�����p�J�E���g
	int m_AnimCnt;
	//�G�t�F�N�g�p�J�E���g
	int m_EffCnt;

	//�C�x���g�V�[���p�̕ϓ�������ϐ�
	float m_MoveX; //X���W
	float m_MoveY; //Y���W
	float m_MoveZ; //Z���W

	//�_���[�W���󂯂��Ƃ����Ă�t���O
	bool m_Damage;

	//�A�j���[�V�������I�������痧�Ă�t���O
	bool m_AnimEnd;

	//�_���[�W�̃A�j���[�V�������I�������痧�Ă�t���O
	bool m_DamageAnimEnd;

private:
	//�p�����[�^�X�V�O�̃p�����[�^���
	enParam m_BeforeParam;

	//�c��X�^�~�i�ɂ��␳
	float m_Correction;

	//�g���[�j���O�����s�����ۂɗ��Ă�t���O
	bool m_Failure;

};