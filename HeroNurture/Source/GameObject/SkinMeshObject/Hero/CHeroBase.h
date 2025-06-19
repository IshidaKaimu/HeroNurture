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
constexpr float INCREASE_VALUE		     = 20.0f; //��{�㏸�l
constexpr float MIN_FAILURE			     = 0.0f;  //���s���̍Œ�
constexpr float MAX_FAILURE			     = 99.0f; //���s���̍ō�
constexpr float GREAT_SUCCESS_RATE       = 0.2f;  //�听���̊m��	
constexpr float GREAT_SUCCESS_MULTIPLIER = 2.0f;  //�听���̔{��	
//------------------------

//----�X�^�~�i�Q�[�W�֘A----
constexpr float MAX_STAMINA	     = 100.0f; //�ő�l
constexpr float REDUSE_STAMINA   = 25.0f;  //������
constexpr float RECOVERY_STAMINA = 25.0f;  //�񕜗�
//--------------------------

//----�o�g���V�[��----
const D3DXVECTOR3 BATTLEINIT_POS = { -5.5f,0.0f,0.0f }; //�������W(����)
const D3DXVECTOR3 ENEMYINIT_POS  = { 2.5f,0.0f,0.0f };	//�������W(�G)
const D3DXVECTOR3 BATTLE_ROTATE  = { 0.0f,D3DXToRadian(-90.0f),0.0f };//��](����)
const D3DXVECTOR3 ENEMY_ROTATE   = { 0.0f,D3DXToRadian(90.0f),0.0f }; //��](�G)
//--------------------

//=====================================
// �q�[���[���N���X
// �����:�Γc�D��
//=====================================
class CHeroBase
	: public CSkinMeshObject
{
public :

	//===============
	// �񋓌^
	//===============

	//�q�[���[�����X�g
	enum enHeroList :char
	{
		Yui,
		Kaito,
		Max,
	};
	
	//===============


	//===============
	// �\����
	//===============

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
	
	//===============


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
	virtual void EnemyInitialize() {};
	//�o�g���J�n���o��V�[���ł̏�����
	virtual void AppearanceInitialize() {};

	// =======================


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
	// =======================


public:
	
	//�g���[�j���O�̎��s����Ԃ��֐�
	float FailureRate(float stamina);

	// =======================
	// �V�[�����Ƃ̃A�j���[�V�����֐�
	// =======================		
	//�琬�q�[���[�I���V�[��
	virtual void NurtureHeroSelectAnimation() {};
	//�o�g���q�[���[�I���V�[��
	virtual void BattleHeroSelectAnimation() {};
	//�o�g���J�n���o��V�[��
	virtual void AppearanceAnimation() {};
	//�琬�V�[��
	virtual void NurtureAnimation(int no) {};
	// =======================
	
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


	//�_���[�W�֐�
	void Damage(float damage);

	// =======================
	// �Q�b�^�[�E�Z�b�^�[�֐�
	// =======================
	// ���W�̎擾
	D3DXVECTOR3 GetPosition() { return m_vPosition; }
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
	bool GetFailureFlag() { return m_Failure; }
	void SetFailureFlag(bool failure) { m_Failure = failure; }
	//�g���[�j���O�听���t���O
	bool GetGreatSuccessFlag() { return m_GreatSuccess; }
	//�o�g���Ɏg�p����p�����[�^���̐ݒ�
	void SetBattleParam(const json& jsondata);
	//�o�g������HP
	float GetHp() { return m_Hp; }
	void SetHp(float hp) { m_Hp = hp; }
	//�_���[�W�t���O
	bool GetDamageFlag() { return m_Damage; }
	void SetDamageFlag(bool damage) { m_Damage = damage; }
	//�U���A�j���[�V�����I���t���O
	bool GetAttackAnimEndFlag()             { return m_AttackAnimEnd; }
	void SetAttackAnimEndFlag(bool animend) { m_AttackAnimEnd = animend; }
	//�_���[�W�A�j���[�V�����I���t���O
	bool GetDamageAnimEndFlag() { return m_DamageAnimEnd; }
	void SetDamageAnimEndFlag(bool damageanimend) { m_DamageAnimEnd = damageanimend; }
	//�o��A�j���[�V�����I���t���O
	bool GetAppealanceAnimEndFlag() { return m_AppealanceAnimEnd; }
	// =======================

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
	//========================

private:
	//�c��X�^�~�i�ʂɂ��␳�֐�
	void CorrectionByStamina(float stamina);
	//�g���[�j���O���ʊ֐�
	void TraningResult(float stamina, float app, float& param);

protected:
	//�琬���̃p�����[�^
	enParam m_Param;
	//�o�g���̃p�����[�^
	enParam m_BattleParam;

	//�o�g������q�[���[�̖��O
	std::string m_BattleHeroName;

	//�q�[���[�̓K�����\����
	enAppropriate m_App;

	//json�N���X
	std::unique_ptr<CJson> m_pJson;

	//���[�U�[�l�[��
	std::string m_UserName;

	//���݂̗̑�
	float m_Hp;

	//�A�j���[�V�����p�J�E���g
	int m_AnimCnt;
	//�G�t�F�N�g�p�J�E���g
	int m_EffCnt;

	//�C�x���g�V�[���p�̕ϓ�������ϐ�
	float m_MoveX; //X���W
	float m_MoveY; //Y���W
	float m_MoveZ; //Z���W

	//----�t���O----
	//�_���[�W���󂯂��Ƃ����Ă�
	bool m_Damage;
	//�U���A�j���[�V�������I�������痧�Ă�
	bool m_AttackAnimEnd;
	//�_���[�W�̃A�j���[�V�������I�������痧�Ă�
	bool m_DamageAnimEnd;
	//�o��A�j���[�V�������I�������痧�Ă�
	bool m_AppealanceAnimEnd;
	//--------------

private:
	//�p�����[�^�X�V�O�̃p�����[�^���
	enParam m_BeforeParam;

	//�c��X�^�~�i�ɂ��␳
	float m_Correction;

	//----�t���O----
	//�g���[�j���O�����s�����痧�Ă�
	bool m_Failure;

	//�g���[�j���O���听�������痧�Ă�
	bool m_GreatSuccess;

	//--------------

};