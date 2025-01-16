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
	void Initialize() override;

	//�f�[�^�ǂݍ��݊֐�
	void LoadMeshData() override;

	//�X�V�֐�
	void Update() override;

	//�`��֐�
	void Draw() override;

	//�f�o�b�O�֐�
	void Debug() override;

	//�쐬����q�[���[�N���X�̐ݒ�
	void CreateEnemyHero(enHeroList list);

	//�e�q�[���[�N���X�̍쐬
	static std::unique_ptr<CHeroBase>Create(enHeroList list);

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

	// =======================
	// �e�o�g���t�F�[�Y�ł̃A�j���[�V����
	// =======================
	// �s���I�𒆂̃A�j���[�V����
	void MoveSelectAnim()  override { m_pEnemyHero->MoveSelectAnim(); }
	//----�U���t�F�[�Y----
	//�U��1���̃A�j���[�V����
	void PowerAttackAnim() override { m_pEnemyHero->PowerAttackAnim(); }
	//�U��2���̃A�j���[�V����
	void MagicAttackAnim() override { m_pEnemyHero->MagicAttackAnim(); }
	//�ŗL�U�����̃A�j���[�V����
	void UniqueAttackAnim()override { m_pEnemyHero->UniqueAttackAnim(); }


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
	//�ŗL�U���Q�[�W
	int GetUniqueGage() { return m_pEnemyHero->GetUniqueGage(); }

private:
	//�q�[���[���N���X
	std::unique_ptr<CHeroBase> m_pEnemyHero;
	//�G�q�[���[
	enHeroList m_SelectEnemyHero;
	//�G�q�[���[�̖��O�̕�����
	std::string m_EnemyHeroName;

};
