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
	void LoadData() override;

	//�X�V�֐�
	void Update() override;

	//�`��֐�
	void Draw( LIGHT& light ) override;

	//�A�j���[�V�����֐�
	void Animation();

	//�e�q�[���[�N���X�̍\�z
	static std::unique_ptr<CHeroBase>Create(enHeroList list);

	//�X�e�[�^�X�㏸�֐�
	void UpStatus(float sta, float inc);


	//----�Q�b�^�[�E�Z�b�^�[----
	//�q�[���[�ݒ�֐�
	void SetHero(enHeroList list);
	//�q�[���[�I���֐�
	void SelectHero(enHeroList list) { m_HeroList = list; }
	//�I�������q�[���[�擾
	enHeroList GetSelectHero() { return m_HeroList; }

private:
	CHeroManager();

private:
	//�q�[���[�x�[�X�N���X
	std::unique_ptr<CHeroBase> m_Hero;

	//�q�[���[���X�g
	enHeroList m_HeroList;

};

