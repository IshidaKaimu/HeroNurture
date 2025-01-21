#pragma once
#include "SkinMeshObject\Hero\CHeroBase.h"
#include "Singleton\CSingleton.h"
#include <memory>
class CHeroManager
	: public CHeroBase
	, public CSingleton<CHeroManager>
{

public:
	//�g���[�j���O���X�g
	enum enTraningList : char
	{
		PowerTraining,
		MagicTraining,
		SpeedTraining,
		HpTraining,
		Rest,
		Max_T,
	};

public:
	//�t�����h�錾�ŃA�N�Z�X����^����.
	friend class CSingleton<CHeroManager>;
	~CHeroManager();

public:
	// =======================
	// �e�V�[�����Ƃ̏�����
	// =======================
	//��Ɏg�p���鏉����
	void Initialize() override;
	//�o�g���V�[���Ŏg�p���鏉����
	void BattleInitialize() override;
	//�ŗL�U���A�j���[�V�������̏�����
	virtual void UniqueInit() override;

	//�f�[�^�ǂݍ��݊֐�
	void LoadMeshData() override;

	//�p�����[�^���̓ǂݍ���
	void LoadParamData(const json& jsondata) override;

	//�X�V�֐�
	void Update() override;

	//�`��֐�
	void Draw() override;

	//�f�o�b�O�֐�
	void Debug() override;

	//�쐬����q�[���[�̐ݒ�
	void CreateHero(enHeroList list);

	//�e�q�[���[�N���X�̍쐬
	static std::unique_ptr<CHeroBase>Create(enHeroList list);

	// =======================
	// �e�V�[�����Ƃ̃A�j���[�V����
	// =======================
    //�q�[���[�I���V�[�� 
	void NatureHeroSelectAnimation() override;
	//�琬�V�[��
	void NatureAnimation(int no) override;

	// =======================
	// �e�p�����[�^�㏸�֐�
	// =======================
	//�ؗ�
	void PowerUp(float stamina) { m_pHero->PowerUp(stamina); }
	//����
	void MagicUp(float stamina) { m_pHero->MagicUp(stamina); }
	//�f����
	void SpeedUp(float stamina) { m_pHero->SpeedUp(stamina); }
	//�̗�
	void HpUp(float stamina)    { m_pHero->HpUp(stamina); }

	// =======================
	// �e�q�[���[�̍U���֐�
	// =======================
	//�U��1(�ؗ͂ɂ��U��)
	float PowerAttack()  override {  return m_pHero->PowerAttack(); }
	//�U��2(���͂ɂ��U��)
	float MagicAttack()  override {  return m_pHero->MagicAttack(); }
	//�ŗL�U��(�e�q�[���[�̈�ԍ����X�e�[�^�X�𔽉f�����U��)
	float UniqueAttack() override {  return m_pHero->UniqueAttack(); }

	// =======================
	// �e�o�g���t�F�[�Y�ł̃A�j���[�V����
	// =======================
	// �s���I���t�F�[�Y���̃A�j���[�V����
	void MoveSelectAnim()  override { m_pHero->MoveSelectAnim(); }
	//----�U���t�F�[�Y----
	//�U��1���̃A�j���[�V����
	void PowerAttackAnim(float vector) override { m_pHero->PowerAttackAnim(vector); }
	//�U��2���̃A�j���[�V����
	void MagicAttackAnim(float vector) override { m_pHero->MagicAttackAnim(vector); }
	//�ŗL�U�����̃A�j���[�V����
	void UniqueAttackAnim()override { m_pHero->UniqueAttackAnim(); }
	//�_���[�W���󂯂��Ƃ��̃A�j���[�V����
	void DamageAnim(float vector) override { m_pHero->DamageAnim(vector); }

	// =======================
	// �X�^�~�i�Q�[�W�֘A�֐�
	// =======================	
	//�X�^�~�i�̏�����
	void InitStamina() { m_Stamina = MAX_STAMINA; }
	//�X�^�~�i�̌���
	void ReduceStamina();
	//�X�^�~�i�̉�
	void StaminaRecovery();

	//�_���[�W�֐�
	void Damage(float damage) { m_pHero->Damage(damage); }

	//���S�֐�
	bool Death() { return m_pHero->GetHp() <= 0.0f; }

	//�o�g�����̈ʒu�̏�����
	void BattleInitPos() { m_pHero->SetPosition(BATTLEINIT_POS); }

	//�I�����Ă���q�[���[�𕶎���ŕԂ��֐�
	std::string GetHeroName();

	// =======================
	// �Q�b�^�[�E�Z�b�^�[�֐�
	// =======================
	//�I�������q�[���[
	void SelectHero(enHeroList list) { m_SelectHero = list; }
	enHeroList GetSelectHero() { return m_SelectHero; }
	//�o�g���Ɏg�p����q�[���[�̖��O
	std::string GetBattleHeroName() { return m_pHero->GetBattleHeroName(); }
	void SetBattleHeroName(std::string heroname) { return m_pHero->SetBattleHeroName(heroname); }
	//���݂̃p�����[�^
	enParam GetParam() { return m_pHero->GetParam(); }	
	//�o�g���Ɏg�p����p�����[�^���
	enParam GetBattleParamData() { return m_pHero->GetBattleParamData(); }
	void SetBattleParamData(const json& jsondata) { m_pHero->SetBattleParamData(jsondata); }
	//�L�������Ƃ̓K����
	enAppropriate GetApp() { return m_pHero->GetApp(); }
	//�X�V�O�̃p�����[�^
	enParam GetBeforeParam() { return m_pHero->GetBeforeParam(); }
	void SetBeforeParam(enParam before) { m_pHero->SetBeforeParam(before); }
	//�X�^�~�i
	float GetStamina() { return m_Stamina; }
	void  SetStamina(float stamina) { m_Stamina = stamina; }
	//�ω��O�̃X�^�~�i
	float GetBeforeStamina() { return m_BeforeStamina; }
	void SetBeforeStamina(float before) { m_BeforeStamina = before; }
	//�ω���̃X�^�~�i
	float GetAfterStamina() { return m_AfterStamina; }
	//�g���[�j���O
	enTraningList GetTraining() { return m_Traning; }
	void SetTraning(enTraningList traning) { m_Traning = traning; }
	//�g���[�j���O�Ɏ��s�������̃t���O
	bool GetFailure() { return m_pHero->GetFailure(); }
	//�o�g�����̗�
	float GetHp() { return m_pHero->GetHp(); }
	void SetHp( float hp ) { m_pHero->SetHp(hp); }
	//�ŗL�U���Q�[�W
	int GetUniqueGage() { return m_pHero->GetUniqueGage(); }
	//�_���[�W�t���O
	bool GetDamageFlag() { return m_pHero->GetDamageFlag(); }
	//�A�j���[�V�����I���t���O
	bool GetAnimEndFlag() { return m_pHero->GetAnimEndFlag(); }
	void SetAnimEndFlag(bool animend) { m_pHero->SetAnimEndFlag(animend); }
	//�_���[�W�A�j���[�V�����I���t���O
	bool GetDamageAnimEndFlag() { return m_pHero->GetDamageAnimEndFlag(); }
	void SetDamageAnimEndFlag(bool damageanimend) { m_pHero->SetDamageAnimEndFlag(damageanimend); }

private:
	//������A�N�Z�X���邱�Ƃ��Ȃ��悤��
	CHeroManager();

protected:
	//�q�[���[�x�[�X�N���X
	std::unique_ptr<CHeroBase> m_pHero;

	//�I������Ă���q�[���[
	enHeroList m_SelectHero;

	//�g���[�j���O���X�g
	enTraningList m_Traning;

	//�q�[���[��
	std::string m_HeroName;

	//�X�^�~�i
    //�ǂ̃q�[���[�ł�����
	float m_Stamina;

	//�ω��O�̃X�^�~�i
	float m_BeforeStamina;
	//�ω���̃X�^�~�i
	float m_AfterStamina;
};

