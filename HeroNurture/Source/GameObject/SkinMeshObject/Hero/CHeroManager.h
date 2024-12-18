#pragma once
#include "SkinMeshObject\Hero\CHeroBase.h"
#include "Singleton\CSingleton.h"
#include <memory>
class CHeroManager
	: public CHeroBase
	, public CSingleton<CHeroManager>
{
public:
	//�q�[���[���X�g�񋓌^
	enum enHeroList :char
	{
		Yui,
		Kaito,
        Max,
	};

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

	//�������֐�
	void Initialize() override;

	//�f�[�^�ǂݍ��݊֐�
	void LoadMeshData() override;

	//�p�����[�^���̓ǂݍ���
	void LoadParamData(const json& jsondata) override;

	//�X�V�֐�
	void Update() override;

	//�`��֐�
	void Draw() override;

	// =======================
	// �e�V�[�����Ƃ̃A�j���[�V����
	// =======================
    //�q�[���[�I���V�[�� 
	void SelectAnimation() override;
	//�琬�V�[��
	void NatureAnimation(int no) override;

	//�e�q�[���[�N���X�̍\�z
	static std::unique_ptr<CHeroBase>Create(enHeroList list);

	// =======================
	// �e�p�����[�^�㏸�֐�
	// =======================
	//�ؗ�
	void PowerUp(float stamina) { m_Hero->PowerUp(stamina); }
	//����
	void MagicUp(float stamina) { m_Hero->MagicUp(stamina); }
	//�f����
	void SpeedUp(float stamina) { m_Hero->SpeedUp(stamina); }
	//�̗�
	void HpUp(float stamina) { m_Hero->HpUp(stamina); }

	// =======================
	// �X�^�~�i�Q�[�W�֘A�֐�
	// =======================	
	//�X�^�~�i�̏�����
	void InitStamina() { m_Stamina = MAX_STAMINA; }
	//�X�^�~�i�̌���
	void ReduceStamina();
	//�X�^�~�i�̉�
	void StaminaRecovery();

	// =======================
	// �Q�b�^�[�E�Z�b�^�[�֐�
	// =======================
	//�q�[���[�ݒ�֐�
	void SetHero(enHeroList list);
	//�q�[���[�I���֐�
	void SelectHero(enHeroList list) { m_HeroList = list; }
	//�I�������q�[���[
	enHeroList GetSelectHero() { return m_HeroList; }
	//���݂̃p�����[�^
	enParam GetParam() { return m_Hero->GetParam(); }	
	//�L�������Ƃ̓K����
	enAppropriate GetApp() { return m_Hero->GetApp(); }
	//�X�V�O�̃p�����[�^
	enParam GetBeforeParam() { return m_Hero->GetBeforeParam(); }
	void SetBeforeParam(enParam before) { m_Hero->SetBeforeParam(before); }
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
	bool GetFailure() { return m_Hero->GetFailure(); }

private:
	//������A�N�Z�X���邱�Ƃ��Ȃ��悤��
	CHeroManager();

private:
	//�q�[���[�x�[�X�N���X
	std::unique_ptr<CHeroBase> m_Hero;

	//�q�[���[���X�g
	enHeroList m_HeroList;

	//�g���[�j���O���X�g
	enTraningList m_Traning;

	//�X�^�~�i
    //�ǂ̃q�[���[�ł�����
	float m_Stamina;

	//�ω��O�̃X�^�~�i
	float m_BeforeStamina;
	//�ω���̃X�^�~�i
	float m_AfterStamina;


};

