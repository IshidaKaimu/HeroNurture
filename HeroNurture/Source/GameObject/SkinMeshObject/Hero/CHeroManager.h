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

	//�A�j���[�V�����֐�
	void Animation();

	//�e�q�[���[�N���X�̍\�z
	static std::unique_ptr<CHeroBase>Create(enHeroList list);

	//----�p�����[�^�֘A�֐�----
	//�p�����[�^�㏸
	//�ؗ�
	void PowerUp() { m_Hero->PowerUp(); }
	//����
	void MagicUp() { m_Hero->MagicUp(); }
	//�f����								   
	void SpeedUp() { m_Hero->SpeedUp(); }
	//�̗�
	void HpUp() { m_Hero->HpUp(); }

	//----�Q�b�^�[�E�Z�b�^�[----
	//�q�[���[�ݒ�֐�
	void SetHero(enHeroList list);
	//�q�[���[�I���֐�
	void SelectHero(enHeroList list) { m_HeroList = list; }
	//�I�������q�[���[�擾
	enHeroList GetSelectHero() { return m_HeroList; }
	//���݂̃p�����[�^�擾
	enParam GetParam() { return m_Hero->GetParam(); }	
	//�L�������Ƃ̓K�����擾
	enAppropriate GetApp() { return m_Hero->GetApp(); }
	//�X�V�O�̃p�����[�^
	enParam GetBeforeParam() { return m_Hero->GetBeforeParam(); }
	void SetBeforeParam(enParam before) { m_Hero->SetBeforeParam(before); }
	//�p�����[�^�㏸�ʎ擾
	//�ؗ�
	float GetPowerUpValue() { return m_Hero->GetPowerUpValue(); }
	//����
	float GetMagicValue() { return m_Hero->GetMagicUpValue(); }
	//�f����
	float GetSpeedUpValue() { return m_Hero->GetSpeedUpValue(); }
	//�̗�
	float GetHpUpValue() { return m_Hero->GetHpUpValue(); }
	//�g���[�j���O
	enTraningList GetTraining() { return m_Traning; }
	void SetTraning(enTraningList traning) { m_Traning = traning; }


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

};

