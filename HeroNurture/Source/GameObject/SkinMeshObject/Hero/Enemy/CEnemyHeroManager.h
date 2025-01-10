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
private:
	CEnemyHeroManager();

public:
	// =======================
	// �Q�b�^�[�E�Z�b�^�[�֐�
	// =======================	
	//�o�g���Ɏg�p����p�����[�^���
	void SetBattleParamData(const json& jsondata) { m_pEnemyHero->SetBattleParamData(jsondata); };
	//�G�q�[���[
	enHeroList GetSelectEnemyHero() { return m_SelectEnemyHero; }
	//�G�q�[���[�̖��O�̕�����
	std::string GetEnemyHeroName();

private:
	//�q�[���[���N���X
	std::unique_ptr<CHeroBase> m_pEnemyHero;
	//�G�q�[���[
	enHeroList m_SelectEnemyHero;
	//�G�q�[���[�̖��O�̕�����
	std::string m_EnemyHeroName;

};
