#pragma once
#include "SkinMeshObject\Hero\CHeroBase.h"
#include "SkinMeshObject\Hero\CHeroManager.h"
#include "Singleton\CSingleton.h"

class CEnemyHeroManager
	: public CHeroBase
	, public CSingleton<CEnemyHeroManager>
{ 
private:
	//�t�����h�錾�ŃA�N�Z�X����^����.
	friend class CSingleton<CEnemyHeroManager>;
	~CEnemyHeroManager();

public:
	//�������֐�
	void Initialize()   { m_pEnemyHero->Initialize(); }

	//�f�[�^�ǂݍ��݊֐�
	void LoadMeshData() { m_pEnemyHero->LoadMeshData(); };

	//�X�V�֐�
	void Update()		{ m_pEnemyHero->Update(); };

	//�`��֐�
	void Draw()			{ m_pEnemyHero->Draw(); };

	//�f�o�b�O�֐�
	void Debug()		{ m_pEnemyHero->Debug(); };

	//�쐬����q�[���[�N���X�̐ݒ�
	void CreateEnemyHero(enHeroList list);

	//�e�q�[���[�N���X�̍쐬
	static std::unique_ptr<CHeroBase>Create(enHeroList list);

	//���S�֐�
	bool Death() { return m_pEnemyHero->GetHp() <= 0.0f; }

	//�_���[�W�֐�
	void Damage(float damage) { m_pEnemyHero->Damage(damage); }

private:
	CEnemyHeroManager();

public:
	// =======================
	// �e�q�[���[�̍U���֐�
	// =======================
	//�U��1(�ؗ͂ɂ��U��)
	float PowerAttack()  override {  return m_pEnemyHero->PowerAttack(); }
	//�U��2(���͂ɂ��U��)
	float MagicAttack()  override {  return m_pEnemyHero->MagicAttack(); }
	//�ŗL�U��(�e�q�[���[�̈�ԍ����X�e�[�^�X�𔽉f�����U��)
	float UniqueAttack() override {  return m_pEnemyHero->UniqueAttack(); }

	//�o�g���J�n���o��V�[���̃A�j���[�V����
	void AppearanceAnimation() { m_pEnemyHero->AppearanceAnimation(); };

	// =======================
	// �e�o�g���t�F�[�Y�ł̃A�j���[�V����
	// =======================
	// �s���I�𒆂̃A�j���[�V����
	void MoveSelectAnim()  override { m_pEnemyHero->MoveSelectAnim(); }
	//----�U���t�F�[�Y----
	//�U��1���̃A�j���[�V����
	void PowerAttackAnim(float vector) override { m_pEnemyHero->PowerAttackAnim(vector); }
	//�U��2���̃A�j���[�V����
	void MagicAttackAnim(float vector) override { m_pEnemyHero->MagicAttackAnim(vector); }
	//�ŗL�U�����̃A�j���[�V����
	void UniqueAttackAnim()override { m_pEnemyHero->UniqueAttackAnim(); }
	//�_���[�W���󂯂�Ƃ��̃A�j���[�V����
	void DamageAnim(float vector)override { m_pEnemyHero->DamageAnim(vector); }

	//�o�g�����̈ʒu�̏�����
	void BattleInitPos() { m_pEnemyHero->SetPosition(ENEMYINIT_POS); }

	// =======================
	// �Q�b�^�[�E�Z�b�^�[�֐�
	// =======================	
	//�o�g���Ɏg�p����p�����[�^���
	void SetBattleParamData(const json& jsondata) { m_pEnemyHero->SetBattleParamData(jsondata); };
	enParam GetBattleParamData() { return m_pEnemyHero->GetBattleParamData(); };
	//�G�q�[���[
	enHeroList GetSelectEnemyHero() { return m_SelectEnemyHero; }
	//�G�q�[���[�̖��O�̕�����
	std::string GetEnemyHeroName();
	//�o�g�����̗�
	float GetHp() { return m_pEnemyHero->GetHp(); }
	void SetHp(float hp) { m_pEnemyHero->SetHp(hp); }
	//�_���[�W�t���O
	bool GetDamageFlag() { return m_pEnemyHero->GetDamageFlag(); }
	//�A�j���[�V�����I���t���O
	bool GetAnimEndFlag() { return m_pEnemyHero->GetAnimEndFlag(); }
	void SetAnimEndFlag(bool animend) { m_pEnemyHero->SetAnimEndFlag(animend); }
	//�_���[�W�A�j���[�V�����I���t���O
	bool GetDamageAnimEndFlag() { return m_pEnemyHero->GetDamageAnimEndFlag(); }
	void SetDamageAnimEndFlag(bool damageanimend) { m_pEnemyHero->SetDamageAnimEndFlag(damageanimend); }


private:
	//�q�[���[���N���X
	std::unique_ptr<CHeroBase> m_pEnemyHero;
	//�G�q�[���[
	enHeroList m_SelectEnemyHero;
	//�G�q�[���[�̖��O�̕�����
	std::string m_EnemyHeroName;

};
