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
	// �g���[�j���O���Ƃ̃A�j���[�V�����֐�
	// =======================		
	//�ؗ�
	void PowerTraningAnimation() { m_pHero->PowerTraningAnimation(); }
	//����
	void MagicTraningAnimation() { m_pHero->MagicTraningAnimation(); }
	//�̗�
	void SpeedTraningAnimation() { m_pHero->SpeedTraningAnimation(); }
	//Hp
	void HpTraningAnimation() { m_pHero->HpTraningAnimation(); }


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
	void HpUp(float stamina) { m_pHero->HpUp(stamina); }

	// =======================
	// �X�^�~�i�Q�[�W�֘A�֐�
	// =======================	
	//�X�^�~�i�̏�����
	void InitStamina() { m_Stamina = MAX_STAMINA; }
	//�X�^�~�i�̌���
	void ReduceStamina();
	//�X�^�~�i�̉�
	void StaminaRecovery();

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

