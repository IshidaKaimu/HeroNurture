#pragma once
#include "SkinMeshObject\Hero\CHeroBase.h"
#include "Singleton\CSingleton.h"
#include <memory>

//=====================================
// �q�[���[�}�l�[�W���[�N���X
// �����:�Γc�D��
//=====================================
class CHeroManager
	: public CHeroBase
	, public CSingleton<CHeroManager>
{

public:

	// =======================
	// �񋓌^
	// =======================

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

	// =======================

public:
	//�t�����h�錾�ŃA�N�Z�X����^����.
	friend class CSingleton<CHeroManager>;
	~CHeroManager();

public:
	// =======================
	// �e�V�[�����Ƃ̏�����
	// =======================
	
	//��Ɏg�p���鏉����
	void Initialize()					{ m_pHero->Initialize(); }
	
	//�o�g���V�[���Ŏg�p���鏉����
	void BattleInitialize()				{ m_pHero->BattleInitialize(); }
	
	//�o�g���J�n���o��V�[���ł̏�����
	void AppearanceInitialize()			{ m_pHero->AppearanceInitialize(); };
	
	//=========================

	//�f�[�^�ǂݍ��݊֐�
	void LoadMeshData()					{ m_pHero->LoadMeshData(); }

	//�p�����[�^���̓ǂݍ���
	void LoadParamData(const json& jsondata) { m_pHero->LoadParamData(jsondata); }

	//�X�V�֐�
	void Update() { m_pHero->Update(); }

	//�`��֐�
	void Draw()   { m_pHero->Draw(); }

	//�f�o�b�O�֐�
	void Debug()  { m_pHero->Debug(); }

	//�쐬����q�[���[�̐ݒ�
	void CreateHero(enHeroList list);

	//�e�q�[���[�N���X�̍쐬
	static std::unique_ptr<CHeroBase>Create(enHeroList list);

	// =======================

	// =======================
	// �e�V�[�����Ƃ̃A�j���[�V����
	// =======================

	//�q�[���[�I���V�[�� 
	void NurtureHeroSelectAnimation() { m_pHero->NurtureHeroSelectAnimation(); } 
	//�琬�V�[��
	void NurtureAnimation(int no)	  { m_pHero->NurtureAnimation(no); }
	//�o�g���J�n���o��V�[��
	void AppearanceAnimation()		  { m_pHero->AppearanceAnimation(); };

	// =======================

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

	// =======================
	// �e�o�g���t�F�[�Y�ł̃A�j���[�V����
	// =======================
	
	// �s���I���t�F�[�Y���̃A�j���[�V����
	void MoveSelectAnim()  override				{ m_pHero->MoveSelectAnim(); }
	//----�U���t�F�[�Y----
	//�U��1���̃A�j���[�V����
	void PowerAttackAnim(float vector) override { m_pHero->PowerAttackAnim(vector); }
	//�U��2���̃A�j���[�V����
	void MagicAttackAnim(float vector) override { m_pHero->MagicAttackAnim(vector); }
	//�ŗL�U�����̃A�j���[�V����
	void UniqueAttackAnim()override			    { m_pHero->UniqueAttackAnim(); }
	//�_���[�W���󂯂��Ƃ��̃A�j���[�V����
	void DamageAnim(float vector) override		{ m_pHero->DamageAnim(vector); }

	//========================


	// =======================
	// �X�^�~�i�Q�[�W�֘A�֐�
	// =======================	
	
	//�X�^�~�i�̏�����
	void InitStamina();
	//�X�^�~�i�̌���
	void ReduceStamina();
	//�X�^�~�i�̉�
	void StaminaRecovery();

	//========================


	//�_���[�W�֐�
	void Damage(float damage) { m_pHero->Damage(damage); }
	//���S�֐�
	bool Death();

	//�o�g�����̈ʒu�̏�����
	void BattleInitPos();

	//�I�����Ă���q�[���[�𕶎���ŕԂ��֐�
	std::string GetSelectHeroName();

	//========================

	// =======================
	// �Q�b�^�[�E�Z�b�^�[�֐�
	// =======================
	
	// ���W�̎擾
	D3DXVECTOR3 GetPosition() { return m_pHero->GetPosition(); }	
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
	//���s��
	float GettFailureRate(float stamina) { return m_pHero->FailureRate(stamina); }
	//�g���[�j���O�Ɏ��s�������̃t���O
	bool GetFailureFlag() { return m_pHero->GetFailureFlag(); }
	//�g���[�j���O�ɑ听���������̃t���O
	bool GetGreatSuccessFlag() { return m_pHero->GetGreatSuccessFlag(); }
	//�o�g�����̗�
	float GetHp() { return m_pHero->GetHp(); }
	void SetHp( float hp ) { m_pHero->SetHp(hp); }
	//�_���[�W�t���O
	bool GetDamageFlag() { return m_pHero->GetDamageFlag(); }
	//�A�j���[�V�����I���t���O
	bool GetAttackAnimEndFlag() { return m_pHero->GetAttackAnimEndFlag(); }
	void SetAttackAnimEndFlag(bool animend) { m_pHero->SetAttackAnimEndFlag(animend); }
	//�_���[�W�A�j���[�V�����I���t���O
	bool GetDamageAnimEndFlag() { return m_pHero->GetDamageAnimEndFlag(); }
	void SetDamageAnimEndFlag(bool damageanimend) { m_pHero->SetDamageAnimEndFlag(damageanimend); }
	//�o��A�j���[�V�����I���t���O
	bool GetAppealanceAnimEndFlag() { return m_pHero->GetAppealanceAnimEndFlag(); }

	// =======================


private:
	//������A�N�Z�X���邱�Ƃ��Ȃ��悤��
	CHeroManager();

protected:
	//�q�[���[�x�[�X�N���X
	std::unique_ptr<CHeroBase> m_pHero;

	//�I������Ă���q�[���[
	enHeroList m_SelectHero;
	//�I������Ă���o�g���Ɏg�p����q�[���[
	enHeroList m_SelectBattleHero;

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

