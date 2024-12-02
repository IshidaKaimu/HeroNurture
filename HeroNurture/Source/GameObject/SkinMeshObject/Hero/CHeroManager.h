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

public:
	//�t�����h�錾�ŃA�N�Z�X����^����.
	friend class CSingleton<CHeroManager>;
	~CHeroManager();

	//�������֐�
	void Initialize() override;

	//�f�[�^�ǂݍ��݊֐�
	void LoadData(const json& jsondata) override;

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
	void PowerUp(int power) { m_Hero->PowerUp(power); }
	//����
	void MagicUp(int magic) { m_Hero->MagicUp(magic); }
	//�f����
	void SpeedUp(int speed) { m_Hero->SpeedUp(speed); }
	//�̗�
	void HpUp(int hp) { m_Hero->HpUp(hp); }

	//----�Q�b�^�[�E�Z�b�^�[----
	//�q�[���[�ݒ�֐�
	void SetHero(enHeroList list);
	//�q�[���[�I���֐�
	void SelectHero(enHeroList list) { m_HeroList = list; }
	//�I�������q�[���[�擾
	enHeroList GetSelectHero() { return m_HeroList; }
	//���݂̃p�����[�^�擾
	enStatus GetParam() { return m_Hero->GetParam(); }	
	//�p�����[�^�㏸�ʎ擾
	//�ؗ�
	int GetPowerUpValue() { return m_Hero->GetPowerUpValue(); }
	//����
	int GetMagicValue() { return m_Hero->GetMagicUpValue(); }
	//�f����
	int GetSpeedUpValue() { return m_Hero->GetSpeedUpValue(); }
	//�̗�
	int GetHpUpValue() { return m_Hero->GetHpUpValue(); }

private:
	//������A�N�Z�X���邱�Ƃ��Ȃ��悤��
	CHeroManager();

private:
	//�q�[���[�x�[�X�N���X
	std::unique_ptr<CHeroBase> m_Hero;

	//�q�[���[���X�g
	enHeroList m_HeroList;

};

